#////////////////////////////////////////////////////////////////////////////
#//
#//  This file is part of RTIMULib
#//
#//  Copyright (c) 2014-2015, richards-tech
#//
#//  Permission is hereby granted, free of charge, to any person obtaining a copy of
#//  this software and associated documentation files (the "Software"), to deal in
#//  the Software without restriction, including without limitation the rights to use,
#//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
#//  Software, and to permit persons to whom the Software is furnished to do so,
#//  subject to the following conditions:
#//
#//  The above copyright notice and this permission notice shall be included in all
#//  copies or substantial portions of the Software.
#//
#//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
#//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
#//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
#//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
#//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
#//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#// The cmake support was based on work by Moritz Fischer at ettus.com.
#// Original copyright notice:
#
# Copyright 2014 Ettus Research LLC
#

########################################################################
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    MESSAGE(FATAL_ERROR "Prevented in-tree built. This is bad practice.")
ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

########################################################################
# Project setup
########################################################################
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)
#PROJECT(RTIMULib)
#ENABLE_TESTING()

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
#set ( CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../")

#INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/../RTIMULibVersion.txt)

SET(LIBRTIMU_SRCS
    senseHat-rep/RTIMULib/RTFusion.cpp
    senseHat-rep/RTIMULib/RTFusionRTQF.cpp
    senseHat-rep/RTIMULib/RTMath.cpp
    senseHat-rep/RTIMULib/RTFusionKalman4.cpp
    senseHat-rep/RTIMULib/RTIMUAccelCal.cpp
    senseHat-rep/RTIMULib/RTIMUHal.cpp
    senseHat-rep/RTIMULib/RTIMUMagCal.cpp
    senseHat-rep/RTIMULib/RTIMUSettings.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMU.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMUGD20M303DLHC.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMUGD20HM303DLHC.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMUGD20HM303D.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMULSM9DS0.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMULSM9DS1.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMUMPU9150.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMUMPU9250.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMUBMX055.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMUBNO055.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTIMUNull.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTPressure.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTPressureBMP180.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTPressureLPS25H.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTPressureMS5611.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTPressureMS5637.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTHumidity.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTHumidityHTS221.cpp
    senseHat-rep/RTIMULib/IMUDrivers/RTHumidityHTU21D.cpp
)

    ADD_LIBRARY(RTIMULib SHARED ${LIBRTIMU_SRCS})
    
    INSTALL(TARGETS RTIMULib DESTINATION lib)
    INSTALL(DIRECTORY . DESTINATION include FILES_MATCHING PATTERN "*.h")

