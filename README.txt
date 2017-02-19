#!/bin/bash

#put gtk+ bundle somewhere on fs
#add gtk+/bin to path in windows env dialog

#might need to run this : 

autoreconf -ivf -I /c/gtk+/share/aclocal/

# put sdl2 for mingw somehere on fs
# copy i686-sql2-package/lib to /lib and i686-sdl2package/include/SDL to /include
# might need to run this to find sdl2 pkg-config files

PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
export PKG_CONFIG_PATH
 
