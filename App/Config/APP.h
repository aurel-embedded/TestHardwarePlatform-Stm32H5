/*
 * APP.h
 *
 *  Created on: 13 janv. 2023
 *      Author: apajadon
 */

#ifndef INC_APP_H_
#define INC_APP_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static const uint8_t 	APP_SoftwareReference[]	= 	"Testing - THW";
static const uint8_t 	APP_SoftwareVersion[] = 	"0.0.2";


//------------------------------------------------------------------------------
/// \fn        const char* APP_getSoftwareReference(void)
/// \brief     Returns the software reference string defined in APP.h.
/// \return    Pointer to a null-terminated C string.
/// \note      The returned pointer refers to a static string; do not modify or free it.
//------------------------------------------------------------------------------
static inline const char* APP_getSoftwareReference(void)
{
    return (const char*)APP_SoftwareReference;
}

//------------------------------------------------------------------------------
/// \fn        const char* APP_getSoftwareVersion(void)
/// \brief     Returns the software version string defined in APP.h.
/// \return    Pointer to a null-terminated C string.
/// \note      The returned pointer refers to a static string; do not modify or free it.
//------------------------------------------------------------------------------
static inline const char* APP_getSoftwareVersion(void)
{
    return (const char*)APP_SoftwareVersion;
}


#ifdef __cplusplus
}
#endif

#endif /* INC_APP_H_ */
