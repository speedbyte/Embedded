/*!
 * \file main.c
 */


#include <stdio.h>
#include "../../hal/Laser/LIDAR.h"

int main (void)
{

	
	double dist=0;
	
	while(1)
	{
		g_LIDAR_readDistanceFromI2C_i32();
		//usleep(100000);
		
		dist=g_LIDAR_getDistance_f64();
		
		printf("Distance: %4.2f m\n",dist);
		usleep(500*1000);


	}


	return 0;
}



