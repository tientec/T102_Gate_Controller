/*******************************************************************************
********************************************************************************
* File Name          : sys.c
* Author             : Tomasz Nowak
* Version            : V1.00a
* Date               : 27/01/2012
* Description        : System functions handling
********************************************************************************
*******************************************************************************/


/*******************************************************************************
* Header Files
*******************************************************************************/
#include  "includes.h"


/*******************************************************************************
* Local Preprocessor #define Constants
*******************************************************************************/


/*******************************************************************************
* Local Preprocessor #define MACROS
*******************************************************************************/


/*******************************************************************************
* Local Type Declarations
*******************************************************************************/

/*******************************************************************************
* Exported Const Object Definitions
*******************************************************************************/


/*******************************************************************************
* Local Object Definitions
*******************************************************************************/
_Timers System_Timers;

_System_Timers Inputs_Timer;
_System_Timers Keyboard_Timer;
_System_Timers Startup_Timer;
_System_Timers Screen_Reload_Timer;
_System_Timers Temperature_Timer;
_System_Timers RS485_Timer;

_System_Timers Pulse_OC1_Timer;
_System_Timers Pulse_OC2_Timer;
_System_Timers Pulse_RL1_Timer;
_System_Timers Pulse_RL2_Timer;
_System_Timers Pulse_RL3_Timer;
_System_Timers Pulse_RL4_Timer;
_System_Timers Pulse_RL5_Timer;
_System_Timers Pulse_RL6_Timer;

_Keyboard Keyboard;
_Keyboard Inputs;

volatile uint32_t Interval;
volatile uint32_t Interval_Sec;
volatile uint32_t Inputs_Level = 0;
volatile uint32_t Inputs_Level_Test = 0;

uint8_t Keyboards_Level = 0;

uint8_t Keyboard_Inputs_Select_Counter = 0;
uint8_t Keyboard_Inputs_Select_Counter1 = 0;

uint16_t Crc_value;
uint16_t Crc_check;
uint16_t Crc_received;
bool INV_PROGRAMMING = TRUE;

bool ADC_MEASURED = FALSE;

_Uart_Packet Uart_Tx_Packet;
_Uart_Packet Uart_Rx_Packet;

/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/


/*******************************************************************************
* Local Inline Function Definitions and Function-Like Macros
*******************************************************************************/


/*******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
* Function Name  : Sys_Init
* Description    : System initialization
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Sys_Init ( void )
{
    Manual_Values.Values.Mos1_Manual_Value = 0;
    Manual_Values.Values.Mos2_Manual_Value = 0;

	System_Timer_Setting ( &Startup_Timer.Timer, STARTUP_TIME, T_10msec );
	while ( System_Timer_Check ( &Startup_Timer.Timer, T_10msec ) == FALSE );
	System_Timer_Setting ( &Keyboard_Timer.Timer, KBD_SAMPLE_TIME, T_10msec );
    System_Timer_Setting ( &Inputs_Timer.Timer, INPUTS_SAMPLE_TIME, T_10msec );
    System_Timer_Setting ( &Screen_Reload_Timer.Timer, SCREEN_RELOAD_TIME, T_10msec );
    System_Timer_Setting ( &Temperature_Timer.Timer, T_SAMPLE_TIME, T_10msec );
 
    System_Timer_Setting ( &Pulse_OC1_Timer.Timer, PULSE_TIME, T_10msec );
    System_Timer_Setting ( &Pulse_OC2_Timer.Timer, PULSE_TIME, T_10msec );
    System_Timer_Setting ( &Pulse_RL1_Timer.Timer, PULSE_TIME, T_10msec );
    System_Timer_Setting ( &Pulse_RL2_Timer.Timer, PULSE_TIME, T_10msec );
    System_Timer_Setting ( &Pulse_RL3_Timer.Timer, PULSE_TIME, T_10msec );
    System_Timer_Setting ( &Pulse_RL4_Timer.Timer, PULSE_TIME, T_10msec );
    System_Timer_Setting ( &Pulse_RL5_Timer.Timer, PULSE_TIME, T_10msec );
    System_Timer_Setting ( &Pulse_RL6_Timer.Timer, PULSE_TIME, T_10msec );
    System_Timer_Setting ( &RS485_Timer.Timer, 40, T_10msec );
    System_Timer_Setting ( &Lamp_Timer.Timer, 100, T_10msec );

    if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_ZABLOKOWANY )
    {
        Machine_State = SW_LOCKED;
    }
    else if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_BLOKADA_CALKOWITA )
    {
        Machine_State = SW_LOCKED;    
    }
    else
    {
        if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
        {
            if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//Two wings gate
            {
                Controller_Variables.Controller_Vars.Inputs_Error = F1_DISCONNECTED | F2_DISCONNECTED;
            }
            else//one wing gate
            {
                Controller_Variables.Controller_Vars.Inputs_Error = F1_DISCONNECTED;
            }
        
            Machine_State = INVERTER_PROG;
        }
        else if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 ) // 24V sliding gate
        {
            Machine_State = WG_POWER_ON;
        }    
/*
        if ( Controlling_Variables.Ctrl_Vars.Way_Learned == 0 )
        {
            Controller_Variables.Controller_Vars.Controller_Status = STATUS_LEARNING_WAY;
            Machine_State = WAIT_4_LEARN;
        }
        else
        {
            Controller_Variables.Controller_Vars.Controller_Status = STATUS_POWER_ON;
            Machine_State = POWER_ON;              
        }
*/
    }

    Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_POWER_ON;

}

/*******************************************************************************
* Function Name  : Sys_sys
* Description    : System functions handling
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Sys_sys ( void )
{
    Controller_Variables.Controller_Vars.Machine_State_Var = (uint16_t)Machine_State;

    AS5040_Angle_Handling();
    Analog_Measure();
    Keyboard_Handling();
    Inputs_Handling();
    RTC_Handler();
    WWDT_Handler();
    Inputs_Alert();
    Inputs_Stop();
    Motors_Enable_Fun();
    RS485_Send();
    Motor_24VDC_handling();
    Status_Handling();


    PULSE_LAMP_FLAG = Square_Generator ( &Lamp_Timer.Timer, Service_Variables.Serv_Vars.Serwis_021, T_10msec );

    Manual_Values.Values.RL1_Manual_Value = Relays_Handling(Service_Variables.Serv_Vars.Out1_Fun);
    Manual_Values.Values.RL2_Manual_Value = Relays_Handling(Service_Variables.Serv_Vars.Out2_Fun);
    Manual_Values.Values.RL3_Manual_Value = Relays_Handling(Service_Variables.Serv_Vars.Out3_Fun);
    Manual_Values.Values.RL4_Manual_Value = Relays_Handling(Service_Variables.Serv_Vars.Out4_Fun);
    Manual_Values.Values.RL5_Manual_Value = Relays_Handling(Service_Variables.Serv_Vars.Out5_Fun);
    Manual_Values.Values.RL6_Manual_Value = Relays_Handling(Service_Variables.Serv_Vars.Out6_Fun);
}

/*******************************************************************************
* Function Name  : System_Timer_Setting
* Description    : Setting timer to count to programmed value
* Input1         : Timer_Counter - pointer to 16 bit register
* Input2         : Time_Value - Set time interval to count
* Input3         : Enable_Flag - pointer to BOOL variable
* Input4         : Sys_Tmr_Intervals - base time interval
* Output         : None
* Return         : None
*******************************************************************************/
void System_Timer_Setting ( uint32_t * Timer_Counter, uint16_t Time_Value, _Sys_Tmr_Intervals Sys_Tmr_Intervals )
{
	*Timer_Counter = System_Timers.Time_Table[Sys_Tmr_Intervals] + Time_Value;
}

/*******************************************************************************
* Function Name  : System_Timer_Check
* Description    : Checking if programed timer has reached programmed value
* Input1         : Timer_Counter - pointer to 16 bit register
* Input2         : Enable_Flag - pointer to BOOL variable
* Input3         : Sys_Tmr_Intervals - base time interval
* Output         : None
* Return         : TRUE - Time match / FALSE Time no match
*******************************************************************************/
uint8_t System_Timer_Check ( uint32_t * Timer_Counter, _Sys_Tmr_Intervals Sys_Tmr_Intervals )
{
		if ( *Timer_Counter == System_Timers.Time_Table[Sys_Tmr_Intervals] )
		{
			return TRUE;	
		}
		else
		{
			return FALSE;
		}
}


/*******************************************************************************
* Function Name  : Square_Generator
* Description    : Checking if programed timer has reached programmed value
* Input1         : Timer_Counter - pointer to 16 bit register
* Input2         : Enable_Flag - pointer to BOOL variable
* Input3         : Sys_Tmr_Intervals - base time interval
* Output         : None
* Return         : TRUE - Time match / FALSE Time no match
*******************************************************************************/
uint8_t Square_Generator ( uint32_t * Timer_Counter, uint16_t Time_Value, _Sys_Tmr_Intervals Sys_Tmr_Intervals )
{
    static bool Flag;

    if ( *Timer_Counter == System_Timers.Time_Table[Sys_Tmr_Intervals] )
    {
        if ( Flag == TRUE )
        {
            *Timer_Counter = System_Timers.Time_Table[Sys_Tmr_Intervals] + Time_Value;
            Flag =  FALSE;	    
        }
        else
        {
        	*Timer_Counter = System_Timers.Time_Table[Sys_Tmr_Intervals] + Time_Value;
            Flag = TRUE;       
        }
    }
    return Flag;
}
/*******************************************************************************
* Function Name  : Keyboard_Handling
* Description    : Checking the keys
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Keyboard_Handling ( void )
{
	if ( System_Timer_Check ( &Keyboard_Timer.Timer, T_10msec ) == TRUE )
	{    
        if ( Keyboard.Keyboard_Memory == 0 && Keyboard.Keyboard_Flag == 0 )
        {
            switch ( Keyboard_Inputs_Select_Counter )
            {       
            case 0:
                if ( !(GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN)) )
                {
                    Keyboards_Level |= KEY_ESCAPE;
                    Keyboard.Keyboard_Memory |= KEY_ESCAPE;
                    Keyboard.Keyboard_Flag = 1;
                } 
                else
                {
                    Keyboards_Level &= ~KEY_ESCAPE;                
                }
            break;
        
            case 2:
                if ( !(GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN)) )
                {
                    Keyboards_Level |= KEY_TEST;
                    Keyboard.Keyboard_Memory |= KEY_TEST;
                    Keyboard.Keyboard_Flag = 1;
                }
                else
                {
                    Keyboards_Level &= ~KEY_TEST;                
                }            
            break;  

            case 3:
                if ( !(GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN)) )
                {
                    Keyboards_Level |= KEY_DOWN;               
                    Keyboard.Keyboard_Memory |= KEY_DOWN;
                    Keyboard.Keyboard_Flag = 1;
                }    
                else
                {
                    Keyboards_Level &= ~KEY_DOWN;                
                }            
            break; 

            case 4:
                if ( !(GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN)) )
                {
                    Keyboards_Level |= KEY_RIGHT;
                    Keyboard.Keyboard_Memory |= KEY_RIGHT;
                    Keyboard.Keyboard_Flag = 1;
                }
                else
                {
                    Keyboards_Level &= ~KEY_RIGHT;                
                }            
            break; 
            
            case 5:
                if ( !(GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN)) )
                {
                    Keyboards_Level |= KEY_ENTER;
                    Keyboard.Keyboard_Memory |= KEY_ENTER;
                    Keyboard.Keyboard_Flag = 1;
                }   
                else
                {
                    Keyboards_Level &= ~KEY_ENTER;                
                }            
            break;    

            case 6:
                if ( !(GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN)) )
                {
                    Keyboards_Level |= KEY_UP;
                    Keyboard.Keyboard_Memory |= KEY_UP;
                    Keyboard.Keyboard_Flag = 1;
                }   
                else
                {
                    Keyboards_Level &= ~KEY_UP;                
                }            
            break;
            
            case 7:
                if ( !(GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN)) )
                {
                    Keyboards_Level |= KEY_LEFT;
                    Keyboard.Keyboard_Memory |= KEY_LEFT;
                    Keyboard.Keyboard_Flag = 1;
                }   
                else
                {
                    Keyboards_Level &= ~KEY_LEFT;                
                }            
            break;
            }
        }
    
        switch ( Keyboard_Inputs_Select_Counter )
        { 
        case 0:
 
            if ( GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN) == 0 )    
                Keyboard.Keyboard_State |= KEY_ESCAPE;
            else
                Keyboard.Keyboard_State &= ~KEY_ESCAPE;

            if ( GPIO_ReadInputDataBit(PORT_IN_INPUTS, PIN_IN_INPUTS) == 0 )    
                Inputs_Level |= INPUT20;
            else
                Inputs_Level &= ~INPUT20;            
 
            GPIO_ResetBits(KBD_SEL1_PORT, KBD_SEL1_PIN);                   
            GPIO_ResetBits(KBD_SEL2_PORT, KBD_SEL2_PIN); 
            GPIO_ResetBits(KBD_SEL3_PORT, KBD_SEL3_PIN); 
            
            Keyboard_Inputs_Select_Counter++;
        break;
        
        case 1:   
            if ( GPIO_ReadInputDataBit(PORT_IN_INPUTS, PIN_IN_INPUTS) == 0 )    
                Inputs_Level |= INPUT13;
            else
                Inputs_Level &= ~INPUT13;            
             
            GPIO_SetBits(KBD_SEL1_PORT, KBD_SEL1_PIN);                   
            GPIO_ResetBits(KBD_SEL2_PORT, KBD_SEL2_PIN); 
            GPIO_ResetBits(KBD_SEL3_PORT, KBD_SEL3_PIN); 
            
            Keyboard_Inputs_Select_Counter++;
        break;
 
        case 2:
            if ( GPIO_ReadInputDataBit(PORT_IN_INPUTS, PIN_IN_INPUTS) == 0 )    
                Inputs_Level |= INPUT15;
            else
                Inputs_Level &= ~INPUT15;            

            if ( GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN) == 0 )    
                Keyboard.Keyboard_State |= KEY_TEST;
            else
                Keyboard.Keyboard_State &= ~KEY_TEST;

            GPIO_ResetBits(KBD_SEL1_PORT, KBD_SEL1_PIN);                   
            GPIO_SetBits(KBD_SEL2_PORT, KBD_SEL2_PIN); 
            GPIO_ResetBits(KBD_SEL3_PORT, KBD_SEL3_PIN); 
            
            Keyboard_Inputs_Select_Counter++;
        break;

        case 3:
            if ( GPIO_ReadInputDataBit(PORT_IN_INPUTS, PIN_IN_INPUTS) == 0 )    
                Inputs_Level |= INPUT17;
            else
                Inputs_Level &= ~INPUT17;            

            if ( GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN) == 0 )    
                Keyboard.Keyboard_State |= KEY_DOWN;
            else
                Keyboard.Keyboard_State &= ~KEY_DOWN;

            GPIO_SetBits(KBD_SEL1_PORT, KBD_SEL1_PIN);                   
            GPIO_SetBits(KBD_SEL2_PORT, KBD_SEL2_PIN); 
            GPIO_ResetBits(KBD_SEL3_PORT, KBD_SEL3_PIN); 
            
            Keyboard_Inputs_Select_Counter++;
        break;

        case 4:
            if ( GPIO_ReadInputDataBit(PORT_IN_INPUTS, PIN_IN_INPUTS) == 0 )    
                Inputs_Level |= INPUT19;
            else
                Inputs_Level &= ~INPUT19;            

            if ( GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN) == 0 )    
                Keyboard.Keyboard_State |= KEY_RIGHT;
            else
                Keyboard.Keyboard_State &= ~KEY_RIGHT;

            GPIO_ResetBits(KBD_SEL1_PORT, KBD_SEL1_PIN);                   
            GPIO_ResetBits(KBD_SEL2_PORT, KBD_SEL2_PIN); 
            GPIO_SetBits(KBD_SEL3_PORT, KBD_SEL3_PIN); 
            
            Keyboard_Inputs_Select_Counter++;
        break;

        case 5:
            if ( GPIO_ReadInputDataBit(PORT_IN_INPUTS, PIN_IN_INPUTS) == 0 )    
                Inputs_Level |= INPUT14;
            else
                Inputs_Level &= ~INPUT14;            

            if ( GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN) == 0 )    
                Keyboard.Keyboard_State |= KEY_ENTER;
            else
                Keyboard.Keyboard_State &= ~KEY_ENTER;

            GPIO_SetBits(KBD_SEL1_PORT, KBD_SEL1_PIN);                   
            GPIO_ResetBits(KBD_SEL2_PORT, KBD_SEL2_PIN); 
            GPIO_SetBits(KBD_SEL3_PORT, KBD_SEL3_PIN); 
            
            Keyboard_Inputs_Select_Counter++;
        break;  

        case 6:
            if ( GPIO_ReadInputDataBit(PORT_IN_INPUTS, PIN_IN_INPUTS) == 0 )    
                Inputs_Level |= INPUT16;
            else
                Inputs_Level &= ~INPUT16;            

            if ( GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN) == 0 )    
                Keyboard.Keyboard_State |= KEY_UP;
            else
                Keyboard.Keyboard_State &= ~KEY_UP;

            GPIO_ResetBits(KBD_SEL1_PORT, KBD_SEL1_PIN);                   
            GPIO_SetBits(KBD_SEL2_PORT, KBD_SEL2_PIN); 
            GPIO_SetBits(KBD_SEL3_PORT, KBD_SEL3_PIN); 
            
            Keyboard_Inputs_Select_Counter++;
        break; 

        case 7:
            if ( GPIO_ReadInputDataBit(PORT_IN_INPUTS, PIN_IN_INPUTS) == 0 )    
                Inputs_Level |= INPUT18;
            else
                Inputs_Level &= ~INPUT18;            

            if ( GPIO_ReadInputDataBit(KBD_OUT_PORT, KBD_OUT_PIN) == 0 )    
                Keyboard.Keyboard_State |= KEY_LEFT;
            else
                Keyboard.Keyboard_State &= ~KEY_LEFT;

            GPIO_SetBits(KBD_SEL1_PORT, KBD_SEL1_PIN);                   
            GPIO_SetBits(KBD_SEL2_PORT, KBD_SEL2_PIN); 
            GPIO_SetBits(KBD_SEL3_PORT, KBD_SEL3_PIN); 
            
            Keyboard_Inputs_Select_Counter = 0;
        break;  
            
        default:
            Keyboard_Inputs_Select_Counter = 0;
        break;
        }

		System_Timer_Setting ( &Keyboard_Timer.Timer, KBD_SAMPLE_TIME, T_10msec );
    }

}

/*******************************************************************************
* Function Name  : Keyboard_Handling
* Description    : Checking the keys
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Inputs_Handling ( void )
{
	if ( System_Timer_Check ( &Inputs_Timer.Timer, T_10msec ) == TRUE )
	{
        Inputs.Keyboard_State = 0;
   
//Edge handling
        if ( Service_Variables.Serv_Vars.In11_Fun == 1 )//O/S/C
        {
            if ( GPIO_ReadInputDataBit(PORT_IN11, PIN_IN11) == 0 )    
                Inputs.Keyboard_State |= OPEN_CLOSE_GATE;
        }

        if ( Service_Variables.Serv_Vars.In14_Fun == 1 )//O/S/C
        { 
            if ((Inputs_Level & INPUT14) != 0 )
            {
                Inputs.Keyboard_State |= OPEN_CLOSE_GATE1;            
            }
        }   
        if ( Service_Variables.Serv_Vars.In15_Fun == 1 )//O/S/C
        { 
            if ((Inputs_Level & INPUT15) != 0 )
            {
                Inputs.Keyboard_State |= OPEN_CLOSE_GATE2;            
            }
        }
        if ( Service_Variables.Serv_Vars.In16_Fun == 1 )//O/S/C
        { 
            if ((Inputs_Level & INPUT16) != 0 )
            {
                Inputs.Keyboard_State |= OPEN_CLOSE_GATE3;            
            }
        }
        if ( Service_Variables.Serv_Vars.In17_Fun == 1 )//O/S/C
        { 
            if ((Inputs_Level & INPUT17) != 0 )
            {
                Inputs.Keyboard_State |= OPEN_CLOSE_GATE4;            
            }
        }
        if ( Service_Variables.Serv_Vars.In18_Fun == 1 )//O/S/C
        { 
            if ((Inputs_Level & INPUT18) != 0 )
            {
                Inputs.Keyboard_State |= OPEN_CLOSE_GATE5;            
            }
        }
        if ( Service_Variables.Serv_Vars.In19_Fun == 1 )//O/S/C
        { 
            if ((Inputs_Level & INPUT19) != 0 )
            {
                Inputs.Keyboard_State |= OPEN_CLOSE_GATE6;            
            }
        }
        if ( Service_Variables.Serv_Vars.In20_Fun == 1 )//O/S/C
        { 
            if ((Inputs_Level & INPUT20) != 0 )
            {
                Inputs.Keyboard_State |= OPEN_CLOSE_GATE7;            
            }
        }
    
        if ( Inputs.Keyboard_Memory == 0 && Inputs.Keyboard_Flag == 0 )
        {
            if ( !(GPIO_ReadInputDataBit(PORT_IN11, PIN_IN11)) )
            {
                if ( Service_Variables.Serv_Vars.In11_Fun == 1 )//O/S/C
                {
                    Inputs.Keyboard_Memory |= OPEN_CLOSE_GATE;
                    Inputs.Keyboard_Flag = 1;
                }
            }            
            else if ( (Inputs_Level & INPUT14 ) != 0 )
            {
                if ( Service_Variables.Serv_Vars.In14_Fun == 1 )//O/S/C
                {
                    Inputs.Keyboard_Memory |= OPEN_CLOSE_GATE1;
                    Inputs.Keyboard_Flag = 1;
                }                
            }
            else if ( (Inputs_Level & INPUT15 ) != 0 )
            {
                if ( Service_Variables.Serv_Vars.In15_Fun == 1 )//O/S/C
                {
                    Inputs.Keyboard_Memory |= OPEN_CLOSE_GATE2;
                    Inputs.Keyboard_Flag = 1;
                }                
            }
            else if ( (Inputs_Level & INPUT16 ) != 0 )
            {
                if ( Service_Variables.Serv_Vars.In16_Fun == 1 )//O/S/C
                {
                    Inputs.Keyboard_Memory |= OPEN_CLOSE_GATE3;
                    Inputs.Keyboard_Flag = 1;
                }                
            }
            else if ( (Inputs_Level & INPUT17 ) != 0 )
            {
                if ( Service_Variables.Serv_Vars.In17_Fun == 1 )//O/S/C
                {
                    Inputs.Keyboard_Memory |= OPEN_CLOSE_GATE4;
                    Inputs.Keyboard_Flag = 1;
                }                
            }
            else if ( (Inputs_Level & INPUT18 ) != 0 )
            {
                if ( Service_Variables.Serv_Vars.In18_Fun == 1 )//O/S/C
                {
                    Inputs.Keyboard_Memory |= OPEN_CLOSE_GATE5;
                    Inputs.Keyboard_Flag = 1;
                }                
            }
            else if ( (Inputs_Level & INPUT19 ) != 0 )
            {
                if ( Service_Variables.Serv_Vars.In19_Fun == 1 )//O/S/C
                {
                    Inputs.Keyboard_Memory |= OPEN_CLOSE_GATE6;
                    Inputs.Keyboard_Flag = 1;
                }                
            }
            else if ( (Inputs_Level & INPUT20 ) != 0 )
            {
                if ( Service_Variables.Serv_Vars.In20_Fun == 1 )//O/S/C
                {
                    Inputs.Keyboard_Memory |= OPEN_CLOSE_GATE7;
                    Inputs.Keyboard_Flag = 1;
                }                
            }
        }
 
//level handling
        Inputs_On_Off ( PORT_IN1, PIN_IN1, Service_Variables.Serv_Vars.In1_Type, &Inputs_Level, INPUT1 );
        Inputs_On_Off ( PORT_IN2, PIN_IN2, Service_Variables.Serv_Vars.In2_Type, &Inputs_Level, INPUT2 );
        Inputs_On_Off ( PORT_IN3, PIN_IN3, Service_Variables.Serv_Vars.In3_Type, &Inputs_Level, INPUT3 );
        Inputs_On_Off ( PORT_IN4, PIN_IN4, Service_Variables.Serv_Vars.In4_Type, &Inputs_Level, INPUT4 );
        Inputs_On_Off ( PORT_IN5, PIN_IN5, Service_Variables.Serv_Vars.In5_Type, &Inputs_Level, INPUT5 );
        Inputs_On_Off ( PORT_IN6, PIN_IN6, Service_Variables.Serv_Vars.In6_Type, &Inputs_Level, INPUT6 );
        Inputs_On_Off ( PORT_IN11, PIN_IN11, Service_Variables.Serv_Vars.In11_Type, &Inputs_Level, INPUT11 );
        Inputs_On_Off ( PORT_IN12, PIN_IN12, Service_Variables.Serv_Vars.In12_Type, &Inputs_Level, INPUT12 );
 
        Analog_Inputs_Fun( Controller_Variables.Controller_Vars.AD_14, Service_Variables.Serv_Vars.In7_Type, Service_Variables.Serv_Vars.In7_Fun, &Inputs_Level, INPUT7);
        Analog_Inputs_Fun( Controller_Variables.Controller_Vars.AD_15, Service_Variables.Serv_Vars.In8_Type, Service_Variables.Serv_Vars.In8_Fun, &Inputs_Level, INPUT8);
        Analog_Inputs_Fun( Controller_Variables.Controller_Vars.AD_8,  Service_Variables.Serv_Vars.In9_Type, Service_Variables.Serv_Vars.In9_Fun, &Inputs_Level, INPUT9);
        Analog_Inputs_Fun( Controller_Variables.Controller_Vars.AD_9,  Service_Variables.Serv_Vars.In10_Type, Service_Variables.Serv_Vars.In10_Fun, &Inputs_Level, INPUT10);
    
    
//Analog inputs handling    

//Level handling for test function
        if ( GPIO_ReadInputDataBit(PORT_IN1, PIN_IN1) == 0 )
            Inputs_Level_Test |= INPUT1;
        else
            Inputs_Level_Test &= ~INPUT1;

        if ( GPIO_ReadInputDataBit(PORT_IN2, PIN_IN2) == 0 )
            Inputs_Level_Test |= INPUT2;
        else
            Inputs_Level_Test &= ~INPUT2;

        if ( GPIO_ReadInputDataBit(PORT_IN3, PIN_IN3) == 0 )
            Inputs_Level_Test |= INPUT3;
        else
            Inputs_Level_Test &= ~INPUT3;
     
        if ( GPIO_ReadInputDataBit(PORT_IN4, PIN_IN4) == 0 )
            Inputs_Level_Test |= INPUT4;
        else
            Inputs_Level_Test &= ~INPUT4;

        if ( GPIO_ReadInputDataBit(PORT_IN5, PIN_IN5) == 0 )
            Inputs_Level_Test |= INPUT5;
        else
            Inputs_Level_Test &= ~INPUT5;
        
        if ( GPIO_ReadInputDataBit(PORT_IN6, PIN_IN6) == 0 )
            Inputs_Level_Test |= INPUT6;
        else
            Inputs_Level_Test &= ~INPUT6;

                if ( GPIO_ReadInputDataBit(PORT_IN7, PIN_IN7) == 0 )
            Inputs_Level_Test |= INPUT7;
        else
            Inputs_Level_Test &= ~INPUT7;

                if ( GPIO_ReadInputDataBit(PORT_IN8, PIN_IN8) == 0 )
            Inputs_Level_Test |= INPUT8;
        else
            Inputs_Level_Test &= ~INPUT8;

        
        if ( Controller_Variables.Controller_Vars.AD_8 < Service_Variables.Serv_Vars.Serwis_002 )
        {
            Inputs_Level_Test |= INPUT9;
        }
        else if ( Controller_Variables.Controller_Vars.AD_8 > Service_Variables.Serv_Vars.Serwis_003 )
        {
            Inputs_Level_Test &= ~INPUT9;
        }
    
        if ( Controller_Variables.Controller_Vars.AD_9 < Service_Variables.Serv_Vars.Serwis_002 )
        {
            Inputs_Level_Test |= INPUT10;
        }
        else if ( Controller_Variables.Controller_Vars.AD_9 > Service_Variables.Serv_Vars.Serwis_003 )
        {
            Inputs_Level_Test &= ~INPUT10;
        }

        if ( GPIO_ReadInputDataBit(PORT_IN11, PIN_IN11) == 0 )
            Inputs_Level_Test |= INPUT11;
        else
            Inputs_Level_Test &= ~INPUT11;
    
        if ( GPIO_ReadInputDataBit(PORT_IN12, PIN_IN12) == 0 )
            Inputs_Level_Test |= INPUT12;
        else
            Inputs_Level_Test &= ~INPUT12;

        
        
//End of level handling for test
		System_Timer_Setting ( &Inputs_Timer.Timer, INPUTS_SAMPLE_TIME, T_10msec );
    }

}

/*******************************************************************************
* Function Name  : Temperature_Measure
* Description    : Measuring the internal temperature
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Analog_Measure ( void )
{
    static const int16_t T25 = 1750;
    static const int16_t Avg_Slope = 5;

	if ( System_Timer_Check ( &Temperature_Timer.Timer, T_10msec ) == TRUE )
	{    
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        ADC_MEASURED = FALSE;
        System_Timer_Setting ( &Temperature_Timer.Timer, T_SAMPLE_TIME, T_10msec );
    }

    if ( ADC_MEASURED == TRUE )
    {
        ADC_MEASURED = FALSE;
    
        Controller_Variables.Controller_Vars.AD_0 = ADC_ConvertedValueTab[0];
        Controller_Variables.Controller_Vars.AD_1 = ADC_ConvertedValueTab[1];
        Controller_Variables.Controller_Vars.AD_8 = ADC_ConvertedValueTab[2];
        Controller_Variables.Controller_Vars.AD_9 = ADC_ConvertedValueTab[3];
        Controller_Variables.Controller_Vars.AD_14 = ADC_ConvertedValueTab[4];
        Controller_Variables.Controller_Vars.AD_15 = ADC_ConvertedValueTab[5];
        Controller_Variables.Controller_Vars.AD_16 = ADC_ConvertedValueTab[6];

        Controller_Variables.Controller_Vars.Internal_Temperature = (int16_t)(T25-Controller_Variables.Controller_Vars.AD_16)/Avg_Slope + 25;
    }
}

/*******************************************************************************
* Function Name  : Periods_Handling
* Description    : Free exit and fast pass periuods handling
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
bool  Periods_Handling ( bool Period1_Enable,
                         bool Period2_Enable,
                         uint8_t Hour_1,
                         uint8_t Hour_2,
                         uint8_t Hour_3,
                         uint8_t Hour_4,
                         uint8_t Minute_1,
                         uint8_t Minute_2,
                         uint8_t Minute_3,
                         uint8_t Minute_4 )
{
    bool Period1_Marker;
    bool Period2_Marker;

    uint32_t Period_1;
    uint32_t Period_2;
    uint32_t Period_3;
    uint32_t Period_4;

    Period_1 = ( Hour_1 * 3600) + ( Minute_1 * 60 );
    Period_2 = ( Hour_2 * 3600) + ( Minute_2 * 60 );
    Period_3 = ( Hour_3 * 3600) + ( Minute_3 * 60 );
    Period_4 = ( Hour_4 * 3600) + ( Minute_4 * 60 );
 
    Period1_Marker = FALSE;
    Period2_Marker = FALSE;

    if ( Period1_Enable == TRUE )
    {
        if ( Period_1 < Period_2 )
        {
            if ( (RTC_GetCounter() >= Period_1) && (RTC_GetCounter() <= Period_2) )
            {
                Period1_Marker = TRUE;
            }
        }
        else if ( Period_1 > Period_2 )
        {
            if ( (RTC_GetCounter() >= Period_1) || (RTC_GetCounter() <= Period_2) )
            {
                Period1_Marker = TRUE;
            } 
        }
    }

    if ( Period2_Enable == TRUE )
    {
        if ( Period_3 < Period_4 )
        {
            if ( (RTC_GetCounter() >= Period_3) && (RTC_GetCounter() <= Period_4) )
            {
                Period2_Marker = TRUE;
            }
        }
        else if ( Period_3 > Period_4 )
        {
            if ( (RTC_GetCounter() >= Period_3) && (RTC_GetCounter() <= Period_4) )
            {
                Period2_Marker = TRUE;
            }
        } 
    }

    if ( Period1_Marker == TRUE || Period2_Marker == TRUE )
        return TRUE;
    else
        return FALSE;;
}



/*******************************************************************************
* Function Name  : Input_Output_Test
* Description    : Manual testing of inputs and outputs
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Input_Output_Test ( void )
{
        if ( Controller_Variables.Controller_Vars.Test_Status == 0 )
        {
            if ( Inputs_Level_Test & INPUT1 )
            {
                Manual_Values.Values.Mos1_Manual_Value = PWM_HALF;
            }
            else
            {
                Manual_Values.Values.Mos1_Manual_Value = PWM_OFF;
            }  
        
            if ( Inputs_Level_Test & INPUT2 )
            {
                Manual_Values.Values.Mos2_Manual_Value = PWM_HALF;
            }
            else
            {
                Manual_Values.Values.Mos2_Manual_Value = PWM_OFF;
            }                
        }
        else if ( Controller_Variables.Controller_Vars.Test_Status == 1 )
        {
            if ( Inputs_Level_Test & INPUT1 )
            {
                Manual_Values.Values.OC1_Manual_Value = TRUE;
            }
            else
            {
                Manual_Values.Values.OC1_Manual_Value = FALSE;
            }  
        
            if ( Inputs_Level_Test & INPUT2 )
            {
                Manual_Values.Values.OC2_Manual_Value = TRUE;
            }
            else
            {
                Manual_Values.Values.OC2_Manual_Value = FALSE;
            }  
        }
        else if ( Controller_Variables.Controller_Vars.Test_Status == 2 )
        {
            if ( Inputs_Level_Test & INPUT1 )
            {
                Manual_Values.Values.RL1_Manual_Value = TRUE;
            }
            else
            {
                Manual_Values.Values.RL1_Manual_Value = FALSE;
            }  
        
            if ( Inputs_Level_Test & INPUT2 )
            {
                Manual_Values.Values.RL2_Manual_Value = TRUE;
            }
            else
            {
                Manual_Values.Values.RL2_Manual_Value = FALSE;
            }   
        
            if ( Inputs_Level_Test & INPUT3 )
            {
                Manual_Values.Values.RL3_Manual_Value = TRUE;
            }
            else
            {
                Manual_Values.Values.RL3_Manual_Value = FALSE;
            }   
        
            if ( Inputs_Level_Test & INPUT4 )
            {
                Manual_Values.Values.RL4_Manual_Value = TRUE;
            }
            else
            {
                Manual_Values.Values.RL4_Manual_Value = FALSE;
            }  

            if ( Inputs_Level_Test & INPUT5 )        
            {
                Manual_Values.Values.Mos1_Dir_Manual_Value = TRUE;
            }
            else
            {
                Manual_Values.Values.Mos1_Dir_Manual_Value = FALSE;
            }   

            if ( Inputs_Level_Test & INPUT6 )
            {
                Manual_Values.Values.RL5_Manual_Value = TRUE;
            }
            else
            {
                Manual_Values.Values.RL5_Manual_Value = FALSE;
            }   
            if ( Inputs_Level_Test & INPUT7 )
            {
                Manual_Values.Values.RL6_Manual_Value = TRUE;
            }
            else
            {
                Manual_Values.Values.RL6_Manual_Value = FALSE;
            }          
        }
        else if ( Controller_Variables.Controller_Vars.Test_Status == 3 )
        {
            if ( Inputs_Level_Test & INPUT4 )
            {
                GPIO_SetBits(PORT_BUZZER, PIN_BUZZER );
            }
            else
            {
                GPIO_ResetBits(PORT_BUZZER, PIN_BUZZER);
            }              
        }
        else if ( Controller_Variables.Controller_Vars.Test_Status == 4 )
        {
        }
}

/*******************************************************************************
* Function Name  : Enable_Manual_Control
* Description    : Manual testing of inputs and outputs
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Enable_Manual_Control ( void )
{
    uint8_t Manual_For_Temp;

    for ( Manual_For_Temp = 0; Manual_For_Temp < sizeof(Manual_Control_Enable.Manual_Control_Bool_Tab); Manual_For_Temp++)
    {
        Manual_Control_Enable.Manual_Control_Bool_Tab[Manual_For_Temp] = TRUE;
    }
}

/*******************************************************************************
* Function Name  : Disable_Manual_Control
* Description    : Manual control disable
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Disable_Manual_Control ( void )
{
    uint8_t Manual_For_Temp1;

    for ( Manual_For_Temp1 = 0; Manual_For_Temp1 < sizeof(Manual_Control_Enable.Manual_Control_Bool_Tab); Manual_For_Temp1++)
    {
        Manual_Control_Enable.Manual_Control_Bool_Tab[Manual_For_Temp1] = FALSE;
    }

    Manual_Control_Enable.Manual_Control.Relay1_Manual = TRUE;
    Manual_Control_Enable.Manual_Control.Relay2_Manual = TRUE;
    Manual_Control_Enable.Manual_Control.Relay3_Manual = TRUE;
    Manual_Control_Enable.Manual_Control.Relay4_Manual = TRUE;
    Manual_Control_Enable.Manual_Control.Relay5_Manual = TRUE;
    Manual_Control_Enable.Manual_Control.Relay6_Manual = TRUE;


}
/*******************************************************************************
* Function Name  : Disable_Manual_Values
* Description    : Manual values disable
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Disable_Manual_Values ( void )
{
    uint8_t Manual_For_Temp2;

    for ( Manual_For_Temp2 = 0; Manual_For_Temp2 < sizeof(Manual_Values.Manual_Byte_Value_Tab); Manual_For_Temp2++)
    {
        Manual_Values.Manual_Byte_Value_Tab[Manual_For_Temp2] = 0;
    }
}

/*******************************************************************************
* Function Name  : RS485_Send
* Description    : Sending data through USART / RS485
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RS485_Send ( void )
{
    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) // Frequency inverters
    {
        if ( RS485_TRANSMIT_ENABLE == FALSE )
        {
            if ( System_Timer_Check ( &RS485_Timer.Timer, T_10msec ) == TRUE )
            {
                if ( INV_PROGRAMMING == TRUE )
                {
                    System_Timer_Setting ( &RS485_Timer.Timer, 10, T_10msec );            
                }
                else
                {
                    System_Timer_Setting ( &RS485_Timer.Timer, Service_Variables.Serv_Vars.Serwis_022, T_10msec );
                }
                RS485_Counter = 0;
                RS485_TRANSMIT_ENABLE = TRUE;
            }
        }

        if ( RS485_TRANSMIT_ENABLE == TRUE )
        {
            RS485_Counter++;
        
            if ( RS485_Counter == 1 )
            {
                GPIO_SetBits ( RS485_DIR_PORT, RS485_DIR_PIN );
            }
            
            if ( RS485_Counter == 10 )
            {
//******************************************************************8//
//******************************************************************8//
//******************************************************************8//
//******************************************************************8//
//Reading data from frequency inverters
//******************************************************************8//
//******************************************************************8//
//******************************************************************8//
//******************************************************************8//
//FREQ1 CONNECTION CHECK
                switch ( RS485_Inverter_Error )
                {
                    case FREQ1_CONNECTED:
                        if ( Uart_Tx_Packet.Uart_Buffer[6] == Uart_Rx_Packet.Uart_Buffer[6] &&
                             Uart_Tx_Packet.Uart_Buffer[7] == Uart_Rx_Packet.Uart_Buffer[7] )
                        {
                            RS485_Comm_Err_Counter1 = 0;
                            Controller_Variables.Controller_Vars.Inputs_Error &= ~F1_DISCONNECTED;
                        }
                        else
                        {
                            RS485_Comm_Err_Counter1++;
                            RS485_Inverter_Counter = FREQ1_CONNECTED;
                        }
                    break;

                    case FREQ2_CONNECTED:
                        if ( Uart_Tx_Packet.Uart_Buffer[6] == Uart_Rx_Packet.Uart_Buffer[6] &&
                             Uart_Tx_Packet.Uart_Buffer[7] == Uart_Rx_Packet.Uart_Buffer[7] )
                        {
                            RS485_Comm_Err_Counter2 = 0;
                            Controller_Variables.Controller_Vars.Inputs_Error &= ~F2_DISCONNECTED;
                        }
                        else
                        {
                            RS485_Comm_Err_Counter2++;
                            RS485_Inverter_Counter = FREQ2_CONNECTED;
                        }            
                    break;

                    case FREQ1_START_STOP:
                        Crc_check = CRC16_CCITT( Uart_Rx_Packet.Uart_Buffer, 6);

                        Crc_received = 0;
                        Crc_received = Uart_Rx_Packet.Uart_Buffer[7];
                        Crc_received <<= 8;
                        Crc_received += Uart_Rx_Packet.Uart_Buffer[6];
                    
                        if ( Uart_Rx_Packet.Uart_Buffer[0] == F1_ADDRESS &&
                             Crc_check == Crc_received )
                        { 
                            RS485_Comm_Err_Counter1 = 0;
                            Controller_Variables.Controller_Vars.Inputs_Error &= ~F1_DISCONNECTED;
                        }
                        else
                        {
                            RS485_Comm_Err_Counter1++;
                        }
                    break;
                    
                    case FREQ2_START_STOP:
                        Crc_check = CRC16_CCITT( Uart_Rx_Packet.Uart_Buffer, 6);

                        Crc_received = 0;
                        Crc_received = Uart_Rx_Packet.Uart_Buffer[7];
                        Crc_received <<= 8;
                        Crc_received += Uart_Rx_Packet.Uart_Buffer[6];
                    
                        if ( Uart_Rx_Packet.Uart_Buffer[0] == F1_ADDRESS &&
                             Crc_check == Crc_received )
                        { 
                            RS485_Comm_Err_Counter2 = 0;
                            Controller_Variables.Controller_Vars.Inputs_Error &= ~F2_DISCONNECTED;
                        }
                        else
                        {
                            RS485_Comm_Err_Counter2++;
                        }                    
                    break;
                    
                    case FREQ1_SET:
                        
                    break;
                    
                    case FREQ2_SET:
                        
                    break;
                    
                    case FREQ1_MONITORING:
                        Crc_check = CRC16_CCITT( Uart_Rx_Packet.Uart_Buffer, 5);

                        Crc_received = 0;
                        Crc_received = Uart_Rx_Packet.Uart_Buffer[6];
                        Crc_received <<= 8;
                        Crc_received += Uart_Rx_Packet.Uart_Buffer[5];
                    
                        if ( Uart_Rx_Packet.Uart_Buffer[0] == F1_ADDRESS &&
                             Crc_check == Crc_received )
                        {
                            Controller_Variables.Controller_Vars.F1_Current = 0;
                            Controller_Variables.Controller_Vars.F1_Current = Uart_Rx_Packet.Uart_Buffer[3];
                            Controller_Variables.Controller_Vars.F1_Current <<= 8;
                            Controller_Variables.Controller_Vars.F1_Current += Uart_Rx_Packet.Uart_Buffer[4];

                            RS485_Comm_Err_Counter1 = 0;
                            Controller_Variables.Controller_Vars.Inputs_Error &= ~F1_DISCONNECTED;
                        }
                        else
                        {
                            if ( RS485_Comm_Err_Counter1 < 20 )
                                RS485_Comm_Err_Counter1++;
                        }

                        if ( Controller_Variables.Controller_Vars.F1_Current > Controlling_Variables.Ctrl_Vars.F1_Current_Limit )
                        {
                            F1_Current_Counter++;
                        }
                        else
                        {
                            F1_Current_Counter = 0;
                        }                    
                    break;
                    
                    case FREQ2_MONITORING:
                        Crc_check = CRC16_CCITT( Uart_Rx_Packet.Uart_Buffer, 5);

                        Crc_received = 0;
                        Crc_received = Uart_Rx_Packet.Uart_Buffer[6];
                        Crc_received <<= 8;
                        Crc_received += Uart_Rx_Packet.Uart_Buffer[5];
                    
                        if ( Uart_Rx_Packet.Uart_Buffer[0] == F2_ADDRESS &&
                             Crc_check == Crc_received )
                        {
                            Controller_Variables.Controller_Vars.F2_Current = 0;
                            Controller_Variables.Controller_Vars.F2_Current = Uart_Rx_Packet.Uart_Buffer[3];
                            Controller_Variables.Controller_Vars.F2_Current <<= 8;
                            Controller_Variables.Controller_Vars.F2_Current += Uart_Rx_Packet.Uart_Buffer[4];

                            RS485_Comm_Err_Counter2 = 0;
                            Controller_Variables.Controller_Vars.Inputs_Error &= ~F2_DISCONNECTED;
                        }
                        else
                        {
                            RS485_Comm_Err_Counter2++;
                        }
                    
                        if ( Controller_Variables.Controller_Vars.F2_Current >= Controlling_Variables.Ctrl_Vars.F2_Current_Limit )
                        {
                            F2_Current_Counter++;
                        }
                        else
                        {
                            F2_Current_Counter = 0;
                        }                    
                    break;
                 
                    default:
                        
                    break;
                }
            
                if ( RS485_Comm_Err_Counter1 >= 10 )
                {
                    Controller_Variables.Controller_Vars.Inputs_Error |= F1_DISCONNECTED;
                }  

                if ( RS485_Comm_Err_Counter2 >= 10 )
                {
                    Controller_Variables.Controller_Vars.Inputs_Error |= F2_DISCONNECTED;
                }  
//******************************************************************8//
//******************************************************************8//
//******************************************************************8//
//******************************************************************8//
//Sendign data to frequency inverters
//******************************************************************8//
//******************************************************************8//
//******************************************************************8//
//******************************************************************8//
                switch ( RS485_Inverter_Counter ) 
                { 
                case FREQ1_CONNECTED:
                    Uart_Tx_Packet.Uart_Buffer[0] = F1_ADDRESS;
                    Uart_Tx_Packet.Uart_Buffer[1] = FUN_TEST;
                    Uart_Tx_Packet.Uart_Buffer[2] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[3] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[4] = 0xa5;
                    Uart_Tx_Packet.Uart_Buffer[5] = 0x37;

                    RS485_Packet_Length = 8;        
                    Crc_value = CRC16_CCITT( Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length-2));
                    Uart_Tx_Packet.Uart_Buffer[6] = (uint8_t)(Crc_value & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[7] = (uint8_t)(Crc_value >> 8 ) & 0x00ff;

                    if ( Motors_Enable == 0 )
                    {
                        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) // Two wings gate
                        { 
                            RS485_Inverter_Counter = FREQ2_CONNECTED;
                        }
                        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || // One wing gate
                                  Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )  // Sliding
                        {
                            if ( INV_PROGRAMMING == TRUE )
                            {
                                RS485_Inverter_Counter = FREQ1_SET;
                            }
                            else
                            {
                                RS485_Inverter_Counter = FREQ1_CONNECTED;
                            }
                        }
                    }
                    else
                    {
                        RS485_Inverter_Counter = FREQ1_START_STOP;                
                    }

                    RS485_Inverter_Error = FREQ1_CONNECTED;
                break;

                case FREQ2_CONNECTED:
                    Uart_Tx_Packet.Uart_Buffer[0] = F2_ADDRESS;
                    Uart_Tx_Packet.Uart_Buffer[1] = FUN_TEST;
                    Uart_Tx_Packet.Uart_Buffer[2] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[3] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[4] = 0xa5;
                    Uart_Tx_Packet.Uart_Buffer[5] = 0x37;

                    RS485_Packet_Length = 8;            
                    Crc_value = CRC16_CCITT( Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length-2));
                    Uart_Tx_Packet.Uart_Buffer[6] = (uint8_t)(Crc_value & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[7] = (uint8_t)(Crc_value >> 8 ) & 0x00ff;
        
                    if ( Motors_Enable == 0 )
                    {
                        if ( INV_PROGRAMMING == TRUE )
                        {
                            RS485_Inverter_Counter = FREQ1_SET;
                        }
                        else
                        {
                            RS485_Inverter_Counter = FREQ1_CONNECTED;
                        }
                    }
                    else
                    {
                        RS485_Inverter_Counter = FREQ1_START_STOP;
                    }
                
                    RS485_Inverter_Error = FREQ2_CONNECTED;            
                break;  
            
                case FREQ1_START_STOP:
                    Uart_Tx_Packet.Uart_Buffer[0] = F1_ADDRESS;
                    Uart_Tx_Packet.Uart_Buffer[1] = FUN_WRITE;
                    Uart_Tx_Packet.Uart_Buffer[2] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[3] = 0x01;
                    Uart_Tx_Packet.Uart_Buffer[4] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[5] = 0x02;
                    Uart_Tx_Packet.Uart_Buffer[6] = 0x04;
                    Uart_Tx_Packet.Uart_Buffer[7] = 0x00;
                
                    if ( Motors_Enable & MOTOR_1_OPENING )
                        Uart_Tx_Packet.Uart_Buffer[8] = FWD_RUN;
                    else if ( Motors_Enable & MOTOR_1_CLOSING )
                        Uart_Tx_Packet.Uart_Buffer[8] = REV_RUN;
                    else
                        Uart_Tx_Packet.Uart_Buffer[8] = STOP_RUN;
                        
                    if ( Uart_Tx_Packet.Uart_Buffer[8] == STOP_RUN )
                    {
                        Uart_Tx_Packet.Uart_Buffer[9] = 0;
                        Uart_Tx_Packet.Uart_Buffer[10] = 0;
                    }
                    else
                    {
                        Uart_Tx_Packet.Uart_Buffer[9] = ((Controller_Variables.Controller_Vars.Frequency1 >>8) & 0x00FF);
                        Uart_Tx_Packet.Uart_Buffer[10] = (Controller_Variables.Controller_Vars.Frequency1 & 0x00FF);
                    }

                    RS485_Packet_Length = 13;
                    Crc_value = CRC16_CCITT( Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length-2));
                    Uart_Tx_Packet.Uart_Buffer[11] = (uint8_t)(Crc_value & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[12] = (uint8_t)(Crc_value >> 8 ) & 0x00ff;

                /*
                    if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) // Two wings gate
                    {  
                        RS485_Inverter_Counter = FREQ2_START_STOP;
                    }
                    else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 ) // One wing gate
                    {
                        RS485_Inverter_Counter = FREQ1_START_STOP;           
                    }
                */
                
                    RS485_Inverter_Counter = FREQ1_MONITORING;
                    RS485_Inverter_Error = FREQ1_START_STOP;
                break;

                case FREQ2_START_STOP:
                    Uart_Tx_Packet.Uart_Buffer[0] = F2_ADDRESS;
                    Uart_Tx_Packet.Uart_Buffer[1] = FUN_WRITE;
                    Uart_Tx_Packet.Uart_Buffer[2] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[3] = 0x01;
                    Uart_Tx_Packet.Uart_Buffer[4] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[5] = 0x02;
                    Uart_Tx_Packet.Uart_Buffer[6] = 0x04;
                    Uart_Tx_Packet.Uart_Buffer[7] = 0x00;
                
                    if ( Motors_Enable & MOTOR_2_OPENING )
                        Uart_Tx_Packet.Uart_Buffer[8] = REV_RUN;
                    else if ( Motors_Enable & MOTOR_2_CLOSING )
                        Uart_Tx_Packet.Uart_Buffer[8] = FWD_RUN;
                    else
                        Uart_Tx_Packet.Uart_Buffer[8] = STOP_RUN;

                    if ( Uart_Tx_Packet.Uart_Buffer[8] == STOP_RUN )
                    {
                        Uart_Tx_Packet.Uart_Buffer[9] = 0;
                        Uart_Tx_Packet.Uart_Buffer[10] = 0;
                    }
                    else
                    {
                        Uart_Tx_Packet.Uart_Buffer[9] = ((Controller_Variables.Controller_Vars.Frequency2 >>8) & 0x00FF);
                        Uart_Tx_Packet.Uart_Buffer[10] = (Controller_Variables.Controller_Vars.Frequency2 & 0x00FF);
                    }
                
                    RS485_Packet_Length = 13;
                    Crc_value = CRC16_CCITT( Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length-2));
                    Uart_Tx_Packet.Uart_Buffer[11] = (uint8_t)(Crc_value & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[12] = (uint8_t)(Crc_value >> 8 ) & 0x00ff;
                
                    RS485_Inverter_Counter = FREQ2_MONITORING;
                    RS485_Inverter_Error = FREQ2_START_STOP;
                break;

                case FREQ_STOP:
                    Uart_Tx_Packet.Uart_Buffer[0] = 0;
                    Uart_Tx_Packet.Uart_Buffer[1] = FUN_WRITE;
                    Uart_Tx_Packet.Uart_Buffer[2] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[3] = 0x01;
                    Uart_Tx_Packet.Uart_Buffer[4] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[5] = 0x01;
                    Uart_Tx_Packet.Uart_Buffer[6] = 0x02;
                    Uart_Tx_Packet.Uart_Buffer[7] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[8] = STOP_RUN;

                    RS485_Packet_Length = 11;
                    Crc_value = CRC16_CCITT( Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length-2));
                    Uart_Tx_Packet.Uart_Buffer[9] = (uint8_t)(Crc_value & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[10] = (uint8_t)(Crc_value >> 8 ) & 0x00ff;
          
                    RS485_Inverter_Counter = FREQ1_CONNECTED;
                    RS485_Inverter_Error = FREQ_STOP; 
                break;
                
                case FREQ1_SET:
                    Uart_Tx_Packet.Uart_Buffer[0] = F1_ADDRESS;
                    Uart_Tx_Packet.Uart_Buffer[1] = FUN_WRITE;
                    Uart_Tx_Packet.Uart_Buffer[2] = 0x02;
                    Uart_Tx_Packet.Uart_Buffer[3] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[4] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[5] = 0x02;
                    Uart_Tx_Packet.Uart_Buffer[6] = 0x04;
                    Uart_Tx_Packet.Uart_Buffer[7] = (uint8_t)(Controlling_Variables.Ctrl_Vars.SoftStart >> 8 ) & 0x00ff;
                    Uart_Tx_Packet.Uart_Buffer[8] = (uint8_t)(Controlling_Variables.Ctrl_Vars.SoftStart & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[9] = (uint8_t)(Controlling_Variables.Ctrl_Vars.SoftStop >> 8 ) & 0x00ff;
                    Uart_Tx_Packet.Uart_Buffer[10] =(uint8_t)(Controlling_Variables.Ctrl_Vars.SoftStop & 0x00ff);
                
                    RS485_Packet_Length = 13;
                    Crc_value = CRC16_CCITT( Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length-2));
                    Uart_Tx_Packet.Uart_Buffer[11] = (uint8_t)(Crc_value & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[12] = (uint8_t)(Crc_value >> 8 ) & 0x00ff;

                    if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) // Two wings gate
                    {  
                        RS485_Inverter_Counter = FREQ2_SET;
                    }
                    else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || // One wing gate
                              Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )  // Sliding
                    {
                        RS485_Inverter_Counter = FREQ1_CONNECTED;
                        INV_PROGRAMMING = FALSE;
                    }

                    RS485_Inverter_Error = FREQ1_SET;            
                break;
                
                case FREQ2_SET:
                    Uart_Tx_Packet.Uart_Buffer[0] = F2_ADDRESS;
                    Uart_Tx_Packet.Uart_Buffer[1] = FUN_WRITE;
                    Uart_Tx_Packet.Uart_Buffer[2] = 0x02;
                    Uart_Tx_Packet.Uart_Buffer[3] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[4] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[5] = 0x02;
                    Uart_Tx_Packet.Uart_Buffer[6] = 0x04;
                    Uart_Tx_Packet.Uart_Buffer[7] = (uint8_t)(Controlling_Variables.Ctrl_Vars.SoftStart >> 8 ) & 0x00ff;
                    Uart_Tx_Packet.Uart_Buffer[8] = (uint8_t)(Controlling_Variables.Ctrl_Vars.SoftStart & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[9] = (uint8_t)(Controlling_Variables.Ctrl_Vars.SoftStop >> 8 ) & 0x00ff;
                    Uart_Tx_Packet.Uart_Buffer[10] =(uint8_t)(Controlling_Variables.Ctrl_Vars.SoftStop & 0x00ff);
               
                    RS485_Packet_Length = 13;
                    Crc_value = CRC16_CCITT( Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length-2));
                    Uart_Tx_Packet.Uart_Buffer[11] = (uint8_t)(Crc_value & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[12] = (uint8_t)(Crc_value >> 8 ) & 0x00ff;

                    RS485_Inverter_Counter = FREQ1_CONNECTED;           
                    RS485_Inverter_Error = FREQ2_SET;
                    INV_PROGRAMMING = FALSE;                
                break;

                case FREQ1_MONITORING:
                    Uart_Tx_Packet.Uart_Buffer[0] = F1_ADDRESS;
                    Uart_Tx_Packet.Uart_Buffer[1] = FUN_READ;
                    Uart_Tx_Packet.Uart_Buffer[2] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[3] = 0x26;
                    Uart_Tx_Packet.Uart_Buffer[4] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[5] = 0x01;

                    RS485_Packet_Length = 8;
                    Crc_value = CRC16_CCITT( Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length-2));
                    Uart_Tx_Packet.Uart_Buffer[6] = (uint8_t)(Crc_value & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[7] = (uint8_t)(Crc_value >> 8 ) & 0x00ff;

                    if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) // Two wings gate
                    {  
                        RS485_Inverter_Counter = FREQ2_START_STOP;
                    }
                    else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || // One wing gate
                              Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )  // Sliding
                    {
                        RS485_Inverter_Counter = FREQ1_START_STOP;           
                    }
                
                    RS485_Inverter_Error = FREQ1_MONITORING;                
                break;
                
                case FREQ2_MONITORING:
                    Uart_Tx_Packet.Uart_Buffer[0] = F2_ADDRESS;
                    Uart_Tx_Packet.Uart_Buffer[1] = FUN_READ;
                    Uart_Tx_Packet.Uart_Buffer[2] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[3] = 0x26;
                    Uart_Tx_Packet.Uart_Buffer[4] = 0x00;
                    Uart_Tx_Packet.Uart_Buffer[5] = 0x01;

                    RS485_Packet_Length = 8;
                    Crc_value = CRC16_CCITT( Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length-2));
                    Uart_Tx_Packet.Uart_Buffer[6] = (uint8_t)(Crc_value & 0x00ff);
                    Uart_Tx_Packet.Uart_Buffer[7] = (uint8_t)(Crc_value >> 8 ) & 0x00ff;

                    RS485_Inverter_Counter = FREQ1_START_STOP;           
                    RS485_Inverter_Error = FREQ2_MONITORING;            
                break;
                } 

                UART_Send(Uart_Tx_Packet.Uart_Buffer, (RS485_Packet_Length + 2));
                RS485_PACKET_SENT = FALSE;
                RS485_TRANSMIT_ENABLE = FALSE;
            }
        }
    }
}


uint16_t CRC16_CCITT ( uint8_t * buf_ptr, uint16_t buf_size)
{
    static uint16_t CRC_value, flag, buf_counter,buf_for;

    buf_counter = 0;
    CRC_value = 0xffff;

    while( buf_size-- > 0 ) 
    {
        CRC_value ^= buf_ptr[buf_counter];
        buf_counter += 1;
        for (buf_for = 0; buf_for <= 7; buf_for++ )
        {
            flag = CRC_value & 0x0001;
            CRC_value  >>=1;
            if ( flag == 0x0001 )
                CRC_value ^= 0xA001;;
        }
    }
    return CRC_value;
}

void Inputs_On_Off ( GPIO_TypeDef* GPIOx, 
                     uint16_t GPIO_Pin,
                     uint8_t Type,
                     uint32_t * Source, 
                     uint32_t Marker )
{
    if ( Type == 0 )
    {
        if ( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0 )
            *Source |= Marker;
        else
            *Source &= ~Marker;
    }
    else if ( Type == 1 )
    {
        if ( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 1 )
            *Source |= Marker;
        else
            *Source &= ~Marker;        
    }
}


void Analog_Inputs_Fun( uint16_t Analog,
                        uint8_t Type,
                        uint8_t Fun,
                        uint32_t * Source, 
                        uint32_t Marker )
{
    uint16_t Safety_Edge_Value;
    
    if ( Fun != 0 )//No OFF
    {
        if ( Type == 0 )//2.0kohm
        {
            Safety_Edge_Value = SAFETY_EDGE_2_0_KOHM;
        }
        else if ( Type == 1 )//4.1kohm
        {
            Safety_Edge_Value = SAFETY_EDGE_4_1_KOHM;
        }
        else if ( Type == 2 )//8.2kohm
        {
            Safety_Edge_Value = SAFETY_EDGE_8_2_KOHM;
        }
        else if ( Type == 3 )//16.4kohm
        {
            Safety_Edge_Value = SAFETY_EDGE_16_4_KOHM;
        }

        if ( Analog < (Safety_Edge_Value - Service_Variables.Serv_Vars.Serwis_005) )
        {
            *Source |= Marker;
        }
        else if ( Analog >= Service_Variables.Serv_Vars.Serwis_006 )
        {
            *Source |= Marker;
        }
        else
        {
            *Source &= ~Marker;
        }            
    }
    else // OFF
    {
       *Source &= ~Marker;
    }
}


void Motors_Enable_Fun ( void )
{
    Motors_Enable = 0;

    if ( Machine_State == WG_POWER_ON_CLOSING_1 )
        Motors_Enable |= MOTOR_1_CLOSING;
    
    if ( Machine_State == WG_POWER_ON_CLOSING_2 )
        Motors_Enable |= MOTOR_2_CLOSING;
        
    if ( Machine_State == WG_POWER_ON_CLOSING_1_2 )
        Motors_Enable |= (MOTOR_1_CLOSING | MOTOR_2_CLOSING);
        
    if ( Machine_State == WG_CLOSING_1 )
        Motors_Enable |= MOTOR_1_CLOSING;
        
    if ( Machine_State == WG_CLOSING_2 )
        Motors_Enable |= MOTOR_2_CLOSING;
        
    if ( Machine_State == WG_CLOSING_1_2 )
        Motors_Enable |= (MOTOR_1_CLOSING | MOTOR_2_CLOSING);
        
    if ( Machine_State == WG_OPENING_1 )
        Motors_Enable |= MOTOR_1_OPENING;
        
    if ( Machine_State == WG_OPENING_2 )
        Motors_Enable |= MOTOR_2_OPENING;
        
    if ( Machine_State == WG_OPENING_1_2 )
        Motors_Enable |= (MOTOR_1_OPENING | MOTOR_2_OPENING);

    if ( Machine_State == START_OPENING )
        Motors_Enable |= MOTOR_1_OPENING;
        
    if ( Machine_State == START_CLOSING )
        Motors_Enable |= MOTOR_2_CLOSING;

    if ( Machine_State == OP_AL_BACK )
        Motors_Enable |= MOTOR_1_CLOSING;

    if ( Machine_State == CL_AL_BACK )
        Motors_Enable |= MOTOR_1_OPENING;

    if ( Machine_State == SENSOR_SETTING && Screen_Number == CZUJNIKI1 )
    {
        if ( Keyboards_Level & KEY_LEFT )
        {
            if ( Edit_Parameter_Counter <= 1)
            {
                Motors_Enable |= MOTOR_1_CLOSING;
            }
            else
            {
                if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
                { 
                    Motors_Enable |= MOTOR_2_CLOSING;
                }
                else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // Reverse
                {
                    Motors_Enable |= MOTOR_1_CLOSING;                
                }
            }
        }
        if ( Keyboards_Level & KEY_RIGHT )
        {
            if ( Edit_Parameter_Counter <= 1)
            {
                Motors_Enable |= MOTOR_1_OPENING;
            }
            else
            {
                if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
                { 
                    Motors_Enable |= MOTOR_2_OPENING;
                }
                else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // Reverse
                {
                    Motors_Enable |= MOTOR_1_OPENING;                
                }
            }
        }
    }
}

void Status_Handling ( void )
{
    if ( Machine_State >= WG_POWER_ON &&
         Machine_State <= WG_POWER_ON_EXT_ALERT )
    {
        Controller_Variables.Controller_Vars.Status = STATUS_WAYDETECT;
    }
    else if (   Machine_State == START_OPENING ||
                Machine_State == WG_OPENING_1 ||
                Machine_State == WG_OPENING_2 ||
                Machine_State == WG_OPENING_1_2 )
    {
        Controller_Variables.Controller_Vars.Status = STATUS_GATEOPENING;
    }
    else if (   Machine_State == START_CLOSING ||
                Machine_State == WG_CLOSING_1 ||
                Machine_State == WG_CLOSING_2 ||
                Machine_State == WG_CLOSING_1_2 )
    {
        Controller_Variables.Controller_Vars.Status = STATUS_GATECLOSING;
    }
    else if (   Machine_State == WG_OPENED_HALF )
    {
        Controller_Variables.Controller_Vars.Status = STATUS_HALFOPENED;
    } 
    else if (   Machine_State == WG_CLOSED_HALF )
    {
        Controller_Variables.Controller_Vars.Status = STATUS_HALFCLOSED;
    }
    else if (   Machine_State == WG_OPENED )
    {
        Controller_Variables.Controller_Vars.Status = STATUS_GATEOPENED;
    }
    else if (   Machine_State == WG_CLOSED )
    {
        Controller_Variables.Controller_Vars.Status = STATUS_GATECLOSED;
    }

    else if (   Machine_State == WG_ALERTS )
    {
        Controller_Variables.Controller_Vars.Status = STATUS_GATEALERT;
    }
    else if (   Machine_State == WG_STOP )
    {
        Controller_Variables.Controller_Vars.Status = STATUS_GATESTOPPED;
    }
}

uint8_t Relays_Handling ( uint8_t Fun )
{
    uint8_t  Relay_Value;

    if ( Fun == 0 ) //Off
    {
        Relay_Value = FALSE;
    }
    else if ( Fun == 1 || Fun == 4 ) //Lamp or pulse lamp
    {
        if ( Machine_State == OPENING_RELAY ||
            Machine_State == OP_AL_STOP ||
            Machine_State == OP_AL_RELAY ||
            Machine_State == OP_AL_BACK ||

            Machine_State == CLOSING_RELAY ||
            Machine_State == CL_AL_STOP ||
            Machine_State == CL_AL_RELAY ||
            Machine_State == CL_AL_BACK ||

            Machine_State == STANDBY_LEARN ||
            Machine_State == LEARN_OPENING ||
            Machine_State == LEARN_OPENED ||
            Machine_State == LEARN_RELAY ||
            Machine_State == LEARN_CLOSING ||
            Machine_State == LEARN_CLOSED ||

            Machine_State == WAIT_4_LEARN ||

            Machine_State == WG_POWER_ON ||
            Machine_State == WG_POWER_ON_CLOSING_1 ||
            Machine_State == WG_POWER_ON_CLOSING_2 ||
            Machine_State == WG_POWER_ON_CLOSING_1_2 ||
            Machine_State == WG_POWER_ON_ALERT ||
            Machine_State == WG_POWER_ON_EXT_ALERT ||

            Machine_State == WG_OPENING_1 ||
            Machine_State == WG_OPENING_2 ||
            Machine_State == WG_OPENING_1_2 ||

            Machine_State == WG_CLOSING_1 ||
            Machine_State == WG_CLOSING_2 ||
            Machine_State == WG_CLOSING_1_2 ||

            Machine_State == PRE_WORNING_OPENING ||
            Machine_State == PRE_WORNING_CLOSING ||
            Machine_State == START_OPENING ||
            Machine_State == START_CLOSING ||
            Machine_State == INVERTER_PROG ||
            Machine_State == INVERTER_ERR ||
            Machine_State == PH_WAIT_OPENING ||
            Machine_State == PH_WAIT_CLOSING ||
            Machine_State == WG_OPENING_ALERTS)
        {
            if ( Fun == 1 )
            {
                Relay_Value = TRUE;
            }
            else if ( Fun == 4 )
            { 
                if ( PULSE_LAMP_FLAG == TRUE )
                {
                    Relay_Value = TRUE;
                }
                else
                {
                    Relay_Value = FALSE;
                }
            }
        } 
        else
        {
            Relay_Value = FALSE;
        }      
    }
    else if ( Fun == 2 ) //Green
    {
        if ( Machine_State == WG_OPENED )
        {
            Relay_Value = TRUE;
        } 
        else
        {
            Relay_Value = FALSE;
        }    
    }
    else if ( Fun == 3 ) //Red
    {
        if (Machine_State == OPENING_RELAY ||
            Machine_State == OP_AL_STOP ||
            Machine_State == OP_AL_RELAY ||
            Machine_State == OP_AL_BACK ||

            Machine_State == CLOSING_RELAY ||
            Machine_State == CL_AL_STOP ||
            Machine_State == CL_AL_RELAY ||
            Machine_State == CL_AL_BACK ||

            Machine_State == STANDBY_LEARN ||
            Machine_State == LEARN_OPENING ||
            Machine_State == LEARN_OPENED ||
            Machine_State == LEARN_RELAY ||
            Machine_State == LEARN_CLOSING ||
            Machine_State == LEARN_CLOSED ||

            Machine_State == SW_LOCKED ||
            Machine_State == WAIT_4_LEARN ||

            Machine_State == WG_POWER_ON ||
            Machine_State == WG_POWER_ON_CLOSING_1 ||
            Machine_State == WG_POWER_ON_CLOSING_2 ||
            Machine_State == WG_POWER_ON_CLOSING_1_2 ||
            Machine_State == WG_POWER_ON_ALERT ||
            Machine_State == WG_POWER_ON_EXT_ALERT ||

            Machine_State == WG_OPENING_1 ||
            Machine_State == WG_OPENING_2 ||
            Machine_State == WG_OPENING_1_2 ||

            Machine_State == WG_CLOSING_1 ||
            Machine_State == WG_CLOSING_2 ||
            Machine_State == WG_CLOSING_1_2 ||

            Machine_State == WG_ALERTS ||
            Machine_State == WG_STOP ||
            Machine_State == WG_EXT_ALERT ||

            Machine_State == PRE_WORNING_OPENING ||
            Machine_State == PRE_WORNING_CLOSING ||
            Machine_State == START_OPENING ||
            Machine_State == START_CLOSING ||
            Machine_State == INVERTER_PROG ||
            Machine_State == INVERTER_ERR ||
            Machine_State == SENSOR_SETTING ||
            
            Machine_State == PH_WAIT_OPENING ||
            Machine_State == PH_WAIT_CLOSING ||
            Machine_State == WG_OPENING_ALERTS)
        {
            if ( PULSE_LAMP_FLAG == TRUE )
            {
                Relay_Value = TRUE;
            }
            else
            {
                Relay_Value = FALSE;
            }        
        }
        else if ( Machine_State == WG_CLOSED ||
                  Machine_State == WG_CLOSED_HALF )
        {
            Relay_Value = TRUE;
        } 
        else
        {
            Relay_Value = FALSE;
        } 
    }
    else if ( Fun == 5 ) //S Zewnetrzny
    {
        if (Machine_State == START_OPENING ||
            Machine_State == WG_OPENING_1 ||
            Machine_State == WG_OPENING_2 ||
            Machine_State == WG_OPENING_1_2 ||

            Machine_State == WG_OPENED )
        {
            Relay_Value = TRUE;
        } 
        else
        {
            Relay_Value = FALSE;
        }  
    }
    else if ( Fun == 6 ) //S Zwrotny otw
    {
        if ( Machine_State == WG_OPENED )
        {
            Relay_Value = TRUE;
        } 
        else
        {
            Relay_Value = FALSE;
        }     
    }
    else if ( Fun == 7 ) //S Zwrotny Zam
    {
        if ( Machine_State == WG_CLOSED )
        {
            Relay_Value = TRUE;
        } 
        else
        {
            Relay_Value = FALSE;
        }     
    }
    else if ( Fun == 8 ) //Elektromagnes
    {
        if ( Machine_State == WG_CLOSED ||
             Machine_State == WG_STOP )
        {
            Relay_Value = TRUE;
        } 
        else
        {
            Relay_Value = FALSE;
        }     
    }
    else if ( Fun == 9 )//Stop
    {
        if ( Controller_Variables.Controller_Vars.Inputs_Error & INPUT_STOP )
        {
            Relay_Value = TRUE;
        } 
        else
        {
            Relay_Value = FALSE;
        } 
    }
    else if ( Fun == 10 )//Safety edges
    {

        if ((Inputs_Level & INPUT7) !=0 ||
            (Inputs_Level & INPUT8) !=0 ||
            (Inputs_Level & INPUT9) !=0 ||
            (Inputs_Level & INPUT10) !=0 )
        {
            Relay_Value = TRUE;
        } 
        else
        {
            Relay_Value = FALSE;
        } 
    }


    return Relay_Value;
}

void AS5040_Angle_Handling ( void )
{
    if ( Machine_State == WG_POWER_ON ||
         Machine_State == WG_CLOSED ||
         Machine_State == WG_CLOSED_HALF ||
         Machine_State == WG_OPENED_HALF ||
         Machine_State ==  WG_OPENED ||
         Machine_State == WG_STOP ||
         Machine_State == INVERTER_PROG )
    {
        Angle1_Max = Controller_Variables.Controller_Vars.MSens1_Pulse_High + Controller_Variables.Controller_Vars.MSens1_Pulse_Low;
        Angle2_Max = Controller_Variables.Controller_Vars.MSens2_Pulse_High + Controller_Variables.Controller_Vars.MSens2_Pulse_Low;
    }

    if (Angle1_Max > 1060)
        Angle1_Max = 1060;

    if (Angle2_Max > 1060)
        Angle2_Max = 1060;

    Controller_Variables.Controller_Vars.MSens1_Angle = Controller_Variables.Controller_Vars.MSens1_Pulse_High;
    Controller_Variables.Controller_Vars.MSens2_Angle = Controller_Variables.Controller_Vars.MSens2_Pulse_High;

    Controller_Variables.Controller_Vars.Deg_Angle1_Op = (uint16_t)((Controlling_Variables.Ctrl_Vars.Angle1_Op*3600)/Angle1_Max);
    Controller_Variables.Controller_Vars.Deg_Angle1_Cl = (uint16_t)((Controlling_Variables.Ctrl_Vars.Angle1_Cl*3600)/Angle1_Max);

    Controller_Variables.Controller_Vars.Deg_Angle2_Op = (uint16_t)((Controlling_Variables.Ctrl_Vars.Angle2_Op*3600)/Angle2_Max);
    Controller_Variables.Controller_Vars.Deg_Angle2_Cl = (uint16_t)((Controlling_Variables.Ctrl_Vars.Angle2_Cl*3600)/Angle2_Max);

    Controller_Variables.Controller_Vars.Deg_MSens1_Angle = (uint16_t)((Controller_Variables.Controller_Vars.MSens1_Angle *3600)/Angle1_Max);
    Controller_Variables.Controller_Vars.Deg_MSens2_Angle = (uint16_t)((Controller_Variables.Controller_Vars.MSens2_Angle *3600)/Angle2_Max);


//TEST
    /*
    if ( Machine_State == WG_CLOSED ||
         Machine_State == WG_OPENED )
    {
        Frequency1_Memory = Controlling_Variables.Ctrl_Vars.Freq1;        
        Frequency2_Memory = Controlling_Variables.Ctrl_Vars.Freq2;        
    }  
    else if ( Machine_State == WG_CLOSED_HALF )
    {
    
    }
    else if ( Machine_State == WG_OPENED_HALF )
    {
    
    }
*/
//WG_ALERTS
//WG_STOP
//PH_WAIT_OPENING
//PH_WAIT_CLOSING
//WG_OPENING_ALERTS, 

//TEST
}

void Motor_24VDC_handling ( void )
{
    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 ) //F24VDC
    {
        if ( Motors_Enable & MOTOR_1_OPENING )
        {
            Manual_Values.Values.Mos1_Dir_Manual_Value = FALSE;
        }
        else if ( Motors_Enable & MOTOR_1_CLOSING )
        {
            Manual_Values.Values.Mos1_Dir_Manual_Value = TRUE;
        }
        else
        {
            Manual_Values.Values.Mos1_Manual_Value = 0;
            Manual_Values.Values.Mos1_Dir_Manual_Value = FALSE;    
        }
    }
    //Manual_Values.Values.Mos2_Manua2_Value = 0;


}
/*******************************************************************************
* End file sys.c
*******************************************************************************/


