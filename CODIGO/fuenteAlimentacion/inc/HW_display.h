
/*************************************************************************//**

  @file     HW_display.h

  @brief    Functions to control the Display

  @author   Marcos Darino (MD)

  @version  20151124 v0.0.1   MD Initial release.
 ******************************************************************************/


#ifndef _HW_DISPLAY_H_
#define _HW_DISPLAY_H_

/** \addtogroup HARDWARE_GROUP HARDWARE
 ** @{ */


/** \addtogroup DISPLAY_GROUP DISPLAY
 ** @{ */


/*==================[inclusions]=============================================*/


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

//MENSSdAGES
//
#define TEXT_POS                  0
#define NUMBER_POS                0

#define OUTPUT_TEXT_POS           0
#define OUTPUT_TEXT_VALUE_POS     6

#define VOLTAGE_TEXT_POS          0
#define VOLTAGE_NUM_POS           3
#define CURRENT_TEXT_POS          8
#define CURRENT_NUM_POS           11
#define MSG_CONFIG_POS    		  0	

#define ROW0                      0
#define ROW1                      1

#define MSG_MENU_ROW0             "MENU -OUTPUT:OFF"
#define MSG_POWERED_ROW0          "OUTPUT:ON       "
#define MSG_OVERCURRENT_ROW0      "OVERCURRENT     "
#define MSG_VOLTAGE_READ          "V:"
#define MSG_CURRENT_READ          "A:"
#define MSG_VOLTAGE_SET           "V:"
#define MSG_CURRENT_SET           "A:"
#define MSG_CONFIG1_ROW0          "Default V  [ENT]"
#define MSG_CONFIG2_ROW0          "Default A  [ENT]"
#define MSG_CONFIG3_ROW0          "OverCurrent[Y/N]"
#define MSG_VOLTAGECONFIG_ROW0    "V:         [ENT]"
#define MSG_CURRENTCONFIG_ROW0    "Imax:      [ENT]"    
#define MSG_VOLTAGE_CONFIG		  "V:              "
#define MSG_CURRENT_CONFIG		  "A:              "	



/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
 * 
 * @brief  Init the 16x 2 display
 */
void showHardware_Init(void);



/**
 * @brief  Clears entire LCD
 * @param  None
 * @retval None
 */
void showTextClean(void);


/**
 * @brief  Puts string on lcd
 * @param  x location
 * @param  y location
 * @param  *str: pointer to string to display
 * @retval None
 */
void showText(uint8_t x, uint8_t y, char* str);


/**
 * @brief  Puts string on lcd
 * @param  x location
 * @param  y location
 * @param  n Number to show
 * @retval None
 */
void showNumber(uint8_t x, uint8_t y, uint16_t n);









/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _HW_DISPLAY_H_ */

