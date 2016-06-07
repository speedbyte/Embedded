set (LIBRARY_SOURCES ImuFilter/ImuFilter.c matrixLib/matrixLib.c Orientation/Orientation.c)
add_library(SIG.lib ${LIBRARY_SOURCES})