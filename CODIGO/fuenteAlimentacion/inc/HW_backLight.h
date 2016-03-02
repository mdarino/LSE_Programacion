/*************************************************************************//**

  @file     HW_backlight.h

  @brief    Hardware Library a RGB backlight

  @author   Marcos Darino (MD)

  @version  20151109 v0.0.1   MD Initial release.

 ******************************************************************************/




#ifndef _HW_BACKLIGHT_H_
#define _HW_BACKLIGHT_H_

/** \addtogroup HARDWARE_GROUP HARDWARE
 ** @{ */


/** \addtogroup BACKLIGHT_GROUP BACKLIGHT
 ** @{ */


/*==================[inclusions]=============================================*/
#include "DRIVER_GPIO.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
//
//	BACKLIGHT NUMBER DEFINES
//

#define BACKLIGHT_BLUE	2	//!< Number of the BACKLIGHT blue
#define BACKLIGHT_GREEN	1	//!< Number of the BACKLIGHT green
#define BACKLIGHT_RED 	0	//!< Number of the BACKLIGHT red


//
//	GPIO DEFINES
//

#define BACKLIGHT_BLUE_GPIO		0	//!< GPIO of the BACKLIGHT
#define BACKLIGHT_GREEN_GPIO	0	//!< GPIO of the BACKLIGHT
#define BACKLIGHT_RED_GPIO 		0	//!< GPIO of the BACKLIGHT

#define BACKLIGHT_BLUE_GPIO_BIT		15	//!< BIT of the BACKLIGHT in the GPIO
#define BACKLIGHT_GREEN_GPIO_BIT	12	//!< BIT of the BACKLIGHT in the GPIO
#define BACKLIGHT_RED_GPIO_BIT 		13	//!< BIT of the BACKLIGHT in the GPIO

//
//	PORT/PIN DEFINES
//

#define BACKLIGHT_BLUE_PORT		1	//!< Port of the BACKLIGHT - Use to configure the pin
#define BACKLIGHT_GREEN_PORT	1	//!< Port of the BACKLIGHT - Use to configure the pin
#define BACKLIGHT_RED_PORT 		1	//!< Port of the BACKLIGHT - Use to configure the pin


#define BACKLIGHT_BLUE_PORT_PIN		20	//!< Pin of the BACKLIGHT in the Port
#define BACKLIGHT_GREEN_PORT_PIN	17	//!< Pin of the BACKLIGHT in the Port
#define BACKLIGHT_RED_PORT_PIN 		18	//!< Pin of!< the BACKLIGHT in the Port


/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/



/**
 * @brief Turn on the backlight
 * @param backlightNumber : Number of the backlight to turn ON
  */
void backlight_SetON (uint8_t backlightNumber);

/**
 * @brief Turn of the backlight
 * @param backlightNumber Number of the backlight to turn OFF
 */
void backlight_SetOFF (uint8_t backlightNumber);

/**
 * @brief 	Configure the Ports and set as output the GPIO
 * @note	If you add new backlight you should add it in this function
 */
void backlight_Init (void);

/**
 * @brief 	Turn off all the backlights and then turn on all
 * @note	To test the backlight you should use the DEBUG mode and breakpoints
 */
void backlight_Test (void);


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _BACKLIGHT_ */

