/* This is a small speedometer demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "tx_api.h"
#include "gx_api.h"

#include "common_hardware_code.h"

#include "speedometer_resources.h"
#include "speedometer_specifications.h"


GX_WINDOW_ROOT      *root;

TX_THREAD           demo_thread;
UCHAR               demo_thread_stack[4096];
TX_THREAD           touch_thread;
ULONG               touch_thread_stack[1024];

/* define memory pool size used to do bitmap rotation and canvas. */
#define CANVAS_SIZE       (VGA_LCD_X_RESOLUTION * VGA_LCD_Y_RESOLUTION)
#define GUIX_POOL_SIZE    (VGA_LCD_X_RESOLUTION * VGA_LCD_Y_RESOLUTION * sizeof(GX_COLOR) / 2)

/* Memory for the canvas. */
__attribute__((section(".SD_RAM"))) GX_COLOR default_canvas_memory[CANVAS_SIZE];
__attribute__((section(".SD_RAM"))) UCHAR guix_pool_memory[GUIX_POOL_SIZE];

/* values used for tachometer animation */
#define NUM_NEEDLE_POSITIONS     5
#define NEEDLE_ANIMATION_FRAMES 30
#define GAUGE_TIMER_TICS         1

int  rotation_increment = 1;
int  needle_position_index = 0;
int  needle_stop_pos[NUM_NEEDLE_POSITIONS + 1] = {-114, -90, 52, -27, 52, -114};

/* a thread-safe byte pool used for temporary storage of rotated bitmap */
TX_BYTE_POOL guix_pool;

/* Define prototypes.   */

VOID  start_guix(VOID);
UINT stm32f746_graphics_driver_setup_24xrgb(GX_DISPLAY *graphic);
VOID demo_thread_entry(ULONG thread_input);
VOID touch_thread_entry(ULONG thread_input);

int main()
{
    /* Setup the hardware. */
    hardware_setup();

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}


/*******************************************************************************/
VOID *memory_alloc(ULONG size)
{
    VOID *memptr;

    if (tx_byte_allocate(&guix_pool, &memptr, size, TX_NO_WAIT) == TX_SUCCESS)
    {
        return memptr;
    }
    return GX_NULL;
}

/*******************************************************************************/
VOID memory_free(VOID *memptr)
{
    tx_byte_release(memptr);
}

VOID tx_application_define(void *first_unused_memory)
{
    /* Create touch thread.  */
    tx_thread_create(&touch_thread, "GUIX Touch Thread", touch_thread_entry, 0,  
                     touch_thread_stack, sizeof(touch_thread_stack), 
                     GX_SYSTEM_THREAD_PRIORITY - 1,
                     GX_SYSTEM_THREAD_PRIORITY - 1, TX_NO_TIME_SLICE, TX_AUTO_START);

    /* Create demo thread.  */
    tx_thread_create(&demo_thread, "Demo Thread", demo_thread_entry, 0,  
                     demo_thread_stack, sizeof(demo_thread_stack), 
                     GX_SYSTEM_THREAD_PRIORITY + 1,
                     GX_SYSTEM_THREAD_PRIORITY + 1, TX_NO_TIME_SLICE, TX_AUTO_START);
}


VOID  demo_thread_entry(ULONG thread_input)
{

GX_WINDOW_ROOT *root;

    /* Initialize GUIX.  */
    gx_system_initialize();
    
    /* Setup graphics-related hardware and create the display. */
    gx_studio_display_configure(VGA_LCD, stm32f746_graphics_driver_setup_24xrgb, 
                                LANGUAGE_ENGLISH, VGA_LCD_THEME_1, &root);
    root -> gx_window_root_canvas -> gx_canvas_memory = default_canvas_memory;

    /* create a byte pool to use for rotating the needle bitmap */
    tx_byte_pool_create(&guix_pool, "guix", guix_pool_memory, GUIX_POOL_SIZE);

    /* install our memory allocation / de-allocation routines */
    gx_system_memory_allocator_set(memory_alloc, memory_free);

    /* create the gauge screen */
    gx_studio_named_widget_create("gauge_window", (GX_WIDGET *) root, GX_NULL);

    /* Show the root window to make it and patients screen visible.  */
    gx_widget_show(root);

    /* start GUIX thread */
    gx_system_start();
}


/*******************************************************************************/
VOID CalcNeedleParams()
{
GX_CIRCULAR_GAUGE *gauge = &gauge_window.gauge_window_gauge_1;

    if (needle_position_index >= NUM_NEEDLE_POSITIONS)
    {
        needle_position_index = 0;
    }

    gx_circular_gauge_angle_set(gauge, needle_stop_pos[needle_position_index]);
}

/*******************************************************************************/
UINT gauge_event_handler(GX_WINDOW *window, GX_EVENT *event_ptr)
{
    switch(event_ptr->gx_event_type)
    {
    case GX_EVENT_SHOW:
        gx_window_event_process(window, event_ptr);
        needle_position_index = 0;
        CalcNeedleParams();
        break;
        
    case GX_SIGNAL(ID_GAUGE, GX_EVENT_ANIMATION_COMPLETE):
        needle_position_index++;
        CalcNeedleParams();
        break;

    default:
        return gx_window_event_process(window, event_ptr);
    }
    return 0;
}

