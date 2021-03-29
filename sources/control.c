/*******************************************************************************
********************************************************************************
* File Name          : control.c
* Author             : Tomasz Nowak / GASTOP
* Version            : V1.00A
* Date               : 04/08/201
1
* Description        : Controllng inputs and outputs - algorithm handling
********************************************************************************
*******************************************************************************/


/*******************************************************************************
* Header Files
----*******************************************************************************/
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
* Local Function Prototypes
*******************************************************************************/
void Op_Al_Stop_Fun ( void );
void Cl_Al_Stop_Fun ( void );

static void Learm_Standby_Fun ( void );
static void Learm_Opening_Fun ( void );
static void Learm_Opened_Fun ( void );
static void Learm_Closing_Fun ( void );
static void Learm_Closed_Fun ( void );
static void Wait_4_Learn_Fun ( void );

//Wave generator functions - Controller 2
static void WG_Inputs_Closed ( void );
static void WG_Inputs_Opened ( void );
static void WG_Inputs_Closed_Half ( void );
static void WG_Inputs_Opened_Half ( void );
static void WG_Inputs_Opening ( void );
static void WG_Inputs_Closing ( void );
static void WG_Inputs_Closed_Handling_Function ( void );
static void WG_Inputs_Opened_Handling_Function ( void );
static void WG_Inputs_Closed_Half_Handling ( void );
static void WG_Inputs_Opened_Half_Handling ( void );

static void WG_Stop_Closed ( void );
static void WG_Stop_Opened ( void );
static void WG_Stop_Opened_Half ( void );

static void WG_Power_On_Fun ( void );

static void WG_Opening_Fun ( void );
static void WG_Closing_Fun ( void );

static void WG_Stop_Release_Fun ( void );

static void Wg_Power_On_Alerts ( void );
static void Wg_Power_On_Alerts_Release ( void );

static void Wg_Alerts_Opening_Handling ( void );
static void Wg_Alerts_Closing_Handling ( void );
static void Wg_Alerts_Release ( void );

static void Inverters_Speed_Control ( void );

static void Gate_Opened_Fun ( void );
static void Inverters_Setting_Fun ( void );

static void Reset_Inputs ( void );

static void DC_Motor_Invert_Direction ( void );

static void Cl_Start_MS_Fun ( void );
static void Op_Start_MS_Fun ( void );

static void Inputs_Back_Handling (void );

static void Release_Photo_Opening ( void );
static void Release_Photo_Closing ( void );
static void Wg_Alerts_Opening_Release ( void );

static void Opening_Pre_Worning_Fun ( void );
static void Closing_Pre_Worning_Fun ( void );

static void Inputs_Pre_Opening ( void );
static void Inputs_Pre_Closing ( void );

uint8_t Position_Closed_1 ( uint16_t Position_1_Range );
uint8_t Position_Closed_2 ( uint16_t Position_2_Range );
uint8_t Position_Opened_1 ( uint16_t Position_3_Range );
uint8_t Position_Opened_2 ( uint16_t Position_4_Range );
/*******************************************************************************
* Local Object Definitions
*******************************************************************************/
/* Variables for system timers */
typedef enum _Mosfet1_Dir {
	NORMAL = 0,
	REVERSE = 1,
} Mosfet1_Dir;

typedef struct {
    bool Mosfet1;
	bool Mosfet2;
	Mosfet1_Dir Mosfet1_Direction;
    _Mosfets_Pwm * Mosfets_Pwm_Ptr;
} _Mosfets_Status;

typedef struct {
    bool OC1;
    bool OC2;
    _Pulse_Enable * OC_Pulse_Ptr;
    _Pulse_Timer * OC_Timer_Ptr;
} _OC_Status;

typedef struct {
    bool Relay1;
    bool Relay2;
    bool Relay3;
    bool Relay4;
    bool Relay5;
    bool Relay6;
    _Pulse_Enable * Relay_Pulse_Ptr;
    _Pulse_Timer * Relays_Timer_Ptr;
} _Relays_Status;

typedef struct {
	uint16_t * Time_Value;
	_Sys_Tmr_Intervals Resolution;
	_Machine_State Next;
	_Timer_Counter * Tmr_Cntr_Ptr;
} _Time_Connection;

typedef struct {
	void (*Control_fun)(void);
	_Machine_State Next[8];
} _Function_Control;


typedef struct {
	const _OC_Status * OC_Status_Ptr;
    const _Mosfets_Status * Mosfets_Status_Ptr;
    const _Relays_Status * Relays_Status_Ptr;
	const _Time_Connection * Time_Connection_Ptr;
	const _Function_Control * Function_Ptr;
	void (*Inputs_fun)(void);
    void (*Outputs_fun)(void);
} _Control_Variables;

_Timer_Counter Opening_Closing_Timer;
_Timer_Counter Relay_Timer;
_Timer_Counter Encoder_Timer;
_Timer_Counter WG_Timer;
_Timer_Counter Opened_Timer;
_Timer_Counter Slow_1_Timer;
_Timer_Counter Slow_2_Timer;
_Timer_Counter Pre_Worning_Timer;

_Timer_Counter Braking_1_Timer;
_Timer_Counter Braking_2_Timer;

_Timer_Counter Lamp_Timer;

_Time_Connection Opening_Relay = { &Service_Variables.Serv_Vars.Serwis_004, T_10msec, WG_OPENING_1, &Relay_Timer };
_Time_Connection Closing_Relay = { &Service_Variables.Serv_Vars.Serwis_004, T_10msec, WG_CLOSING_1, &Relay_Timer };
_Time_Connection Power_On_Closing_Relay = { &Service_Variables.Serv_Vars.Serwis_004, T_10msec, WG_POWER_ON_CLOSING_1, &Relay_Timer };

_Time_Connection Opening_Al_Relay = { &Service_Variables.Serv_Vars.Serwis_004, T_10msec, OP_AL_BACK, &Relay_Timer };
_Time_Connection Closing_Al_Relay = { &Service_Variables.Serv_Vars.Serwis_004, T_10msec, CL_AL_BACK, &Relay_Timer };

_Time_Connection Op_Alert_Back = { &Service_Variables.Serv_Vars.Serwis_007, T_10msec, WG_STOP, &Opening_Closing_Timer };
_Time_Connection Cl_Alert_Back = { &Service_Variables.Serv_Vars.Serwis_007, T_10msec, WG_STOP, &Opening_Closing_Timer };

_Time_Connection Learning_Relay = { &Service_Variables.Serv_Vars.Serwis_010, T_10msec, LEARN_CLOSING, &Relay_Timer };

_Time_Connection Opening_Start = { &Service_Variables.Serv_Vars.Serwis_018, T_10msec, WG_OPENING_1_2, &Opening_Closing_Timer };
_Time_Connection Closing_Start = { &Service_Variables.Serv_Vars.Serwis_018, T_10msec, WG_CLOSING_1_2, &Opening_Closing_Timer };

_Function_Control Op_Alert_Stop = { Op_Al_Stop_Fun, { OP_AL_RELAY } };
_Function_Control Cl_Alert_Stop = { Cl_Al_Stop_Fun, { CL_AL_RELAY } };

_Function_Control Waiting_4_Learn = { Wait_4_Learn_Fun, { WG_ALERTS, WG_ALERTS, WAIT_4_LEARN, WAIT_4_LEARN, WG_ALERTS, WG_ALERTS, STANDBY_LEARN  } };
_Function_Control LearnStandby = { Learm_Standby_Fun, { LEARN_OPENING, WAIT_4_LEARN } };
_Function_Control LearnOpening = { Learm_Opening_Fun, { WG_ALERTS, WG_ALERTS, LEARN_OPENED, WG_ALERTS, WG_ALERTS, WG_ALERTS, WAIT_4_LEARN } };
_Function_Control LearnOpened =  { Learm_Opened_Fun, { WG_ALERTS, WG_ALERTS, LEARN_OPENED, LEARN_OPENED, WG_ALERTS, WG_ALERTS, LEARN_RELAY, WAIT_4_LEARN } };
_Function_Control LearnClosing = { Learm_Closing_Fun, { WG_ALERTS, WG_ALERTS, LEARN_CLOSED, WG_ALERTS, WG_ALERTS, WG_ALERTS, WAIT_4_LEARN } };
_Function_Control LearnClosed =  { Learm_Closed_Fun, { WG_CLOSED } };

_Function_Control Wg_Power_On_Wait = { WG_Power_On_Fun, { WG_POWER_ON_CLOSING_1, WG_POWER_ON_CLOSING_2, WG_POWER_ON_CLOSING_1_2, WG_CLOSED, WG_POWER_ON_ALERT, WG_POWER_ON_CLOSING_RELAY  } };
_Function_Control Wg_Power_On_Closing = { WG_Closing_Fun, { WG_POWER_ON_CLOSING_1, WG_POWER_ON_CLOSING_2, WG_POWER_ON_CLOSING_1_2, WG_CLOSED, WG_POWER_ON_ALERT  } };
_Function_Control Wg_Opening = { WG_Opening_Fun, { WG_OPENING_1, WG_OPENING_2, WG_OPENING_1_2, WG_OPENED, WG_OPENED_HALF, WG_ALERTS  } };
_Function_Control Wg_Closing = { WG_Closing_Fun, { WG_CLOSING_1, WG_CLOSING_2, WG_CLOSING_1_2, WG_CLOSED, WG_CLOSED_HALF, WG_ALERTS  } };
_Function_Control Wg_Stop_Release = { WG_Stop_Release_Fun, { WG_POWER_ON, WG_CLOSED, WG_OPENED, WG_OPENED_HALF  } };

_Function_Control Gate_Opened_Time_Wait = { Gate_Opened_Fun, { START_CLOSING, WG_CLOSING_1, CLOSING_RELAY } };
_Function_Control Inverters_Setting = { Inverters_Setting_Fun, { WG_POWER_ON } };
_Function_Control Closing_Start_MS = { Cl_Start_MS_Fun, { WG_CLOSING_1_2 } };
_Function_Control Opening_Start_MS = { Op_Start_MS_Fun, { WG_OPENING_1_2 } };

_Function_Control Pre_Worning_Op = { Opening_Pre_Worning_Fun, { WG_OPENING_1_2 } };
_Function_Control Pre_Worning_Cl = { Closing_Pre_Worning_Fun, { WG_OPENING_1_2 } };

//                                  1      2      PULSE_PTR,TIMER_VALUE*/
const _OC_Status OC_Off          ={ FALSE, FALSE, &Enable_Pulse_Oc_Outs_Off, &Pulse_OC_Timer };

//                                  1      2      3      4      5      6      PULSE_PTR,TIMER_VALUE*/
const _Relays_Status Relays_Off  = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, &Enable_Pulse_Relays_Off, &Pulse_Relay_Timer };

/*                                     1      2      DIR      PWM VALUES*/
const _Mosfets_Status Mosfets_Off_N ={ FALSE, FALSE, NORMAL , &Mosfets_Pwm }; 
const _Mosfets_Status Mosfets_Off_R ={ FALSE, FALSE, REVERSE, &Mosfets_Pwm }; 

_Control_Variables Control_Variables[] = {

/*OPENING_RELAY*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, &Opening_Relay, NULL, NULL, DC_Motor_Invert_Direction },
/*OP_AL_STOP*/   { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Op_Alert_Stop, NULL, NULL },
/*OP_AL_RELAY*/  { &OC_Off, &Mosfets_Off_R, &Relays_Off, &Opening_Al_Relay, NULL, NULL, DC_Motor_Invert_Direction },
/*OP_AL_BACK*/   { &OC_Off, &Mosfets_Off_R, &Relays_Off, &Op_Alert_Back, NULL, &Inputs_Back_Handling, Inverters_Speed_Control },

/*CLOSING_RELAY*/{ &OC_Off, &Mosfets_Off_R, &Relays_Off, &Closing_Relay, NULL, NULL, DC_Motor_Invert_Direction },
/*CL_AL_STOP*/   { &OC_Off, &Mosfets_Off_R, &Relays_Off, NULL, &Cl_Alert_Stop, NULL, DC_Motor_Invert_Direction },
/*CL_AL_RELAY*/  { &OC_Off, &Mosfets_Off_N, &Relays_Off, &Closing_Al_Relay, NULL, NULL, NULL },
/*CL_AL_BACK*/   { &OC_Off, &Mosfets_Off_N, &Relays_Off, &Op_Alert_Back, NULL, &Inputs_Back_Handling, Inverters_Speed_Control },

/*STANDBY_LEARN*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &LearnStandby, NULL, NULL },
/*LEARN_OPENING*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &LearnOpening, NULL, Inverters_Speed_Control },
/*LEARN_OPENED*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &LearnOpened, NULL, NULL },

/*LEARN_RELAY*/  { &OC_Off, &Mosfets_Off_R, &Relays_Off, &Learning_Relay, NULL, NULL, DC_Motor_Invert_Direction },
/*LEARN_CLOSING*/{ &OC_Off, &Mosfets_Off_R, &Relays_Off, NULL, &LearnClosing, NULL, Inverters_Speed_Control },
/*LEARN_CLOSED*/ { &OC_Off, &Mosfets_Off_R, &Relays_Off, NULL, &LearnClosed, NULL, NULL },

/*MANUAL_TEST*/  { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, Input_Output_Test, NULL },  
/*SW_LOCKED*/    { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, NULL, NULL },  
/*WAIT_4_LEARN*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Waiting_4_Learn, NULL, NULL },  

/*************************************************************************************************************************************************/

/*WG_PON*/       { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Power_On_Wait, Reset_Inputs, DC_Motor_Invert_Direction },
/*WG_PON_CLOS_1*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Power_On_Closing, Wg_Power_On_Alerts, Inverters_Speed_Control },
/*WG_PON_CLOS_2*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Power_On_Closing, Wg_Power_On_Alerts, Inverters_Speed_Control },
/*WG_PON_CLO_12*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Power_On_Closing, Wg_Power_On_Alerts, Inverters_Speed_Control },
/*WG_PON_ALERT*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, Wg_Power_On_Alerts_Release, NULL },
/*WG_PON_EXT_AL*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, NULL, NULL },
/*POW_ON_CL_REL*/{ &OC_Off, &Mosfets_Off_R, &Relays_Off, &Power_On_Closing_Relay, NULL, NULL, DC_Motor_Invert_Direction },

/*WG_CLOSED*/    { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, WG_Inputs_Closed, NULL },
/*WG_CLOSED_H*/  { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, WG_Inputs_Closed_Half, NULL },

/*WG_OPENING_1*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Opening, WG_Inputs_Opening, Inverters_Speed_Control },
/*WG_OPENING_2*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Opening, WG_Inputs_Opening, Inverters_Speed_Control },
/*WG_OPENING_12*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Opening, WG_Inputs_Opening, Inverters_Speed_Control },

/*WG_OPENED_H*/  { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, WG_Inputs_Opened_Half, NULL },
/*WG_OPENED*/    { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Gate_Opened_Time_Wait, WG_Inputs_Opened, NULL },

/*WG_CLOSING_1*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Closing, WG_Inputs_Closing, Inverters_Speed_Control },
/*WG_CLOSING_2*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Closing, WG_Inputs_Closing, Inverters_Speed_Control },
/*WG_CLOSING_12*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Closing, WG_Inputs_Closing, Inverters_Speed_Control },

/*WG_ALERTS */   { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, Wg_Alerts_Release, NULL },
/*WG_STOP*/      { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Wg_Stop_Release, NULL, NULL },
/*WG_EXT_ALERT*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, NULL, NULL },

/*PRE_W_OPENING*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Pre_Worning_Op, Inputs_Pre_Opening, NULL },
/*WG_ST_OPENING*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, &Opening_Start, NULL, Reset_Inputs, Inverters_Speed_Control },
/*WG_ST_CLOSING*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, &Closing_Start, NULL, Reset_Inputs, Inverters_Speed_Control },
/*PRE_W_CLOSING*/{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Pre_Worning_Cl, Inputs_Pre_Closing, NULL },

/*INV_PROG*/     { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, &Inverters_Setting, NULL, NULL },
/*INV_ERR*/      { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, NULL, NULL },
/*SENSOR_SETT*/  { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, NULL, Inverters_Speed_Control },

/*PH_WAIT_OPEN*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, NULL, Release_Photo_Opening },
/*PH_WAIT_CLOS*/ { &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, NULL, Release_Photo_Closing },
/*WG_OP_ALERTS */{ &OC_Off, &Mosfets_Off_N, &Relays_Off, NULL, NULL, Wg_Alerts_Opening_Release, NULL },

};

volatile _Machine_State Machine_State = 0;

/*                                        OC1    OC2    RL1    RL2    RL3    RL4    RL5    RL6    MOS1   MOS2 MOS1DIR*/
_Manual_Control Manual_Control_Enable = { FALSE, FALSE, TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE, TRUE, TRUE};
_Manual_Values Manual_Values;
_Pulse_Timer Pulse_Relay_Timer; 
_Pulse_Timer Pulse_OC_Timer;
_Mosfets_Pwm Mosfets_Pwm;

_Pulse_Enable Enable_Pulse_Relays_Off = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
_Pulse_Enable Enable_Pulse_Oc_Outs_Off = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };

bool OPENING_HALF_FLAG;

bool LEARN_WAY_FLAG = FALSE;
bool ENCODER_SIGNAL_DETECTED;
bool ENCODER_ENABLE_FLAG = FALSE;

bool RECEIVER_DISABLED = FALSE;
bool RS485_TRANSMIT_ENABLE = FALSE;
bool RS485_PACKET_SENT = FALSE;

bool OPENING_MARKER = FALSE;

bool WG_TIMER_FLAG = FALSE;

bool ALERTS_FLAG = FALSE;

bool OPENED_WAIT  = FALSE;
bool READY_4_CLOSING = FALSE;
bool CLOSE_GATE_FLAG = FALSE;

bool SLOW_ENABLE_FLAG_1 = TRUE;
bool SLOW_ENABLE_FLAG_2 = TRUE;
bool BRAKING_FLAG_1 = FALSE;
bool BRAKING_FLAG_2 = FALSE;

bool OPEN_ON_LEVEL_14 = FALSE;
bool OPEN_ON_LEVEL_15 = FALSE;
bool OPEN_ON_LEVEL_16 = FALSE;
bool OPEN_ON_LEVEL_17 = FALSE;
bool OPEN_ON_LEVEL_18 = FALSE;
bool OPEN_ON_LEVEL_19 = FALSE;
bool OPEN_ON_LEVEL_20 = FALSE;

bool PULSE_LAMP_FLAG;

bool PHOTO_PRIORITY_ENABLE = FALSE;

bool PRE_WORNING_FLAG = FALSE;

uint8_t RS485_Inverter_Counter = 0;
uint8_t RS485_Inverter_Error = 0;
uint16_t RS485_Counter = 0;
uint8_t RS485_Comm_Err_Counter1 = 0;
uint8_t RS485_Comm_Err_Counter2 = 0;
uint8_t RS485_Packet_Length;
uint8_t RS485_Packet_Counter;

uint8_t F1_Current_Counter = 0;
uint8_t F2_Current_Counter = 0;

uint16_t Time_4_Gate1;
uint16_t Time_4_Gate2;

uint8_t Motors_Enable = 0;

uint16_t Angle1_Max;
uint16_t Angle2_Max;

uint16_t Angle1_Memory;
uint16_t Angle2_Memory;
/*******************************************************************************
* Local Inline Function Definitions and Function-Like Macros
*******************************************************************************/


/*******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
* Function Name  : Control
* Description    : Control functions - algorithm handling
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Control ( void )
{
/*Inputs handling */
    if ( Control_Variables[Machine_State].Inputs_fun != NULL )
    {
        (*Control_Variables[Machine_State].Inputs_fun)();
    }

/*Outputs handling */
    if ( Control_Variables[Machine_State].Outputs_fun != NULL )
    {
        (*Control_Variables[Machine_State].Outputs_fun)();
    }

/* Function for jumping for different machine states*/
	if ( Control_Variables[Machine_State].Function_Ptr != NULL )
	{
		if ( ( Control_Variables[Machine_State].Function_Ptr->Control_fun) != NULL )
		{
			(*Control_Variables[Machine_State].Function_Ptr->Control_fun)();
		}
	}



/* System timer handling - time conection between two different machine states */
    if ( Control_Variables[Machine_State].Time_Connection_Ptr != NULL )
    {
		if ( System_Timer_Check ( &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
							       Control_Variables[Machine_State].Time_Connection_Ptr->Resolution ) == TRUE )
		{
			Machine_State = Control_Variables[Machine_State].Time_Connection_Ptr->Next;
            if ( Control_Variables[Machine_State].Time_Connection_Ptr != NULL )
            {
                System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                                        *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                                        Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;            
            }
		}
	}

//Pulse timers nandling for relays and OC outputsControl_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse1_Flag = Square_Generator ( &Pulse_RL1_Timer.Timer, Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Timer1, T_10msec );

    Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse1_Flag = Square_Generator ( &Pulse_RL1_Timer.Timer, Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Timer1, T_10msec );
    Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse2_Flag = Square_Generator ( &Pulse_RL2_Timer.Timer, Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Timer2, T_10msec );
    Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse3_Flag = Square_Generator ( &Pulse_RL3_Timer.Timer, Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Timer3, T_10msec );
    Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse4_Flag = Square_Generator ( &Pulse_RL4_Timer.Timer, Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Timer4, T_10msec );
    Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse5_Flag = Square_Generator ( &Pulse_RL5_Timer.Timer, Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Timer5, T_10msec );
    Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse6_Flag = Square_Generator ( &Pulse_RL6_Timer.Timer, Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Timer6, T_10msec );

    Control_Variables[Machine_State].OC_Status_Ptr->OC_Timer_Ptr->Pulse_Timer_Flags.Pulse1_Flag = Square_Generator ( &Pulse_OC1_Timer.Timer, Control_Variables[Machine_State].OC_Status_Ptr->OC_Timer_Ptr->Pulse_Timer_Flags.Timer1, T_10msec );
    Control_Variables[Machine_State].OC_Status_Ptr->OC_Timer_Ptr->Pulse_Timer_Flags.Pulse2_Flag = Square_Generator ( &Pulse_OC2_Timer.Timer, Control_Variables[Machine_State].OC_Status_Ptr->OC_Timer_Ptr->Pulse_Timer_Flags.Timer2, T_10msec );

//Relays handling
    On_Off_Output_Handling ( PORT_RELAY1, PIN_RELAY1,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay1,//On_Off_State,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay_Pulse_Ptr->Pulse_Enable.Pulse1,//On_Off_Pulse,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse1_Flag,//On_Off_Pulse_Value,
                             Manual_Control_Enable.Manual_Control.Relay1_Manual,//On_Off_Manual,
                             Manual_Values.Values.RL1_Manual_Value, //On_Off_Manual_Value,
                             TRUE);//On_Off_Enable );

    On_Off_Output_Handling ( PORT_RELAY2, PIN_RELAY2,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay2,//On_Off_State,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay_Pulse_Ptr->Pulse_Enable.Pulse2,//On_Off_Pulse,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse2_Flag,//On_Off_Pulse_Value,
                             Manual_Control_Enable.Manual_Control.Relay2_Manual,//On_Off_Manual,
                             Manual_Values.Values.RL2_Manual_Value, //On_Off_Manual_Value,
                             TRUE);//On_Off_Enable );

    On_Off_Output_Handling ( PORT_RELAY3, PIN_RELAY3,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay3,//On_Off_State,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay_Pulse_Ptr->Pulse_Enable.Pulse3,//On_Off_Pulse,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse3_Flag,//On_Off_Pulse_Value,
                             Manual_Control_Enable.Manual_Control.Relay3_Manual,//On_Off_Manual,
                             Manual_Values.Values.RL3_Manual_Value, //On_Off_Manual_Value,
                             TRUE);//On_Off_Enable );

    On_Off_Output_Handling ( PORT_RELAY4, PIN_RELAY4,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay4,//On_Off_State,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay_Pulse_Ptr->Pulse_Enable.Pulse4,//On_Off_Pulse,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse4_Flag,//On_Off_Pulse_Value,
                             Manual_Control_Enable.Manual_Control.Relay4_Manual,//On_Off_Manual,
                             Manual_Values.Values.RL4_Manual_Value, //On_Off_Manual_Value,
                             TRUE);//On_Off_Enable );


    On_Off_Output_Handling ( PORT_RELAY5, PIN_RELAY5,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay5,//On_Off_State,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay_Pulse_Ptr->Pulse_Enable.Pulse5,//On_Off_Pulse,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse5_Flag,//On_Off_Pulse_Value,
                             Manual_Control_Enable.Manual_Control.Relay5_Manual,//On_Off_Manual,
                             Manual_Values.Values.RL5_Manual_Value, //On_Off_Manual_Value,
                             TRUE);//On_Off_Enable );

    On_Off_Output_Handling ( PORT_RELAY6, PIN_RELAY6,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay6,//On_Off_State,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relay_Pulse_Ptr->Pulse_Enable.Pulse6,//On_Off_Pulse,
                             Control_Variables[Machine_State].Relays_Status_Ptr->Relays_Timer_Ptr->Pulse_Timer_Flags.Pulse6_Flag,//On_Off_Pulse_Value,
                             Manual_Control_Enable.Manual_Control.Relay6_Manual,//On_Off_Manual,
                             Manual_Values.Values.RL6_Manual_Value, //On_Off_Manual_Value,
                             TRUE);//On_Off_Enable );

//OC handling
    On_Off_Output_Handling ( PORT_OC1_OUT, PIN_OC1_OUT,
                             Control_Variables[Machine_State].OC_Status_Ptr->OC1,//On_Off_State,
                             Control_Variables[Machine_State].OC_Status_Ptr->OC_Pulse_Ptr->Pulse_Enable.Pulse1,//On_Off_Pulse,
                             Control_Variables[Machine_State].OC_Status_Ptr->OC_Timer_Ptr->Pulse_Timer_Flags.Pulse1_Flag,//On_Off_Pulse_Value,
                             Manual_Control_Enable.Manual_Control.OC1_Manual,//On_Off_Manual,
                             Manual_Values.Values.OC1_Manual_Value, //On_Off_Manual_Value,
                             TRUE);//On_Off_Enable );

    On_Off_Output_Handling ( PORT_OC2_OUT, PIN_OC2_OUT,
                             Control_Variables[Machine_State].OC_Status_Ptr->OC2,//On_Off_State,
                             Control_Variables[Machine_State].OC_Status_Ptr->OC_Pulse_Ptr->Pulse_Enable.Pulse2,//On_Off_Pulse,
                             Control_Variables[Machine_State].OC_Status_Ptr->OC_Timer_Ptr->Pulse_Timer_Flags.Pulse2_Flag,//On_Off_Pulse_Value,
                             Manual_Control_Enable.Manual_Control.OC2_Manual,//On_Off_Manual,
                             Manual_Values.Values.OC2_Manual_Value, //On_Off_Manual_Value,
                             TRUE);//On_Off_Enable );

//Mosfet 1 direction handling                             
    On_Off_Output_Handling ( PORT_MOSFET1_DIR, PIN_MOSFET1_DIR,
                             Control_Variables[Machine_State].Mosfets_Status_Ptr->Mosfet1_Direction,//On_Off_State,
                             FALSE,//On_Off_Pulse,
                             FALSE,//On_Off_Pulse_Value,
                             Manual_Control_Enable.Manual_Control.Mosfet1_Dir_Manual,//On_Off_Manual,
                             Manual_Values.Values.Mos1_Dir_Manual_Value, //On_Off_Manual_Value,
                             TRUE);//On_Off_Enable );
                        
//Mosfets outputs handling
    Pwm_Output_Handling ( MOS1_TIMER,//ST Timer
                          Control_Variables[Machine_State].Mosfets_Status_Ptr->Mosfets_Pwm_Ptr->Pwm_Mos.Pwm_Mos1,//PWM value
                          Control_Variables[Machine_State].Mosfets_Status_Ptr->Mosfet1,//Pwm_State
                          TIM_SetCompare1,//void (*TimComparePtr)
                          Manual_Control_Enable.Manual_Control.Mosfet1_Manual,//Pwm_Manual
                          Manual_Values.Values.Mos1_Manual_Value, //Pwm_Manual_Value
                          TRUE );//Pwm_Enable)

    Pwm_Output_Handling ( MOS2_TIMER,//ST Timer
                          Control_Variables[Machine_State].Mosfets_Status_Ptr->Mosfets_Pwm_Ptr->Pwm_Mos.Pwm_Mos2,//PWM value
                          Control_Variables[Machine_State].Mosfets_Status_Ptr->Mosfet2,//Pwm_State
                          TIM_SetCompare4,//void (*TimComparePtr)
                          Manual_Control_Enable.Manual_Control.Mosfet2_Manual,//Pwm_Manual
                          Manual_Values.Values.Mos2_Manual_Value, //Pwm_Manual_Value
                          TRUE );//Pwm_Enable)

}
/*******************************************************************************
* Function Name  : On_Off_Output_Handling
* Description    :  0 / 1 outpus handling
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void On_Off_Output_Handling ( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, bool On_Off_State, bool On_Off_Pulse, bool On_Off_Pulse_Value, bool On_Off_Manual, bool On_Off_Manual_Value, bool On_Off_Enable )
{
    if ( On_Off_Manual == FALSE )
    {
        if ( On_Off_Enable == TRUE )
        {
            if ( On_Off_State == TRUE )
            {
                if ( On_Off_Pulse == TRUE )
                {
                    if ( On_Off_Pulse_Value == TRUE )
                    {
                        GPIO_SetBits(GPIOx, GPIO_Pin);                   
                    }
                    else
                    {
                        GPIO_ResetBits(GPIOx, GPIO_Pin);                   
                    } 
                }
                else
                {
                    GPIO_SetBits(GPIOx, GPIO_Pin);  
                }
            }
            else
            {
                GPIO_ResetBits(GPIOx, GPIO_Pin);            
            }
        }
        else
        {
            GPIO_ResetBits(GPIOx, GPIO_Pin);
        }
    }
    else
    {
         if ( On_Off_Manual_Value == TRUE )
        {
            GPIO_SetBits(GPIOx, GPIO_Pin);   
        }
        else
        {
            GPIO_ResetBits(GPIOx, GPIO_Pin);
        }   
    }
}

/*******************************************************************************
* Function Name  : Pwm_Output_Handling
* Description    : Pwm mosfets outpus handling
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Pwm_Output_Handling ( TIM_TypeDef* TIMx, uint16_t Pwm_Value, bool Pwm_State, void (*TimComparePtr)(TIM_TypeDef* TIMxx, uint16_t Tim_Value), bool Pwm_Manual, uint16_t Pwm_Manual_Value, bool Pwm_Enable)
{
    if ( Pwm_Manual == FALSE )
    {
        if ( Pwm_Enable == TRUE )
        {
            if ( Pwm_State == TRUE )
            {
                TimComparePtr(TIMx, Pwm_Value);  
            }
            else
            {
                TimComparePtr(TIMx, PWM_OFF);  
            }
        }
        else
        {
            TimComparePtr(TIMx, PWM_OFF);  
        }
    }
    else
    {
       TimComparePtr(TIMx, Pwm_Manual_Value);  
    }
}

//*********************************************************************888//
//*********************************************************************888//
//*********************************************************************888//
//Algorithmfunction
//*********************************************************************888//
//*********************************************************************888//
//*********************************************************************888//


/*******************************************************************************
* Function Name  : Input_Stop
* Description    : Input STOP handling
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Inputs_Stop ( void )
{
    if ( Machine_State != MANUAL_TEST &&
         Machine_State != INVERTER_PROG &&
         Machine_State != INVERTER_ERR )
    {
        if ( Controller_Variables.Controller_Vars.Inputs_Error & INPUT_STOP )
        {
           if ( (Controller_Variables.Controller_Vars.Controller_Status == STATUS_WG_POWER_ON) ||
                (Controller_Variables.Controller_Vars.Controller_Status == STATUS_WG_NORMAL) )
           {
                Machine_State = WG_STOP;
           }
        }
    }
}
/*******************************************************************************
* Function Name  : Inputs_Alert
* Description    : Outputs handling in LEARN CLOSING state
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Inputs_Alert ( void )
{
        if ( Inputs_Level & INPUT6 )
        {
            Controller_Variables.Controller_Vars.Inputs_Error |= INPUT_STOP;
        }
        else
        {
            Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_STOP;   
        }

        if ( Inputs_Level & INPUT5 )
        {
            Controller_Variables.Controller_Vars.Inputs_Error |= INPUT_PHOTO1;
        }
        else
        {
            Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_PHOTO1;   
        }

        if ( Inputs_Level & INPUT7 )
        {
            Controller_Variables.Controller_Vars.Inputs_Error |= INPUT_SE1;    
        }
        else
        {
            Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_SE1;   
        }

        if ( Inputs_Level & INPUT8 )
        {
            Controller_Variables.Controller_Vars.Inputs_Error |= INPUT_SE2;    
        }
        else
        {
            Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_SE2;   
        }
    
        if ( Inputs_Level & INPUT9 )
        {
            Controller_Variables.Controller_Vars.Inputs_Error |= INPUT_SE3;    
        }
        else
        {
            Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_SE3;   
        }
    
        if ( Inputs_Level & INPUT10 )
        {
            Controller_Variables.Controller_Vars.Inputs_Error |= INPUT_SE4;    
        }
        else
        {
            Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_SE4;   
        }

        if ( F1_Current_Counter >= Controlling_Variables.Ctrl_Vars.F1_Current_Counter )
            Controller_Variables.Controller_Vars.Inputs_Error |= CURRENT_OV1;          
        else
            Controller_Variables.Controller_Vars.Inputs_Error &= ~CURRENT_OV1;

        if ( F2_Current_Counter >= Controlling_Variables.Ctrl_Vars.F2_Current_Counter )
            Controller_Variables.Controller_Vars.Inputs_Error |= CURRENT_OV2;          
        else
            Controller_Variables.Controller_Vars.Inputs_Error &= ~CURRENT_OV2;

        if ( System_Timer_Check ( &Encoder_Timer.Timer, T_10msec ) == TRUE )
        {
            if ( ENCODER_SIGNAL_DETECTED == TRUE )
            {
                ENCODER_SIGNAL_DETECTED = FALSE;
                Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_ENCODER;   
            }
            else
            {
                Controller_Variables.Controller_Vars.Inputs_Error |= INPUT_ENCODER;
            }

            System_Timer_Setting ( &Encoder_Timer.Timer, Service_Variables.Serv_Vars.Serwis_009, T_10msec );
        }
}

/*******************************************************************************
* Function Name  : Op_Al_Stop_Fun
* Description    : Safety edge handling in opening mode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Op_Al_Stop_Fun ( void )
{
    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];
    System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                            *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                            Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;

}

/*******************************************************************************
* Function Name  : Cl_Al_Stop_Fun
* Description    : Safety edge handling ioncosing mode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Cl_Al_Stop_Fun ( void )
{
    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];
    System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                            *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                            Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;

}

/*******************************************************************************
* Function Name  : Learm_Standby_Fun
* Description    : WAY detecting - handling the standby learn mode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Learm_Standby_Fun ( void )
{
    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];
    System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                            *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                            Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;
    
    if ( LEARN_WAY_FLAG == TRUE )
    {
       Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];
       LEARN_WAY_FLAG = FALSE;
    }
}

/*******************************************************************************
* Function Name  : Learm_
* Description    : WAY detecting - handling the Opening learn mode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Learm_Opening_Fun ( void )
{
    if ( LEARN_WAY_FLAG == TRUE )
    {
       Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[6];
       LEARN_WAY_FLAG = FALSE;
    }

    Wg_Power_On_Alerts();
}

/*******************************************************************************
* Function Name  : Learm_Opened_Fun
* Description    : WAY detecting - handling the Opened learn mode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Learm_Opened_Fun ( void )
{
    static uint16_t Encoder_Timer_Temp1;

    Encoder_Timer_Temp1 = (Service_Variables.Serv_Vars.Serwis_003 + Service_Variables.Serv_Vars.Serwis_013 + Service_Variables.Serv_Vars.Serwis_010);
    System_Timer_Setting ( &Encoder_Timer.Timer, Encoder_Timer_Temp1, T_10msec );
    Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_ENCODER;   
    ENCODER_SIGNAL_DETECTED = TRUE;

    Controller_Variables.Controller_Vars.Motor_Encoder_Counter = ENCODER_OFFSET;
    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[6];
    System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                            *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                            Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;

    if ( LEARN_WAY_FLAG == TRUE )
    {
       Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[7];
       LEARN_WAY_FLAG = FALSE;
    }

    Wg_Power_On_Alerts();
}
/*******************************************************************************
* Function Name  : Learm_Closing_Fun
* Description    : WAY detecting - handling the Opening learn mode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Learm_Closing_Fun ( void )
{
    if ( LEARN_WAY_FLAG == TRUE )
    {
       Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[6];
       LEARN_WAY_FLAG = FALSE;
    }

    Wg_Power_On_Alerts();
}

/*******************************************************************************
* Function Name  : Learm_Closed_Fun
* Description    : WAY detecting - handling the Opened learn mode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Learm_Closed_Fun ( void )
{
    Controlling_Variables_Set.Ctrl_Vars.Encoder_Open = Controller_Variables.Controller_Vars.Motor_Encoder_Counter;        
    Controlling_Variables_Set.Ctrl_Vars.Way_Learned = 1;
    Write_Settings();
    Controller_Variables.Controller_Vars.Motor_Encoder_Counter = ENCODER_OFFSET;
    Controller_Variables.Controller_Vars.Controller_Status = STATUS_NORMAL;
    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];
}

/*******************************************************************************
* Function Name  : Wait_4_Learn
* Description    : Waiting for learning enable
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Wait_4_Learn_Fun ( void )
{
    if ( LEARN_WAY_FLAG == TRUE )
    {
       Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[6];
       System_Timer_Setting ( &Encoder_Timer.Timer, Service_Variables.Serv_Vars.Serwis_013, T_10msec );
       Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_ENCODER;   
       ENCODER_SIGNAL_DETECTED = TRUE;
       LEARN_WAY_FLAG = FALSE;
    }

    Wg_Power_On_Alerts();
}

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/

static void WG_Power_On_Fun ( void )
{
    if ((Controller_Variables.Controller_Vars.Inputs_Error & WG_ALL_ALERTS ) == 0 )
    {
        if ( WG_TIMER_FLAG == FALSE ) 
        {
            System_Timer_Setting ( &WG_Timer.Timer, Service_Variables.Serv_Vars.Serwis_016, T_10msec );        
            WG_TIMER_FLAG = TRUE;
        }
        else
        {
            if ( System_Timer_Check ( &WG_Timer.Timer, T_10msec ) == TRUE )
            {
                if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 0 )//Limitswitches
                { 
                    if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
                    {                
                        //BOTH CLOSED
                        if ( (Inputs_Level & INPUT1) && (Inputs_Level & INPUT3) )
                        {
                            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                            Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
                        }
                        //1 OPENED 2 CLOSED
                        else if ( !(Inputs_Level & INPUT1) && (Inputs_Level & INPUT3) )
                        {
                            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
                        }
                        //2 OPENED 1 CLOSED
                        else if ( (Inputs_Level & INPUT1) && !(Inputs_Level & INPUT3) )
                        {
                            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];        
                        }
                        //BOTH OPENED
                        else if ( !(Inputs_Level & INPUT1) && !(Inputs_Level & INPUT3) )
                        {
                            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];
                        }
                    }
                    else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                              Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//sliding
                    {
                        //1 CLOSED
                        if ( Inputs_Level & INPUT1 )
                        {
                            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                            Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
                        }
                        //1 OPENED
                        else if ( !(Inputs_Level & INPUT1) )
                        {
                            if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 )//inverters
                            {
                                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
                            }
                            else if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 )//24vdc
                   
                            {
                                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[5];                                
                                System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                                                        *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                                                        Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;            
                            }
                        }                    
                    }

                }
                if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 1 )//Magnetic Sensor
                {
                    if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
                    {
                        //BOTH CLOSED
                        if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                             ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
                        {
                            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                            Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
                        }
                        //1 OPENED 2 CLOSED
                        else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                                  ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
                        {
                            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
                        }
                        //2 OPENED 1 CLOSED
                        else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                                  ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
                        {
                            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];        
                        }
                        //BOTH OPENED
                        else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                                  ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
                        {        
                            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[2];
                        }
                    }
                    else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                              Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )  //Sliding
                    {
                        if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) //Normal
                        {
                            //1 CLOSED
                            if ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                            {
                                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                                Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
                            }
                            //1 OPENED
                            else if ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                            {
                                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
                            } 
                        }
                        else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) //Revers
                        {
                            //1 CLOSED
                            if ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                            {
                                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                                Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
                            }
                            //1 OPENED
                            else if ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                            {
                                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
                            } 
                        }
                    }
                }
            
                WG_TIMER_FLAG = FALSE;
        
                F1_Current_Counter = 0;
                F2_Current_Counter = 0;            
            }
        }
    }
    else
    {
        WG_TIMER_FLAG = FALSE;    
    }
}

static void WG_Closing_Fun ( void )
{
    if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 0 )//Limitswitches
    { 
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
        {                
            //BOTH CLOSED
            if ( (Inputs_Level & INPUT1) && (Inputs_Level & INPUT3) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
            }
            //1 OPENED 2 CLOSED
            else if ( !(Inputs_Level & INPUT1) && (Inputs_Level & INPUT3) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
            }
            //2 OPENED 1 CLOSED
            else if ( (Inputs_Level & INPUT1) && !(Inputs_Level & INPUT3) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];        
            }
            //BOTH OPENED
            else if ( !(Inputs_Level & INPUT1) && !(Inputs_Level & INPUT3) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[2];
            }
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                  Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//sliding
        {
            //1 CLOSED
            if ( Inputs_Level & INPUT1 )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
            }
            //1 OPENED
            if ( !(Inputs_Level & INPUT1) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
            }
        }
    }
    if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 1 )//Magnetic Sensor
    {
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
        {
            //BOTH CLOSED
            if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                 ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
            }
            // 1OPENED 2 CLOSED
            else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                      ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
            }
            // 2 OPENED 1 CLOSED
            else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                      ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];        
            }
            //BOTH OPENED
            else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                      ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
            {        
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[2];
            }
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                  Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
        {
            if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
            {
                //1 CLOSED
                if ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                {
                    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                    Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
                }
                //1 OPENED
                else if ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                {
                    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
                } 
            }
            else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // Reverse
            {
                //1 CLOSED
                if ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                {
                    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                    Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
                }
                //1 OPENED
                else if ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                {
                    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
                } 
            }
        }
    }
}

static void WG_Opening_Fun ( void )
{
    if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 0 )//Limitswitches
    { 
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
        {                
            //BOTH OPENED
            if ( (Inputs_Level & INPUT2) && (Inputs_Level & INPUT4) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
            }
            //1 CLOSED 2 OPENED
            else if ( !(Inputs_Level & INPUT2) && (Inputs_Level & INPUT4) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
            }
            //1 OPENED 2 CLOSED
            else if ( (Inputs_Level & INPUT2) && !(Inputs_Level & INPUT4) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];        
            }
            //BOTH OPENED
            else if ( !(Inputs_Level & INPUT2) && !(Inputs_Level & INPUT4) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[2];
            }
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                  Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
        {
            //1 OPENED
            if ( Inputs_Level & INPUT2 )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
            }
            //1 CLOSED
            else if ( !(Inputs_Level & INPUT2) )
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
            }

        }
    }
    if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 1 )//Magnetic Sensor
    {
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
        {
            //BOTH CLOSED
            if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                 ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
            }
            //1 OPENED 2 CLOSED
            else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                      ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
            }
            //2 OPENED 1 CLOSED
            else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                      ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
            {
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];        
            }
            //BOTH OPENED
            else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                      ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
            {        
                Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[2];
            }
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                  Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
        {
            if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
            {
                //1 CLOSED
                if ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                {
                    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                    Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
                }
                //1 OPENED
                else if ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                {
                    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
                }  
            }
            else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // Reverse
            {
                //1 CLOSED
                if ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                {
                    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];    
                    Controller_Variables.Controller_Vars.Controller_Status = STATUS_WG_NORMAL;
                }
                //1 OPENED
                else if ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                {
                    Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];    
                }             
            }
        }
    }

    OPENED_WAIT = FALSE;
}

static void WG_Inputs_Closed ( void )
{
    if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
    {
        switch ( Inputs.Keyboard_Memory )
        {
            case OPEN_CLOSE_GATE:
                WG_Inputs_Closed_Handling_Function();   
            break;

            case OPEN_CLOSE_GATE1:
                WG_Inputs_Closed_Handling_Function();   
            break;
            
            case OPEN_CLOSE_GATE2:
                WG_Inputs_Closed_Handling_Function();   
            break;
                        
            case OPEN_CLOSE_GATE3:
                WG_Inputs_Closed_Handling_Function();   
            break;
                                    
            case OPEN_CLOSE_GATE4:
                WG_Inputs_Closed_Handling_Function();   
            break;
                                                
            case OPEN_CLOSE_GATE5:
                WG_Inputs_Closed_Handling_Function();   
            break;
                                                            
            case OPEN_CLOSE_GATE6:
                WG_Inputs_Closed_Handling_Function();   
            break;
                                                                        
            case OPEN_CLOSE_GATE7:
                WG_Inputs_Closed_Handling_Function();   
            break;
                        
            default:
            break;
        }
        Inputs.Keyboard_Flag = 0;
    }

    if ( Inputs.Keyboard_State == 0 )
    {
        Inputs.Keyboard_Memory = 0;
    }

    if ( Inputs_Level & INPUT12 )
    {
        if ( Service_Variables.Serv_Vars.In12_Fun == 2 )  //Open
        {
            WG_Inputs_Closed_Handling_Function();     
        }
    }

    if ( Inputs_Level & INPUT14 )
    {
        if ( Service_Variables.Serv_Vars.In14_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In14_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 4 )
                OPEN_ON_LEVEL_14 = TRUE;
    
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_14 = FALSE;
    }

    if ( Inputs_Level & INPUT15 )
    {
        if ( Service_Variables.Serv_Vars.In15_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In15_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 4 )
                OPEN_ON_LEVEL_15 = TRUE;
    
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_15 = FALSE;
    }

    if ( Inputs_Level & INPUT16 )
    {
        if ( Service_Variables.Serv_Vars.In16_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In16_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 4 )
                OPEN_ON_LEVEL_16 = TRUE;
    
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_16 = FALSE;
    }

    if ( Inputs_Level & INPUT17 )
    {
        if ( Service_Variables.Serv_Vars.In17_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In17_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 4 )
                OPEN_ON_LEVEL_17 = TRUE;
    
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_17 = FALSE;
    }

    if ( Inputs_Level & INPUT18 )
    {
        if ( Service_Variables.Serv_Vars.In18_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In18_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 4 )
                OPEN_ON_LEVEL_18 = TRUE;
    
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_18 = FALSE;
    }

    if ( Inputs_Level & INPUT19 )
    {
        if ( Service_Variables.Serv_Vars.In19_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In19_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 4 )
                OPEN_ON_LEVEL_19 = TRUE;
    
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_19 = FALSE;
    }

    if ( Inputs_Level & INPUT20 )
    {
        if ( Service_Variables.Serv_Vars.In20_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In20_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 4 )
                OPEN_ON_LEVEL_20 = TRUE;
    
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_20 = FALSE;
    }
}

static void WG_Inputs_Closed_Handling_Function ( void )
{
    Machine_State = PRE_WORNING_OPENING;
    PRE_WORNING_FLAG = FALSE;
}

static void WG_Inputs_Closed_Half ( void )
{
        if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
        {
            switch ( Inputs.Keyboard_Memory )
            {
                case OPEN_CLOSE_GATE:
                    WG_Inputs_Closed_Half_Handling();              
                break;

                case OPEN_CLOSE_GATE1:
                    WG_Inputs_Closed_Half_Handling();              
                break;
                
                case OPEN_CLOSE_GATE2:
                    WG_Inputs_Closed_Half_Handling();              
                break;
                                
                case OPEN_CLOSE_GATE3:
                    WG_Inputs_Closed_Half_Handling();              
                break;
                
                case OPEN_CLOSE_GATE4:
                    WG_Inputs_Closed_Half_Handling();              
                break;
                
                case OPEN_CLOSE_GATE5:
                    WG_Inputs_Closed_Half_Handling();              
                break;
                
                case OPEN_CLOSE_GATE6:
                    WG_Inputs_Closed_Half_Handling();              
                break;
               
                case OPEN_CLOSE_GATE7:
                    WG_Inputs_Closed_Half_Handling();              
                break;
                
                default:
                break;
            }
            Inputs.Keyboard_Flag = 0;
        }

        if ( Inputs.Keyboard_State == 0 )
        {
            Inputs.Keyboard_Memory = 0;
        }
    
    if ( Inputs_Level & INPUT12 )
    {
        if ( Service_Variables.Serv_Vars.In12_Fun == 2 )  //Open
        {
            WG_Inputs_Closed_Half_Handling();     
        }
    }

    if ( Inputs_Level & INPUT14 )
    {
        if ( Service_Variables.Serv_Vars.In14_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In14_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 4 )
                OPEN_ON_LEVEL_14 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_14 = FALSE;
    }

    if ( Inputs_Level & INPUT15 )
    {
        if ( Service_Variables.Serv_Vars.In15_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In15_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 4 )
                OPEN_ON_LEVEL_15 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_15 = FALSE;
    }

    if ( Inputs_Level & INPUT16 )
    {
        if ( Service_Variables.Serv_Vars.In16_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In16_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 4 )
                OPEN_ON_LEVEL_16 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_16 = FALSE;
    }

    if ( Inputs_Level & INPUT17 )
    {
        if ( Service_Variables.Serv_Vars.In17_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In17_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 4 )
                OPEN_ON_LEVEL_17 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_17 = FALSE;
    }

    if ( Inputs_Level & INPUT18 )
    {
        if ( Service_Variables.Serv_Vars.In18_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In18_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 4 )
                OPEN_ON_LEVEL_18 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_18 = FALSE;
    }

    if ( Inputs_Level & INPUT19 )
    {
        if ( Service_Variables.Serv_Vars.In19_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In19_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 4 )
                OPEN_ON_LEVEL_19 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_19 = FALSE;
    }

    if ( Inputs_Level & INPUT20 )
    {
        if ( Service_Variables.Serv_Vars.In20_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In20_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 4 )
                OPEN_ON_LEVEL_20 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_20 = FALSE;
    }

    if ((Controller_Variables.Controller_Vars.Inputs_Error & WG_ALL_ALERTS ) == 0 )
    {
        if ( Inputs_Level & INPUT13 )
        {
            if ( Service_Variables.Serv_Vars.In13_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }
    
        if ( Inputs_Level & INPUT14 )
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT15 )
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }


        if ( Inputs_Level & INPUT16 )
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT17 )
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT18 )
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT19 )
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT20 )
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }
    }
}

static void WG_Inputs_Closed_Half_Handling ( void )
{
    if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 0 )//Limitswitches
    { 
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
        {                
            //BOTH CLOSED HALF
            if ( !(Inputs_Level & INPUT2) && !(Inputs_Level & INPUT4) )
            {
                Machine_State = WG_OPENING_1_2;    
            }
            //1 OPENED 2 CLOSED
            else if ( !(Inputs_Level & INPUT2) && (Inputs_Level & INPUT4) )
            {
                Machine_State = WG_OPENING_1; 
            }
            //2 OPENED 1 CLOSED
            else if ( (Inputs_Level & INPUT2) && !(Inputs_Level & INPUT4) )
            {
                Machine_State = WG_OPENING_2;        
            }
            //BOTH OPENED
            else if ( (Inputs_Level & INPUT2) && (Inputs_Level & INPUT4) )
            {
                Machine_State = WG_OPENED;
            }
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                  Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
        {
            //1 OPENED
            if ( !(Inputs_Level & INPUT2) )
            {
                if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Inverter
                {
                    Machine_State = WG_OPENING_1; 
                }
                if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 ) //24VDC
                {

                    Machine_State = OPENING_RELAY;
                    System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                                            *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                                            Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );                
                }
            }
            //BOTH OPENED
            else if ( Inputs_Level & INPUT2 )
            {
                Machine_State = WG_OPENED;
            }
        }
    }
    if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 1 )//Magnetic Sensor
    {
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
        {
            //BOTH CLOSED HALF
            if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                 ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
            {
                Machine_State = WG_OPENING_1_2; ;    
            }
            //1 OPENED 2 CLOSED
            else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                      ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
            {
                Machine_State = WG_OPENING_1;    
            }
            //2 OPENED 1 CLOSED
            else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                      ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
            {
                Machine_State = WG_OPENING_2;        
            }
            //BOTH OPENED
            else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                      ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
            {        
                Machine_State = WG_OPENED;
            }
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                  Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
        {
            if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
            {        
                //1 CLOSED
                if ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                {
                    Machine_State = WG_OPENING_1;    
                }
                //1 OPENED
                else if ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                {
                    Machine_State = WG_OPENED;
                } 
            }
            else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // Reverse
            {
                //1 CLOSED
                if ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                {
                    Machine_State = WG_OPENING_1;    
                }
                //1 OPENED
                else if ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                {
                    Machine_State = WG_OPENED;
                }
            }
        }
    }

    SLOW_ENABLE_FLAG_1 = TRUE;
    SLOW_ENABLE_FLAG_2 = TRUE;
    BRAKING_FLAG_1 = FALSE;
    BRAKING_FLAG_2 = FALSE;
                
    Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_ENCODER;   

    F1_Current_Counter = 0;
    F2_Current_Counter = 0; 

    PHOTO_PRIORITY_ENABLE = FALSE;

    READY_4_CLOSING = FALSE;
    CLOSE_GATE_FLAG = FALSE;

}



static void WG_Inputs_Opened ( void )
{
    uint16_t Time_Temp1;

    if ((Controller_Variables.Controller_Vars.Inputs_Error & WG_ALL_ALERTS ) == 0 )
    {
        if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
        {
            switch ( Inputs.Keyboard_Memory )
            {
                case OPEN_CLOSE_GATE:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE1:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE2:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE3:
                    WG_Inputs_Opened_Handling_Function();
                break;

                case OPEN_CLOSE_GATE4:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE5:
                    WG_Inputs_Opened_Handling_Function();
                break;

                case OPEN_CLOSE_GATE6:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE7:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                default:
                break;
            }
            Inputs.Keyboard_Flag = 0;
        }

        if ( Inputs.Keyboard_State == 0 )
        {
            Inputs.Keyboard_Memory = 0;
        }
    
        if ( Inputs_Level & INPUT13 )
        {
            if ( Service_Variables.Serv_Vars.In13_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT14 )
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT15 )
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT16 )
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT17 )
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 3 )  //Close
            {
                 WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT18 )
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT19 )
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT20 )
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }    
    }
}

static void WG_Inputs_Opened_Handling_Function ( void )
{
    Machine_State = PRE_WORNING_CLOSING;
    PRE_WORNING_FLAG = FALSE;
}

static void WG_Inputs_Opened_Half ( void )
{
    if ((Controller_Variables.Controller_Vars.Inputs_Error & WG_ALL_ALERTS ) == 0 )
    {
        if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
        {
            switch ( Inputs.Keyboard_Memory )
            {
                case OPEN_CLOSE_GATE:
                    WG_Inputs_Opened_Half_Handling();
                break;

                case OPEN_CLOSE_GATE1:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE2:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE3:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE4:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE5:
                    WG_Inputs_Opened_Half_Handling();
                break;

                case OPEN_CLOSE_GATE6:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE7:
                    WG_Inputs_Opened_Half_Handling();
                break;
 
                default:
                break;
            }
            Inputs.Keyboard_Flag = 0;
        }

        if ( Inputs.Keyboard_State == 0 )
        {
            Inputs.Keyboard_Memory = 0;
        }
    
        if ( Inputs_Level & INPUT13 )
        {
            if ( Service_Variables.Serv_Vars.In13_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT14 )
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT15 )
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT16 )
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT17 )
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT18 )
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT19 )
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT20 )
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }
    }
    else
    {
        if ((Controller_Variables.Controller_Vars.Inputs_Error & INPUT_PHOTO1 ) != 0 )
        {
            if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
            {
                switch ( Inputs.Keyboard_Memory )
                {
                    case OPEN_CLOSE_GATE:
                        WG_Inputs_Closed_Half_Handling();     
                    break;

                    case OPEN_CLOSE_GATE1:
                        WG_Inputs_Closed_Half_Handling();     
                    break;
                    
                    case OPEN_CLOSE_GATE2:
                        WG_Inputs_Closed_Half_Handling();     
                    break;
                    
                    case OPEN_CLOSE_GATE3:
                        WG_Inputs_Closed_Half_Handling();     
                    break;
                    
                    case OPEN_CLOSE_GATE4:
                        WG_Inputs_Closed_Half_Handling();     
                    break;
                    
                    case OPEN_CLOSE_GATE5:
                        WG_Inputs_Closed_Half_Handling();     
                    break;

                    case OPEN_CLOSE_GATE6:
                        WG_Inputs_Closed_Half_Handling();     
                    break;
                    
                    case OPEN_CLOSE_GATE7:
                        WG_Inputs_Closed_Half_Handling();     
                    break;
     
                    default:
                    break;
                }
                Inputs.Keyboard_Flag = 0;
            }

            if ( Inputs.Keyboard_State == 0 )
            {
                Inputs.Keyboard_Memory = 0;
            }            
        }
    }

    if ( Inputs_Level & INPUT12 )
    {
        if ( Service_Variables.Serv_Vars.In12_Fun == 2 )  //Open
        {
            WG_Inputs_Closed_Half_Handling();     
        }
    }

    if ( Inputs_Level & INPUT14 )
    {
        if ( Service_Variables.Serv_Vars.In14_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In14_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 4 )
                OPEN_ON_LEVEL_14 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_14 = FALSE;
    }

    if ( Inputs_Level & INPUT15 )
    {
        if ( Service_Variables.Serv_Vars.In15_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In15_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 4 )
                OPEN_ON_LEVEL_15 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_15 = FALSE;
    }

    if ( Inputs_Level & INPUT16 )
    {
        if ( Service_Variables.Serv_Vars.In16_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In16_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 4 )
                OPEN_ON_LEVEL_16 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_16 = FALSE;
    }

    if ( Inputs_Level & INPUT17 )
    {
        if ( Service_Variables.Serv_Vars.In17_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In17_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 4 )
                OPEN_ON_LEVEL_17 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_17 = FALSE;
    }

    if ( Inputs_Level & INPUT18 )
    {
        if ( Service_Variables.Serv_Vars.In18_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In18_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 4 )
                OPEN_ON_LEVEL_18 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_18 = FALSE;
    }

    if ( Inputs_Level & INPUT19 )
    {
        if ( Service_Variables.Serv_Vars.In19_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In19_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 4 )
                OPEN_ON_LEVEL_19 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_19 = FALSE;
    }

    if ( Inputs_Level & INPUT20 )
    {
        if ( Service_Variables.Serv_Vars.In20_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In20_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 4 )
                OPEN_ON_LEVEL_20 = TRUE;
    
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_20 = FALSE;
    }
}


static void WG_Inputs_Opened_Half_Handling ( void )
{
    if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 0 )//Limitswitches
    { 
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
        {                
            //BOTH OPENED HALF
            if ( !(Inputs_Level & INPUT1) && !(Inputs_Level & INPUT3) )
            {
                Machine_State = WG_CLOSING_1_2;    
            }
            //1 OPENED 2 CLOSED
            else if ( !(Inputs_Level & INPUT1) && (Inputs_Level & INPUT3) )
            {
                Machine_State = WG_CLOSING_1;    
            }
            //2 OPENED 1 CLOSED
            else if ( (Inputs_Level & INPUT1) && !(Inputs_Level & INPUT3) )
            {
                Machine_State = WG_CLOSING_2;        
            }
            //BOTH CLOSED
            else if ( (Inputs_Level & INPUT1) && (Inputs_Level & INPUT3) )
            {
                Machine_State = WG_CLOSED;
            }
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                  Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
        {
            //1 OPENED HALF
            if ( !(Inputs_Level & INPUT1) )
            {
                if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 )//inverters
                {
                    Machine_State = WG_CLOSING_1;    
                }
                else if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 )//24vdc
                {
                    Machine_State = CLOSING_RELAY;                                
                    System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                                            *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                                            Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;            
                }            
            }
            //CLOSED
            else if ( Inputs_Level & INPUT1 )
            {
                Machine_State = WG_CLOSED;
            }
        }
    }
    if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 1 )//Magnetic Sensor
    {
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
        {
            //BOTH OPENED HALF
            if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                 ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
            {
                Machine_State = WG_CLOSING_1_2; ;    
            }
            //1 OPENED 2 CLOSED
            else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                      ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
            {
                Machine_State = WG_CLOSING_1;    
            }
            //2 OPENED 1 CLOSED
            else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                      ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
            {
                Machine_State = WG_CLOSING_2;        
            }
            //BOTH OPENED
            else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                      ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
            {        
                Machine_State = WG_CLOSED;
            }
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                  Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
        {
            if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
            {
                //1 CLOSED
                if ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                {
                    Machine_State = WG_CLOSING_1;    
                }
                //1 OPENED
                else if ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                {
                    Machine_State = WG_CLOSED;
                } 
            }
            else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // Reverse
            {
                //1 CLOSED
                if ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                {
                    Machine_State = WG_CLOSING_1;    
                }
                //1 OPENED
                else if ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                {
                    Machine_State = WG_CLOSED;
                } 
            }
        }
    }

    SLOW_ENABLE_FLAG_1 = TRUE;
    SLOW_ENABLE_FLAG_2 = TRUE;
    BRAKING_FLAG_1 = FALSE;
    BRAKING_FLAG_2 = FALSE;

    Controller_Variables.Controller_Vars.Inputs_Error &= ~INPUT_ENCODER;   

    PHOTO_PRIORITY_ENABLE = FALSE;

    F1_Current_Counter = 0;
    F2_Current_Counter = 0;
}
                

static void Reset_Inputs ( void )
{
    if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
    {
        switch ( Inputs.Keyboard_Memory )
        {
            default:
            break;
        }
        Inputs.Keyboard_Flag = 0;
    }

    if ( Inputs.Keyboard_State == 0 )
    {
        Inputs.Keyboard_Memory = 0;
    }

    if ( Machine_State == START_CLOSING )
    {
        Wg_Alerts_Closing_Handling();      
    }
    else if ( Machine_State == START_OPENING )
    {
        Wg_Alerts_Opening_Handling();      
    }    
}

static void WG_Inputs_Opening ( void )
{
        if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
        {
            switch ( Inputs.Keyboard_Memory )
            {
                case OPEN_CLOSE_GATE:
                    Machine_State = WG_OPENED_HALF;        
                break;
                            
                case OPEN_CLOSE_GATE1:
                    Machine_State = WG_OPENED_HALF;        
                break;

                case OPEN_CLOSE_GATE2:
                    Machine_State = WG_OPENED_HALF;        
                break;

                case OPEN_CLOSE_GATE3:
                    Machine_State = WG_OPENED_HALF;        
                break;

                case OPEN_CLOSE_GATE4:
                    Machine_State = WG_OPENED_HALF;        
                break;

                case OPEN_CLOSE_GATE5:
                    Machine_State = WG_OPENED_HALF;        
                break;

                case OPEN_CLOSE_GATE6:
                    Machine_State = WG_OPENED_HALF;        
                break;

                case OPEN_CLOSE_GATE7:
                    Machine_State = WG_OPENED_HALF;        
                break;
                
                default:
                break;
            }
            Inputs.Keyboard_Flag = 0;
        }

        if ( Inputs.Keyboard_State == 0 )
        {
            Inputs.Keyboard_Memory = 0;
        }
    
    Wg_Alerts_Opening_Handling();
}

static void WG_Inputs_Closing ( void )
{
    if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
    {
        switch ( Inputs.Keyboard_Memory )
        {
            case OPEN_CLOSE_GATE:
                Machine_State = WG_CLOSED_HALF;        
            break;

            case OPEN_CLOSE_GATE1:
                Machine_State = WG_CLOSED_HALF;        
            break;

            case OPEN_CLOSE_GATE2:
                Machine_State = WG_CLOSED_HALF;        
            break;

            case OPEN_CLOSE_GATE3:
                Machine_State = WG_CLOSED_HALF;        
            break;

            case OPEN_CLOSE_GATE4:
                Machine_State = WG_CLOSED_HALF;        
            break;

            case OPEN_CLOSE_GATE5:
                Machine_State = WG_CLOSED_HALF;        
            break;

            case OPEN_CLOSE_GATE6:
                Machine_State = WG_CLOSED_HALF;        
            break;

            case OPEN_CLOSE_GATE7:
                Machine_State = WG_CLOSED_HALF;        
            break;
            
            default:
            break;
        }
        Inputs.Keyboard_Flag = 0;
    }

    if ( Inputs.Keyboard_State == 0 )
    {
        Inputs.Keyboard_Memory = 0;
    }

    if ( Service_Variables.Serv_Vars.In12_Fun == 2 )
    {
        if ( Inputs_Level & INPUT12 )
        {            
            Machine_State = WG_ALERTS;
            ALERTS_FLAG = FALSE;
        }
    }

    if ( Inputs_Level & INPUT14 )
    {
        if ( Service_Variables.Serv_Vars.In14_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In14_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 4 )
                OPEN_ON_LEVEL_14 = TRUE;
    
            Machine_State = WG_ALERTS;
            ALERTS_FLAG = FALSE;        }
    }
    else
    {
        OPEN_ON_LEVEL_14 = FALSE;
    }

    if ( Inputs_Level & INPUT15 )
    {
        if ( Service_Variables.Serv_Vars.In15_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In15_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 4 )
                OPEN_ON_LEVEL_15 = TRUE;
    
            Machine_State = WG_ALERTS;
            ALERTS_FLAG = FALSE;        }
    }
    else
    {
        OPEN_ON_LEVEL_15 = FALSE;
    }

    if ( Inputs_Level & INPUT16 )
    {
        if ( Service_Variables.Serv_Vars.In16_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In16_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 4 )
                OPEN_ON_LEVEL_16 = TRUE;
    
            Machine_State = WG_ALERTS;
            ALERTS_FLAG = FALSE;        }
    }
    else
    {
        OPEN_ON_LEVEL_16 = FALSE;
    }

    if ( Inputs_Level & INPUT17 )
    {
        if ( Service_Variables.Serv_Vars.In17_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In17_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 4 )
                OPEN_ON_LEVEL_17 = TRUE;
    
            Machine_State = WG_ALERTS;
            ALERTS_FLAG = FALSE;        }
    }
    else
    {
        OPEN_ON_LEVEL_17 = FALSE;
    }

    if ( Inputs_Level & INPUT18 )
    {
        if ( Service_Variables.Serv_Vars.In18_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In18_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 4 )
                OPEN_ON_LEVEL_18 = TRUE;
    
            Machine_State = WG_ALERTS;
            ALERTS_FLAG = FALSE; 
        }
    }
    else
    {
        OPEN_ON_LEVEL_18 = FALSE;
    }

    if ( Inputs_Level & INPUT19 )
    {
        if ( Service_Variables.Serv_Vars.In19_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In19_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 4 )
                OPEN_ON_LEVEL_19 = TRUE;
    
            Machine_State = WG_ALERTS;
            ALERTS_FLAG = FALSE;
        }
    }
    else
    {
        OPEN_ON_LEVEL_19 = FALSE;
    }

    if ( Inputs_Level & INPUT20 )
    {
        if ( Service_Variables.Serv_Vars.In20_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In20_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 4 )
                OPEN_ON_LEVEL_20 = TRUE;
    
            Machine_State = WG_ALERTS;
            ALERTS_FLAG = FALSE;
        }
    }
    else
    {
        OPEN_ON_LEVEL_20 = FALSE;
    }

    Wg_Alerts_Closing_Handling();


}


/*******************************************************************************
* Function Name  : WG_Stop_Release
* Description    : Input stop handling in STOP mode
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WG_Stop_Release_Fun ( void )
{
    if ( (Controller_Variables.Controller_Vars.Inputs_Error & INPUT_STOP) == 0 )
    {
        if ( Controller_Variables.Controller_Vars.Controller_Status == STATUS_WG_POWER_ON )
        {
            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];
            WG_TIMER_FLAG = FALSE;
        }
        else if ( Controller_Variables.Controller_Vars.Controller_Status == STATUS_WG_NORMAL )
        {
            if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 0 ) //Limit switches
            {
                if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) //2 wings speed
                {
                    if ( (Inputs_Level & INPUT1) && (Inputs_Level & INPUT3) )
                    { 
                       // Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];
                        WG_Stop_Closed();
                    }
                    else if ( (Inputs_Level & INPUT2) && (Inputs_Level & INPUT4) )
                    {
                       // Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[2];
                        WG_Stop_Opened();
                    }
                    else
                    {
                        //Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];
                        WG_Stop_Opened_Half();
                        SLOW_ENABLE_FLAG_1 = TRUE;
                        SLOW_ENABLE_FLAG_2 = TRUE;
                        BRAKING_FLAG_1 = FALSE;
                        BRAKING_FLAG_2 = FALSE;             
                    }
                }
                if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing speed
                     Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )  //sliding
                {
                    if ( Inputs_Level & INPUT1 )
                    { 
                       // Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[1];
                        WG_Stop_Closed();
                    }
                    else if ( (Inputs_Level & INPUT2) )
                    {
                       // Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[2];
                        WG_Stop_Opened();
                    }
                    else
                    {
                        //Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[3];
                        WG_Stop_Opened_Half();
                        SLOW_ENABLE_FLAG_1 = TRUE;
                        SLOW_ENABLE_FLAG_2 = TRUE;
                        BRAKING_FLAG_1 = FALSE;
                        BRAKING_FLAG_2 = FALSE;             
                    }                
                }
            }
            else if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 1 ) //Magnetic sensor
            {
                if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
                {
                    //BOTH CLOSED
                    if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                         ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
                    {
                         WG_Stop_Closed();
                    }
                    //BOTH OPENED
                    else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                              ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
                    {        
                        WG_Stop_Opened();
                    }
                    else
                    {
                        WG_Stop_Opened_Half();
                        SLOW_ENABLE_FLAG_1 = TRUE;
                        SLOW_ENABLE_FLAG_2 = TRUE;
                        BRAKING_FLAG_1 = FALSE;
                        BRAKING_FLAG_2 = FALSE;                     
                    }
                }
                else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                          Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
                {
                    if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
                    {
                        //1 CLOSED
                        if ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                        {
                              WG_Stop_Closed();
                        }
                        //1 OPENED
                        else if ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                        {
                             WG_Stop_Opened();
                        } 
                        else
                        {
                            WG_Stop_Opened_Half();
                            SLOW_ENABLE_FLAG_1 = TRUE;
                            SLOW_ENABLE_FLAG_2 = TRUE;
                            BRAKING_FLAG_1 = FALSE;
                            BRAKING_FLAG_2 = FALSE;                     
                        }
                    }
                    else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // Reverse
                    {
                        //1 CLOSED
                        if ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                        {
                              WG_Stop_Closed();
                        }
                        //1 OPENED
                        else if ( Position_Opened_2 (Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                        {
                             WG_Stop_Opened();
                        } 
                        else
                        {
                            WG_Stop_Opened_Half();
                            SLOW_ENABLE_FLAG_1 = TRUE;
                            SLOW_ENABLE_FLAG_2 = TRUE;
                            BRAKING_FLAG_1 = FALSE;
                            BRAKING_FLAG_2 = FALSE;                     
                        }
                    }        
                }            
            }        
        }
    }
    else
    {
        Reset_Inputs();
    }
}

static void Wg_Power_On_Alerts ( void )
{
    if ((Controller_Variables.Controller_Vars.Inputs_Error & WG_ALL_ALERTS ) != 0 )
    {
        Machine_State = WG_POWER_ON_ALERT;
    }

    Reset_Inputs();
}

static void Wg_Power_On_Alerts_Release ( void )
{
    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) // Inverters
    {
        if ((Controller_Variables.Controller_Vars.Inputs_Error & WG_ALL_ALERTS ) == 0 )
        {
            Machine_State = WG_POWER_ON;
            WG_TIMER_FLAG = FALSE;
        }
    }
    else if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 ) // 24VDC
    {
        if ((Controller_Variables.Controller_Vars.Inputs_Error & DC24V_ALL_ALERTS ) == 0 )
        {
            Machine_State = WG_POWER_ON;
            WG_TIMER_FLAG = FALSE;
        }
    }
}

static void Wg_Alerts_Closing_Handling ( void )
{
    uint16_t Alerts_Temp1 = NO_PHOTO_ALL_ALERTS;

    if ( Service_Variables.Serv_Vars.In7_Fun == 1) // Listwa na otwieranie
        Alerts_Temp1 &= ~INPUT_SE1;
    if ( Service_Variables.Serv_Vars.In8_Fun == 1) // Listwa na otwieranie
        Alerts_Temp1 &= ~INPUT_SE2;
    if ( Service_Variables.Serv_Vars.In9_Fun == 1) // Listwa na otwieranie
        Alerts_Temp1 &= ~INPUT_SE3;
    if ( Service_Variables.Serv_Vars.In10_Fun == 1) // Listwa na otwieranie
        Alerts_Temp1 &= ~INPUT_SE4;

    if ((Controller_Variables.Controller_Vars.Inputs_Error & Alerts_Temp1 ) != 0 )
    {
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 || //2 wings
             Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 )  //1 wings
        {
            Machine_State = WG_ALERTS;
            ALERTS_FLAG = FALSE;
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 ) //1 wing
        {
            if ( (Controller_Variables.Controller_Vars.Inputs_Error & NO_SE_ALERTS ) != 0 )
            {
                Machine_State = WG_ALERTS;
                ALERTS_FLAG = FALSE;
            } 
        
            if ( (Controller_Variables.Controller_Vars.Inputs_Error & (INPUT_SE_RELEASED & Alerts_Temp1)) != 0 )
            {
                Machine_State = CL_AL_STOP;
                SLOW_ENABLE_FLAG_1 = TRUE;
                SLOW_ENABLE_FLAG_2 = TRUE;
                BRAKING_FLAG_1 = FALSE;
                BRAKING_FLAG_2 = FALSE; 
            }
        }    
    }
    else
    {
        if ( (Controller_Variables.Controller_Vars.Inputs_Error & INPUT_PHOTO1) != 0 )
        {
            if ( Controlling_Variables.Ctrl_Vars.Photo_Closing_Fun == 1 )
            {
                Machine_State = WG_ALERTS;
                PHOTO_PRIORITY_ENABLE = TRUE;
                ALERTS_FLAG = FALSE;            
            }
            else if ( Controlling_Variables.Ctrl_Vars.Photo_Closing_Fun == 2 )
            {
                if ( PHOTO_PRIORITY_ENABLE == FALSE )
                    Machine_State = PH_WAIT_CLOSING;
            }
            else if ( Controlling_Variables.Ctrl_Vars.Photo_Closing_Fun == 3 )
            {
                if( PHOTO_PRIORITY_ENABLE == FALSE )
                    Machine_State = PH_WAIT_CLOSING;            
            }        
        }        
    }
}

static void Wg_Alerts_Opening_Handling ( void )
{
    uint16_t Alerts_Temp2 = NO_PHOTO_ALL_ALERTS;

    if ( Service_Variables.Serv_Vars.In7_Fun == 2) // Listwa na zamykanie
        Alerts_Temp2 &= ~INPUT_SE1;
    if ( Service_Variables.Serv_Vars.In8_Fun == 2) // Listwa na Zamykanie
        Alerts_Temp2 &= ~INPUT_SE2;
    if ( Service_Variables.Serv_Vars.In9_Fun == 2) // Listwa na Zamykanie
        Alerts_Temp2 &= ~INPUT_SE3;
    if ( Service_Variables.Serv_Vars.In10_Fun == 2) // Listwa na Zamykanie
        Alerts_Temp2 &= ~INPUT_SE4;
    
    if ((Controller_Variables.Controller_Vars.Inputs_Error & Alerts_Temp2 ) != 0 )
    {
        if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 || //1 wings
             Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 ) //2 wings
        {
            Machine_State = WG_OPENED_HALF;
        }
        else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 ) //Sliding
        {
            Machine_State = OP_AL_STOP;
            SLOW_ENABLE_FLAG_1 = TRUE;
            SLOW_ENABLE_FLAG_2 = TRUE;
            BRAKING_FLAG_1 = FALSE;
            BRAKING_FLAG_2 = FALSE; 
        }
    } 
    else
    {
        if ( (Controller_Variables.Controller_Vars.Inputs_Error & INPUT_PHOTO1) != 0 )
        {
            if ( Controlling_Variables.Ctrl_Vars.Photo_Opening_Fun == 1 )
            {
                Machine_State = WG_OPENING_ALERTS;
                PHOTO_PRIORITY_ENABLE = TRUE;
                ALERTS_FLAG = FALSE;             
            }
            else if ( Controlling_Variables.Ctrl_Vars.Photo_Opening_Fun == 2 )
            {
                if ( PHOTO_PRIORITY_ENABLE == FALSE )
                    Machine_State = PH_WAIT_OPENING;
            }
            else if ( Controlling_Variables.Ctrl_Vars.Photo_Opening_Fun == 3 )
            {
                if ( PHOTO_PRIORITY_ENABLE == FALSE )
                    Machine_State = PH_WAIT_OPENING;            
            }        
        }
    }
}

static void Wg_Alerts_Release ( void )
{
    if ( ALERTS_FLAG == FALSE )
    {
        System_Timer_Setting ( &WG_Timer.Timer, Service_Variables.Serv_Vars.Serwis_017, T_10msec );        
        ALERTS_FLAG = TRUE;
    }
    else
    {
        if ( System_Timer_Check ( &WG_Timer.Timer, T_10msec ) == TRUE )
        {
            if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 0 ) //Limit switches
            {
                if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) //2 wings speed
                {
                    //BOTH CLOSED HALF
                    if ( !(Inputs_Level & INPUT2) && !(Inputs_Level & INPUT4) )
                    {
                        Machine_State = WG_OPENING_1_2;    
                    }
                    //1 OPENED 2 CLOSED
                    else if ( !(Inputs_Level & INPUT2) && (Inputs_Level & INPUT4) )
                    {
                        Machine_State = WG_OPENING_1;    
                    }
                    //2 OPENED 1 CLOSED
                    else if ( (Inputs_Level & INPUT2) && !(Inputs_Level & INPUT4) )
                    {
                        Machine_State = WG_OPENING_2;        
                    }
                    //BOTH OPENED
                    else if ( (Inputs_Level & INPUT2) && (Inputs_Level & INPUT4) )
                    {
                        Machine_State = WG_OPENED;
                    }
                }
                if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing speed
                     Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )  //sliding
                {
                    //1 OPENED
                    if ( !(Inputs_Level & INPUT2) )
                    {
                        if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Inverters
                        {                    
                            Machine_State = WG_OPENING_1; 
                        }
                        if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 ) //24VDC
                        {                    
                            Machine_State = OPENING_RELAY; 
                            System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                                                    *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                                                    Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;            
                        }
                    }
                    //1 CLOSED
                    else if ( Inputs_Level & INPUT2 )
                    {
                        Machine_State = WG_OPENED;        
                    }                
                }
            }
            else if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 1 ) //Magnetic sensor
            {
                if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
                {
                    //BOTH OPENED
                    if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                         ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
                    {
                        Machine_State = WG_OPENED;
                    }
                    //1 OPENED 2 CLOSED
                    else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                              ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
                    {
                        Machine_State = WG_OPENING_1;    
                    }
                    //2 OPENED 1 CLOSED
                    else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                              ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
                    {
                        Machine_State = WG_OPENING_2;
                    }
                    //BOTH  NOT OPENED
                    else if ( ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                              ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
                    {        
                        Machine_State = WG_OPENING_1_2;
                    }
                }
                else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                          Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
                {
                    if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
                    {
                        //1 CLOSED
                        if ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                        {
                            Machine_State = WG_OPENED;
                        }
                        //1 OPENED
                        else if ( Position_Opened_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                        {
                            Machine_State = WG_OPENING_1;
                        }
                    }
                    else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // reverse
                    {
                        //1 CLOSED
                        if ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                        {
                            Machine_State = WG_OPENED;
                        }
                        //1 OPENED
                        else if ( Position_Opened_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                        {
                            Machine_State = WG_OPENING_1;
                        }
                    }                
                }
            }
        

            SLOW_ENABLE_FLAG_1 = TRUE;
            SLOW_ENABLE_FLAG_2 = TRUE;
            BRAKING_FLAG_1 = FALSE;
            BRAKING_FLAG_2 = FALSE;        
            ALERTS_FLAG = FALSE;
        }
    }
}

/*******************************************************************************
* Function Name  : Gate_Opened_Fun
* Description    : Defines for howlong gateis opened if set to 0, gate is openedcontiunously
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Gate_Opened_Fun ( void )
{
    uint16_t Time_Temp2;

    if ( OPEN_ON_LEVEL_14 == FALSE && OPEN_ON_LEVEL_15 == FALSE && OPEN_ON_LEVEL_16 == FALSE && OPEN_ON_LEVEL_17 == FALSE && OPEN_ON_LEVEL_18 == FALSE && OPEN_ON_LEVEL_19 == FALSE && OPEN_ON_LEVEL_20 == FALSE )
    {
        if ( Controlling_Variables.Ctrl_Vars.Photo_Opened == 1 )
        {
            if ( (Controller_Variables.Controller_Vars.Inputs_Error & INPUT_PHOTO1) != 0 )
            {
                if ( READY_4_CLOSING == FALSE )
                    READY_4_CLOSING = TRUE;
            }
            else
            {
                if ( READY_4_CLOSING == TRUE )
                {
                    CLOSE_GATE_FLAG = TRUE;
                    READY_4_CLOSING = FALSE;
                }
            }        
        }
        else if ( Controlling_Variables.Ctrl_Vars.Photo_Opened == 2 )
        {
            if ( (Controller_Variables.Controller_Vars.Inputs_Error & INPUT_PHOTO1) != 0 )
            {
                if ( READY_4_CLOSING == FALSE )
                    READY_4_CLOSING = TRUE;            
            }
            else
            {
                if ( READY_4_CLOSING == TRUE )
                {
                    OPENED_WAIT = FALSE;
                    READY_4_CLOSING = FALSE;
                }
            }
        }

        if ( Controlling_Variables.Ctrl_Vars.Gate_Opened_Time != 0 )
        {
            if ( OPENED_WAIT == FALSE )
            {
                System_Timer_Setting ( &Opened_Timer.Timer, Controlling_Variables.Ctrl_Vars.Gate_Opened_Time, T_1sec );
                OPENED_WAIT = TRUE;
            }
            else
            {
                if ( System_Timer_Check ( &Opened_Timer.Timer, T_1sec ) == TRUE )
                {
                    CLOSE_GATE_FLAG = TRUE;
                }
            }
        } 

        if ( CLOSE_GATE_FLAG == TRUE )
        {
            Machine_State = PRE_WORNING_OPENING;
            PRE_WORNING_FLAG = FALSE;
        }
    }
    else
    {
        if ( Service_Variables.Serv_Vars.In14_Fun == 4 && OPEN_ON_LEVEL_14 == TRUE )
        {
            if (!(Inputs_Level & INPUT14))
            {
                CLOSE_GATE_FLAG = TRUE;
                OPEN_ON_LEVEL_14 = FALSE;
            }
        }
     
        if ( Service_Variables.Serv_Vars.In15_Fun == 4 && OPEN_ON_LEVEL_15 == TRUE )
        {
            if (!(Inputs_Level & INPUT15))
            {
                CLOSE_GATE_FLAG = TRUE;
                OPEN_ON_LEVEL_15 = FALSE;
            }
        }
     
        if ( Service_Variables.Serv_Vars.In16_Fun == 4 && OPEN_ON_LEVEL_16 == TRUE )
        {
            if (!(Inputs_Level & INPUT16))
            {
                CLOSE_GATE_FLAG = TRUE;
                OPEN_ON_LEVEL_16 = FALSE;
            }
        }
     
        if ( Service_Variables.Serv_Vars.In17_Fun == 4 && OPEN_ON_LEVEL_17 == TRUE )
        {
            if (!(Inputs_Level & INPUT17))
            {
                CLOSE_GATE_FLAG = TRUE;
                OPEN_ON_LEVEL_17 = FALSE;
            }
        }
    
        if ( Service_Variables.Serv_Vars.In18_Fun == 4 && OPEN_ON_LEVEL_18 == TRUE )
        {
            if (!(Inputs_Level & INPUT18))
            {
                CLOSE_GATE_FLAG = TRUE;
                OPEN_ON_LEVEL_18 = FALSE;
            }
        }

        if ( Service_Variables.Serv_Vars.In19_Fun == 4 && OPEN_ON_LEVEL_19 == TRUE )
        {
            if (!(Inputs_Level & INPUT19))
            {
                CLOSE_GATE_FLAG = TRUE;
                OPEN_ON_LEVEL_19 = FALSE;
            }
        }
    
        if ( Service_Variables.Serv_Vars.In20_Fun == 4 && OPEN_ON_LEVEL_20 == TRUE )
        {
            if (!(Inputs_Level & INPUT20))
            {
                CLOSE_GATE_FLAG = TRUE;
                OPEN_ON_LEVEL_20 = FALSE;
            }
        }
    }

    if ((Inputs_Level & INPUT13))
    {
        CLOSE_GATE_FLAG = TRUE;
    }
    
    if ( Service_Variables.Serv_Vars.In14_Fun == 3 )
    {
        if ((Inputs_Level & INPUT14))
        {
            CLOSE_GATE_FLAG = TRUE;
        }
    }

    if ( Service_Variables.Serv_Vars.In15_Fun == 3 )
    {
        if ((Inputs_Level & INPUT15))
        {
            CLOSE_GATE_FLAG = TRUE;
        }
    }

    if ( Service_Variables.Serv_Vars.In16_Fun == 3 )
    {
        if ((Inputs_Level & INPUT16))
        {
            CLOSE_GATE_FLAG = TRUE;
        }
    }
    
    if ( Service_Variables.Serv_Vars.In17_Fun == 3 )
    {
        if ((Inputs_Level & INPUT17))
        {
            CLOSE_GATE_FLAG = TRUE;
        }
    }    

    if ( Service_Variables.Serv_Vars.In18_Fun == 3 )
    {
        if ((Inputs_Level & INPUT18))
        {
            CLOSE_GATE_FLAG = TRUE;
        }
    }

    if ( Service_Variables.Serv_Vars.In19_Fun == 3 )
    {
        if ((Inputs_Level & INPUT19))
        {
            CLOSE_GATE_FLAG = TRUE;
        }
    }

    if ( Service_Variables.Serv_Vars.In20_Fun == 3 )
    {
        if ((Inputs_Level & INPUT20))
        {
            CLOSE_GATE_FLAG = TRUE;
        }
    }
    
    if ( CLOSE_GATE_FLAG == TRUE )
    {
        CLOSE_GATE_FLAG = FALSE;
        OPENED_WAIT = FALSE;
        Machine_State = PRE_WORNING_CLOSING;
        PRE_WORNING_FLAG = FALSE;  
    }
}

/*******************************************************************************
* Function Name  : Inverters_Setting_Fun
* Description    : Srtting the frequency inverters during powering on the controller
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Inverters_Setting_Fun ( void )
{
    if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) // Two wings gate
    {   
        if ( (Controller_Variables.Controller_Vars.Inputs_Error & INVERTERS_CONNECTED) == 0 )
        {
            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];
            Inputs_Error_Mask = 0;
        }
    }
    else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || // One wing gate
              Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 ) // sliding
    {
        if ( (Controller_Variables.Controller_Vars.Inputs_Error & F1_DISCONNECTED) == 0 )
        {
            Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];
            Inputs_Error_Mask = 0;
        }    
    }
}

static void Inverters_Speed_Control ( void )
{
    uint16_t Slowing_Angle_Temp1;
    uint16_t Slowing_Angle_Temp2;
    uint16_t Freq_Sub1;
    uint16_t Freq_Sub2;
    uint16_t Freq_Sub3;

    if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 0 ) //Limit switches
    {    
        if ( Machine_State == WG_CLOSED ||
             Machine_State == WG_OPENED )
        {
            SLOW_ENABLE_FLAG_1 = FALSE;
            SLOW_ENABLE_FLAG_2 = FALSE;
            BRAKING_FLAG_1 = FALSE;
            BRAKING_FLAG_2 = FALSE;    
        }

        if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) // inverters
        {
            if ( SLOW_ENABLE_FLAG_1 == FALSE )
            {
                Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq1;

                if ( System_Timer_Check ( &Slow_1_Timer.Timer, T_100msec ) == TRUE )
                {
                    System_Timer_Setting ( &Braking_1_Timer.Timer, Service_Variables.Serv_Vars.Serwis_019, T_10msec );
                    SLOW_ENABLE_FLAG_1 = TRUE;
                    BRAKING_FLAG_1= TRUE;
                }
            }
            else
            {
                if ( BRAKING_FLAG_1 == TRUE )
                {
                    if ( System_Timer_Check ( &Braking_1_Timer.Timer, T_10msec ) == TRUE )
                    {
                        System_Timer_Setting ( &Braking_1_Timer.Timer, Service_Variables.Serv_Vars.Serwis_019, T_10msec );

                        if ( Controller_Variables.Controller_Vars.Frequency1 > (Controlling_Variables.Ctrl_Vars.Freq_Slow + 500) )
                            Controller_Variables.Controller_Vars.Frequency1 -= 500;
                        else
                            BRAKING_FLAG_1 = FALSE;
                    }
                }
                else
                {
                    Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq_Slow;
                }
            }

            if ( SLOW_ENABLE_FLAG_2 == FALSE )
            {
                Controller_Variables.Controller_Vars.Frequency2 = Controlling_Variables.Ctrl_Vars.Freq2;

                if ( System_Timer_Check ( &Slow_2_Timer.Timer, T_100msec ) == TRUE )
                {
                    System_Timer_Setting ( &Braking_2_Timer.Timer, Service_Variables.Serv_Vars.Serwis_019, T_10msec );
                    SLOW_ENABLE_FLAG_2 = TRUE;
                    BRAKING_FLAG_2 = TRUE;
                }
            }
            else
            {
                if ( BRAKING_FLAG_2 == TRUE )
                {
                    if ( System_Timer_Check ( &Braking_2_Timer.Timer, T_10msec ) == TRUE )
                    {
                        System_Timer_Setting ( &Braking_2_Timer.Timer, Service_Variables.Serv_Vars.Serwis_019, T_10msec );

                        if ( Controller_Variables.Controller_Vars.Frequency2 > (Controlling_Variables.Ctrl_Vars.Freq_Slow + 500) )
                            Controller_Variables.Controller_Vars.Frequency2 -= 500;
                        else
                            BRAKING_FLAG_2 = FALSE;
                    }
                }
                else
                {
                    Controller_Variables.Controller_Vars.Frequency2 = Controlling_Variables.Ctrl_Vars.Freq_Slow;
                }
            }
        }
        else if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 ) // 24VDC
        {
            Manual_Values.Values.Mos1_Manual_Value = 500;
            Manual_Values.Values.Mos2_Manual_Value = 500;
        }
    }
    else if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 1 ) //MAgneticSensor
    {
        if ( Machine_State == SENSOR_SETTING )
        {
            Controller_Variables.Controller_Vars.Frequency1 = Service_Variables.Serv_Vars.Serwis_023;        
            Controller_Variables.Controller_Vars.Frequency2 = Service_Variables.Serv_Vars.Serwis_023;
        }
    
        if ( Machine_State == WG_POWER_ON_CLOSING_1 ||
             Machine_State == WG_POWER_ON_CLOSING_2 ||
             Machine_State == WG_POWER_ON_CLOSING_1_2 )
        {
            Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq_Slow;        
            Controller_Variables.Controller_Vars.Frequency2 = Controlling_Variables.Ctrl_Vars.Freq_Slow;
        }

        if ( Machine_State == WG_CLOSING_1 ||
             Machine_State == WG_CLOSING_2 ||
             Machine_State == WG_CLOSING_1_2 ||
             Machine_State == START_CLOSING )
        {
            Slowing_Angle_Temp1 = (uint16_t)( (Controlling_Variables.Ctrl_Vars.Braking_Angle * Angle1_Max )/3600 );
            Slowing_Angle_Temp2 = (uint16_t)( (Controlling_Variables.Ctrl_Vars.Braking_Angle * Angle2_Max )/3600 );
        
            Freq_Sub1 = (uint16_t)((Controlling_Variables.Ctrl_Vars.Freq1 - Service_Variables.Serv_Vars.Serwis_023)/(Controlling_Variables.Ctrl_Vars.Angle1_Op - Controlling_Variables.Ctrl_Vars.Angle1_Cl - Slowing_Angle_Temp1 - 20));
            Freq_Sub2 = (uint16_t)((Controlling_Variables.Ctrl_Vars.Freq2 - Service_Variables.Serv_Vars.Serwis_023)/(Controlling_Variables.Ctrl_Vars.Angle2_Cl - Controlling_Variables.Ctrl_Vars.Angle2_Op - Slowing_Angle_Temp2 - 20));

            Freq_Sub3 = (uint16_t)((Controlling_Variables.Ctrl_Vars.Freq1 - Service_Variables.Serv_Vars.Serwis_023)/(Controlling_Variables.Ctrl_Vars.Angle2_Cl - Controlling_Variables.Ctrl_Vars.Angle2_Op - Slowing_Angle_Temp2 - 20));

        //1
        
            if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
            { 
                if (  Controller_Variables.Controller_Vars.MSens1_Angle > (Controlling_Variables.Ctrl_Vars.Angle1_Op - Slowing_Angle_Temp1) )
                {
                    Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq1;        
                }
                else
                {
                    if (  Controller_Variables.Controller_Vars.MSens1_Angle > (Controlling_Variables.Ctrl_Vars.Angle1_Cl + 20) )
                    {
                        if ( Controller_Variables.Controller_Vars.Frequency1 > Service_Variables.Serv_Vars.Serwis_023 )
                            Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq1 - (Freq_Sub1 * ( (Controlling_Variables.Ctrl_Vars.Angle1_Op - Slowing_Angle_Temp1 ) - Controller_Variables.Controller_Vars.MSens1_Angle) );
                    }
                }
            }
            else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // Reverse
            { 
                if (  Controller_Variables.Controller_Vars.MSens2_Angle < (Controlling_Variables.Ctrl_Vars.Angle2_Op + Slowing_Angle_Temp2) )
                {
                    Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq1;        
                }
                else
                {
                    if (  Controller_Variables.Controller_Vars.MSens2_Angle < (Controlling_Variables.Ctrl_Vars.Angle2_Cl - 20) )
                    {
                        if ( Controller_Variables.Controller_Vars.Frequency1 > Service_Variables.Serv_Vars.Serwis_023 )
                            Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq1 - (Freq_Sub3 * ( Controller_Variables.Controller_Vars.MSens2_Angle - (Controlling_Variables.Ctrl_Vars.Angle2_Op + Slowing_Angle_Temp2) ) );
                    }
                }
            }    
                
    //2   
            if (  Controller_Variables.Controller_Vars.MSens2_Angle < (Controlling_Variables.Ctrl_Vars.Angle2_Op + Slowing_Angle_Temp2) )
            {
                Controller_Variables.Controller_Vars.Frequency2 = Controlling_Variables.Ctrl_Vars.Freq2;        
            }
            else
            {
                if (  Controller_Variables.Controller_Vars.MSens2_Angle < (Controlling_Variables.Ctrl_Vars.Angle2_Cl - 20) )
                {
                    if ( Controller_Variables.Controller_Vars.Frequency2 > Service_Variables.Serv_Vars.Serwis_023 )
                        Controller_Variables.Controller_Vars.Frequency2 = Controlling_Variables.Ctrl_Vars.Freq2 - (Freq_Sub2 * ( Controller_Variables.Controller_Vars.MSens2_Angle - (Controlling_Variables.Ctrl_Vars.Angle2_Op + Slowing_Angle_Temp2) ) );
                }
            }
        }

        if ( Machine_State == WG_OPENING_1 ||
             Machine_State == WG_OPENING_2 ||
             Machine_State == WG_OPENING_1_2 ||
             Machine_State == START_OPENING )
        {
            Slowing_Angle_Temp1 = (uint16_t)( (Controlling_Variables.Ctrl_Vars.Braking_Angle * Angle1_Max )/3600 );
            Slowing_Angle_Temp2 = (uint16_t)( (Controlling_Variables.Ctrl_Vars.Braking_Angle * Angle2_Max )/3600 );
        
            Freq_Sub1 = (uint16_t)((Controlling_Variables.Ctrl_Vars.Freq1 - Service_Variables.Serv_Vars.Serwis_023)/(Controlling_Variables.Ctrl_Vars.Angle1_Op - Controlling_Variables.Ctrl_Vars.Angle1_Cl - Slowing_Angle_Temp1 - 20));
            Freq_Sub2 = (uint16_t)((Controlling_Variables.Ctrl_Vars.Freq2 - Service_Variables.Serv_Vars.Serwis_023)/(Controlling_Variables.Ctrl_Vars.Angle2_Cl - Controlling_Variables.Ctrl_Vars.Angle2_Op - Slowing_Angle_Temp2 - 20));
            Freq_Sub3 = (uint16_t)((Controlling_Variables.Ctrl_Vars.Freq1 - Service_Variables.Serv_Vars.Serwis_023)/(Controlling_Variables.Ctrl_Vars.Angle2_Cl - Controlling_Variables.Ctrl_Vars.Angle2_Op - Slowing_Angle_Temp2 - 20));

        //1 
        
            if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
            { 
                if (  Controller_Variables.Controller_Vars.MSens1_Angle < (Controlling_Variables.Ctrl_Vars.Angle1_Cl + Slowing_Angle_Temp1) )
                {
                    Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq1;        
                }
                else
                {
                    if (  Controller_Variables.Controller_Vars.MSens1_Angle < (Controlling_Variables.Ctrl_Vars.Angle1_Op - 20) )
                    {
                        if ( Controller_Variables.Controller_Vars.Frequency1 > Service_Variables.Serv_Vars.Serwis_023 )
                            Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq1 - (Freq_Sub1 * ( Controller_Variables.Controller_Vars.MSens1_Angle - (Controlling_Variables.Ctrl_Vars.Angle1_Cl + Slowing_Angle_Temp1)) );
                    }
                }
            }
            else if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // Reverse
            { 
                if (  Controller_Variables.Controller_Vars.MSens2_Angle > (Controlling_Variables.Ctrl_Vars.Angle2_Cl - Slowing_Angle_Temp2) )
                {
                    Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq1;        
                }
                else
                {
                    if (  Controller_Variables.Controller_Vars.MSens2_Angle > (Controlling_Variables.Ctrl_Vars.Angle2_Op + 20) )
                    {
                        if ( Controller_Variables.Controller_Vars.Frequency1 > Service_Variables.Serv_Vars.Serwis_023 )
                            Controller_Variables.Controller_Vars.Frequency1 = Controlling_Variables.Ctrl_Vars.Freq1 - (Freq_Sub3 * ( (Controlling_Variables.Ctrl_Vars.Angle2_Cl - Slowing_Angle_Temp2 ) - Controller_Variables.Controller_Vars.MSens2_Angle) );
                    }
                }
            }
        
        
        //2
            if (  Controller_Variables.Controller_Vars.MSens2_Angle > (Controlling_Variables.Ctrl_Vars.Angle2_Cl - Slowing_Angle_Temp2) )
            {
                Controller_Variables.Controller_Vars.Frequency2 = Controlling_Variables.Ctrl_Vars.Freq2;        
            }
            else
            {
                if (  Controller_Variables.Controller_Vars.MSens2_Angle > (Controlling_Variables.Ctrl_Vars.Angle2_Op + 20) )
                {
                    if ( Controller_Variables.Controller_Vars.Frequency2 > Service_Variables.Serv_Vars.Serwis_023 )
                        Controller_Variables.Controller_Vars.Frequency2 = Controlling_Variables.Ctrl_Vars.Freq2 - (Freq_Sub2 * ( (Controlling_Variables.Ctrl_Vars.Angle2_Cl - Slowing_Angle_Temp2 ) - Controller_Variables.Controller_Vars.MSens2_Angle) );
                }
            }
        }
    }
}

static void WG_Stop_Closed ( void )
{
    if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
    {
        switch ( Inputs.Keyboard_Memory )
        {
            case OPEN_CLOSE_GATE:
                WG_Inputs_Closed_Handling_Function();   
            break;

            case OPEN_CLOSE_GATE1:
                WG_Inputs_Closed_Handling_Function();   
            break;
            
            case OPEN_CLOSE_GATE2:
                WG_Inputs_Closed_Handling_Function();   
            break;
                        
            case OPEN_CLOSE_GATE3:
                WG_Inputs_Closed_Handling_Function();   
            break;
                                    
            case OPEN_CLOSE_GATE4:
                WG_Inputs_Closed_Handling_Function();   
            break;
                                                
            case OPEN_CLOSE_GATE5:
                WG_Inputs_Closed_Handling_Function();   
            break;
                                                            
            case OPEN_CLOSE_GATE6:
                WG_Inputs_Closed_Handling_Function();   
            break;
                                                                        
            case OPEN_CLOSE_GATE7:
                WG_Inputs_Closed_Handling_Function();   
            break;
                        
            default:
            break;
        }
        Inputs.Keyboard_Flag = 0;
    }

    if ( Inputs.Keyboard_State == 0 )
    {
        Inputs.Keyboard_Memory = 0;
    }

    if ( Inputs_Level & INPUT12 )
    {
        if ( Service_Variables.Serv_Vars.In12_Fun == 2 )  //Open
        {
            WG_Inputs_Closed_Handling_Function();     
        }
    }

    if ( Inputs_Level & INPUT14 )
    {
        if ( Service_Variables.Serv_Vars.In14_Fun == 2 )  //Open
        {
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_14 = FALSE;
    }

    if ( Inputs_Level & INPUT15 )
    {
        if ( Service_Variables.Serv_Vars.In15_Fun == 2 )
        {
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_15 = FALSE;
    }

    if ( Inputs_Level & INPUT16 )
    {
        if ( Service_Variables.Serv_Vars.In16_Fun == 2 )
        {
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_16 = FALSE;
    }

    if ( Inputs_Level & INPUT17 )
    {
        if ( Service_Variables.Serv_Vars.In17_Fun == 2 )
        {
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_17 = FALSE;
    }

    if ( Inputs_Level & INPUT18 )
    {
        if ( Service_Variables.Serv_Vars.In18_Fun == 2 )
        {
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_18 = FALSE;
    }

    if ( Inputs_Level & INPUT19 )
    {
        if ( Service_Variables.Serv_Vars.In19_Fun == 2 )
        {
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_19 = FALSE;
    }

    if ( Inputs_Level & INPUT20 )
    {
        if ( Service_Variables.Serv_Vars.In20_Fun == 2 )   //Open
        {
            WG_Inputs_Closed_Handling_Function();   
        }
    }
    else
    {
        OPEN_ON_LEVEL_20 = FALSE;
    }
}

static void WG_Stop_Opened ( void )
{
    if ((Controller_Variables.Controller_Vars.Inputs_Error & WG_ALL_ALERTS ) == 0 )
    {
        if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
        {
            switch ( Inputs.Keyboard_Memory )
            {
                case OPEN_CLOSE_GATE:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE1:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE2:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE3:
                    WG_Inputs_Opened_Handling_Function();
                break;

                case OPEN_CLOSE_GATE4:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE5:
                    WG_Inputs_Opened_Handling_Function();
                break;

                case OPEN_CLOSE_GATE6:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                case OPEN_CLOSE_GATE7:
                    WG_Inputs_Opened_Handling_Function();
                break;
                
                default:
                break;
            }
            Inputs.Keyboard_Flag = 0;
        }

        if ( Inputs.Keyboard_State == 0 )
        {
            Inputs.Keyboard_Memory = 0;
        }
    
        if ( Inputs_Level & INPUT13 )
        {
            if ( Service_Variables.Serv_Vars.In13_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT14 )
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT15 )
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT16 )
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT17 )
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 3 )  //Close
            {
                 WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT18 )
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT19 )
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }

        if ( Inputs_Level & INPUT20 )
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Handling_Function();
            }
        }    
    }
}

static void WG_Stop_Opened_Half ( void )
{
    if ((Controller_Variables.Controller_Vars.Inputs_Error & WG_ALL_ALERTS ) == 0 )
    {
        if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
        {
            switch ( Inputs.Keyboard_Memory )
            {
                case OPEN_CLOSE_GATE:
                    WG_Inputs_Opened_Half_Handling();
                break;

                case OPEN_CLOSE_GATE1:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE2:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE3:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE4:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE5:
                    WG_Inputs_Opened_Half_Handling();
                break;

                case OPEN_CLOSE_GATE6:
                    WG_Inputs_Opened_Half_Handling();
                break;
                
                case OPEN_CLOSE_GATE7:
                    WG_Inputs_Opened_Half_Handling();
                break;
 
                default:
                break;
            }
            Inputs.Keyboard_Flag = 0;
        }

        if ( Inputs.Keyboard_State == 0 )
        {
            Inputs.Keyboard_Memory = 0;
        }
    
        if ( Inputs_Level & INPUT13 )
        {
            if ( Service_Variables.Serv_Vars.In13_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT14 )
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT15 )
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT16 )
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT17 )
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT18 )
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT19 )
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }

        if ( Inputs_Level & INPUT20 )
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 3 )  //Close
            {
                WG_Inputs_Opened_Half_Handling();     
            }
        }
    }

    if ( Inputs_Level & INPUT12 )
    {
        if ( Service_Variables.Serv_Vars.In12_Fun == 2 )  //Open
        {
            WG_Inputs_Closed_Handling_Function();     
        }
    }

    if ( Inputs_Level & INPUT14 )
    {
        if ( Service_Variables.Serv_Vars.In14_Fun == 2 )
        {
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_14 = FALSE;
    }

    if ( Inputs_Level & INPUT15 )
    {
        if ( Service_Variables.Serv_Vars.In15_Fun == 2 )
        {
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_15 = FALSE;
    }

    if ( Inputs_Level & INPUT16 )
    {
        if ( Service_Variables.Serv_Vars.In16_Fun == 2 )
        {
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_16 = FALSE;
    }

    if ( Inputs_Level & INPUT17 )
    {
        if ( Service_Variables.Serv_Vars.In17_Fun == 2 )
        {
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_17 = FALSE;
    }

    if ( Inputs_Level & INPUT18 )
    {
        if ( Service_Variables.Serv_Vars.In18_Fun == 2 )  //Open
        {
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_18 = FALSE;
    }

    if ( Inputs_Level & INPUT19 )
    {
        if ( Service_Variables.Serv_Vars.In19_Fun == 2 )  //Open
        {
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_19 = FALSE;
    }

    if ( Inputs_Level & INPUT20 )
    {
        if ( Service_Variables.Serv_Vars.In20_Fun == 2 )  //Open
        {
            WG_Inputs_Closed_Half_Handling();              
        }
    }
    else
    {
        OPEN_ON_LEVEL_20 = FALSE;
    }
}

static void Inputs_Back_Handling (void )
{
    if ( Inputs_Level & INPUT1 )
        Machine_State = WG_CLOSED;
    
    if ( Inputs_Level & INPUT2 )
        Machine_State = WG_OPENED;
}

uint8_t Position_Closed_1 ( uint16_t Position_1_Range )
{
    static uint16_t Gate_1_Position;
    static uint16_t Set_1_Position;

    Gate_1_Position = MAGNETIC_SENSOR_OFFSET + Controller_Variables.Controller_Vars.MSens1_Angle;
    Set_1_Position = MAGNETIC_SENSOR_OFFSET + Controlling_Variables.Ctrl_Vars.Angle1_Cl;

    if ( Controlling_Variables.Ctrl_Vars.Angle1_Cl >= 500 )
    {
        if ( Gate_1_Position <= ( Set_1_Position - 500 ) ) 
            Gate_1_Position += 1024;
    }
    else
    {
        if ( Gate_1_Position > ( Set_1_Position + 500 ) )  
            Gate_1_Position -= 1024;
    }

    if ( (Gate_1_Position >= (Set_1_Position - 50/*Position_1_Range*/)) && (Gate_1_Position <= (Set_1_Position + Position_1_Range)) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

uint8_t Position_Closed_2 ( uint16_t Position_2_Range )
{
    static uint16_t Gate_2_Position;
    static uint16_t Set_2_Position;

    Gate_2_Position = MAGNETIC_SENSOR_OFFSET + Controller_Variables.Controller_Vars.MSens2_Angle;
    Set_2_Position = MAGNETIC_SENSOR_OFFSET + Controlling_Variables.Ctrl_Vars.Angle2_Cl;

    if ( Controlling_Variables.Ctrl_Vars.Angle2_Cl >= 500 )
    {
        if ( Gate_2_Position <= ( Set_2_Position - 500 ) ) 
            Gate_2_Position += 1024;
    }
    else
    {
        if ( Gate_2_Position > ( Set_2_Position + 500 ) )  
            Gate_2_Position -= 1024;
    }

    if ( (Gate_2_Position >= (Set_2_Position - Position_2_Range)) && (Gate_2_Position <= (Set_2_Position + 50/*Position_2_Range*/)) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}




uint8_t Position_Opened_1 ( uint16_t Position_3_Range )
{
    static uint16_t Gate_3_Position;
    static uint16_t Set_3_Position;

    Gate_3_Position = MAGNETIC_SENSOR_OFFSET + Controller_Variables.Controller_Vars.MSens1_Angle;
    Set_3_Position = MAGNETIC_SENSOR_OFFSET + Controlling_Variables.Ctrl_Vars.Angle1_Op;

    if ( Controlling_Variables.Ctrl_Vars.Angle1_Op >= 500 )
    {
        if ( Gate_3_Position <= ( Set_3_Position - 500 ) ) 
            Gate_3_Position += 1024;
    }
    else
    {
        if ( Gate_3_Position > ( Set_3_Position + 500 ) )  
            Gate_3_Position -= 1024;
    }

    if ( (Gate_3_Position >= (Set_3_Position - Position_3_Range)) && (Gate_3_Position <= (Set_3_Position + 50/*Position_3_Range*/)) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

uint8_t Position_Opened_2 ( uint16_t Position_4_Range )
{
    static uint16_t Gate_4_Position;
    static uint16_t Set_4_Position;

    Gate_4_Position = MAGNETIC_SENSOR_OFFSET + Controller_Variables.Controller_Vars.MSens2_Angle;
    Set_4_Position = MAGNETIC_SENSOR_OFFSET + Controlling_Variables.Ctrl_Vars.Angle2_Op;

    if ( Controlling_Variables.Ctrl_Vars.Angle2_Op >= 500 )
    {
        if ( Gate_4_Position <= ( Set_4_Position - 500 ) ) 
            Gate_4_Position += 1024;
    }
    else
    {
        if ( Gate_4_Position > ( Set_4_Position + 500 ) )  
            Gate_4_Position -= 1024;
    }

    if ( (Gate_4_Position >= (Set_4_Position - 50/*Position_4_Range*/)) && (Gate_4_Position <= (Set_4_Position + Position_4_Range)) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

static void Cl_Start_MS_Fun ( void )
{
/*
    uint16_t Angle_Closed1;
    uint16_t Angle_Closed2;

    Angle_Closed1 = Controller_Variables.Controller_Vars.MSens1_Angle - Controlling_Variables.Ctrl_Vars.Angle1_Cl;
    Angle_Closed2 = Controlling_Variables.Ctrl_Vars.Angle2_Cl - Controller_Variables.Controller_Vars.MSens2_Angle;

    if ( Angle_Closed2 < Angle_Closed1 - Service_Variables.Serv_Vars.Serwis_001 )
    {
        Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];
    }
*/
}

static void Op_Start_MS_Fun ( void )
{
/*
    uint16_t Angle_Opened1;
    uint16_t Angle_Opened2;

    Angle_Opened1 = Controller_Variables.Controller_Vars.MSens1_Angle - Controlling_Variables.Ctrl_Vars.Angle1_Cl;
    Angle_Opened2 = Controlling_Variables.Ctrl_Vars.Angle2_Cl - Controller_Variables.Controller_Vars.MSens2_Angle;

    if ( Angle_Opened1 > Angle_Opened2 + Service_Variables.Serv_Vars.Serwis_001 )
    {
        Machine_State = Control_Variables[Machine_State].Function_Ptr->Next[0];
    }
*/
}

static void DC_Motor_Invert_Direction ( void )
{
    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 ) //24VDC
        Manual_Values.Values.Mos1_Dir_Manual_Value = TRUE;  
}

static void Release_Photo_Opening ( void )
{
    if ( !(Controller_Variables.Controller_Vars.Inputs_Error & INPUT_PHOTO1) )
    {
        if ( Controlling_Variables.Ctrl_Vars.Photo_Opening_Fun == 2 )
        {
            WG_Inputs_Opened_Half_Handling(); 
        }
        else if ( Controlling_Variables.Ctrl_Vars.Photo_Opening_Fun == 3 )
        {
            WG_Inputs_Closed_Half_Handling();
        }
    }
}

static void Release_Photo_Closing ( void )
{
    if ( !(Controller_Variables.Controller_Vars.Inputs_Error & INPUT_PHOTO1) )
    {
        if ( Controlling_Variables.Ctrl_Vars.Photo_Closing_Fun == 3 )
        {
            WG_Inputs_Opened_Half_Handling(); 
        }
        else if ( Controlling_Variables.Ctrl_Vars.Photo_Closing_Fun == 2 )
        {
            WG_Inputs_Closed_Half_Handling();
        }
    }
}

static void Wg_Alerts_Opening_Release ( void )
{
    if ( ALERTS_FLAG == FALSE )
    {
        System_Timer_Setting ( &WG_Timer.Timer, Service_Variables.Serv_Vars.Serwis_017, T_10msec );        
        ALERTS_FLAG = TRUE;
    }
    else
    {
        if ( System_Timer_Check ( &WG_Timer.Timer, T_10msec ) == TRUE )
        {
            if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 0 ) //Limit switches
            {
                if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) //2 wings speed
                {
                    //BOTH CLOSED HALF
                    if ( !(Inputs_Level & INPUT1) && !(Inputs_Level & INPUT3) )
                    {
                        Machine_State = WG_CLOSING_1_2;    
                    }
                    //1 OPENED 2 CLOSED
                    else if ( !(Inputs_Level & INPUT1) && (Inputs_Level & INPUT3) )
                    {
                        Machine_State = WG_CLOSING_1;    
                    }
                    //2 OPENED 1 CLOSED
                    else if ( (Inputs_Level & INPUT1) && !(Inputs_Level & INPUT3) )
                    {
                        Machine_State = WG_CLOSING_2;        
                    }
                    //BOTH OPENED
                    else if ( (Inputs_Level & INPUT1) && (Inputs_Level & INPUT3) )
                    {
                        Machine_State = WG_CLOSED;
                    }
                }
                if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing speed
                     Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )  //sliding
                {
                    //1 OPENED
                    if ( !(Inputs_Level & INPUT1) )
                    {
                        if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Inverters
                        {                    
                            Machine_State = WG_CLOSING_1; 
                        }
                        if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 ) //24VDC
                        {                    
                            Machine_State = CLOSING_RELAY; 
                            System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                                                    *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                                                    Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;            
                        }
                    }
                    //1 CLOSED
                    else if ( Inputs_Level & INPUT1 )
                    {
                        Machine_State = WG_CLOSED;        
                    }                
                }
            }
            else if ( Controlling_Variables.Ctrl_Vars.Sensor_Type == 1 ) //Magnetic sensor
            {
                if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 )//2 wings speed
                {
                    //BOTH OPENED
                    if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                         ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
                    {
                        Machine_State = WG_CLOSED;
                    }
                    //1 OPENED 2 CLOSED
                    else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                              ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ))
                    {
                        Machine_State = WG_CLOSING_1;    
                    }
                    //2 OPENED 1 CLOSED
                    else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE ) &&
                              ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
                    {
                        Machine_State = WG_CLOSING_2;
                    }
                    //BOTH  NOT OPENED
                    else if ( ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ) &&
                              ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE ))
                    {        
                        Machine_State = WG_CLOSING_1_2;
                    }
                }
                else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || //1 wing
                          Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 )//2 wings speed
                {
                
                    if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 0 ) // Normal
                    {
                        //1 CLOSED
                        if ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                        {
                            Machine_State = WG_CLOSED;
                        }
                        //1 OPENED
                        else if ( Position_Closed_1( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                        {
                                Machine_State = WG_CLOSING_1;
                        }  
                    }
                    if ( Controlling_Variables.Ctrl_Vars.One_Wing_Gate_Type == 1 ) // reverse
                    {
                        //1 CLOSED
                        if ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == TRUE )
                        {
                            Machine_State = WG_CLOSED;
                        }
                        //1 OPENED
                        else if ( Position_Closed_2( Service_Variables.Serv_Vars.Serwis_024 ) == FALSE )
                        {
                                Machine_State = WG_CLOSING_1;
                        } 
                    }                    
                }
            }
        

            SLOW_ENABLE_FLAG_1 = TRUE;
            SLOW_ENABLE_FLAG_2 = TRUE;
            BRAKING_FLAG_1 = FALSE;
            BRAKING_FLAG_2 = FALSE;        
            ALERTS_FLAG = FALSE;
        }
    }
}

static void Opening_Pre_Worning_Fun ( void )
{
    if ( PRE_WORNING_FLAG == FALSE )
    {
        System_Timer_Setting ( &Pre_Worning_Timer.Timer, Service_Variables.Serv_Vars.Serwis_020, T_100msec );
        PRE_WORNING_FLAG = TRUE;
    }
    else
    {
        if ( System_Timer_Check ( &Pre_Worning_Timer.Timer, T_100msec ) == TRUE )
        {
            OPENED_WAIT  = FALSE;

            if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) // 2 wings gate
            {
                Machine_State = START_OPENING;
                System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                                        *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                                        Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;            
            
            }
            else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || // 1 wings gate
                      Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 ) // sliding gate

            {
                Machine_State = WG_OPENING_1;  
            }

            Time_4_Gate1 = Controlling_Variables.Ctrl_Vars.Time_Slow + (Service_Variables.Serv_Vars.Serwis_020 / 10);
            Time_4_Gate2 = Controlling_Variables.Ctrl_Vars.Time_Slow + ((Service_Variables.Serv_Vars.Serwis_018 + Service_Variables.Serv_Vars.Serwis_020) / 10);
                            
            System_Timer_Setting ( &Slow_1_Timer.Timer, Time_4_Gate1, T_100msec );
            System_Timer_Setting ( &Slow_2_Timer.Timer, Time_4_Gate2, T_100msec );
            SLOW_ENABLE_FLAG_1 = FALSE;
            SLOW_ENABLE_FLAG_2 = FALSE;
            BRAKING_FLAG_1 = FALSE;
            BRAKING_FLAG_2 = FALSE;
            F1_Current_Counter = 0;
            F2_Current_Counter = 0;
            READY_4_CLOSING = FALSE;
            CLOSE_GATE_FLAG = FALSE;

            PHOTO_PRIORITY_ENABLE = FALSE;        

            PRE_WORNING_FLAG = FALSE;
        }
    }
}

static void Closing_Pre_Worning_Fun ( void )
{
    if ( PRE_WORNING_FLAG == FALSE )
    {
        System_Timer_Setting ( &Pre_Worning_Timer.Timer, Service_Variables.Serv_Vars.Serwis_020, T_100msec );
        PRE_WORNING_FLAG = TRUE;
    }
    else
    {
        if ( System_Timer_Check ( &Pre_Worning_Timer.Timer, T_100msec ) == TRUE )
        {
            if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) // 2 wings gate
            {
                Machine_State = START_CLOSING;
                System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                                    *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                                     Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );
            }
            else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1 || // 1 wings gate
                      Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2 ) // sliding gate

            {
                if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 )//inverters
                {
                    Machine_State = WG_CLOSING_1;    
                }
                else if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 1 )//24vdc
                {
                    Machine_State = CLOSING_RELAY;                                
                    System_Timer_Setting (  &Control_Variables[Machine_State].Time_Connection_Ptr->Tmr_Cntr_Ptr->Timer,
                                            *Control_Variables[Machine_State].Time_Connection_Ptr->Time_Value,
                                            Control_Variables[Machine_State].Time_Connection_Ptr->Resolution );;            
                }     
            }

            CLOSE_GATE_FLAG = FALSE;
            OPENED_WAIT = FALSE;

            Time_4_Gate1 = Controlling_Variables.Ctrl_Vars.Time_Slow + (Service_Variables.Serv_Vars.Serwis_018 / 10);
                        
            System_Timer_Setting ( &Slow_2_Timer.Timer, Controlling_Variables.Ctrl_Vars.Time_Slow, T_100msec );
            System_Timer_Setting ( &Slow_1_Timer.Timer, Time_4_Gate1, T_100msec );
            SLOW_ENABLE_FLAG_1 = FALSE;
            SLOW_ENABLE_FLAG_2 = FALSE;
            BRAKING_FLAG_1 = FALSE;
            BRAKING_FLAG_2 = FALSE;
            READY_4_CLOSING = FALSE; 
            PHOTO_PRIORITY_ENABLE = FALSE;
            F1_Current_Counter = 0;
            F2_Current_Counter = 0; 
            PRE_WORNING_FLAG = FALSE;
        }
    }
}

static void Inputs_Pre_Opening ( void )
{
        if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
        {
            switch ( Inputs.Keyboard_Memory )
            {
                case OPEN_CLOSE_GATE:
                    Machine_State = WG_CLOSED;
                break;
                
                case OPEN_CLOSE_GATE1:
                    Machine_State = WG_CLOSED;
                break;
                
                case OPEN_CLOSE_GATE2:
                    Machine_State = WG_CLOSED;
                break;
                
                case OPEN_CLOSE_GATE3:
                    Machine_State = WG_CLOSED;
                break;

                case OPEN_CLOSE_GATE4:
                    Machine_State = WG_CLOSED;
                break;
                
                case OPEN_CLOSE_GATE5:
                    Machine_State = WG_CLOSED;
                break;

                case OPEN_CLOSE_GATE6:
                    Machine_State = WG_CLOSED;
                break;
                
                case OPEN_CLOSE_GATE7:
                    Machine_State = WG_CLOSED;
                break;
                
                default:
                break;
            }
            Inputs.Keyboard_Flag = 0;
        }

        if ( Inputs.Keyboard_State == 0 )
        {
            Inputs.Keyboard_Memory = 0;
        }
    
        if ( Inputs_Level & INPUT13 )
        {
            if ( Service_Variables.Serv_Vars.In13_Fun == 3 )  //Close
            {
                Machine_State = WG_CLOSED;
            }
        }

        if ( Inputs_Level & INPUT14 )
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 3 )  //Close
            {
                Machine_State = WG_CLOSED;
            }
        }

        if ( Inputs_Level & INPUT15 )
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 3 )  //Close
            {
                Machine_State = WG_CLOSED;
            }
        }

        if ( Inputs_Level & INPUT16 )
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 3 )  //Close
            {
                Machine_State = WG_CLOSED;
            }
        }

        if ( Inputs_Level & INPUT17 )
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 3 )  //Close
            {
                Machine_State = WG_CLOSED;
            }
        }

        if ( Inputs_Level & INPUT18 )
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 3 )  //Close
            {
                Machine_State = WG_CLOSED;
            }
        }

        if ( Inputs_Level & INPUT19 )
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 3 )  //Close
            {
                Machine_State = WG_CLOSED;
            }
        }

        if ( Inputs_Level & INPUT20 )
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 3 )  //Close
            {
                Machine_State = WG_CLOSED;
            }
        } 
}

static void Inputs_Pre_Closing ( void )
{
    if ( Inputs.Keyboard_Memory != 0 && Inputs.Keyboard_Flag == 1 )
    {
        switch ( Inputs.Keyboard_Memory )
        {
            case OPEN_CLOSE_GATE:
                Machine_State = WG_OPENED;
            break;

            case OPEN_CLOSE_GATE1:
                Machine_State = WG_OPENED;
            break;
            
            case OPEN_CLOSE_GATE2:
                Machine_State = WG_OPENED;
            break;
                        
            case OPEN_CLOSE_GATE3:
                Machine_State = WG_OPENED;
            break;
                                    
            case OPEN_CLOSE_GATE4:
                Machine_State = WG_OPENED;
            break;
                                                
            case OPEN_CLOSE_GATE5:
                Machine_State = WG_OPENED;
            break;
                                                            
            case OPEN_CLOSE_GATE6:
                Machine_State = WG_OPENED;
            break;
                                                                        
            case OPEN_CLOSE_GATE7:
                Machine_State = WG_OPENED;
            break;
                        
            default:
            break;
        }
        Inputs.Keyboard_Flag = 0;
    }

    if ( Inputs.Keyboard_State == 0 )
    {
        Inputs.Keyboard_Memory = 0;
    }
    if ( Inputs_Level & INPUT12 )
    {
        if ( Service_Variables.Serv_Vars.In12_Fun == 2 )  //Open
        {
            Machine_State = WG_OPENED;
        }
    }

    if ( Inputs_Level & INPUT14 )
    {
        if ( Service_Variables.Serv_Vars.In14_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In14_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In14_Fun == 4 )
                OPEN_ON_LEVEL_14 = TRUE;
    
            Machine_State = WG_OPENED;
        }
    }
    else
    {
        OPEN_ON_LEVEL_14 = FALSE;
    }

    if ( Inputs_Level & INPUT15 )
    {
        if ( Service_Variables.Serv_Vars.In15_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In15_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In15_Fun == 4 )
                OPEN_ON_LEVEL_15 = TRUE;
    
            Machine_State = WG_OPENED;
        }
    }
    else
    {
        OPEN_ON_LEVEL_15 = FALSE;
    }

    if ( Inputs_Level & INPUT16 )
    {
        if ( Service_Variables.Serv_Vars.In16_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In16_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In16_Fun == 4 )
                OPEN_ON_LEVEL_16 = TRUE;
    
            Machine_State = WG_OPENED;
        }
    }
    else
    {
        OPEN_ON_LEVEL_16 = FALSE;
    }

    if ( Inputs_Level & INPUT17 )
    {
        if ( Service_Variables.Serv_Vars.In17_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In17_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In17_Fun == 4 )
                OPEN_ON_LEVEL_17 = TRUE;
    
            Machine_State = WG_OPENED;
        }
    }
    else
    {
        OPEN_ON_LEVEL_17 = FALSE;
    }

    if ( Inputs_Level & INPUT18 )
    {
        if ( Service_Variables.Serv_Vars.In18_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In18_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In18_Fun == 4 )
                OPEN_ON_LEVEL_18 = TRUE;
    
            Machine_State = WG_OPENED;
        }
    }
    else
    {
        OPEN_ON_LEVEL_18 = FALSE;
    }

    if ( Inputs_Level & INPUT19 )
    {
        if ( Service_Variables.Serv_Vars.In19_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In19_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In19_Fun == 4 )
                OPEN_ON_LEVEL_19 = TRUE;
    
            Machine_State = WG_OPENED;
        }
    }
    else
    {
        OPEN_ON_LEVEL_19 = FALSE;
    }

    if ( Inputs_Level & INPUT20 )
    {
        if ( Service_Variables.Serv_Vars.In20_Fun == 2 ||  //Open
             Service_Variables.Serv_Vars.In20_Fun == 4 )   //Open_Close
        {
            if ( Service_Variables.Serv_Vars.In20_Fun == 4 )
                OPEN_ON_LEVEL_20 = TRUE;
    
            Machine_State = WG_OPENED;
        }
    }
    else
    {
        OPEN_ON_LEVEL_20 = FALSE;
    }
}
/***************************************************************************
* End file control.c
*******************************************************************************/

