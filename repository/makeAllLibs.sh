#!/bin/bash


# make libcommunication.so
/home/robin/workspace/Project_Hochschule/Embedded/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc -shared -O0  -Wall -I. -fmessage-length=0 -g3  CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/HAL_LIB/GPIO.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/HAL_LIB/udpLib.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/HAL_LIB/HAL_ADC.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/HAL_LIB/udpSensorLib.c.o -o libcommunication.so

# make liblld.so
/home/robin/workspace/Project_Hochschule/Embedded/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc -shared -O0  -Wall -I. -fmessage-length=0 -g3   CMakeFiles/HELIKOPTER.dir/helikopter-src/lld/LLD_UART.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/lld/LLD_I2C.c.o -o liblld.so

# make libmotor.so
/home/robin/workspace/Project_Hochschule/Embedded/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc -shared -O0  -Wall -I. -fmessage-length=0 -g3   CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/MOTOR/MOTOR.c.o -o libmotor.so

# make libsensor.so
/home/robin/workspace/Project_Hochschule/Embedded/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc -shared -O0  -Wall -I. -fmessage-length=0 -g3  CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/SENSOR/LIDAR.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/SENSOR/Sensor_Lib.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/SENSOR/GPS.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/SENSOR/imu.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/SENSOR/barometer.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/SENSOR/accMag.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/SENSOR/batteryCheck.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/hal/SENSOR/Gyro.c.o -o libsensor.so

# make libsig.so
/home/robin/workspace/Project_Hochschule/Embedded/helikopter-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc -shared -O0  -Wall -I. -fmessage-length=0 -g3   CMakeFiles/HELIKOPTER.dir/helikopter-src/sig/Orientation.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/sig/matrixLib.c.o CMakeFiles/HELIKOPTER.dir/helikopter-src/sig/ImuFilter.c.o -o libsig.so
