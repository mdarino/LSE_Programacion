/*************************************************************************//**

  @file     HW_display.c

  @brief    Functions to control the display

  @author   Marcos Darino (MD)


 ******************************************************************************/


/** \addtogroup HARDWARE_GROUP HARDWARE
 ** @{ */


/** \addtogroup DISPLAY_GROUP DISPLAY
 ** @{ */



/*==================[inclusions]=============================================*/

#include "EX_display.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


/**
 * @brief Convert a number to String
 * @param n   number to be converted
 * @param s   String where is copy the number 
 */

STATIC char *hidden(int n, char *s) {
    char *p;

    if(n / 10) {
        p = hidden(n / 10, s);
    }
    else {
        p = s;

    }
    *p++ = n % 10 + '0';
    *p = '\0';

    return p;

}


/**
 * @brief Convert a number to String (but only 3 dig)
 * @param n   number to be converted
 * @param s   String where is copy the number 
 */

STATIC void numberToString(int n, char *s) {

    char *p;
    int num;
    p = s+3;
    *p = '\0';
    p--;
    num=n;
    *p = (num%10) + '0';

    p--;
    num=num/10;

    *p = (num%10) + '0';

    p--;
    num=num/10;
    *p = (num%10) + '0';


}




/*==================[external functions definition]==========================*/

/**
 * 
 * @brief  Init the 16x 2 display
 */

void showHardware_Init(void)
{
	TM_HD44780_Init(16,2);
}

/**
 * 
 * @brief  Clears entire LCD
 * @param  None
 * @retval None
 */

void showTextClean(void)
{
	TM_HD44780_Clear();
}

/**
 * @brief  Puts string on lcd
 * @param  x location
 * @param  y location
 * @param  *str: pointer to string to display
 * @retval None
 */
void showText(uint8_t x, uint8_t y, char* str)
{
	TM_HD44780_Puts(x,y,str);
}


/**
 * @brief  Puts string on lcd
 * @param  x location
 * @param  y locations
 * @param  n Number to show
 * @retval None
 */
void showNumber(uint8_t x, uint8_t y, uint16_t n)
{
    char str[5]; //the max number is 65536
	numberToString(n,str); //pass the number to string
    TM_HD44780_Puts(x,y,str); //show it
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

