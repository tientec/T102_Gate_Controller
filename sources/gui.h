#ifndef _GUI_H
#define _GUI_H

/*******************************************************************************
********************************************************************************
* File Name          : gui.h
* Author             : Tomasz Nowak
* Version            : V1.00a
* Date               : 05/07/2011
* Description        : Header file for gui.c
********************************************************************************
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/

/*******************************************************************************
* Exported Preprocessor #define Constants
*******************************************************************************/
#define STRINGS_COUNT   255

#define ENABLE_STRING           0b0000111111111111
#define ENABLE_STRING_SE1       0b0000000000000100
#define ENABLE_STRING_SE2       0b0000000000001000
#define ENABLE_STRING_SE3       0b0000000000010000
#define ENABLE_STRING_SE4       0b0000000000100000
#define ENABLE_STRING_PHOTO     0b0000000001000000
#define ENABLE_STRING_STOP      0b0000000010000000
#define ENABLE_STRING_F1        0b0000000100000000
#define ENABLE_STRING_F2        0b0000001000000000
#define ENABLE_STRING_COV1      0b0000010000000000
#define ENABLE_STRING_COV2      0b0000100000000000

#define TEST_STOPPED            0b0000000000000011
#define TEST_STARTED            0b0000000000000101

#define STRING_LICENCE_LOCKED   0b0000000001110111
#define STRING_LICENCE_UNLOCKED 0b0000000000001011
#define VAR_LICENCE_UNLOCKED    0b0000000000000000
#define VAR_LICENCE_LOCKED      0b0000000000000111

#define STER_ODBLOKOWANY        0
#define STER_ZABLOKOWANY        1
#define STER_BLOKADA_CALKOWITA  2
#define STER_BLOKOWANY          3

#define NUM_OF_LANG             1

#define EEPROM_BASE_ADDRESS     ((uint32_t)0x0801FC00)
#define EEPROM_END_ADDRESS      ((uint32_t)0x08020000)

#define CONTROLLER_PROGRAMMED   0xa5

#define SERVICE_PASSWORD        3872

#define STATUS_LEARNING_WAY     0
#define STATUS_POWER_ON         1
#define STATUS_NORMAL           3
#define STATUS_WG_POWER_ON      4
#define STATUS_WG_NORMAL        5
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/  
extern volatile uint32_t Flash_Address;
extern volatile uint32_t NbrOfPage;
extern volatile FLASH_Status FLASHStatus;

//USB DEFINES
#define USB_READ_DATA           0x81
#define USB_WEITE_DATA          0x82
#define USB_UPDATE_MCU_FLASH    0x83
#define USB_STATUS_WR_OK        0x84
#define USB_STATUS_WR_NOK       0x85
#define USB_WRITE_SN            0x86
#define USB_WRITE_TIME          0x87

#define SOFTWARE_VER_OFFSET     0
#define SOFTWARE_VER_SIZE       14

#define USB_SERVICE_VARIABLES_OFFSET_1      0x0000//60 bytes
#define USB_SERVICE_VARIABLES_OFFSET_2      0x003C//60 bytes
#define USB_SERVICE_VARIABLES_OFFSET_3      0x0078//60 bytes
#define USB_CONTROLLING_VARIABLES_OFFSET    0x00B4//60 bytes
#define USB_CONTROLLER_VARIABLES_OFFSET     0x00F0//60 bytes
#define USB_COUNTERS_OFFSET                 0x012C//60 bytes
#define USB_OTHER_VARIABLES_OFFSET          0x0168//60 bytes
#define USB_END_TABLE                       0x01A4//60 bytes

#define PAGE_1                  0x00
#define PAGE_2                  0x01
#define PAGE_3                  0x02
#define PAGE_4                  0x03
#define PAGE_5                  0x04
#define PAGE_6                  0x05
#define PAGE_7                  0x06

#define TOTAL_PAGES             0x06

#define START_YEAR              2015
/*******************************************************************************
* Exported Preprocessor #define MACROS
*******************************************************************************/

/*******************************************************************************
* Exported Type Declarations
*******************************************************************************/
typedef enum {
    TEXT_VAR = 0,
    DIGITS_VAR,
} _Var_Type;

typedef enum {
    VAR_U8 = 0,
    VAR_U16,
    VAR_U32,
    VAR_S8,
    VAR_S16,
    VAR_S32,
} _Var_Size;

typedef enum {
    STANDBY_SCR = 0,
    CONTROLLER_ON,

    MENU,

    SUBMENU1,
    SUBMENU2,
    SUBMENU2a,
    SUBMENU2b,
    SUBMENU2c,
    SUBMENU3,
    FUNKCJE_DODATKOWE1,
    FUNKCJE_DODATKOWE2,
    FUNKCJE_DODATKOWE3,
    FUNKCJE_DODATKOWE4,
    DATA_I_CZAS,
    LICENCJA,
    SUBMENU4,
    UST_FABRYCZNE,
    KONTAKT,
    INFO,

    HASLO,

    BRAMA_MOTOR1,   
    PRAD1,
    LISTWY1,
    LISTWY2,
    USTAW_WEWY1,
    USTAW_WEWY2,
    USTAW_WEWY3,
    USTAW_WEWY4,
    WE_STER1,
    WE_STER2,
    WY_PRZEK1,
    WY_PRZEK2,
    CZUJNIKI_MENU,
    CZUJNIKI1,
    CZUJNIKI2,

    WYB_JEZ,
    UST_HASEL,
    UST_BLOKADY,
    ZER_LICZNIKI, 
    KAL_RTC, 

    LICZNIK_PRACY,
    PROG_TESTOWY,
    TEST_WEWY,

    UST_SERWISOWE1,
    UST_SERWISOWE2,
    UST_SERWISOWE3,
    UST_SERWISOWE4,
    
    ODCZYT_SERWISOWY1,
    ODCZYT_SERWISOWY2,
    ODCZYT_SERWISOWY3,
    
    BLOK_CALKOWITA,
    STEROWNIK_BLOKOWANY,
    ODBLOKUJ,  
    ALERT_ERROR,
} _Screen_Number;
/*******************************************************************************
* Exported Const Object Declarations
*******************************************************************************/

/*******************************************************************************
* Exported Object Declarations
*******************************************************************************/

typedef union {
    uint8_t Controlling_Tab8[64];
    uint32_t Variables_Tab[16];
    struct {
//0
        uint16_t Encoder_Open;
        uint16_t Encoder_Open_Half;
//1
        uint16_t High_Speed_Opening;
        uint16_t High_Speed_Closing;
//2
        uint16_t Start_Speed_Opening;
        uint16_t Start_Speed_Closing;
//3
        uint16_t Speed_Opening;
        uint16_t Speed_Closing;
//4
        uint16_t Learn_Speed_Opening;
        uint16_t Learn_Speed_Closing;
//5   
        uint32_t Pilot_Code_Set;
//6
        uint8_t Way_Learned;
        uint8_t F1_Current_Counter;
        uint8_t F2_Current_Counter;
        uint8_t Fast_Gate_Type;
//7
        uint16_t Gate_Opened_Time;
        uint16_t Freq1;
//8
        uint16_t Freq2;
        uint16_t SoftStart;
//9
        uint16_t SoftStop;
        uint16_t Freq_Slow;
//10
        uint16_t Time_Slow;
        uint8_t F1_Current_Limit;
        uint8_t F2_Current_Limit;
//11
        uint8_t One_Wing_Gate_Type;
        uint8_t Sensor_Type;
        uint8_t Motor_Type;
        uint8_t Photo_Opened;
//12
        uint16_t Angle1_Cl;
        uint16_t Angle1_Op;
//13
        uint16_t Angle2_Cl;
        uint16_t Angle2_Op;
//14
        uint16_t Braking_Angle;
        uint8_t Photo_Opening_Fun;
        uint8_t Photo_Closing_Fun;
        
    } Ctrl_Vars;
} _Controlling_Variables;

typedef union {
    uint8_t Service_Tab8[128];
    uint32_t Service_Tab[32];
    struct {
//0
        uint32_t Haslo_Dostepu;
//1
        uint32_t Haslo_Blokady;
//2
        uint8_t Blokada;
        uint8_t Ilosc_Prob_Dostepu;
        uint8_t Ilosc_Prob_Blokady;
        uint8_t Jezyk;
//3
        uint8_t Blokada_dzien;
        uint8_t Blokada_miesiac;
        uint16_t Blokada_rok;
//4
        uint8_t RTC_Cal_Var;       
        uint8_t Marker_Blokady;
        uint8_t Blok_Dostep_Pozostalo;
        uint8_t Blok_Prog_Pozostalo; 
//5
        uint16_t Lock_Interval;
        uint16_t Lock_Counter; 
//6
        uint8_t First_On_Marker;
        uint8_t Insp_Day;
        uint8_t Insp_Month;
        uint8_t Insp_Marker;
//7
        uint16_t Serwis_001;
        uint16_t Serwis_002;
        uint16_t Serwis_003;
        uint16_t Serwis_004;
        uint16_t Serwis_005;
        uint16_t Serwis_006;
        uint16_t Serwis_007;
        uint16_t Serwis_008;
        uint16_t Serwis_009;
        uint16_t Serwis_010;
        uint16_t Serwis_011;
        uint16_t Serwis_012;
        uint16_t Serwis_013;
        uint16_t Serwis_014;
        uint16_t Serwis_015;
        uint16_t Serwis_016;
        uint16_t Serwis_017;
        uint16_t Serwis_018;
        uint16_t Serwis_019;
        uint16_t Serwis_020;
        uint16_t Serwis_021;
        uint16_t Serwis_022;
        uint16_t Serwis_023;
        uint16_t Serwis_024;
//19  
        uint16_t Insp_Year;
        uint16_t Insp_Counter;
//20        
        uint8_t In1_Fun;        
        uint8_t In2_Fun;
        uint8_t In3_Fun;
        uint8_t In4_Fun;
//21        
        uint8_t In1_Type;        
        uint8_t In2_Type;
        uint8_t In3_Type;
        uint8_t In4_Type;
        
//22        
        uint8_t In5_Fun;
        uint8_t In5_Type;
        uint8_t In6_Fun;
        uint8_t In6_Type;
//23        
        uint8_t In7_Fun;        
        uint8_t In8_Fun;
        uint8_t In9_Fun;
        uint8_t In10_Fun;
//24
        uint8_t In7_Type;        
        uint8_t In8_Type;
        uint8_t In9_Type;
        uint8_t In10_Type; 
//25        
        uint8_t In11_Fun;        
        uint8_t In12_Fun;
        uint8_t In13_Fun;
        uint8_t In14_Fun;        
//26        
        uint8_t In15_Fun;        
        uint8_t In16_Fun;
        uint8_t In17_Fun;
        uint8_t In18_Fun;        
//27
        uint8_t In19_Fun;        
        uint8_t In20_Fun;
        uint8_t In11_Type;
        uint8_t In12_Type;        
//28
        uint8_t In13_Type;        
        uint8_t In14_Type;
        uint8_t In15_Type;
        uint8_t In16_Type;        
//29
        uint8_t In17_Type;        
        uint8_t In18_Type;
        uint8_t In19_Type;
        uint8_t In20_Type;        
//30
        uint8_t Out1_Fun;        
        uint8_t Out2_Fun;
        uint8_t Out3_Fun;
        uint8_t Out4_Fun;        
//31
        uint8_t Out5_Fun;        
        uint8_t Out6_Fun;
        

    } Serv_Vars;
} _Service_Variables;


typedef union {
    uint8_t Controller_Tab8[72];
    uint32_t Controller_Tab[18];
    struct {
//0 - 3
        uint16_t Software_Version[3];
        uint16_t Controller_Date[3]; 
    
        uint16_t Serial_Number;
        uint8_t Test_Status;
        uint8_t Status;
//4
        uint16_t AD_0;
        uint16_t AD_1;
//5
        uint16_t AD_8;
        uint16_t AD_9;
//6
        uint16_t AD_14;
        uint16_t AD_15;
//7    
        uint16_t AD_16;
        int16_t Inputs_Error;
//8    
        int16_t Internal_Temperature;
        uint16_t Machine_State_Var;
//9
        uint16_t Test_Counter;
        uint16_t Lock_Counter;
//10    
        volatile uint16_t MSens1_Pulse_High;
        volatile uint16_t MSens1_Pulse_Low;
//11        
        volatile uint16_t MSens2_Pulse_High;
        volatile uint16_t MSens2_Pulse_Low;
//12
        uint16_t MSens1_Angle;
        uint16_t MSens2_Angle;        
//13
        uint16_t Frequency1;
        uint16_t Frequency2;
//14
        uint16_t F1_Current;
        uint16_t F2_Current;
//14
        uint16_t Deg_Angle1_Cl;
        uint16_t Deg_Angle1_Op;
//15
        uint16_t Deg_Angle2_Cl;
        uint16_t Deg_Angle2_Op;
//16
        uint16_t Deg_MSens1_Angle;
        uint16_t Deg_MSens2_Angle;        
//17
        uint16_t Motor_Encoder_Counter;
        uint8_t Controller_Status;


    } Controller_Vars;
} _Controller_Variables;

typedef union {
    uint8_t Counters_Tab8[4];
    uint16_t Counters_Tab[2];
    struct {
        uint32_t Service_Counter;
    } Counters_Vars;
} _Counters_Variables;

typedef union {
    uint8_t Other_Variables_Tab8[60];
    uint16_t Other_Variables_Tab16[30];
    uint32_t Other_Variables_Tab32[15];
} _Other_Variables;

typedef union {
    uint8_t  Usb_Byte_Tab[512];
    uint16_t Usb_Word_Tab[256];
    uint32_t Usb_Long_Tab[128];
} _Usb_buffer;

extern _Screen_Number Screen_Number;

extern _Keyboard Keyboard;
extern _Keyboard Inputs;

extern _Controlling_Variables Controlling_Variables_Set;
extern _Service_Variables Service_Variables_Set;
extern _Counters_Variables Counters_Variables_Set;
extern _Controller_Variables Controller_Variables_Set;
extern _Other_Variables Other_Variables;

extern _Controlling_Variables Controlling_Variables;
extern _Service_Variables Service_Variables;
extern _Counters_Variables Counters_Variables;
extern _Controller_Variables Controller_Variables;

extern _Usb_buffer Usb_Tx_Buf_Tab;
extern _Usb_buffer Usb_Rx_Buf_Tab;

extern bool Reload_Screen;
extern bool Enable_Lcd_Write;
extern bool Lcd_Write_Strobe;
extern uint8_t Lcd_Write_Ptr;

extern uint16_t Lock_Counter;

extern uint32_t Div_Temp;

extern uint16_t Inputs_Error_Mask;

extern uint8_t Edit_Parameter_Counter;
/*******************************************************************************
* Exported Function Prototypes
*******************************************************************************/
void Menu_Keyboard ( void );
void Gui_Init ( void );
void Gui ( void );
void Bin2String ( int32_t Source_Count, uint8_t * Result, uint8_t Digits_Count, uint8_t Resolution, uint8_t Zero_Blank );

void Write_Settings ( void );
void Read_Settings ( void );
void Update_Counters ( void );
void Update_Lock_Counter ( uint16_t Update_Counter );
void Lock_Init ( void );
void Lock_Handling ( void );
/*******************************************************************************
 * Exported Inline Function Definitions and #define Function-Like Macros
*******************************************************************************/

/*******************************************************************************
* End fo file gui.h
*******************************************************************************/
#endif



