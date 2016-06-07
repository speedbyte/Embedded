cmake_minimum_required(VERSION 2.8)
project(helikopter-raspberry)

include_directories("${CMAKE_BINARY_DIR}")

include_directories("${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/include/c++/4.8.3")
include_directories("${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/include")
include_directories("${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/include")

#include_directories("${CMAKE_SOURCE_DIR}/impl/trunk/sig")
#find_path(RT librt NO_CMAKE_SYSTEM_PATH NO_DEFAULT_PATH)

#find_library(ADC.lib NAMES ${CMAKE_SOURCE_DIR}/impl/trunk/hal/ADC/ADC.lib)
set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_AR ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-ar)
set(CMAKE_RANLIB ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-ranlib)

message(STATUS "the value of CC: " ${CMAKE_C_COMPILER})
find_library(ARM_MATH_LIBRARY NAMES libm.so HINTS "${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf")
find_library(ARM_C_LIBRARY NAMES libc.so HINTS "${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf")
find_library(ARM_RT_LIBRARY NAMES librt.so HINTS "${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf")
message(STATUS "the path of ARM_MATH_LIBRARY: " ${ARM_MATH_LIBRARY})

set(CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/hal/ADC)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/hal/BATTERY)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/hal/GPIO)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/hal/GPS)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/hal/IMU)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/hal/LASER)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/hal/LLD_IF)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/hal/MOTOR)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/hal/REMOTECONTROLLER)
#add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/kern)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/matlab)
add_subdirectory(${CMAKE_SOURCE_DIR}/impl/trunk/sig)

set (EXTRA_LIBS ${EXTRA_LIBS} ADC.lib BATTERY.lib GPIO.lib GPS.lib IMU.lib LASER.lib LLD_IF.lib MOTOR.lib REMOTECONTROLLER.lib MATLAB.lib SIG.lib)

add_executable(HELIKOPTER ${CMAKE_SOURCE_DIR}/impl/trunk/MAIN/main.c)
target_link_libraries(HELIKOPTER ${EXTRA_LIBS} ${ARM_RT_LIBRARY} ${ARM_MATH_LIBRARY} ${ARM_C_LIBRARY})