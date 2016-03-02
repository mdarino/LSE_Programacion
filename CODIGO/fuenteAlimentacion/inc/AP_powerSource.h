
/*************************************************************************//**

  @file     AP_powerSource.h

  @brief    Digital Power Sourse firmware

  @author   Marcos Darino (MD)

  @version  20151124 v0.0.1   MD Initial release.
 ******************************************************************************/




#ifndef POWERSOURCE_H
#define POWERSOURCE_H


/** \addtogroup APP_GROUP PowerSource
 ** @{ */


/** \addtogroup PS_GROUP StateMachine
 ** @{ */



/*==================[inclusions]=============================================*/
#include "stdint.h"

/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

/*==================[typedef]================================================*/


typedef uint8_t   machineStates_t; //!< Create a type to the states of the machine
typedef uint16_t  machineStateTime_t; //!< Create a type check time in the machine



#define MACHINE_OVERCURRENT_MNG_TIME  200   //!< Define how long shows OVERCURRENT menssage

#define MAX_CURRENT 500   //!< Max Current Number
#define MAX_VOLTAGE 12    //!< Max Voltage Number
#define MIN_CURRENT 0     //!< Min Current Number
#define MIN_VOLTAGE 0     //!< Min Voltage Number



typedef uint16_t voltageValues_t; //!<Create a type to all voltage variables
typedef uint16_t currentValues_t; //!<Create a type to all current variables

//!< Struct to the voltage variables
typedef struct voltage_st {   
  voltageValues_t   defaul;
  voltageValues_t   read;
  voltageValues_t   set;
  voltageValues_t   max;
}voltage_t;

//!< Struct to the current variables
typedef struct current_st {  
  currentValues_t   defaul;
  currentValues_t   read;
  currentValues_t   set;
  currentValues_t   max;
}current_t;

//!<Enumerate the states
typedef  enum states_enum { 
    standby,
    menu,
    powered,
    overCurrent,
    currentConfig,
    voltageConfig,
    onlineCurrentConfig,
    onlineVoltageConfig,
    numberOfStates
  }states_t; 


//!< Enumerate the events
typedef  enum events_enum{  
    noEvent,
    overCurrentEvent,
    numberOfEvents
  }events_t; 





/*==================[external data declaration]==============================*/
#if (CPU == mk60fx512vlq15)
/* Reset_Handler is defined in startup_MK60F15.S_CPP */
void Reset_Handler( void );

extern uint32_t __StackTop;
#elif (CPU == lpc4337)
/** \brief Reset ISR
 **
 ** ResetISR is defined in cr_startup_lpc43xx.c
 **
 ** \remark the definition is in
 **         externals/drivers/cortexM4/lpc43xx/src/cr_startup_lpc43xx.c
 **/
extern void ResetISR(void);

/** \brief Stack Top address
 **
 ** External declaration for the pointer to the stack top from the Linker Script
 **
 ** \remark only a declaration is needed, there is no definition, the address
 **         is set in the linker script:
 **         externals/base/cortexM4/lpc43xx/linker/ciaa_lpc4337.ld.
 **/
extern void _vStackTop(void);
#else
#endif

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */

/*==================[end of file]============================================*/
#endif /* #ifndef PORWERSOURCE_H */

