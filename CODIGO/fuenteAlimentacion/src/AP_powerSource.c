/*************************************************************************//**

  @file     AP_powerSource.c

  @brief    Digital Power Sourse firmware

  @author   Marcos Darino (MD)

 ******************************************************************************/


/**
\mainpage The mainpage documentation

This project is for the LSE - It is a power source firmware.
*/


/** \addtogroup APP_GROUP PowerSource
 ** @{ */


/** \addtogroup PS_GROUP StateMachine
 ** @{ */



/*==================[inclusions]=============================================*/

#include "AP_powerSource.h"       /* <= own header */

#include "HW_leds.h"    /* <= Hardware LEDS */
#include "HW_buttons.h"   /* <= Hardware Buttons */
#include "HW_display.h"   /* <= Hardware display */
#include "HW_backLight.h"   /* <= Hardware backlight */
#include "HW_potenciometer.h"   /* <= Hardware potenciometer */


#include "OS_SCH.h" /* <= Operative System */
#include "OS_tasks.h" /* <= Tasks System */




/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/


/*==================[external data definition]===============================*/


  
  button_t buttonOnOff; //!< Global Struct to Control the buttons OnOff.
  button_t buttonBack;  //!< Global Struct to Control the buttons Back.
  button_t buttonDown;  //!< Global Struct to Control the buttons Down.
  button_t buttonEnter; //!< Global Struct to Control the buttons Enter.
  button_t buttonUp;    //!< Global Struct to Control the buttons Up.

  
  pote_t poteCurrent; //!< Global Struct to Control the potenciometer of the current.
  pote_t poteVoltage; //!< Global Struct to Control the potenciometer of the voltage.

  
  events_t events; //!< Storage the value of the events

 
  voltage_t  voltage;  //!< Struct to control the voltage variables
  current_t  current;  //!< Struct to control the current variables


  
  machineStates_t     enterAction=TRUE;  //!< EnterAction, it use to do and enteraction when change the state
  machineStateTime_t  machineStateTime=0; //!< It use to control time in a state
  states_t machineState=standby; //!< Storage the state of the machine
  states_t lastState=standby; //!< Storage the last state to know when state change



/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/*==================[external functions definition]==========================*/


/**
 * @brief Initializes all the Hardwares modules
 */
void hardware_init(void)
{
  //button1 CIAA -> ENTER AND ONOFF
  
  buttonConstructor(&buttonEnter,0,4);
  buttonInitWithoutPullUp(&buttonEnter,1,0,FUNC0);
  
  //button2 CIAA -> UP

  buttonConstructor(&buttonUp,0,8);
  buttonInitWithoutPullUp(&buttonUp,1,1,FUNC0);
 
  //button3 CIAA -> DOWN

  buttonConstructor(&buttonDown,0,9);
  buttonInitWithoutPullUp(&buttonDown,1,2,FUNC0);
  
  //button4 CIAA -> BACK

  buttonConstructor(&buttonBack,1,9);
  buttonInitWithoutPullUp(&buttonBack,1,6,FUNC0);
  

  //switch ON OFF

  buttonConstructor(&buttonOnOff,2,0);
  buttonInitWithoutPullUp(&buttonOnOff,4,0,FUNC0);

  //Init the four LEDs of the CIAA
  led_Init();
    
  //Init the three LEDS of the backlight
  backlight_Init();

  //Init the Display
  showHardware_Init();

  //Init the Relay
    //relay_Init();

  //Init the potenciometer
  poteConstructor(&poteCurrent);
  poteInit(&poteCurrent,2);
  poteConstructor(&poteVoltage);
  poteInit(&poteVoltage,1);

}

/**
 * @brief Initializes all the drivers modules
 */
void drivers_init(void)
{

  //System clock
  SystemCoreClockUpdate();
  //ADC to simulate the current and voltage
  Analog_Init();
  //Make the voltage out

}

/**
 * @brief Initializes the Drivers - OS system - Hardware - Add the tasks 
 */

void boardInit(void) {

  //Init all the drivers
  drivers_init();
   
  // Init the OS
   SCH_Init();
   OS_Init();

    // Start the OS
   SCH_Start();

   //Init all the hardware
   hardware_init();
   

   // Add the tasks
   
  SCH_Add_Task(buttons_task, 0, 10); //!< Add the task to control the buttons 
  SCH_Add_Task(current_task, 0, 5); //!< Add the task to control the current
  SCH_Add_Task(voltage_task, 0, 10); //!< Add the task to control the voltage

   }


/**
 * @brief Check if there is a change in the machine state, 
 * It use to update the "enter action" and update the time.  
 * @return true if there is a change, other False
 */

uint8_t machine_changes(void)
{
  
  uint8_t newChanges; //save if there is a new change
  if (lastState==machineState) //Check
  {
      newChanges=FALSE;
  }
  else
  {
      newChanges=TRUE;
      machineStateTime=0; //reset the timer (check how much time is in the state)
      lastState=machineState; //update the the last state
  }
  return newChanges;

}

//--------------------------------------------------//
//-----------------MAIN FUNCTION--------------------//
//--------------------------------------------------//

int main(void)
{

  //Init Driver-Hardware-OS
  boardInit();

  //Varialbe to control the refesh of the display
  uint16_t DisplayRef=0;
  
  //Set the Max value of the current and the voltage
  voltage.max=MAX_VOLTAGE;
  current.max=MAX_CURRENT;

  //timer of the machine state (using the OS in the Main)
  timer_t  machineTimer=0;


//--------------------------------------------------//
//-----------------INFINETE WHILE-------------------//
//--------------------------------------------------//

  while(1)  
  {


    //Check if there is an event - for this case, only check overcurrent
    if(events==overCurrentEvent)
      {
        //If the event overcurrent arrival, only if we are simulating
        //the current with a pote, we need to check if the machine is in a powered state 
        //If we not are simulating, the relay open the circuit and the current is zero
        if (machineState==powered || machineState==onlineCurrentConfig || machineState==onlineVoltageConfig)
          //If there is an overcurrent event
          //change the machine state to overcurrent
          //and open the output relay
          machineState=overCurrent;
          led_SetOFF(LED_RELAY); 
      }

    //Check if the on off switch is ON  
    if(buttonGetState(&buttonOnOff)==RELEASE)
      {
          //If release, change the state to standby
          machineState=standby; 
      } 

  //Check if the OS machine Timer is compliment    
  if(OS_TimerExpired(machineTimer))
  {    

    //Run the machine switch case
    switch (machineState) 
    {
      case standby:
        //--Enter action--//
          if (enterAction==TRUE)   //enter action check if it is the first time in the state
          {
              showTextClean();        //Clean the display
              led_SetON(LED_ONOFF);   //It indicates it is in standby
              led_SetOFF(LED_OUTPUT); //Output LED off
              led_SetOFF(LED_CURRENT);//OverCurrent LED is OFF
              //All of the backlight LED off
              backlight_SetOFF(BACKLIGHT_RED); 
              backlight_SetOFF(BACKLIGHT_GREEN);
              backlight_SetOFF(BACKLIGHT_BLUE);
        
              // //Voltage and current set the defaul values
              //Must be store in the EPROM - pending for the next versions
              voltage.defaul=5;
              current.defaul=350;

              //Set the defaul values
              voltage.set=voltage.defaul; 
              current.set=current.defaul;
          }
        //--Run action--//
              //Check the on off button if it is press jump to menu state
              if(buttonGetState(&buttonOnOff)==PRESS)
              {
                 machineState=menu; 
                 
              } 
        //--Exit action--//
          //Nothing
      break;

      case menu:
        //--Enter action--//
          if (enterAction==TRUE)
          {      
            
            //Update the LEDs
            led_SetOFF(LED_ONOFF);   
            led_SetOFF(LED_OUTPUT);
            led_SetOFF(LED_CURRENT);
            //Update the Relay (simulate with a LED)
            led_SetOFF(LED_RELAY);
            //Set the backlight BLUE
            backlight_SetOFF(BACKLIGHT_RED);
            backlight_SetOFF(BACKLIGHT_GREEN);
            backlight_SetON(BACKLIGHT_BLUE);

            //First ROW menssage - see defines in HW_display.h
            showText(TEXT_POS,ROW0,MSG_MENU_ROW0);
            //Show Voltage and Current (set voltage)
            showText(VOLTAGE_TEXT_POS,ROW1,MSG_VOLTAGE_SET);
            showNumber(VOLTAGE_NUM_POS,ROW1,voltage.set);
            showText(CURRENT_TEXT_POS,ROW1,MSG_CURRENT_SET);
            showNumber(CURRENT_NUM_POS,ROW1,current.set);
            
          }

    //--Run action--//
          //Check all the button, the button define the next state
          if(buttonGetStateWithRl(&buttonEnter)==PRESS)
          {
             //if the button Enter is press, jump to powered state
             machineState=powered;
          }

          if (buttonGetStateWithRl(&buttonUp)==PRESS)
          {
              //if the button up is press, jump to voltage config state
              machineState=voltageConfig;
          }

          if (buttonGetStateWithRl(&buttonDown)==PRESS)
          {
              //if the button down is press, jump to current config state
              machineState=currentConfig;
          }

  
    //--Exit action--//
      //Nothing      break;      
       break;
              

  case powered:
    //--Enter action--//
      if (enterAction==TRUE)
      {

          //Update the LEDs
          led_SetOFF(LED_ONOFF);   
          led_SetON(LED_OUTPUT);
          led_SetOFF(LED_CURRENT);
          //Update the Relay (simulate with a LED)
          led_SetON(LED_RELAY);
          //Set the backlight GREEN (everything is OK)
          backlight_SetOFF(BACKLIGHT_RED);
          backlight_SetON(BACKLIGHT_GREEN);
          backlight_SetOFF(BACKLIGHT_BLUE);
          //Show the text, just once
          showText(TEXT_POS,ROW0,MSG_POWERED_ROW0); //show the first row menssage
          showText(VOLTAGE_TEXT_POS,ROW1,MSG_VOLTAGE_READ);
          showText(CURRENT_TEXT_POS,ROW1,MSG_CURRENT_READ);

      }

    //--Run action--//
      //show the read value - the value is update in the task
      //current_task and voltage_task
               if (DisplayRef==0)
              {
                  showNumber(VOLTAGE_NUM_POS,ROW1,voltage.read);
                  showNumber(CURRENT_NUM_POS,ROW1,current.read);
              }


      //Check all the button, the button define the next state
      if (buttonGetStateWithRl(&buttonEnter)==PRESS)
      {
          //if the button Enter is press, jump to menu state
          machineState=menu;
      }

      if (buttonGetStateWithRl(&buttonUp)==PRESS)
      {
          //if the button up is press, jump to online Voltage Config state
          machineState=onlineVoltageConfig;
      }

      if (buttonGetStateWithRl(&buttonDown)==PRESS)
      {
          //if the button down is press, jump to online Current Config state
          machineState=onlineCurrentConfig;
      }

      if (buttonGetStateWithRl(&buttonBack)==PRESS)
      {
          //if the button back is press, jump to menu state
          machineState=menu;
      }

    //--Exit action--//
    //  Nothing
  break;

  case overCurrent:
    //--Enter action--//
      if (enterAction==TRUE)
      {      
        //Update the LEDs
        led_SetOFF(LED_ONOFF);   //indicate stanby
        led_SetOFF(LED_OUTPUT);
        led_SetON(LED_CURRENT);
        //Turn OFF the Relay (simulate with a LED)
        led_SetOFF(LED_RELAY);
        //Set the backlight RED (ahh there's a problem)
        backlight_SetON(BACKLIGHT_RED);
        backlight_SetOFF(BACKLIGHT_GREEN);
        backlight_SetOFF(BACKLIGHT_BLUE);
        //Show the overcurrent problem
        showText(TEXT_POS,ROW0,MSG_OVERCURRENT_ROW0);
      }
    //--Run action--//
      //Delay to show the menssage of overcurrent, then jump to menu
      machineStateTime++;
      if (machineStateTime>=MACHINE_OVERCURRENT_MNG_TIME)
        {
          machineState=menu;      
        }       
    //--Exit action--//
        //Nothing
  break;


case currentConfig:
    //--Enter action--//
      if (enterAction==TRUE)
      { 
        //Show the menssage in the first row
        showText(MSG_CONFIG_POS,ROW0,MSG_CURRENT_CONFIG);
      }
    //--Run action--//
      
      //check if it is the time to refresh - to avoid update continuously
      if (DisplayRef==0)
      {
        showNumber(CURRENT_NUM_POS,ROW0,current.set);
      }

      //Check the button
      if (buttonGetStateWithRl(&buttonUp)==PRESS)
      {
          //if the button up is press
          if (current.set<MAX_CURRENT)
          {
            //And it is not the max, increase
            current.set++;
          }

      }

      if (buttonGetStateWithRl(&buttonDown)==PRESS)
      {
          //if the button down is press
          if (current.set>MIN_CURRENT)
          {
            //And it is not the min, decrement
            current.set--;
          }
      }

      if (buttonGetStateWithRl(&buttonBack)==PRESS)
      {
           //if the button back is press, jump to menu state
          machineState=menu;
      }

      
      if (buttonGetStateWithRl(&buttonEnter)==PRESS)
      {
          //if the button enter is press, jump to powered state
          machineState=powered;
      }
    
    //--Exit action--//
  break;
  
  case voltageConfig:
    //--Enter action--//
    if (enterAction==TRUE)
      { 
        //Show the menssage in the first row
        showText(MSG_CONFIG_POS,ROW0,MSG_VOLTAGE_CONFIG);
      }
    //--Run action--//
      //check if it is the time to refresh - to avoid update continuously
      if (DisplayRef==0)
          {
            showNumber(VOLTAGE_NUM_POS,ROW0,voltage.set);
          }
      if (buttonGetStateWithRl(&buttonUp)==PRESS)
      {
          //And it is not the max, increase
          if (voltage.set<MAX_VOLTAGE)
          {
            voltage.set++;
          }

      }
      //Check the button
      
      if (buttonGetStateWithRl(&buttonDown)==PRESS)
      {
          //if the button down is press
          if (voltage.set>MIN_VOLTAGE)
          {
            //And it is not the min, decrement
            voltage.set--;
          }
      }

      if (buttonGetStateWithRl(&buttonBack)==PRESS)
      {
           //if the button back is press, jump to menu state
          machineState=menu;
      }
      
      if (buttonGetStateWithRl(&buttonEnter)==PRESS)
      {
           //if the button enter is press, jump to powered state
          machineState=powered;
      }              
    //--Exit action--//

  break;

  case onlineCurrentConfig:
    //--Enter action--//
    if (enterAction==TRUE)
      { 
        //Show the menssage in the first row
        showText(MSG_CONFIG_POS,ROW0,MSG_CURRENT_CONFIG);
        //Show the menssage in the second row
        showText(VOLTAGE_TEXT_POS,ROW1,MSG_VOLTAGE_READ);
        showText(CURRENT_TEXT_POS,ROW1,MSG_CURRENT_READ);
      }    
    //--Run action--//
      //check if it is the time to refresh - to avoid update continuously
      if (DisplayRef==0)
      {
        showNumber(CURRENT_NUM_POS,ROW0,current.set);
        showNumber(VOLTAGE_NUM_POS,ROW1,voltage.read);
        showNumber(CURRENT_NUM_POS,ROW1,current.read);
      }

      //Check the button

      if (buttonGetStateWithRl(&buttonUp)==PRESS)
      {
          //if the button up is press
          if (current.set<MAX_CURRENT)
          {
            //And it is not the max, increase
            current.set++;
          }

      }

      if (buttonGetStateWithRl(&buttonDown)==PRESS)
      {
          //if the button down is press
          if (current.set>MIN_CURRENT)
          {
            //And it is not the min, decrement
            current.set--;
          }
      }

      if (buttonGetStateWithRl(&buttonBack)==PRESS)
      {
           //if the button back is press, jump to powered state
          machineState=powered;
      }

      
      if (buttonGetStateWithRl(&buttonEnter)==PRESS)
      {
           //if the button enter is press, jump to menu state
          machineState=menu;
      }

      
      //currentSetvalue(voltage.set);
      //--Exit action--//



  break;

  case onlineVoltageConfig:
    //--Enter action--//
    if (enterAction==TRUE)
      { 
        //Show the menssage in the first row
        showText(MSG_CONFIG_POS,ROW0,MSG_VOLTAGE_CONFIG);
        //Show the menssage in the second row
        showText(VOLTAGE_TEXT_POS,ROW1,MSG_VOLTAGE_READ);  
        showText(CURRENT_TEXT_POS,ROW1,MSG_CURRENT_READ);
      }    
    //--Run action--//
      //check if it is the time to refresh - to avoid update continuously
      if (DisplayRef==0)
      {
        showNumber(VOLTAGE_NUM_POS,ROW0,voltage.set);
        showNumber(VOLTAGE_NUM_POS,ROW1,voltage.read);
        showNumber(CURRENT_NUM_POS,ROW1,current.read);
      }
    
      //Check the button

      if (buttonGetStateWithRl(&buttonUp)==PRESS)
      {
          //if the button up is press
          if (voltage.set<MAX_VOLTAGE)
          {
            //And it is not the max, increase
            voltage.set++;
          }

      }

      if (buttonGetStateWithRl(&buttonDown)==PRESS)
      {
          //if the button down is press
          if (voltage.set>MIN_VOLTAGE)
          {
            //And it is not the min, decrement
            voltage.set--;
          }
      }

      if (buttonGetStateWithRl(&buttonBack)==PRESS)
      {
          //if the button back is press, jump to powered state
          machineState=powered;
      }
      
      if (buttonGetStateWithRl(&buttonEnter)==PRESS)
      {
          //if the button enter is press, jump to menu state
          machineState=menu;
      }

      //voltageSetvalue(voltage.set);          
    //--Exit action--//

  break;

      //DEFAUL OPTION
      default:
      break;
    }//close switch - End of the machine state
    

    //Update the display refresh  variable
    DisplayRef++;
    if (DisplayRef>=10)
    {
      //if the variable is cero, update the value in the machine
      DisplayRef=0; 
    }

    //Check the laststate and the current state
    //if there are a difference, enterAction is TRUE
    enterAction = machine_changes();
    //Update the timer of the machine state 20mseg
    machineTimer=OS_TimerStart(20);
  } //end os timer for the machine state
    
  }  //Close the while(1)
   return 0;
} //Close main

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

