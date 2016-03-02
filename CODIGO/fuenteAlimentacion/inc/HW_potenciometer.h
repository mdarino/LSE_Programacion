/*************************************************************************//**

  @file     HW_potenciometer.h

  @brief    Hardware Library to use LEDs

  @author   Marcos Darino (MD)

  @version  20151109 v0.0.1   MD Initial release.
 ******************************************************************************/



#ifndef _HW_POTENCIOMETER__H_
#define _HW_POTENCIOMETER_H_



/** \addtogroup HARDWARE_GROUP HARDWARE
 ** @{ */


/** \addtogroup POTE_GROUP Potenciometer
 ** @{ */



/*==================[inclusions]=============================================*/
#include "DRIVER_ADC.h"


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif


/*==================[macros]=================================================*/

//STATES
#define		READY		0	//!< Number if it is press
#define		NOTREADY	1	//!< Number if it is release
#define		UNDEFINED	2	//!< Number if it is undefined 

#define 	POTE_SAMPLES			16
#define 	POTE_SAMPLES_SHIFT		3 // 2^2^2^2=16
#



/*==================[typedef]================================================*/
typedef struct	STR_pote
{
	uint8_t		state;
	uint16_t	value;
	uint8_t		channel;
	uint8_t		samples;
	uint32_t	averange;
}pote_t;



/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/


/**
 * @brief Create the object potenciometer
 * @param Struct of the potenciometer
 */
void poteConstructor (pote_t *pote);

/**
 * @brief Init the channel
 * @param Struct of the potenciometer
 * @param Channel
 */
void poteInit (pote_t *pote, uint8_t  channel);

/**
 * @brief Update the values of the potenciometer
 * @param Struct of the potenciometer
 */
void poteUpdate (pote_t *pote);

/**
 * @brief Get the state of the potenciometer
 * @param Struct of the potenciometer
 * @retun State of the potenciometer
 */
uint8_t poteGetstate (pote_t *pote);

/**
 * @brief Get the value of the potenciometer
 * @param Struct of the potenciometer
 * @retun Value of the potenciometer
 */
uint16_t poteGetValue (pote_t *pote);



/*==================[cplusplus]==============================================*/




#ifdef __cplusplus
}
#endif



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _HW_LEDS_H_ */

