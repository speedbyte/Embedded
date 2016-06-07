set (LIBRARY_SOURCES accMag/accMag.c barometer/barometer.c gyro/Gyro.c Lib/Hal_Lib.c imu.c)
add_library(IMU.lib ${LIBRARY_SOURCES})