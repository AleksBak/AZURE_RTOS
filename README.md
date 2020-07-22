# AZURE_RTOS
Collection of examples of working with <b>Microsoft® Azure RTOS</b> on <b>STM32F746-Discovery</b>

All projects work in the <b>STM2CubeIDE</b> environment. You can download and place all these
projects in one directory (call it for example as AZURE_RTOS) inside the workspace.

The following projects are components of <b>Microsoft® Azure RTOS</b>:
<table>
  <colgroup>
    <col span="2" style="background:Khaki"><!-- Using this construction, we set the background color for the first two columns of the table.-->
    <col style="background-color:LightCyan"><!-- Set the background color for the next (one) table column-->
  </colgroup>
  <tr>
    <th>project</th>
    <th>component</th>
    <th>short description</th>
    <th>after build gives</th>
  </tr>
  <tr>
    <td>fx</td>
    <td>FileX</td>
    <td>high-performance, FAT-compatible file system</td>
    <td>libfx.a</td>
  </tr>
  <tr>
    <td>gx</td>
    <td>GUIX</td>
    <td>provides a complete, embedded GUI</td>
    <td>libgx.a</td>
  </tr>
  <tr>
    <td>nx_secure</td>
    <td>NetX</td>
    <td>a high-performance implementation of TCP/IP protocol standards (IPv4 only)</td>
    <td>libnx_secure.a</td>
  </tr>
  <tr>
    <td>nxd</td>
    <td>NetX Duo</td>
    <td>dual IPv4/IPv6 network stack that provides a rich set of protocols, including security and cloud protocols</td>
    <td>libnxd.a</td>
  </tr>
  <tr>
    <td>ux</td>
    <td>USBX</td>
    <td>a high-performance USB host and device embedded stack</td>
    <td>libux.a</td>
  </tr>
  <tr>
    <td>tx</td>
    <td>ThreadX</td>
    <td>this advanced real-time operating system (RTOS) is designed specifically for deeply embedded applications</td>
    <td>libtx.a</td>
  </tr>
</table>

<b>stm32f7xx_library</b> project is HAL + BSP for STM32F746-Discovery board.