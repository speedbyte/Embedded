/*!**********************************************************************
 * \author 		Juergen Schmidt (juscgs00)
 * \date 			2014/04/01
 * 
 * \brief		Enumeration of all possible GPS sensor states.
 * \details	A detailed descripction about the purpose of the variable 
 *					or typedef. Multiple lines of description is possible. 
 * 					Doxygen will recognize the format automatically.
 * 
 * \internal
 * CHANGELOG:
 * 2015/04/02 olbrgs00:
 * Changed internal blaa production to foo creation
 *
 * \endinternal
 ***********************************************************************/
typedef enum e_gpsStates{
	GPS_UNDEF_EN,             //!< undefined state   
	GPS_INIT_EN,              //!< startup of sensor
	GPS_UNFIXED_SIGNAL_EN,    //!< sensor is searching for satellites
	GPS_FIXED_SIGNAL_EN,      //!< found enough satellites
	GPS_ERROR_EN              //!< non-functional operation
} gpsStatesType;

/*!
	the following line is intentionally commented improperly, since it shall
	only clarify the context of the typedef above. A complete commenting
	block - as depicted for the enum type definition above - would be 
	required for the global variable below!
*/
gpsStatesType g_halGps_opState_en; 