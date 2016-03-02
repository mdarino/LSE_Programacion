/*************************************************************************//**

  @file     HW_backlight.c

  @brief    Hardware Library a RGB backlight

  @author   Marcos Darino (MD)


 ******************************************************************************/




/** \addtogroup HARDWARE_GROUP HARDWARE
 ** @{ */


/** \addtogroup BACKLIGHT_GROUP BACKLIGHT
 ** @{ */




/*==================[inclusions]=============================================*/
#include "HW_backLight.h"



/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
static gpioPin_t backlightLed[6] = {{BACKLIGHT_RED_GPIO,BACKLIGHT_RED_GPIO_BIT},
{BACKLIGHT_GREEN_GPIO,BACKLIGHT_GREEN_GPIO_BIT},
{BACKLIGHT_BLUE_GPIO,BACKLIGHT_BLUE_GPIO_BIT}};
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*Set ON the backlight*/
void backlight_SetON (uint8_t backlightNumber)
{
	GPIO_setON(backlightLed[backlightNumber].gpio,backlightLed[backlightNumber].bit);
}
/*Set OFF the Backlight*/
void backlight_SetOFF (uint8_t backlightNumber)
{
	GPIO_setOFF(backlightLed[backlightNumber].gpio,backlightLed[backlightNumber].bit);
}

/*Configure the port and the GPIO of the backlights*/
void backlight_Init (void)
{

	//Configure the fuction of the pin -> as GPIO and without pullups
	GPIO_pinConfiguration(BACKLIGHT_RED_PORT,BACKLIGHT_RED_PORT_PIN,SCU_MODE_INACT ,FUNC0);
	GPIO_pinConfiguration(BACKLIGHT_GREEN_PORT,BACKLIGHT_GREEN_PORT_PIN,SCU_MODE_INACT ,FUNC0);
	GPIO_pinConfiguration(BACKLIGHT_BLUE_PORT,BACKLIGHT_BLUE_PORT_PIN,SCU_MODE_INACT ,FUNC0);

	// Set as outputs all the GPIO
	GPIO_setAsOutput(BACKLIGHT_RED_GPIO,BACKLIGHT_RED_GPIO_BIT);
	GPIO_setAsOutput(BACKLIGHT_GREEN_GPIO,BACKLIGHT_GREEN_GPIO_BIT);
	GPIO_setAsOutput(BACKLIGHT_BLUE_GPIO,BACKLIGHT_BLUE_GPIO_BIT);
}

/*test backlights - YOU MUST USE DEBUG AND BREAKPOINTS*/
void backlight_Test (void)
{

	backlight_SetOFF(BACKLIGHT_RED);
	backlight_SetOFF(BACKLIGHT_GREEN);
	backlight_SetOFF(BACKLIGHT_BLUE);

	backlight_SetON(BACKLIGHT_RED);
	backlight_SetON(BACKLIGHT_GREEN);
	backlight_SetON(BACKLIGHT_BLUE);

	backlight_SetOFF(BACKLIGHT_RED);
	backlight_SetOFF(BACKLIGHT_GREEN);
	backlight_SetOFF(BACKLIGHT_BLUE);
}





/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

