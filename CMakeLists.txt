cmake_minimum_required(VERSION 2.8)
project(helikopter-raspberry)

include_directories("${CMAKE_BINARY_DIR}")

include_directories("${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/include/c++/4.8.3")
include_directories("${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/include")
include_directories("${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/include")
include_directories(${CMAKE_SOURCE_DIR}/helikopter-src/hal/SENSOR/inc)
include_directories(${CMAKE_SOURCE_DIR}/helikopter-src/hal/HAL_LIB/inc)
include_directories(${CMAKE_SOURCE_DIR}/helikopter-src/hal/MOTOR/inc)
include_directories(${CMAKE_SOURCE_DIR}/helikopter-src/sig/inc)
include_directories(${CMAKE_SOURCE_DIR}/helikopter-src/lld/)
include_directories(${CMAKE_SOURCE_DIR}/helikopter-src/remotecontroller)
option(DO_TARGET_CONNECT "If the target needs to be connected")
set(DO_TARGET_CONNECT OFF)

option(GENERATE_LIBRARIES "This method will generate individual libraries")

set(GENERATE_LIBRARIES OFF)

option(HATSENSE "This method will generate hat sense libraries and executables")
set(HATSENSE ON)


set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_AR ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-ar)
set(CMAKE_RANLIB ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-ranlib)
set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++)
set(OBJCOPY ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-objcopy)
set(CMAKE_OBJDUMP ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-objdump)
set(CMAKE_SIZE ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-size)
set(CMAKE_NM ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-nm)
set(CMAKE_READELF ${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-readelf)

set(${CFLAGSNOERROR} -Wno-error=unused-but-set-variable -Wno-error=unused-variable)
set(${CFLAGSERROR} CFLAGSERROR=-Werror)
set(CMAKE_C_FLAGS "-O0 ${CFLAGSNOERROR} -Wall -I. -fmessage-length=0")
set(CMAKE_C_FLAGS_DEBUG -g3)
set(CMAKE_C_FLAGS_RELEASE)
set(CMAKE_SHARED_LINKER_FLAGS "-g")

#ARFLAGS=rcs
#LDFLAGS=-g -z -c -x
#Dependancy : -MMD -MP

find_library(ARM_MATH_LIBRARY NAMES libm.so HINTS "${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf")
find_library(ARM_C_LIBRARY NAMES libc.so HINTS "${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf")
find_library(ARM_RT_LIBRARY NAMES librt.so HINTS "${CMAKE_SOURCE_DIR}/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf")

set(CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR})


if(HATSENSE) 

include_directories("${CMAKE_SOURCE_DIR}/senseHat-src/")
include_directories("${CMAKE_SOURCE_DIR}/senseHat-src/senseHat-rep/RTIMULib/")
set (CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/senseHat-src/senseHat-install")
add_subdirectory(${CMAKE_SOURCE_DIR}/senseHat-src/)
ADD_EXECUTABLE(HATSENSE ${CMAKE_SOURCE_DIR}/helikopter-src/main/readSens.cpp)
target_link_libraries(HATSENSE RTIMULib)


endif(HATSENSE)

if(GENERATE_LIBRARIES)

file(GLOB_RECURSE SRC_COMMUNICATION ${CMAKE_SOURCE_DIR}/helikopter-src/hal/HAL_LIB/*.c)
file(GLOB_RECURSE SRC_LLD ${CMAKE_SOURCE_DIR}/helikopter-src/lld/*.c)
file(GLOB_RECURSE SRC_SENSOR ${CMAKE_SOURCE_DIR}/helikopter-src/hal/SENSOR/*.c)
file(GLOB_RECURSE SRC_SIG ${CMAKE_SOURCE_DIR}/helikopter-src/sig/*.c)
file(GLOB_RECURSE SRC_MOTOR ${CMAKE_SOURCE_DIR}/helikopter-src/hal/MOTOR/*.c)

add_library(communication SHARED ${SRC_COMMUNICATION})   # compile "SRC_COMMUNICATION.cpp" and create a SHARED library called "comminication"
add_library(lld SHARED ${SRC_LLD})   # compile "SRC_LLD" and create a SHARED library called "lld"
add_library(sensor SHARED ${SRC_SENSOR})   # compile "SRC_SENSOR" and create a SHARED library called "sensor"
add_library(sig SHARED ${SRC_SIG})   # compile "SRC_SIG" and create a SHARED library called "sig"
add_library(motor SHARED ${SRC_MOTOR})   # compile "SRC_MOTOR" and create a SHARED library called "motor"


set_target_properties(communication PROPERTIES LINKER_LANGUAGE C)
set_target_properties(lld PROPERTIES LINKER_LANGUAGE C)
set_target_properties(sensor PROPERTIES LINKER_LANGUAGE C)
set_target_properties(sig PROPERTIES LINKER_LANGUAGE C)
set_target_properties(motor PROPERTIES LINKER_LANGUAGE C)

target_compile_definitions(motor PRIVATE Quadro_Plus=1)

add_executable(HELIKOPTER ${CMAKE_SOURCE_DIR}/helikopter-src/main/main.c)           # compile "main.c" the the executable called "HELIKOPTER"

target_link_libraries(HELIKOPTER ${ARM_RT_LIBRARY} ${ARM_MATH_LIBRARY} ${ARM_C_LIBRARY}  communication lld sensor sig motor)      # link our previously created shared libraries to the exectable "HELIKOPTER"

add_custom_command(TARGET HELIKOPTER POST_BUILD COMMAND echo "WE HAVE FINISHED COMPILING ${HELIKOPTER} WITH SHARED LIBRARIES")

else()

file(GLOB_RECURSE HAL_SRC ${CMAKE_SOURCE_DIR}/helikopter-src/hal/*.c)
MESSAGE( STATUS "HAL_SRC:         " ${HAL_SRC} )

file(GLOB MATLAB_SRC ${CMAKE_SOURCE_DIR}/helikopter-src/matlab/*.c)
MESSAGE( STATUS "MATLAB_SRC:         " ${MATLAB_SRC} )

file(GLOB_RECURSE SIG_SRC ${CMAKE_SOURCE_DIR}/helikopter-src/sig/*.c)
MESSAGE( STATUS "SIG_SRC             " ${SIG_SRC} )

file(GLOB_RECURSE LLD_SRC ${CMAKE_SOURCE_DIR}/helikopter-src/lld/*.c)
MESSAGE( STATUS "LLD_SRC             " ${LLD_SRC} )

# ...${HAL_SRC} ${MATLAB_SRC} ${SIG_SRC} ...
add_executable(HELIKOPTER ${HAL_SRC} ${SIG_SRC} ${LLD_SRC} ${CMAKE_SOURCE_DIR}/helikopter-src/main/main.c)
target_link_libraries(HELIKOPTER ${ARM_RT_LIBRARY} ${ARM_MATH_LIBRARY} ${ARM_C_LIBRARY})
add_custom_command(TARGET HELIKOPTER POST_BUILD COMMAND echo "WE HAVE FINISHED COMPILING ${HELIKOPTER}")
target_compile_definitions(HELIKOPTER PRIVATE Quadro_Plus=1)

endif(GENERATE_LIBRARIES)


if (DO_TARGET_CONNECT)
# execute_process(COMMAND ls _NPROCESSORS_ONLN OUTPUT_VARIABLE NB_PROCESSOR)
# To automate the login processs, add helikopter to /etc/hosts and do a ssh-copy-id to pi@helikopter
add_custom_command(TARGET HELIKOPTER POST_BUILD COMMAND scp HELIKOPTER pi@helikopter:/home/pi/HELIKOPTER )
add_custom_command(TARGET HELIKOPTER POST_BUILD COMMAND ssh pi@helikopter \"ls | grep HELIKOPTER \")
endif (DO_TARGET_CONNECT)

# ------------------------- Begin Generic CMake Variable Logging ------------------

# /*    C++ comment style not allowed   */


# if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise 
# this is the top level directory of your build tree 
MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR} )

# if you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this 
# is the directory where the compiled or generated files from the current CMakeLists.txt will go to 
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )

# this is the directory, from which cmake was started, i.e. the top level source directory 
MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )

# this is the directory where the currently processed CMakeLists.txt is located in 
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

# contains the full path to the top level directory of your build tree 
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

# contains the full path to the root of your project source directory,
# i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command 
MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )

# set this variable to specify a common place where CMake should put all executable files
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH} )

# set this variable to specify a common place where CMake should put all libraries 
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH} )

# tell CMake to search first in directories listed in CMAKE_MODULE_PATH
# when you use FIND_PACKAGE() or INCLUDE()
MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )

# this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake) 
MESSAGE( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )

# this is the CMake installation directory 
MESSAGE( STATUS "CMAKE_ROOT: " ${CMAKE_ROOT} )

# this is the filename including the complete path of the file where this variable is used. 
MESSAGE( STATUS "CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE} )

# this is linenumber where the variable is used
MESSAGE( STATUS "CMAKE_CURRENT_LIST_LINE: " ${CMAKE_CURRENT_LIST_LINE} )

# this is used when searching for include files e.g. using the FIND_PATH() command.
MESSAGE( STATUS "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH} )

# this is used when searching for libraries e.g. using the FIND_LIBRARY() command.
MESSAGE( STATUS "CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH} )

# the complete system name, e.g. "Linux-2.4.22", "FreeBSD-5.4-RELEASE" or "Windows 5.1" MESSAGE( STATUS "CMAKE_SYSTEM: " ${CMAKE_SYSTEM} )

# the short system name, e.g. "Linux", "FreeBSD" or "Windows"
MESSAGE( STATUS "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME} )

# only the version part of CMAKE_SYSTEM 
MESSAGE( STATUS "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION} )

# the processor name (e.g. "Intel(R) Pentium(R) M processor 2.00GHz") 
MESSAGE( STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR} )

# is TRUE on all UNIX-like OS's, including Apple OS X and CygWin
MESSAGE( STATUS "UNIX: " ${UNIX} )

# is TRUE on Windows, including CygWin 
MESSAGE( STATUS "WIN32: " ${WIN32} )

# is TRUE on Apple OS X
MESSAGE( STATUS "APPLE: " ${APPLE} )

# is TRUE when using the MinGW compiler in Windows
MESSAGE( STATUS "MINGW: " ${MINGW} )

# is TRUE on Windows when using the CygWin version of cmake
MESSAGE( STATUS "CYGWIN: " ${CYGWIN} )

# is TRUE on Windows when using a Borland compiler 
MESSAGE( STATUS "BORLAND: " ${BORLAND} )

# Microsoft compiler 
MESSAGE( STATUS "MSVC: " ${MSVC} )
MESSAGE( STATUS "MSVC_IDE: " ${MSVC_IDE} )
MESSAGE( STATUS "MSVC60: " ${MSVC60} )
MESSAGE( STATUS "MSVC70: " ${MSVC70} )
MESSAGE( STATUS "MSVC71: " ${MSVC71} )
MESSAGE( STATUS "MSVC80: " ${MSVC80} )
MESSAGE( STATUS "CMAKE_COMPILER_2005: " ${CMAKE_COMPILER_2005} )


# set this to true if you don't want to rebuild the object files if the rules have changed, 
# but not the actual source files or headers (e.g. if you changed the some compiler switches) 
MESSAGE( STATUS "CMAKE_SKIP_RULE_DEPENDENCY: " ${CMAKE_SKIP_RULE_DEPENDENCY} )

# since CMake 2.1 the install rule depends on all, i.e. everything will be built before installing. 
# If you don't like this, set this one to true.
MESSAGE( STATUS "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: " ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY} )

# If set, runtime paths are not added when using shared libraries. Default it is set to OFF
MESSAGE( STATUS "CMAKE_SKIP_RPATH: " ${CMAKE_SKIP_RPATH} )

# set this to true if you are using makefiles and want to see the full compile and link 
# commands instead of only the shortened ones 
MESSAGE( STATUS "CMAKE_VERBOSE_MAKEFILE: " ${CMAKE_VERBOSE_MAKEFILE} )

# this will cause CMake to not put in the rules that re-run CMake. This might be useful if 
# you want to use the generated build files on another machine. 
MESSAGE( STATUS "CMAKE_SUPPRESS_REGENERATION: " ${CMAKE_SUPPRESS_REGENERATION} )


# A simple way to get switches to the compiler is to use ADD_DEFINITIONS(). 
# But there are also two variables exactly for this purpose: 

# the compiler flags for compiling C sources 
MESSAGE( STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS} )

# the compiler flags for compiling C++ sources 
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )


# Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug) 
MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )

# if this is set to ON, then all libraries are built as shared libraries by default.
MESSAGE( STATUS "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS} )

# the compiler used for C files 
MESSAGE( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )

# the compiler used for C++ files 
MESSAGE( STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )

# if the compiler is a variant of gcc, this should be set to 1 
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCC: " ${CMAKE_COMPILER_IS_GNUCC} )

# if the compiler is a variant of g++, this should be set to 1 
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCXX : " ${CMAKE_COMPILER_IS_GNUCXX} )

# the tools for creating libraries 
MESSAGE( STATUS "CMAKE_AR: " ${CMAKE_AR} )
MESSAGE( STATUS "CMAKE_RANLIB: " ${CMAKE_RANLIB} )

# external library paths
message(STATUS "the path of ARM_C_LIBRARY: " ${ARM_C_LIBRARY})
#
#MESSAGE( STATUS ": " ${} )

# ------------------------- End of Generic CMake Variable Logging -----------------


# Legacy code for learning -------------------------

## The below 2 lines needs to be written in further CMakeLists.txt
#set (LIBRARY_SOURCES HAL_ADC.c)
#add_library(ADC.lib ${LIBRARY_SOURCES})

## The below line adds the subdirectory where further CMakeLists.txt can be found
#add_subdirectory(${CMAKE_SOURCE_DIR}/helikopter-src/lld)

#set (EXTRA_LIBS ${EXTRA_LIBS} ADC.lib BATTERY.lib GPIO.lib GPS.lib IMU.lib LASER.lib MOTOR.lib UDP.lib REMOTECONTROLLER.lib MATLAB.lib SIG.lib LLD.lib)

#add_executable(HELIKOPTER ${CMAKE_SOURCE_DIR}/helikopter-src/main/main.c)
#target_link_libraries(HELIKOPTER ${EXTRA_LIBS} ${ARM_RT_LIBRARY} ${ARM_MATH_LIBRARY} ${ARM_C_LIBRARY})
#add_custom_command(TARGET HELIKOPTER POST_BUILD COMMAND echo "WE HAVE FINISHED COMPILING ${HELIKOPTER}")

