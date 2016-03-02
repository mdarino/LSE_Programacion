/*************************************************************************//**

  @file     DRIVER_GPIO.c

  @brief    Driver to use the GPIO and PIN configurations

  @author   Marcos Darino (MD)


 ******************************************************************************/


/** \addtogroup DRIVERS_GROUP DRIVERS
 ** @{ */


/** \addtogroup GPIO_GROUP GPIO
 ** @{ */




/*==================[inclusions]=============================================*/
#include "DRIVER_GPIO.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/**
 * @brief Set GPIO direction for a single GPIO pin to an input
 */
void GPIO_setAsInput(uint8_t port, uint8_t pin)
{
  Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT,port,pin);
}


/**
 * @brief Set GPIO direction for a single GPIO pin to an output
 */
void GPIO_setAsOutput(uint8_t port, uint8_t pin)
{
  Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,port,pin);
}

/**
 * @brief Set a GPIO pin state via the GPIO byte register
 */
void GPIO_setON(uint32_t port, uint32_t pin)
{
  Chip_GPIO_SetPinState(LPC_GPIO_PORT,port,pin,1);
}

/**
 * @brief Set a GPIO port/bit to the low state
 */
void GPIO_setOFF(uint32_t port, uint32_t pin)
{
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,port,pin,0);
}


/**
 * @brief Set a GPIO port/bit to the low state
 */
void GPIO_setValue(uint32_t port, uint32_t pin, uint32_t value)
{
   Chip_GPIO_SetPinState(LPC_GPIO_PORT,port,pin,value);
}


/**
 * @brief Sets I/O Control pin mux (see scu_18xx_43xx.h)
 */
void GPIO_pinConfiguration(uint8_t port, uint8_t pin, uint16_t mode, uint8_t func)
{
  Chip_SCU_PinMuxSet(port, pin, (mode | (uint16_t) func));
}


/**
 * @brief Read a GPIO state
 */
bool GPIO_getValue(uint8_t port, uint8_t pin)
{
  return Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, port, pin );
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

