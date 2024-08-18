/// \file main.cc
/// \brief The entry of the program
///
///

/*!  
 \mainpage My Project's Main Page  
 
 \section intro_sec Introduction  
 This is a binary search tree visualization project made with Qt6.
 
 \section env_sec Environment
 I tested and build it on archlinux.
 build with:<br> 
`clang version 18.1.8`<br>
`cmake version 3.30.2`<br>
`ninja version 1.12.1`<br>
`qt6   version 6.7.2`<br>

\section dep_sec Local Dependency
        linux-vdso.so.1 (0x0000712cd0c14000)<br>
        libQt6Widgets.so.6 => /usr/lib/libQt6Widgets.so.6 (0x0000712cd0400000)<br>
        libQt6Gui.so.6 => /usr/lib/libQt6Gui.so.6 (0x0000712ccfa00000)<br>
        libQt6Core.so.6 => /usr/lib/libQt6Core.so.6 (0x0000712ccf400000)<br>
        libGLX.so.0 => /usr/lib/libGLX.so.0 (0x0000712cd0b8a000)<br>
        libOpenGL.so.0 => /usr/lib/libOpenGL.so.0 (0x0000712cd0b5f000)<br>
        libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x0000712ccf000000)<br>
        libm.so.6 => /usr/lib/libm.so.6 (0x0000712cd0311000)<br>
        libgcc_s.so.1 => /usr/lib/libgcc_s.so.1 (0x0000712cd0b2f000)<br>
        libc.so.6 => /usr/lib/libc.so.6 (0x0000712ccee0f000)<br>
        libEGL.so.1 => /usr/lib/libEGL.so.1 (0x0000712cd0b1d000)<br>
        libfontconfig.so.1 => /usr/lib/libfontconfig.so.1 (0x0000712cd02c1000)<br>
        libX11.so.6 => /usr/lib/libX11.so.6 (0x0000712ccf2bf000)<br>
        libglib-2.0.so.0 => /usr/lib/libglib-2.0.so.0 (0x0000712ccecc1000)<br>
        libQt6DBus.so.6 => /usr/lib/libQt6DBus.so.6 (0x0000712ccec09000)<br>
        libxkbcommon.so.0 => /usr/lib/libxkbcommon.so.0 (0x0000712cd0279000)<br>
        libpng16.so.16 => /usr/lib/libpng16.so.16 (0x0000712ccebcf000)<br>
        libharfbuzz.so.0 => /usr/lib/libharfbuzz.so.0 (0x0000712cceab5000)<br>
        libmd4c.so.0 => /usr/lib/libmd4c.so.0 (0x0000712cd0263000)<br>
        libfreetype.so.6 => /usr/lib/libfreetype.so.6 (0x0000712cce9eb000)<br>
        libz.so.1 => /usr/lib/libz.so.1 (0x0000712ccf2a6000)<br>
        libicui18n.so.75 => /usr/lib/libicui18n.so.75 (0x0000712cce600000)<br>
        libicuuc.so.75 => /usr/lib/libicuuc.so.75 (0x0000712cce406000)<br>
        libsystemd.so.0 => /usr/lib/libsystemd.so.0 (0x0000712cce312000)<br>
        libdouble-conversion.so.3 => /usr/lib/libdouble-conversion.so.3 (0x0000712ccf28f000)<br>
        libb2.so.1 => /usr/lib/libb2.so.1 (0x0000712cce9cd000)<br>
        libpcre2-16.so.0 => /usr/lib/libpcre2-16.so.0 (0x0000712cce280000)<br>
        libzstd.so.1 => /usr/lib/libzstd.so.1 (0x0000712cce1a1000)<br>
        /lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x0000712cd0c16000)<br>
        libGLdispatch.so.0 => /usr/lib/libGLdispatch.so.0 (0x0000712cce0e9000)<br>
        libexpat.so.1 => /usr/lib/libexpat.so.1 (0x0000712cce9a4000)<br>
        libxcb.so.1 => /usr/lib/libxcb.so.1 (0x0000712cce0be000)<br>
        libpcre2-8.so.0 => /usr/lib/libpcre2-8.so.0 (0x0000712cce01f000)<br>
        libdbus-1.so.3 => /usr/lib/libdbus-1.so.3 (0x0000712ccdfce000)<br>
        libgraphite2.so.3 => /usr/lib/libgraphite2.so.3 (0x0000712cce982000)<br>
        libbz2.so.1.0 => /usr/lib/libbz2.so.1.0 (0x0000712ccdfbb000)<br>
        libbrotlidec.so.1 => /usr/lib/libbrotlidec.so.1 (0x0000712cd0254000)<br>
        libicudata.so.75 => /usr/lib/libicudata.so.75 (0x0000712ccc200000)<br>
        libcap.so.2 => /usr/lib/libcap.so.2 (0x0000712cd0b07000)<br>
        libgomp.so.1 => /usr/lib/libgomp.so.1 (0x0000712ccdf68000)<br>
        libXau.so.6 => /usr/lib/libXau.so.6 (0x0000712ccf28a000)<br>
        libXdmcp.so.6 => /usr/lib/libXdmcp.so.6 (0x0000712ccdf60000)<br>
        libbrotlicommon.so.1 => /usr/lib/libbrotlicommon.so.1 (0x0000712ccc1dd000)<br>
*/

#include "bstmainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  BstMainWindow w;
  w.show();
  return a.exec();
}
