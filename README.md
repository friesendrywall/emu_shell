# emu_shell
Shell web C emulation project

Built with mingw + emscripten using NetBeans IDE 8.2

Requirements:
Leave canvas size at 660 x 340 for C code LCD emulation

# TODO:
Make this multi-device friendly.  As it stands it is either too big or 
too small on different mobile devices, PC's, etc.

It should scale proportionately to the browser's max view height and width 
so that the buttons and all are completely in view without scrolling. This 
may require JS, but perhaps CSS is sufficient.

Some devices like iOS safari seem to interpret button tapping as a signal 
to zoom in or out, this should be disabled on all targets.

# NOTES:
The Makefile copies compiled files back to the web/ directory, as well as copying
the static web/* files to the build directory.  Web developement work should be done in
the web/* directory.  This arrangement allows setting up a dev webserver to either
directory.

# TARGETS:
iOS safari, chrome, HTML5 major targets.
