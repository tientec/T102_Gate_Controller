#ifndef _CONTROL_H
#define _CONTROL_H

/*******************************************************************************
********************************************************************************
* File Name          : control.h
* Author             : Tomasz Nowak / GASTOP
* Version            : V1.00a
* Date               : 04/08/2011
* Description        : control.c header file
********************************************************************************
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/


/*******************************************************************************
* Exported Preprocessor #define Constants
*******************************************************************************/
#define ENCODER_OFFSET          100
#define MAGNETIC_SENSOR_OFFSET  1000

#define INPUT_STOP              0x0001
#define INPUT_SE1               0x0002
#define INPUT_SE2               0x0004
#define INPUT_SE3               0x0008
#define INPUT_SE4               0x0010
#define INPUT_PHOTO1            0x0020
#define INPUT_ENCODER           0x0040

#define F1_DISCONNECTED         0x0080
#define F2_DISCONNECTED         0x0100

#define CURRENT_OV1             0x0200
#define CURRENT_OV2             0x0400

#define INVERTERS_CONNECTED     0x0180
#define INPUT_SE_RELEASED       0x001E
#define WG_ALL_ALERTS           0x07BE
#define NO_SE_ALERTS            0x07A0
#define NO_PHOTO_ALL_ALERTS     0x079E

#define DC24V_ALL_ALERTS        0x063E
#define DC24V_NO_SE_ALERTS      0x0620

#define MASTER_PACKET_LENGTH    14
#define SLAVE_PACKET_LENGTH     8

#define UART_SLAVE_ACK       0x2B
#define UART_SLAVE_START     0x21
#define UART_SLAVE_STOP      0xAA
#define UART_SLAVE_FINISH    0x78
#define UART_SLAVE_RESET     0xC5


#define FREQ1_CONNECTED         0
#define FREQ2_CONNECTED         1
#define FREQ1_START_STOP        2
#define FREQ2_START_STOP        3
#define FREQ_STOP               4
#define FREQ1_SET               5
#define FREQ2_SET               6
#define FREQ1_MONITORING        7
#define FREQ2_MONITORING        8

#define FWD_RUN          0x01
#define REV_RUN           0x02
#define STOP_RUN          0x00

#define F1_ADDRESS       0x01
#define F2_ADDRESS       0x02
#define FUN_TEST         0x08
#define FUN_READ         0x03
#define FUN_WRITE        0x10
#define FUN_ERR_READ     0x83
#define FUN_ERR_TEST     0x89
#define FUN_ERR_WRITE    0x90


#define MOTOR_1_OPENING      0x01
#define MOTOR_2_OPENING      0x02
#define MOTOR_1_CLOSING      0x10
#define MOTOR_2_CLOSING      0x20


#define STATUS_WAYDETECT        0
#define STATUS_GATECLOSED       1
#define STATUS_HALFCLOSED       2
#define STATUS_GATEOPENING      3
#define STATUS_GATEOPENED       4
#define STATUS_HALFOPENED       5
#define STATUS_GATECLOSING      6
#define STATUS_GATESTOPPED      7
#define STATUS_GATEALERT        8

/*******************************************************************************
* Exported Preprocessor #define MACROS
*******************************************************************************/


/*******************************************************************************
* Exported Type Declarations
*******************************************************************************/
typedef enum {

/*0*/  OPENING_RELAY,
/*1*/  OP_AL_STOP,
/*2*/  OP_AL_RELAY,
/*3*/  OP_AL_BACK,

/*4*/  CLOSING_RELAY,
/*5*/  CL_AL_STOP,
/*6*/  CL_AL_RELAY,
/*7*/  CL_AL_BACK,

/*8*/  STANDBY_LEARN,
/*9*/  LEARN_OPENING,
/*10*/ LEARN_OPENED,
/*11*/ LEARN_RELAY,
/*12*/ LEARN_CLOSING,
/*13*/ LEARN_CLOSED,

/*14*/ MANUAL_TEST,
/*15*/ SW_LOCKED,
/*16*/ WAIT_4_LEARN,

/*17*/ WG_POWER_ON,
/*18*/ WG_POWER_ON_CLOSING_1,
/*19*/ WG_POWER_ON_CLOSING_2,
/*20*/ WG_POWER_ON_CLOSING_1_2,
/*21*/ WG_POWER_ON_ALERT,  
/*22*/ WG_POWER_ON_EXT_ALERT,
/*23*/ WG_POWER_ON_CLOSING_RELAY,

/*24*/ WG_CLOSED,
/*25*/ WG_CLOSED_HALF,

/*26*/ WG_OPENING_1,
/*27*/ WG_OPENING_2,
/*28*/ WG_OPENING_1_2,

/*29*/ WG_OPENED_HALF,
/*30*/ WG_OPENED,

/*31*/ WG_CLOSING_1,
/*32*/ WG_CLOSING_2,
/*33*/ WG_CLOSING_1_2,

/*34*/ WG_ALERTS,
/*35*/ WG_STOP,
/*36*/ WG_EXT_ALERT,

/*37*/ PRE_WORNING_OPENING,
/*38*/ START_OPENING,
/*39*/ START_CLOSING,
/*40*/ PRE_WORNING_CLOSING,

/*41*/ INVERTER_PROG,
/*42*/ INVERTER_ERR,
/*43*/ SENSOR_SETTING,

/*44*/ PH_WAIT_OPENING,
/*45*/ PH_WAIT_CLOSING,
/*46*/ WG_OPENING_ALERTS,

} _Machine_State;

/*******************************************************************************
* Exported Const Object Declarations
*******************************************************************************/


/*******************************************************************************
* Exported Object Declarations
*******************************************************************************/
typedef union {
    uint16_t Pwm_Tab[2];
    struct {
        uint16_t Pwm_Mos1;
        uint16_t Pwm_Mos2;
    } Pwm_Mos;
} _Mosfets_Pwm;

typedef union {
    bool Pulse_Bool_Timer_Tab[18];
    uint8_t Pulse_Byte_Timer_Tab[18];
    uint16_t Pulse_Word_Timer_Tab[9];
    struct {
        bool Pulse1_Flag;
        bool Pulse2_Flag;
        bool Pulse3_Flag;
        bool Pulse4_Flag; 
        bool Pulse5_Flag; 
        bool Pulse6_Flag; 
        uint16_t Timer1;
        uint16_t Timer2;
        uint16_t Timer3;
        uint16_t Timer4;
        uint16_t Timer5;
        uint16_t Timer6;
    } Pulse_Timer_Flags;
} _Pulse_Timer;

typedef union {
    bool Manual_Control_Bool_Tab[11];
    uint8_t Manula_Control_Byte_Tab[11];
    struct {
        bool OC1_Manual;
        bool OC2_Manual;
        bool Relay1_Manual;
        bool Relay2_Manual;
        bool Relay3_Manual;
        bool Relay4_Manual;
        bool Relay5_Manual;
        bool Relay6_Manual;
        bool Mosfet1_Manual;
        bool Mosfet2_Manual;
        bool Mosfet1_Dir_Manual;
    } Manual_Control;
} _Manual_Control;

typedef union {
    bool Pulse_Bool_Tab[6];
    uint8_t Pulse_Byte_Tab[6];
    struct {
        bool Pulse1;
        bool Pulse2;
        bool Pulse3;
        bool Pulse4;
        bool Pulse5;
        bool Pulse6;
    } Pulse_Enable;
} _Pulse_Enable;

typedef union {
    bool Manual_Bool_Values_Tab[14];
    uint8_t Manual_Byte_Value_Tab[14];
    uint16_t Manual_Word_Value_Tab[7];
    struct {
        bool OC1_Manual_Value;
        bool OC2_Manual_Value;
        bool RL1_Manual_Value;
        bool RL2_Manual_Value;
        bool RL3_Manual_Value;
        bool RL4_Manual_Value;
        bool RL5_Manual_Value;
        bool RL6_Manual_Value;
        uint16_t Mos1_Manual_Value;
        uint16_t Mos2_Manual_Value;
        bool Mos1_Dir_Manual_Value;
    } Values;
} _Manual_Values;

typedef struct {
	uint32_t Timer;
} _Timer_Counter;

extern _Timer_Counter Slow_1_Timer;
extern _Timer_Counter Slow_2_Timer;

extern _Timer_Counter Lamp_Timer;


extern volatile  _Machine_State Machine_State;
extern _Manual_Control Manual_Control_Enable;
extern _Manual_Values Manual_Values;
extern _Pulse_Timer Pulse_Relay_Timer;
extern _Pulse_Timer Pulse_OC_Timer;

extern _Pulse_Enable Enable_Pulse_Relays_Off;
extern _Pulse_Enable Enable_Pulse_Oc_Outs_Off;
extern _Mosfets_Pwm Mosfets_Pwm;

extern bool PILOT_ENABLE_DECODING;
extern bool PILOT_CODE_RECEIVED;
extern bool PILOT_LOCKED;

extern bool LEARN_WAY_FLAG;
extern bool ENCODER_SIGNAL_DETECTED;
extern bool ENCODER_ENABLE_FLAG;

extern bool RECEIVER_DISABLED;
extern bool RS485_TRANSMIT_ENABLE;
extern bool RS485_PACKET_SENT;

extern bool OPENING_MARKER;

extern bool WG_TIMER_FLAG;


extern bool OPENED_WAIT;

extern bool SLOW_ENABLE_FLAG_1;
extern bool SLOW_ENABLE_FLAG_2;

extern bool PULSE_LAMP_FLAG;

extern uint8_t RS485_Inverter_Counter;
extern uint8_t RS485_Inverter_Error;
extern uint8_t RS485_Packet_Length;
extern uint8_t RS485_Comm_Err_Counter1;
extern uint8_t RS485_Comm_Err_Counter2;
extern uint16_t RS485_Counter;
extern uint8_t RS485_Packet_Counter;

extern uint8_t F1_Current_Counter;
extern uint8_t F2_Current_Counter;

extern uint16_t Angle1_Max;
extern uint16_t Angle2_Max;


extern uint16_t Angle1_Memory;
extern uint16_t Angle2_Memory;
/*******************************************************************************
* Exported Function Prototypes
*******************************************************************************/
void Control ( void );
void On_Off_Output_Handling ( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, bool On_Off_State, bool On_Off_Pulse, bool On_Off_Pulse_Value, bool On_Off_Manual, bool On_Off_Manual_Value, bool On_Off_Enable );
void Pwm_Output_Handling ( TIM_TypeDef* TIMx, uint16_t Pwm_Value, bool Pwm_State, void (*TimComparePtr)(TIM_TypeDef* TIMxx, uint16_t Tim_Value), bool Pwm_Manual, uint16_t Pwm_Manual_Value, bool Pwm_Enable);

void Inputs_Alert ( void );
void Inputs_Stop ( void );

/*******************************************************************************
 * Exported Inline Function Definitions and #define Function-Like Macros
*******************************************************************************/


/*******************************************************************************
* End fo file control.h
*******************************************************************************/
#endif /*_CONTROL_H*/



