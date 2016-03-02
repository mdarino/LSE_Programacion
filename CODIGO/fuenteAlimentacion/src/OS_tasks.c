/*************************************************************************//**

  @file     OS_tasks.c

  @brief    Operative System / dispacher structure required for the program
            architecture and system plataform.

  @author   Marcos Darino (MD)

  @version  20151109 v0.0.1   MD first version

 ******************************************************************************/


/** \addtogroup OS_GROUP OS 
 ** @{ */

/**
 * \addtogroup TASK_GROUP Task 
 * @{
*/




/*==================[inclusions]=============================================*/


#include "OS_tasks.h"

#include "DRIVER_ADC.h" 

#include "HW_buttons.h"
#include "HW_potenciometer.h"
#include "HW_leds.h"

#include "AP_powerSource.h" 
/*==================[macros and definitions]=================================*/
 
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/


//Global buttons variables
extern   button_t buttonOnOff;
extern   button_t buttonBack;
extern   button_t buttonDown;
extern   button_t buttonEnter;
extern   button_t buttonUp;

//Global potenciometer variables
extern   pote_t poteCurrent;
extern   pote_t poteVoltage;

//Global events variables
extern    events_t events;

//Global Voltage/Current variables
extern    voltage_t  voltage;
extern    current_t  current;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/





//--Buttons Task--//
//This task update the state of the buttons
void buttons_task(void)
{
  buttonUpdate(&buttonEnter);
  buttonUpdate(&buttonUp);
  buttonUpdate(&buttonDown);
  buttonUpdate(&buttonBack);
  buttonUpdate(&buttonOnOff);

}

//--Current Task--//
//This task read the value and check this value
////It is simulate with a potenciometer
void current_task(void)
{
  //mensure the current value
  uint16_t countToTest;
  uint16_t adcValue=0;  

  poteUpdate(&poteCurrent);

  if (poteGetstate(&poteCurrent)==READY)
    {
      adcValue=poteGetValue(&poteCurrent);
      countToTest=current.set*(1023/current.max);
      current.read=adcValue/(1023/current.max);

      if (adcValue>=countToTest)
      {
        events=overCurrentEvent;
      }
      else
      {
        events=noEvent;
      }


    }


}

//--Voltage Task--//
//This task read the value of the voltage
//It is simulate with a potenciometer
void voltage_task(void)
{
  //mensure the current value
  uint16_t adcValue=0;  

  poteUpdate(&poteVoltage);

  if (poteGetstate(&poteVoltage)==READY)
    {
      adcValue=poteGetValue(&poteVoltage);
      voltage.read=adcValue/(1023/voltage.max);
    }

}
///-------------------///




/** @} doxygen end group definition */
/*==================[end of file]============================================*/

