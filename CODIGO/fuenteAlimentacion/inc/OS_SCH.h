/* Copyright Year, Author
 *
 * This file is part of a project.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*************************************************************************//**

  @file     OS_SCH.h

  @brief    Operative System / dispacher structure required for the program
            architecture and system plataform.

  @author   Modified: Marcos Darino (MD)

  @version  20151111 v0.0.1   MD first version
  @version  20151111 v0.0.2   MD add all the function in the same files
  @version  20151117 v0.0.3   Add a easy way to add task and delay in the main loop
 ******************************************************************************/



#ifndef _OS_SCH_H_
#define _OS_SCH_H_


/** \addtogroup OS_GROUP OS
 ** @{ */

/** \addtogroup OS_FUCTION_GROUP Functions
 ** @{ */





/*==================[inclusions]=============================================*/
#include "chip.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

// The maximum number of tasks required at any one time during the execution
// of the program
// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS (3)
#define TICKRATE_HZ (1000) /* 1000 ticks per second */

/*==================[typedef]================================================*/

//MD- Os typedef
typedef int32_t timer_t;


// Store in DATA area, if possible, for rapid access
// Total memory per task is 7 bytes
typedef struct
{
   // Pointer to the task (must be a 'void (void)' function)
   void (* pTask)(void);
   // Delay (ticks) until the function will (next) be run
   // - see SCH_Add_Task() for further details
   int Delay;
   // Interval (ticks) between subsequent runs.
   // - see SCH_Add_Task() for further details
   int Period;
   // Incremented (by scheduler) when task is due to execute
   int RunMe;
} sTask;

/*==================[external data declaration]==============================*/

//MD - Os counter
volatile timer_t os_time_counter; ///OS counter

/*==================[external functions declaration]=========================*/

void SCH_Init(void);
void SCH_Start(void);
void SCH_Update(void);

void SCH_Dispatch_Tasks(void);
char SCH_Add_Task(void (*) (void), const int, const int);
char SCH_Delete_Task(const int);
void SCH_Report_Status(void);


// MD -  OS Functions

/**
 * @brief Initialice OS module (variable and peripheral initial values)
 */

void OS_Init(void); //clean the "os_time_counter"
/**
 * @brief Principal Task function from OS module.
 *        It must be called continuosly from the main loop.
 */
void OS_Task(void);

/**
 * @brief Update the OS global counter.
 */
void OS_Ticks(void);//increment "os_time_counter" in 1

/**
 * @brief Start Periodic 1mS System Timer
 * @param delay_in_ticks charge timer ticks to be counted
 * @return nowcopy = system TimerTick Counter
 */
timer_t OS_TimerStart(timer_t delay_in_ticks); //actual tick "os_time" + "delay_in_ticks"
/**
 * @brief Verify if a timer has run timeout
 * @param timer_val timer to check for expiration
 * @return 1 = timer expired!
 */
timer_t OS_TimerExpired(timer_t timer_inst);//check if "os_time_counter" >= "timer_inst"
   
/**
 * @brief Wait the specified time. Valid for delays smaller than 32 seconds
 * @param delay_in_ms time to wait in miliseconds
 */
void  OS_Delay(timer_t delay);    

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end defgroup */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_SCH_H_ */
