/*************************************************************************//**

  @file     HW_buttons.c

  @brief    Hardware Library to use buttons

  @author   Marcos Darino (MD)


 ******************************************************************************/


/** \addtogroup HARDWARE_GROUP HARDWARE
 ** @{ */


/** \addtogroup BUTTONS_GROUP BUTTONS
 ** @{ */


/*==================[inclusions]=============================================*/

#include "HW_buttons.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/*Button constructor: define the GPIO and the bit*/
void buttonConstructor (button_t *button, uint8_t gpio, uint8_t gpio_bit)
{
	button->state=UNDEFINED;
	button->time=0;
	button->gpio=gpio;
	button->gpio_bit=gpio_bit;
	button->lastState=UNDEFINED;
}

/*Button init: configure the pin and set as output*/
void buttonInitWithoutPullUp (button_t *button, uint8_t  port, uint8_t  port_pin ,uint8_t function)
{
	GPIO_pinConfiguration(port,port_pin, MD_PUP|MD_EZI|MD_ZI,function);
	GPIO_setAsInput(button->gpio,button->gpio_bit);
}

/*buttons Update: update the state of the buttons*/
void buttonUpdate (button_t *button)
{
	if (!(GPIO_getValue(button->gpio,button->gpio_bit)))
	{
		button->time++;
		if (button->time>65000)
			button->time=65000;
		if (button->time>TICKS_BUTTON)
			button->state=PRESS;
	}
	else
	{
		button->state=RELEASE;
		button->time=0;
	}
	
}



/*buttons get time: return how many ticks it is pressed the button */
uint16_t buttonGetTime (button_t *button)
{
	return (button->time);
}	

/*buttons get state: return if the button is press or release */
uint8_t buttonGetState (button_t *button)
{
	return (button->state);
}	

/*buttons get state: return if the button is press or release */
/*only is press if after was release*/
uint8_t buttonGetStateWithRl (button_t *button)
{
	uint8_t bState=RELEASE;
	

	if (button->state==PRESS)
	{
		if (button->lastState==RELEASE)
		{
			bState=PRESS;
		}
		button->lastState=PRESS;
	}
	else
	{
		button->lastState=RELEASE;
	}

	return (bState);
}	

/*buttons lastState: return the last state of the button */
uint8_t buttonGetLastState (button_t *button)
{
	return (button->lastState);
}
/*buttons lastState: set the last state of the button (to remember) */
void buttonSetLastState (button_t *button, uint8_t lastButState)
{
	button->lastState=lastButState;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

