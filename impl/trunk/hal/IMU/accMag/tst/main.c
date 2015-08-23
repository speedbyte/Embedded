/*!
 * \file main.c
 */
#include "../accMag.h"

#include <stdio.h>
#include <unistd.h>

int main (void)
{
	halAccmag_dataContainer l_sensorData_st;

	if ( g_halAccmag_initSensor_bl() != M_HAL_ACCMAG_SUCCESS_BL )
	{
		printf( "Init failed!\n" );
		return 1;
	}

	while (1)
	{
		if ( g_halAccmag_triggerAccUpdate_bl() != M_HAL_ACCMAG_SUCCESS_BL )
		{
			printf( "ACC update failed!\n" );
			return 1;
		}
		if ( g_halAccmag_triggerMagUpdate_bl() != M_HAL_ACCMAG_SUCCESS_BL )
		{
			printf( "MAG update failed!\n" );
			return 1;
		}

		l_sensorData_st = g_halAccmag_getAccMagContainer_st();

		printf("Acc - x:%f y:%lf z:%f | Mag - x:%.10f y:%.10f z:%.10f\n",
				l_sensorData_st.acc.x_f64,
				l_sensorData_st.acc.y_f64,
				l_sensorData_st.acc.z_f64,
				l_sensorData_st.mag.x_f64,
				l_sensorData_st.mag.y_f64,
				l_sensorData_st.mag.z_f64
				);

		usleep( 250000 );
	}

	return 0;
}

