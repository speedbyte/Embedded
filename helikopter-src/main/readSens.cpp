////////////////////////////////////////////////////////////////////////////
//
//  Read values from sensor of Sense HAT
//
//  Author: Massimiliano Botticelli
//  Date: 2017.05.21
//
//
/////////////////////////////////////////////////////////////////////////////

#include "RTIMULib.h"

int main(){
  int sampleRate = 0;
  int sampleCount = 0;
  uint64_t rateTimer;
  uint64_t displayTimer;
  uint64_t now;
  
  RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

  RTIMU *imu = RTIMU::createIMU(settings); 
  
  if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
    printf("No IMU found\n");
    exit(1);
  }

  imu->IMUInit();
  
   imu->setSlerpPower(0.02);
   imu->setGyroEnable(true);
   imu->setAccelEnable(true);
   imu->setCompassEnable(true);
  
  rateTimer = displayTimer = RTMath::currentUSecsSinceEpoch();
  
  while(1){
    usleep(imu->IMUGetPollInterval() * 1000);
    
    while(imu->IMURead()){
      RTIMU_DATA imuData = imu->getIMUData();
      sampleCount++;
      
      now = RTMath::currentUSecsSinceEpoch();
      
      if ((now - displayTimer) > 100000) {
        printf("Sample rate %d: %s\r", sampleRate, RTMath::displayDegrees("", imuData.fusionPose));
        fflush(stdout);
      	displayTimer = now;
      }
      
      if ((now - rateTimer) > 1000000) {
      sampleRate = sampleCount;
      sampleCount = 0;
      rateTimer = now;
      }
    }
      
  }
}


