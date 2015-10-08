/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/04/01
 *
 * DESCRIPTION:
 * Interfaces to access all good foos and producting cumquats
 * 
 * CHANGELOG:
 * 2015/04/02 olbrgs00:
 * Changed internal blaa production to foo creation
 * -------------------------------------------------------------------- */
int 	m_halGps_getFooToCumquat_i32(int, float);
int 	m_halGps_SetFooToCumquat_i32(int, float);
int 	m_sigGpsfilt_getCumquatToFoo_int(float, int);
void 	g_sigGpsfilt_updateFooStorage_vd(void);
void 	g_appOrient_updateCumquatStorage_vd(void);