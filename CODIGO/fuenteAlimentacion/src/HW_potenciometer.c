/*************************************************************************//**

  @file     HW_potenciometer.c

  @brief    Functions to use potenciometer.

  @author   Marcos Darino (MD)


 ******************************************************************************/


/** \addtogroup HARDWARE_GROUP HARDWARE
 ** @{ */


/** \addtogroup POTE_GROUP Potenciometer
 ** @{ */


/*==================[inclusions]=============================================*/
#include "HW_potenciometer.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/




/*Potenciometer constructor: */
void poteConstructor (pote_t *pote)
{
	pote->state=UNDEFINED;
	pote->value=0;
	pote->channel=0;
	pote->samples=0;
	pote->averange=0;
}

/*Potenciometer init: configure the channel*/
void poteInit (pote_t *pote, uint8_t  channel)
{
	pote->state=NOTREADY;
	pote->value=0;
	pote->channel=channel;

}

/*Potenciometer Update: update the state of the potes*/
void poteUpdate (pote_t *pote)
{


	pote->samples++;
	pote->averange+=Analog_Read(pote->channel);
	
	if (pote->samples>=POTE_SAMPLES)
	{
		pote->samples = 0;
		pote->value = (pote->averange>>POTE_SAMPLES_SHIFT);
		pote->averange = 0;
		pote->state=READY;
	}
	
}

/*Potenciometer get state: Return the state, if the value is ready */
uint8_t poteGetstate (pote_t *pote)
{
	return (pote->state);
}	

/*Potenciometer get value: Return the value of the potenciometer */
uint16_t poteGetValue (pote_t *pote)
{
	return (pote->value);
}	

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

