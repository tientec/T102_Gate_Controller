#ifndef _SYS_H
#define _SYS_H

/*******************************************************************************
********************************************************************************
* File Name          : sys.h
* Author             : Tomasz Nowak
* Version            : V1.00a
* Date               : 27/01/2012
* Description        : sys.c header file
********************************************************************************
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/


/*******************************************************************************
* Exported Preprocessor #define Constants
*******************************************************************************/
#define STARTUP_TIME		100
#define KBD_SAMPLE_TIME		1
#define INPUTS_SAMPLE_TIME  3
#define SCREEN_RELOAD_TIME  100
#define T_SAMPLE_TIME       3
#define PULSE_TIME          100

#define OPEN_CLOSE_GATE         0x01
#define OPEN_CLOSE_GATE1        0x02
#define OPEN_CLOSE_GATE2        0x04
#define OPEN_CLOSE_GATE3        0x08
#define OPEN_CLOSE_GATE4        0x10
#define OPEN_CLOSE_GATE5        0x20
#define OPEN_CLOSE_GATE6        0x40
#define OPEN_CLOSE_GATE7        0x80

#define OPEN_HALF_CLOSE_GATE    0x08

#define SAFETY_EDGE_2_0_KOHM   1030
#define SAFETY_EDGE_4_1_KOHM   1770
#define SAFETY_EDGE_8_2_KOHM   2800
#define SAFETY_EDGE_16_4_KOHM  3850


#define     INPUT1              0x00000001
#define     INPUT2              0x00000002
#define     INPUT3              0x00000004
#define     INPUT4              0x00000008
#define     INPUT5              0x00000010
#define     INPUT6              0x00000020
#define     INPUT7              0x00000040
#define     INPUT8              0x00000080
#define     INPUT9              0x00000100
#define     INPUT10             0x00000200
#define     INPUT11             0x00000400
#define     INPUT12             0x00000800
#define     INPUT13             0x00001000
#define     INPUT14             0x00002000
#define     INPUT15             0x00004000
#define     INPUT16             0x00008000
#define     INPUT17             0x00010000
#define     INPUT18             0x00020000
#define     INPUT19             0x00040000
#define     INPUT20             0x00080000

#define KEY_ENTER           0x01
#define KEY_ESCAPE          0x02
#define KEY_LEFT            0x04
#define KEY_UP              0x08
#define KEY_RIGHT           0x10
#define KEY_DOWN            0x20
#define KEY_TEST            0x40
#define KEY_REALEASE        0x7F

#define PORT_OC1_OUT        GPIOA
#define PORT_OC2_OUT        GPIOA

#define PIN_OC1_OUT         GPIO_Pin_10
#define PIN_OC2_OUT         GPIO_Pin_9

#define PORT_MOS1_OUT       GPIOA
#define PORT_MOS2_OUT       GPIOC

#define MOS1_TIMER         TIM1
#define MOS2_TIMER         TIM3

#define PIN_MOS1           GPIO_Pin_8
#define PIN_MOS2           GPIO_Pin_9

#define PORT_MOSFET1_DIR   GPIOB
#define PIN_MOSFET1_DIR    GPIO_Pin_2

#define PORT_RELAY1         GPIOB
#define PORT_RELAY2         GPIOA
#define PORT_RELAY3         GPIOB
#define PORT_RELAY4         GPIOB
#define PORT_RELAY5         GPIOB
#define PORT_RELAY6         GPIOC

#define PIN_RELAY1          GPIO_Pin_3
#define PIN_RELAY2          GPIO_Pin_15
#define PIN_RELAY3          GPIO_Pin_11
#define PIN_RELAY4          GPIO_Pin_10
#define PIN_RELAY5          GPIO_Pin_5
#define PIN_RELAY6          GPIO_Pin_13

#define PORT_BUZZER         GPIOA
#define PIN_BUZZER          GPIO_Pin_9

#define PORT_IN1            GPIOA
#define PORT_IN2            GPIOC
#define PORT_IN3            GPIOC
#define PORT_IN4            GPIOC
#define PORT_IN5            GPIOC
#define PORT_IN6            GPIOC
#define PORT_IN7            GPIOC
#define PORT_IN8            GPIOC
#define PORT_IN9            GPIOB
#define PORT_IN10           GPIOB
#define PORT_IN11           GPIOA
#define PORT_IN12           GPIOB

#define PORT_IN_INPUTS      GPIOC
#define PORT_IN_KEYBOARD    GPIOC

#define PIN_IN1             GPIO_Pin_14
#define PIN_IN2             GPIO_Pin_6
#define PIN_IN3             GPIO_Pin_3
#define PIN_IN4             GPIO_Pin_2
#define PIN_IN5             GPIO_Pin_1
#define PIN_IN6             GPIO_Pin_0
#define PIN_IN7             GPIO_Pin_4
#define PIN_IN8             GPIO_Pin_5
#define PIN_IN9             GPIO_Pin_0
#define PIN_IN10            GPIO_Pin_1
#define PIN_IN11            GPIO_Pin_13
#define PIN_IN12            GPIO_Pin_4

#define PIN_IN_INPUTS       GPIO_Pin_7
#define PIN_IN_KEYBOARDS    GPIO_Pin_8

#define TRIAC_TH_PORT       GPIOA
#define TRIAC_RL_PORT       GPIOB
#define TRIAC_ZC_PORT       GPIOC

#define TRIAC_TH_PIN        GPIO_Pin_8
#define TRIAC_RL_PIN        GPIO_Pin_2
#define TRIAC_ZC_PIN        GPIO_Pin_9

#define KBD_SEL1_PORT       GPIOC
#define KBD_SEL2_PORT       GPIOC
#define KBD_SEL3_PORT       GPIOC
#define KBD_OUT_PORT        GPIOC

#define KBD_SEL1_PIN        GPIO_Pin_10
#define KBD_SEL2_PIN        GPIO_Pin_11
#define KBD_SEL3_PIN        GPIO_Pin_12
#define KBD_OUT_PIN         GPIO_Pin_8


#define RS485_DIR_PORT      GPIOD
#define RS485_DIR_PIN       GPIO_Pin_2

/*******************************************************************************
* Exported Preprocessor #define MACROS
*******************************************************************************/


/*******************************************************************************
* Exported Type Declarations
*******************************************************************************/
typedef struct {
    uint8_t Keyboard_Memory;
    uint8_t Keyboard_State;
    uint8_t Keyboard_Flag;
} _Keyboard;

typedef enum {
	T_1msec = 0,
	T_10msec,
	T_100msec,
	T_1sec,
	T_1min,
} _Sys_Tmr_Intervals;

typedef union {
	volatile uint32_t Time_Table[5];
	struct {
		volatile uint32_t Timer_1ms;
		volatile uint32_t Timer_10ms;
		volatile uint32_t Timer_100ms;
		volatile uint32_t Timer_1s;
		volatile uint32_t Timer_1min;
	} Counters;
} _Timers;

typedef struct {
	uint32_t Timer;
} _System_Timers;

typedef union {
    uint8_t Uart_Buffer[64];
    struct {
        uint8_t Address;
        uint8_t Fun_Code;    
        uint8_t Data[62];
    } Packet;
} _Uart_Packet;

class Printer
    {
    int_16
        a;
        b;
        c;
    };
/*******************************************************************************
* Exported Const Object Declarations
*******************************************************************************/

Printer Printer1;
/*******************************************************************************
* Exported Object Declarations
*******************************************************************************/
extern _Timers System_Timers;
extern _System_Timers Keyboard_Timer;
extern _System_Timers Inputs_Timer;
extern _System_Timers Startup_Timer;
extern _System_Timers Pulse_Timer;
extern _System_Timers Screen_Reload_Timer;
extern _System_Timers Temperature_Timer;

extern _System_Timers Pulse_OC1_Timer;
extern _System_Timers Pulse_OC2_Timer;
extern _System_Timers Pulse_RL1_Timer;
extern _System_Timers Pulse_RL2_Timer;
extern _System_Timers Pulse_RL3_Timer;
extern _System_Timers Pulse_RL4_Timer;
extern _System_Timers Pulse_RL5_Timer;
extern _System_Timers Pulse_RL6_Timer;

extern _Keyboard Keyboard;
extern _Keyboard Inputs;

extern volatile uint32_t Interval;
extern volatile uint32_t Interval_Sec;

extern volatile uint32_t Inputs_Level;
extern volatile uint32_t Inputs_Level_Test;

extern uint8_t Keyboards_Level;

extern _Uart_Packet Uart_Tx_Packet;
extern _Uart_Packet Uart_Rx_Packet;

extern uint8_t Motors_Enable;

extern bool ADC_MEASURED;

extern uint16_t Crc_check;
extern uint16_t Crc_received;
/*******************************************************************************
* Function Name  : Heat_Cool
* Description    : Heater and ventilation handling
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

/*******************************************************************************
* Exported Function Prototypes
*******************************************************************************/
void Sys_Init ( void );
void Sys_sys ( void );
void System_Timer_Setting ( uint32_t * Timer_Counter, uint16_t Time_Value, _Sys_Tmr_Intervals Sys_Tmr_Intervals );
uint8_t System_Timer_Check ( uint32_t * Timer_Counter, _Sys_Tmr_Intervals Sys_Tmr_Intervals );
uint8_t Square_Generator ( uint32_t * Timer_Counter, uint16_t Time_Value, _Sys_Tmr_Intervals Sys_Tmr_Intervals );
void Keyboard_Handling ( void );
void Inputs_Handling ( void );
void Analog_Measure ( void );
void AS5040_Angle_Handling ( void );
bool  Periods_Handling ( bool Period1_Enable,
                         bool Period2_Enable,
                         uint8_t Hour_1,
                         uint8_t Hour_2,
                         uint8_t Hour_3,
                         uint8_t Hour_4,
                         uint8_t Minute_1,
                         uint8_t Minute_2,
                         uint8_t Minute_3,
                         uint8_t Minute_4 );
void Internal_Fan_Control ( void );
void Input_Output_Test ( void );
void Enable_Manual_Control ( void );
void Disable_Manual_Control ( void );
void Disable_Manual_Values ( void );
void RS485_Send ( void );
void Motors_Enable_Fun ( void );
void Status_Handling ( void );
void Motor_24VDC_handling ( void );

uint16_t CRC16_CCITT ( uint8_t * buf_ptr, uint16_t buf_size);

void Inputs_On_Off ( GPIO_TypeDef* GPIOx, 
                     uint16_t GPIO_Pin,
                     uint8_t Type,
                     uint32_t * Source, 
                     uint32_t Marker );
                     
void Analog_Inputs_Fun( uint16_t Analog,
                        uint8_t Type,
                        uint8_t Fun,
                        uint32_t * Source, 
                        uint32_t Marker );
                        
uint8_t Relays_Handling ( uint8_t Fun );
/*******************************************************************************
 * Exported Inline Function Definitions and #define Function-Like Macros
*******************************************************************************/


/*******************************************************************************
* End fo file sys.h
*******************************************************************************/
#endif /*_SYS_H*/



