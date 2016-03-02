
/*************************************************************************//**

  @file     DRIVER_ADC.c

  @brief    Driver to use the ADC

  @author   Pablo Llull (PL)  &  Marcos Darino (MD)

 ******************************************************************************/


/** \addtogroup DRIVERS_GROUP DRIVERS
 ** @{ */


/** \addtogroup ADC_GROUP ADC
 ** @{ */





/*==================[inclusions]=============================================*/
#include "DRIVER_ADC.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/


/**
 * @brief Initialize the ADC and setup structure to default value
 * @param setup  : ADC setup structure to be set
 * @return  Nothing
 */
STATIC void ADC_init(ADC_CLOCK_SETUP_T *setup)
{
  Chip_ADC_Init(LPC_ADC0,setup);  
}
/**
 * @brief Enable burst mode
 * @param newState : 
 * @return  Nothing
 */
STATIC void ADC_setBurst(FunctionalState newState)
{
  Chip_ADC_SetBurstCmd(LPC_ADC0,newState);
}

/**
 * @brief Enable or disable the ADC channel
 * @param channel  : Channel to be enable or disable
 * @param newState : New state, ENABLE or DISABLE
 * @return  Nothing
 */
STATIC void ADC_setChannel(ADC_CHANNEL_T channel, FunctionalState newState)
{
  Chip_ADC_EnableChannel(LPC_ADC0, channel, newState);
}

/**
 * @brief Enable or Disable interrupt for ADC channel
 * @param channel  : Channel to be enable or disable
 * @param newState : New state, ENABLE or DISABLE
 */
STATIC void ADC_setIntChannel(ADC_CHANNEL_T channel, FunctionalState newState)
{
  Chip_ADC_Int_SetChannelCmd(LPC_ADC0, channel, newState);
}

/**
 * @brief Select the mode starting the AD conversion
 * @param mode  : Stating mode, should be :
 *              - ADC_NO_START        : Must be set for Burst mode
 *              - ADC_START_NOW       : Start conversion now
 *              - ADC_START_ON_CTOUT15    : Start conversion when the edge selected by bit 27 occurs on CTOUT_15
 *              - ADC_START_ON_CTOUT8   : Start conversion when the edge selected by bit 27 occurs on CTOUT_8
 *              - ADC_START_ON_ADCTRIG0   : Start conversion when the edge selected by bit 27 occurs on ADCTRIG0
 *              - ADC_START_ON_ADCTRIG1   : Start conversion when the edge selected by bit 27 occurs on ADCTRIG1
 *              - ADC_START_ON_MCOA2    : Start conversion when the edge selected by bit 27 occurs on Motocon PWM output MCOA2
 * @param EdgeOption : Stating Edge Condition, should be :
 *              - ADC_TRIGGERMODE_RISING  : Trigger event on rising edge
 *              - ADC_TRIGGERMODE_FALLING : Trigger event on falling edge
 * @return  Nothing
 */
STATIC void ADC_setStartMode(ADC_START_MODE_T mode, ADC_EDGE_CFG_T edgeOption)
{
  Chip_ADC_SetStartMode(LPC_ADC0, mode, edgeOption);
}

/**
 * @brief Get ADC Channel status from ADC data register
 * @param channel    : ADC channel to read
 * @param statusType : Status type of ADC_DR_*
 * @return  SET or RESET
 */
STATIC FlagStatus ADC_getChannelStatus(uint8_t channel, uint32_t statusType)
{
  return Chip_ADC_ReadStatus(LPC_ADC0, channel, statusType);
}

/**
 * @brief Get the ADC value
 * @param  channel : ADC channel to read
 * @param  data    : Pointer to where to put data
 * @return SUCCESS or ERROR if no conversion is ready
 */
STATIC Status ADC_getValue(uint8_t channel, uint16_t *data)
{
  return Chip_ADC_ReadValue(LPC_ADC0 , channel, data);
}


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/**
 * @brief Init the Analog ADC
 */
void Analog_Init(void){
   ADC_CLOCK_SETUP_T ADCSetup;

   /*
    * Chip_ADC_Init inicializa el periférico ADC (el LPC4337 tiene: LPC_ADC0 y 1)
    * Chip_ADC_EnableChannel habilita un canal del ADC (el LPC4337 tiene: ADC_CH1, 2 y 3)
    */

   /*Configuro los pines correspondientes a los canales de ADC*/

   /* Habilito el ADC0 */
   ADC_init(&ADCSetup);
   ADC_setBurst(DISABLE);

   ADC_setChannel(ADC_CH1,DISABLE);
   ADC_setIntChannel(ADC_CH1,DISABLE);
   ADC_setChannel(ADC_CH2,DISABLE);
   ADC_setIntChannel(ADC_CH2,DISABLE);  
   ADC_setChannel(ADC_CH3,DISABLE);
   ADC_setIntChannel(ADC_CH3,DISABLE);       
}


/**
 * @brief Get the ADC value
 */
int16_t Analog_Read(int32_t channel){

   uint16_t adcVal=0;

   ADC_setChannel(channel,ENABLE);
   ADC_setStartMode(ADC_START_NOW, ADC_TRIGGERMODE_RISING);

   while((ADC_getChannelStatus(channel , ADC_DR_DONE_STAT) != SET));
   ADC_getValue(channel, &adcVal);

   ADC_setChannel(channel,DISABLE);

   return (int16_t)adcVal;
}


