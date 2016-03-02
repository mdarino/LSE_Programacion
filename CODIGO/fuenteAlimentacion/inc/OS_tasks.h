/*************************************************************************//**

  @file     OS_tasks.h

  @brief    Operative System / dispacher structure required for the program
            architecture and system plataform.

  @author   Marcos Darino (MD)

  @version  20151109 v0.0.1   MD first version

 ******************************************************************************/



#ifndef _OS_TASKS_H_
#define _OS_TASKS_H_


/** \addtogroup OS_GROUP OS 
 ** @{ */

/**
 * \addtogroup TASK_GROUP Task 
 * @{
*/



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
 * @brief This task update the state of the buttons
 */
void buttons_task(void);
/**
 * @brief This task read the value of the current and check it
 *        It is simulate with a potenciometer
 */
void current_task(void);
/**
 * @brief This task read the value of the voltage
 *        It is simulate with a potenciometer
 */
void voltage_task(void);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end defgroup */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_TASKS_H_ */

