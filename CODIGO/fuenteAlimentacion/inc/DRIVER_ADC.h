/*************************************************************************//**

  @file     DRIVER_ADC.h

  @brief    Control the ADC peripheral and channels configurations. It uses the LPCOPEN's librarys

  @author   Marcos Darino (MD)

  @version  20151124 v0.0.1   PL first version
  @version  20151126 v0.0.2   MD add new functions and comments

 ******************************************************************************/





#ifndef _DRIVER_ADC_H_
#define _DRIVER_ADC_H_


/** \addtogroup DRIVERS_GROUP DRIVERS
 ** @{ */


/** \addtogroup ADC_GROUP ADC
 ** @{ */



/*==================[inclusions]=============================================*/
#include "chip.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/


/**
 * @brief Init the Analog ADC
 */
void Analog_Init(void);

/**
 * @brief Get the ADC value
 * @param  channel : ADC channel to read
 * @return The value of the ADC
 */
int16_t Analog_Read(int32_t channel);


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _DRIVER_ADC_H_ */

