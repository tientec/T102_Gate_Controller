
/*******************************************************************************
********************************************************************************
* File Name          : gui.c
* Author             : Tomasz Nowak
* Version            : V1.00A
* Date               : 05/07/2011
* Description        : General user interface
********************************************************************************
*******************************************************************************/


/*******************************************************************************
* Header Files
*******************************************************************************/
#include "includes.h"

#include "Languages/Texts.h"

/*******************************************************************************
* Local Preprocessor #define Constants
*******************************************************************************/

/*******************************************************************************
* Local Preprocessor #define MACRO
*******************************************************************************/


/*******************************************************************************
* Local Type Declarations
*******************************************************************************/
typedef enum {
    Header = 0,
    Name1,
    Name2,
    Version,
    Pn,
    Wt,
    Sr,
    Cz,
    Pt,
    So,
    Nd,
    Menu_List,
    Menu_0,
    Menu_1,
    Menu_2,
    Menu_3,
    Menu_4,
    Menu_5,
    Menu_6,
    Menu_7,
    Menu_8,
    Menu_9,
    Menu_10,
    Menu_11,
    Submenu_00,
    Submenu_01,
    Submenu_02,
    Submenu_03,
    Submenu_04,
    Submenu_05,
    Submenu_06,
    
    Submenu_10,
    Submenu_11,
    Submenu_12,
    Submenu_13,
    Submenu_14,
    
    Submenu_20,
    Submenu_21,
    Submenu_22,
    Submenu_23,
    Submenu_24,
    
    Haslo_menu,
    Haslo_blokady,
    Sterownik,
    Zablokowany,
    Blokada_calkowita,
    Data_blokady,
    Ilosc_prob,
    Lic_Programu,
    Bezterminowo,
    Do_dnia,
    Odblokuj,   
    Haslo,
    Proby,
    Dostepu,
    Blokady,
    Blok,
    Blok_data,
    
    Alert_Text,
    Error_Text,
    
    English,    
    Polski,
    Tak,
    Nie,
    Wl,
    Wyl,
    Min,
    Max,
    St_R,
    St_L,
    Kropki,
    Kropki_1,
    Kropka,
    Dwukropek,
    Test_Start_Text,
    Test_Stop_Text,
    OK_Tak,
    ESC_Nie,
    Start_Text,
    Stop_Text,   
    _1z,
    _2z,
    _3z,
    _4z,
    _5z,
    _6z,
    z1,
    z2,
    z3,
    z4,
    z5,
    z6,
    Par1,
    Par2,
    Par3,
    Par4,
    Par5,
    Par6,
    Par7,
    Par8,
    Par9,
    Par10,
    Par11,
    Par12,
    
    Bl,
    
    Kontakt_Text1,
    Kontakt_Text2,
    Kontakt_Text3,
    Kontakt_Text4,
 
    Speed_1S,
    Speed_2S,
    Uchylna_1S,
    Uchylna_2S,
    Przesowna,
    Przes_Master,
    Przes_Slave,
    Falownik,
    DC24V,
    AC230V,

    Limit_Switches,
    Magnetic_Sensor,
    Encoder_Sensor,

    In1,
    In2,
    In3,
    In4,
    In5,
    In6,
    In7,
    In8,
    In9,
    In10,
    In11,
    In12,
    In13,
    In14,
    In15,
    In16,
    In17,
    In18,
    In19,
    In20,
    
    NO,         
    NC,
    Impulsowe,
    Otw,
    Zam,
    Otw_Zam,
    Otw_Zam_Imp,
    LB_Otw,
    LB_Zam,
    WK1_CLO,
    WK1_OP,
    WK2_CLO,
    WK2_OP,
    Magn_Sens1,
    Magn_Sens2,
    Enk_Sens1,
    Enk_Sens2,
     
    Out1,
    Out2,
    Out3,
    Out4,
    Out5,
    Out6,
    Out7,
    Out8,
    Out9,
    Out10,

    Lampa,
    Ziel,
    Czerw,
    Puls,
    S_Zewn,
    S_Zwr_Otw,
    S_Zwr_Zam,
    E_Magnes,
    Em_Stop,
    Safety_Edges,
    L_20k,
    L_41k,
    L_82k,
    L_164k,

    Menu_Sens_Magnetic,
    Menu_Sens_Encoder,

    Test_M,
    Test_OC,
    Test_P,
    Test_W,
    Test_In,

    Soft_Version,
    Manufactured,
    S_N,

    Przeglad,
    Przeglad_licznik,
    Godz,    
    Czas_Ham,
    Predk_Ham,
    Kat_Ham,
    
    Status,
    Way_Detection,
    Gate_Closed,
    Gate_Closed_Half,
    Gate_Opening,
    Gate_Opened,
    Gate_Opened_Half,
    Gate_Closing,
    Gate_Stopped,
    Gate_Alert,
    Opening_Speed_HS,
    Opening_Speed_Min,
    Opening_Speed_Max,
    Closing_Speed_HS,
    Closing_Speed_Min,
    Closing_Speed_Max,
    Opening_Speed_Learn,
    Closing_Speed_Learn,
    LZ1,
    LZ2,
    LZ3,
    LZ4,
    Foto,
    Main_Stop,
    Cov1,
    Cov2,
    Encoder1,
    Enkoder2,
    Inv1,
    Inv2,
    Open_Time,
    Speed1,
    Speed2,
    Soft_start,
    Soft_stop,
    
    Pre_Worning,
    Photo_sett,
    Photo_Opened,
    Ph_Closing,
    Ph_Co_Again,
    Photo_Opening,
    Photo_Closing,
    Ph_Stop_Rev,
    Ph_Stop_Wait_Rev,
    Ph_Stop_Wait_Go,

    Typ_bramy,
    Typ_silnika,
    Typ_czujnika,
    
    Ust_pradu,
    Pom_ust,
    Ampery1,
    Ampery2,
    Sensors_Text1,
    Sensors_Text2,
    Sensors_Text3,
    Sensors_Text4,
    
} _String_Number;

typedef enum {
    ENGLISH = 0,
    POLISH,
    DEUTSCH,

} _Language_Num;

typedef struct _Languages_ {
    const uint8_t ** Languages_Tab[8];
} _Languages;


typedef struct _Strings_ {
    uint8_t String_Index;
    uint8_t String_X_Pos;
    uint8_t String_Y_Pos;
    _String_Number String_Num;
    const struct _Languages_ * Languages_Ptr;
    const struct _Strings_ * Next_String;
} _Strings;

typedef struct _Menu_ {
    uint8_t Menu_X_Pos;
    uint8_t Menu_Y_Pos;
    uint8_t Lines_On_Screen;
    uint8_t Total_Lines;
    const struct _Languages_ * Languages_Ptr;
    _String_Number Menu_String_Num[16];
} _Menu;

typedef struct {
    uint8_t First_On_Screen;
    uint8_t Active_String;
    uint8_t Active_On_Screen;
} _Menu_Keys_Ptrs;

typedef struct _Var_Param_ {
    _Var_Type Variable_Type;
    _Var_Size Variable_Size;
    uint8_t Variable_Digits_Count;
    uint8_t Variable_Resolution;
    _String_Number Variable_String_Num[16];
    bool Variable_Hide_Zeros;
    uint8_t Variable_Accuracy;
    const struct _Var_Ranges_ * Ranges;
} _Var_Param;

typedef struct _Variables_ {
    uint8_t Variable_Index;
    uint8_t Variable_X_Pos;
    uint8_t Variable_Y_Pos;
    void * Var_Ptr;
    bool Edit_Var;
    const struct _Var_Param_ * Var_Param_Ptr;
    const struct _Languages_ * Languages_Ptr;
    const struct _Variables_ * Next_Variable;
} _Variables;

typedef struct _Var_Ranges_ {
    int32_t Var_min;
    int32_t Var_max;
} _Var_Ranges;

typedef struct {
    const _Strings * String_Ptr;
    const _Menu * Menu_Ptr;
    const _Variables * Variable_Ptr;
    uint32_t * String_Mask;
    uint32_t * Menu_Mask;
    uint32_t * Variable_Mask;
} _Screen_Ptrs_Masks;

typedef struct {
    void (*Keybord_Ptr)(void);
    const _Screen_Ptrs_Masks * Screen_Objects;
    bool Auto_Reload_Screen;
    uint16_t Auto_Reload_Period;
} _Screen_Lcd;

    uint8_t k;
    uint8_t Count_Add;
    uint32_t Div_Temp;

    const int32_t Add_Tab[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 };
/*******************************************************************************
* Exported Const Object Definitions
*******************************************************************************/


/*******************************************************************************
* Local Object Definitions
*******************************************************************************/
bool Reload_Screen;
bool Enable_Lcd_Write = FALSE;
bool Lcd_Write_Strobe = FALSE;
uint8_t Lcd_Write_Ptr;

static uint32_t Password_Set;
static uint32_t Lock_Interval_Tmp;
static uint32_t Lock_Date_Now_Tmp;
static uint32_t Lock_Date_Set_Tmp;

uint32_t String_Lic_Mask;
uint32_t Var_Lic_Mask;
uint32_t Enable_String_Mask;
uint32_t Test_String_Mask;
uint32_t Manual_Test_Mask;

_Language_Num Language_Num;
_Screen_Number Screen_Number;
_Screen_Number Screen_After_Password;
_Screen_Number Screen_Before_Password;
_Menu_Keys_Ptrs Menu_Keys = { 0 ,0 ,0 };
_Menu_Keys_Ptrs Menu_Backup_Keys;
_Menu_Keys_Ptrs Menu_Backup_Keys_Set;
_Menu_Keys_Ptrs Menu_Backup_Keys_Sensors;

_Controlling_Variables Controlling_Variables;
_Service_Variables Service_Variables;
_Counters_Variables Counters_Variables;
_Controller_Variables Controller_Variables;
_Other_Variables Other_Variables;

_Controlling_Variables Controlling_Variables_Set;
_Service_Variables Service_Variables_Set;
_Counters_Variables Counters_Variables_Set;
_Controller_Variables Controller_Variables_Set;

_Usb_buffer Usb_Tx_Buf_Tab;
_Usb_buffer Usb_Rx_Buf_Tab;

const _Languages Languages = { { English_Tab, Polish_Tab } };

const _Variables * Variable_Editing_Ptr;

uint16_t Lock_Counter = 0;

uint16_t Inputs_Error_Mask;

volatile uint32_t Flash_Address;
volatile uint32_t NbrOfPage = 0;
volatile FLASH_Status FLASHStatus;

static bool TEST_ENABLE = FALSE;

static bool SCREEN_PULSE = 0;

uint8_t Edit_Parameter_Counter = 0;

const uint32_t Settings_Default[32] = {
12345,/*Haslo dostepu*/
12345,/*Haslo blokady*/
0x00050A01, /*Blokada,Il.P.Dost,Il.P.Blo,Jezyk*/
0x00000000,/*,Blokada_dzien,Blokada_miesiac,Blokada_rok-16*/
0x050A007F,/*RTC_Cal_Var,Marker_Blokady,Blok_Dostep_Pozostalo,Blok_Prog_Pozostalo*/
0x00000000,/*Lock_Interval-16,Lock_Counter-16*/
0x000101A5,/*First_On_Marker, Inspection month/day, Insp_Marker*/
0x00050064,/*Servis1, Serwis2*/
0x0014000A,/*Servis3, Serwis4*/
0x0ffe01f4,/*Servis5, Serwis6*/
0x003200C8,/*Servis7, Serwis8*/
0x0064000A,/*Servis9, Serwis10*/
0x019000C8,/*Servis11, Serwis12*/
0x0003000A,/*Servis13, Serwis14*/
0x012c000A,/*Servis15, Serwis16*/
0x0005000A,/*Servis17, Serwis18*/
0x0002000A,/*Servis19, Serwis20*/
0x00030028,/*Servis21, Serwis22*/
0x000505DC,/*Servis23, Serwis24*/
0x000007e0,/*Insp.Year, Insp_Counter*/

0x01010101,/* In1_Fun,In2_Fun, In3_Fun, In4_fun,*/
0x00000000,/* In1_Type,In2_Type, In3_Type, In4_Type,*/
0x01010102,/* In5_Fun,In5_Type, In6_Fun, In6_Type,*/
0x02020000,/* In7_Fun,In8_Fun, In9_Fun, In10_fun,*/
0x02020202,/* In7_Type, In8_Type, In9_Type, In10_Type*/
0x00030201,/* In11_Fun,In12_Fun, In13_Fun, In14_fun,*/
0x00000000,/* In15_Fun,In16_Fun, In17_Fun, In18_fun,*/
0x00000000,/* In19_Fun,In20_Fun, In11_Type, In12_Type,*/
0x00000000,/* In13_Type,In14_Type, In15_Type, In16_Type,*/
0x00000000,/* In17_Type,In18_Type, In19_Type, In20_Type,*/
0x00000001,/* Out1_Type,Out2_Type, Out3_Type, Out4_Type,*/
0x00000800,/* Out5_Type,Out6_Type, */
};

                                                                                                               
const uint32_t Controlling_Default[16] = {
0x01F403E8,/*Encoder_Open, Encoder_Opened_Half*/
0x002D002D,/*High_Speed_Opening, High_Speed_Closing*/
0x00140014,/*Start_Speed_Opening, Start_Speed_Closing*/
0x002D002D,/*Speed_Opening, Speed_Closing*/
0x00140014,/*Learn_Speed_Opening, Learn_Speed_Closing*/
0x00033333,/*Pilot_Code_Set*/
0x00050500,/*Way_Learned, F1_Current_Counter, F2_Current_Counter, Fast_Gate_Type */
0x2710001e,/*Opened_time, Freq1  */
0x000F2710,/*Freq2, Softstart, */
0x0bb80001,/*Softstop, Freq_Slow*/
0x19190027,/*Time_Slow, F1_Current_Limit, F2_Current_Limit,  */
0x02000100,/*One_Wing_Gate_Type, Sensor_Type, Motor_Type, Photo_Opened  */
0x02df0129,/*Angle1_Cl, Angle1_OP*/
0x013302f3,/*Angle2_Cl, Angle2_Op*/
0x010002ee,/*braking_angle, Photo_Opening_Fun, Photo_Opening_Fun */
0x00000000,/*  */
};

/*******************************************************************************
* Handling functions for variables' editing
*******************************************************************************/
static void Keyboard_Edit_Variable ( void );
static void First_Editable_Variable ( void );
static uint8_t Next_Editable_Variable ( void );
/*******************************************************************************
* Keyboard functions declarations
*******************************************************************************/
static void Keyboard_Standby ( void );
static void Keyboard_Enable ( void );
static void Keyboard_Menu ( void );
static void Keyboard_Haslo ( void );

static void Keyboard_Submenu1 ( void );
static void Keyboard_Submenu2 ( void );
static void Keyboard_Funkcje1 ( void );
static void Keyboard_Data ( void );
static void Keyboard_Licencja ( void );
static void Keyboard_Submenu3 ( void );
static void Keyboard_Submenu4 ( void );
static void Keyboard_Fabryczne ( void );
static void Keyboard_Kontakt ( void );
static void Keyboard_Info ( void );

static void Keyboard_Brama_Motor ( void );
static void Keyboard_Prad( void );
static void Keyboard_Listwy ( void );
static void Keyboard_Ustaw_Wejsc ( void );
static void Keyboard_Ustaw_Wejsc_Ster ( void );
static void Keyboard_Ustaw_Wyjsc_Przek ( void );
static void Keyboard_Czujniki_Menu ( void );
static void Keyboard_Czujniki1 ( void );
static void Keyboard_Czujniki2 ( void );

static void Keyboard_Jezyk ( void );
static void Keyboard_Zmiana_Hasel ( void );
static void Keyboard_Ust_Blokady ( void );
static void Keyboard_RTC ( void );
static void Keyboard_Zer_Licznikow ( void );

static void Keyboard_Licznik_Pracy ( void );
static void Keyboard_Prog_Testowy ( void );
static void Keyboard_Test_WeWy ( void );
static void Keyboard_Ust_Serwisowe ( void );
static void Keyboard_Odczyt_Serwisowy ( void );

static void Keyboard_Ster_Blokowany ( void );
static void Keyboard_Odblokuj ( void );
static void Keyboard_Alert_Error ( void );

void Write_Settings ( void );
void Read_Settings ( void );

const _Var_Ranges Ranges_Sec = { 0, 59 };
const _Var_Ranges Ranges_Minute = { 0, 59 };
const _Var_Ranges Ranges_Hour= { 0, 23 };
const _Var_Ranges Ranges_Day = { 1, 31 };
const _Var_Ranges Ranges_Month = { 1, 12 };
const _Var_Ranges Ranges_Year = { 2013, 2099 };
const _Var_Ranges Ranges_DOW = { 0, 6 };
const _Var_Ranges Ranges_Pass = { 0, 99999 };
const _Var_Ranges Ranges_Prob = { 3, 20 };
const _Var_Ranges Ranges_Lang = { 0, 1 };
const _Var_Ranges Ranges_PWM = { 0, 1000 };
const _Var_Ranges Ranges_Tak_Nie = { 0, 1 };
const _Var_Ranges Ranges_counters = { 0, 50000000 };
const _Var_Ranges Ranges_RTC = { 0, 127 };
const _Var_Ranges Ranges_Serwis = { 0, 65000 };
const _Var_Ranges Ranges_Temperature = { 0, 120 };
const _Var_Ranges Ranges_2_digits = { 0, 99 };
const _Var_Ranges Ranges_4_digits = { 0, 9999 };
const _Var_Ranges Ranges_TestWeWy = { 0, 4 };
const _Var_Ranges Ranges_Vent_Min = { 15, 24 };
const _Var_Ranges Ranges_Vent_Max = { 25, 40 };
const _Var_Ranges Ranges_Heat_Min = { 0, 10 };
const _Var_Ranges Ranges_Heat_Max = { 12, 25 };

const _Var_Ranges Ranges_Status = { 0, 10 };
const _Var_Ranges Ranges_0_50 = { 0, 50 };

const _Var_Ranges Ranges_Adres = { 1, 30 };
const _Var_Ranges Ranges_MS = { 0, 4 };
const _Var_Ranges Ranges_5_Digits = { 0, 65535 };
const _Var_Ranges Ranges_6_Digits = { 0, 999999 };
const _Var_Ranges Ranges_10_Digits = { 0, 1000000000 };

const _Var_Ranges Ranges_LP_Marker = { 0, 2 };
const _Var_Ranges Ranges_LP_Counter = { 0, 9999 };
const _Var_Ranges Ranges_Delay = { 2, 60 };
const _Var_Ranges Ranges_0_1 = {0, 1 };
const _Var_Ranges Ranges_0_2 = {0, 2 };
const _Var_Ranges Ranges_0_3 = {0, 3 };
const _Var_Ranges Ranges_0_4 = {0, 4 };
const _Var_Ranges Ranges_0_5 = {0, 5 };
const _Var_Ranges Ranges_0_6 = {0, 6 };
const _Var_Ranges Ranges_0_7 = {0, 7 };
const _Var_Ranges Ranges_0_8 = {0, 8 };
const _Var_Ranges Ranges_0_9 = {0, 9 };
const _Var_Ranges Ranges_0_10 ={0, 10 };

const _Var_Ranges Ranges_Opened_Time = {0, 50000 };

const _Var_Ranges Ranges_Freq = {1000, 12000 };
const _Var_Ranges Ranges_Soft = {1, 999 };
const _Var_Ranges Ranges_Current = {1, 50 };
const _Var_Ranges Ranges_Current_Counter = {1, 50 };
const _Var_Ranges Ranges_Braking_Angle = { 100, 1200 };

const _Var_Ranges Ranges_Unlock_Brake = { 2, 99 };

const _Var_Param Clock_Sec = { DIGITS_VAR, VAR_U8, 2, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_Sec };
const _Var_Param Clock_Minute = { DIGITS_VAR, VAR_U8, 2, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_Minute };
const _Var_Param Clock_Hour = { DIGITS_VAR, VAR_U8, 2, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_Hour };
const _Var_Param Clock_Day = { DIGITS_VAR, VAR_U8, 2, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_Day };
const _Var_Param Clock_Month = { DIGITS_VAR, VAR_U8, 2, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_Month };
const _Var_Param Clock_Year = { DIGITS_VAR, VAR_U16, 4, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_Year };
const _Var_Param Clock_DOW =   { TEXT_VAR, VAR_U8, 1, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_DOW };
const _Var_Param Passwd = { DIGITS_VAR, VAR_U32, 5, 0, { Pn }, FALSE, 1, &Ranges_Pass };
const _Var_Param Lang_Param =   { TEXT_VAR, VAR_U8, 1, 0, { Polski, English }, FALSE, 1, &Ranges_Lang };
const _Var_Param TN_Param =   { TEXT_VAR, VAR_U8, 1, 0, { Tak, Nie }, FALSE, 1, &Ranges_Tak_Nie };
const _Var_Param PWM_Param = { DIGITS_VAR, VAR_U16, 4, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_PWM };
const _Var_Param Counters = { DIGITS_VAR, VAR_U32, 7, 0, { Pn }, TRUE, 1, &Ranges_counters };
const _Var_Param Param_Prob = { DIGITS_VAR, VAR_U8, 2, 0, { Pn }, FALSE, 1, &Ranges_Prob };
const _Var_Param Param_RTC = { DIGITS_VAR, VAR_U8, 3, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_RTC };
const _Var_Param Param_Serwis = { DIGITS_VAR, VAR_U16, 5, 0, { Tak, Nie }, FALSE, 1, &Ranges_Serwis };
const _Var_Param Param_Temperature = { DIGITS_VAR, VAR_U8, 2, 0, { Pn }, FALSE, 1, &Ranges_Temperature };
const _Var_Param Param_2_Digits = { DIGITS_VAR, VAR_U8, 2, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd } , TRUE, 1, &Ranges_2_digits };
const _Var_Param Param_3_Digits = { DIGITS_VAR, VAR_U8, 3, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_PWM };
const _Var_Param Param_4_Digits = { DIGITS_VAR, VAR_U16, 4, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_PWM };
const _Var_Param Param_5_Digits = { DIGITS_VAR, VAR_U16, 5, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_5_Digits };
const _Var_Param Param_6_Digits = { DIGITS_VAR, VAR_U32, 6, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_6_Digits };
const _Var_Param Param_10_Digits = { DIGITS_VAR, VAR_U32, 10, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_10_Digits };

const _Var_Param Param_2_Dot_Digits = { DIGITS_VAR, VAR_U16, 2, 1, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_Unlock_Brake };
const _Var_Param Param_4_Dot_Digits = { DIGITS_VAR, VAR_U16, 4, 1, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_PWM };

const _Var_Param Param_Vent_Min = { DIGITS_VAR, VAR_U16, 2, 0, { Tak, Nie }, TRUE, 1, &Ranges_Vent_Min };
const _Var_Param Param_Vent_Max = { DIGITS_VAR, VAR_U16, 2, 0, { Tak, Nie }, TRUE, 1, &Ranges_Vent_Max };
const _Var_Param Param_Heat_Min = { DIGITS_VAR, VAR_U16, 2, 0, { Tak, Nie }, TRUE, 1, &Ranges_Heat_Min };
const _Var_Param Param_Heat_Max = { DIGITS_VAR, VAR_U16, 2, 0, { Tak, Nie }, TRUE, 1, &Ranges_Heat_Max };

const _Var_Param Param_Inputs1 =   { TEXT_VAR, VAR_U8, 1, 0, { NO, NC }, FALSE, 1, &Ranges_0_1 };
const _Var_Param Param_Inputs2 =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, Otw_Zam, Otw, Zam, Otw_Zam_Imp }, FALSE, 1, &Ranges_0_4 };
const _Var_Param Param_Inputs3 =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, LB_Otw, LB_Zam }, FALSE, 1, &Ranges_0_2 };
const _Var_Param Param_Inputs4 =   { TEXT_VAR, VAR_U8, 1, 0, { L_20k, L_41k, L_82k, L_164k }, FALSE, 1, &Ranges_0_3 };
const _Var_Param Param_Inputs5 =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, Main_Stop, Foto }, FALSE, 1, &Ranges_0_2 };

const _Var_Param Param_In_1 =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, WK1_CLO, Magn_Sens1, Enk_Sens1 }, FALSE, 1, &Ranges_0_1 };
const _Var_Param Param_In_2 =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, WK1_OP, Magn_Sens2, Enk_Sens2 }, FALSE, 1, &Ranges_0_1 };
const _Var_Param Param_In_3 =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, WK2_CLO }, FALSE, 1, &Ranges_0_1 };
const _Var_Param Param_In_4 =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, WK2_OP}, FALSE, 1, &Ranges_0_1 };

const _Var_Param Param_Outputs1 =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, Lampa, Ziel, Czerw, Puls, S_Zewn, S_Zwr_Otw, S_Zwr_Zam, E_Magnes, Em_Stop, Safety_Edges }, FALSE, 1, &Ranges_0_10 };

const _Var_Param Param_Gate_Type =   { TEXT_VAR, VAR_U8, 1, 0, { Speed_2S,Speed_1S, Przesowna, Uchylna_2S, Uchylna_1S, Przes_Master, Przes_Slave }, FALSE, 1, &Ranges_0_2 };
const _Var_Param Param_Motor_Type =   { TEXT_VAR, VAR_U8, 1, 0, { Falownik, DC24V, AC230V }, FALSE, 1, &Ranges_0_1 };
const _Var_Param Param_Sensor_Type =  { TEXT_VAR, VAR_U8, 1, 0, { Limit_Switches, Magnetic_Sensor, Encoder_Sensor }, FALSE, 1, &Ranges_0_1 };

const _Var_Param Param_Braking_Angle = { DIGITS_VAR, VAR_U16, 4, 1, { Tak, Nie }, TRUE, 1, &Ranges_Braking_Angle };

const _Var_Param TestWeWy_Param = { TEXT_VAR, VAR_U8, 1, 0, { Test_M, Test_OC, Test_P, Test_W, Test_In }, FALSE, 1, &Ranges_TestWeWy };   
const _Var_Param Param_Serial =   { DIGITS_VAR, VAR_U16, 2, 0, { Tak, Nie }, FALSE, 1, &Ranges_Serwis };

/* Controller parameters*/
const _Var_Param Param_Status =   { TEXT_VAR, VAR_U8, 1, 0, { Way_Detection, Gate_Closed, Gate_Closed_Half, Gate_Opening, Gate_Opened, Gate_Opened_Half, Gate_Closing, Gate_Stopped, Gate_Alert }, FALSE, 1, &Ranges_Status };
const _Var_Param Param_0_50 = { DIGITS_VAR, VAR_U16, 2, 0, { Tak, Nie }, TRUE, 1, &Ranges_0_50 };

//const _Var_Param Param_Adres = { DIGITS_VAR, VAR_U8, 2, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, FALSE, 1, &Ranges_Adres };
const _Var_Param Param_Delay = { DIGITS_VAR, VAR_U16, 2, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_Delay };

const _Var_Param Param_LP_Counter = { DIGITS_VAR, VAR_U16, 4, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_LP_Counter };
const _Var_Param Param_LP_Marker = { TEXT_VAR, VAR_U8, 1, 0, { Nie, Przeglad_licznik, Blok_data }, FALSE, 1, &Ranges_LP_Marker };

const _Var_Param Param_Opened_Time = { DIGITS_VAR, VAR_U16, 5, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_Opened_Time };
const _Var_Param Param_Freq = { DIGITS_VAR, VAR_U16, 5, 2, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_Freq };
const _Var_Param Param_SoftStartStop = { DIGITS_VAR, VAR_U16, 3, 1, { Pn, Wt, Sr, Cz, Pt, So, Nd }, TRUE, 1, &Ranges_Soft };
const _Var_Param Param_Photo_Opened =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, Ph_Closing, Ph_Co_Again }, FALSE, 1, &Ranges_0_2 };

const _Var_Param Param_Photo_Opening_Closing =   { TEXT_VAR, VAR_U8, 1, 0, { Wyl, Ph_Stop_Rev, Ph_Stop_Wait_Rev, Ph_Stop_Wait_Go }, FALSE, 1, &Ranges_0_3 };

const _Var_Param Param_Current = { DIGITS_VAR, VAR_U8, 2, 1, { Pn, Wt, Sr, Cz, Pt, So, Nd } , TRUE, 1, &Ranges_Current };
const _Var_Param Param_Current_Counter = { DIGITS_VAR, VAR_U8, 2, 0, { Pn, Wt, Sr, Cz, Pt, So, Nd } , TRUE, 1, &Ranges_Current_Counter };

/*******************************************************************************
* StandBy screen objects definition - SCREEN 0
*******************************************************************************/
const _Variables Var_Standby7 = { 6, 9, 2, &Crc_check, FALSE, &Param_5_Digits, &Languages, NULL };
const _Variables Var_Standby6 = { 5, 9, 1, &Crc_received, FALSE, &Param_5_Digits, &Languages, &Var_Standby7 };
const _Variables Var_Standby5 = { 4, 0, 2, &F2_Current_Counter, FALSE, &Param_4_Digits, &Languages, &Var_Standby6 };
const _Variables Var_Standby4 = { 3, 0, 1, &F1_Current_Counter, FALSE, &Param_4_Digits, &Languages, &Var_Standby5 };

const _Variables Var_Standby3 = { 2, 15, 3, &Controller_Variables.Controller_Vars.Software_Version[2], FALSE, &Param_Serial, &Languages, NULL/*&Var_Standby4*/ };
const _Variables Var_Standby2 = { 1, 12,  3, &Controller_Variables.Controller_Vars.Software_Version[1], FALSE, &Param_Serial, &Languages, &Var_Standby3 };
const _Variables Var_Standby1 = { 0, 9,  3, &Controller_Variables.Controller_Vars.Software_Version[0], FALSE, &Param_Serial, &Languages, &Var_Standby2 };

const _Strings String_Standby4 = { 2, 0, 3, Version, &Languages, NULL };
const _Strings String_Standby3 = { 2, 0, 2, Name2, &Languages, &String_Standby4 };
const _Strings String_Standby2 = { 1, 0, 1, Name1, &Languages, &String_Standby3 };
const _Strings String_Standby1 = { 0, 0, 0, Header, &Languages, &String_Standby2 };

const _Screen_Ptrs_Masks Screen_Standby = { &String_Standby1, NULL, &Var_Standby1, NULL, NULL, NULL };
/*******************************************************************************
* Enable screen objects definition - SCREEN 1
*******************************************************************************/
const _Variables Var_Enable7 = { 6, 8,  1, &Controller_Variables.Controller_Vars.Status, FALSE, &Param_Status, &Languages, NULL};//&Var_Enable8 };
const _Variables Var_Enable6 = { 5, 18, 0, &Time.Time_Vars.Minute, FALSE, &Clock_Minute, &Languages, &Var_Enable7 };
const _Variables Var_Enable5 = { 4, 15, 0, &Time.Time_Vars.Hour, FALSE, &Clock_Hour, &Languages, &Var_Enable6 };
const _Variables Var_Enable4 = { 3, 10, 0, &Date.Date_Vars.Year, FALSE, &Clock_Year, &Languages, &Var_Enable5 };
const _Variables Var_Enable3 = { 2, 7,  0, &Date.Date_Vars.Month, FALSE, &Clock_Month, &Languages,&Var_Enable4 };
const _Variables Var_Enable2 = { 1, 4,  0, &Date.Date_Vars.Day, FALSE, &Clock_Day, &Languages, &Var_Enable3 };
const _Variables Var_Enable1 = { 0, 0,  0, &Date.Date_Vars.Day_Of_Week, FALSE, &Clock_DOW, &Languages, &Var_Enable2 };


const _Strings String_Enable12 = {11, 16, 3, Cov2, &Languages, NULL };//&String_Enable5 };
const _Strings String_Enable11 = {10, 16, 2, Cov1, &Languages, &String_Enable12 };
const _Strings String_Enable10 = {9, 13, 3, Inv2, &Languages, &String_Enable11 };
const _Strings String_Enable9 = {8, 13, 2, Inv1, &Languages, &String_Enable10 };
const _Strings String_Enable8 = {7, 8, 3, Main_Stop, &Languages, &String_Enable9 };
const _Strings String_Enable7 = {6, 8, 2, Foto, &Languages, &String_Enable8 };
const _Strings String_Enable6 = {5, 4, 3, LZ4, &Languages, &String_Enable7 };
const _Strings String_Enable5 = {4, 0, 3, LZ3, &Languages, &String_Enable6 };
const _Strings String_Enable4 = {3, 4, 2, LZ2, &Languages, &String_Enable5 };
const _Strings String_Enable3 = {2, 0, 2, LZ1, &Languages, &String_Enable4 };
const _Strings String_Enable2 = {1, 0, 1, Status, &Languages, &String_Enable3 };
const _Strings String_Enable1 = {0, 6, 0, Kropki, &Languages, &String_Enable2 };

const _Screen_Ptrs_Masks Screen_Enable = { &String_Enable1, NULL, &Var_Enable1, &Enable_String_Mask, NULL, NULL };

/*******************************************************************************
* MENU screen objects definition - SCREEN 2
*******************************************************************************/
const _Menu Menu_Menu1 = { 1, 1, 3, 12, &Languages, { Menu_0, Menu_1, Menu_2, Menu_3, Menu_4, Menu_5, Menu_6, Menu_7, Menu_8, Menu_9, Menu_10, Menu_11 } };

const _Strings String_Menu1 = { 0, 0, 0, Menu_List, &Languages, NULL };

const _Screen_Ptrs_Masks Screen_Menu1 = { &String_Menu1, &Menu_Menu1, NULL, NULL, NULL, NULL };

/*******************************************************************************
* Parameters screen objects definition - SCREEN 3
*******************************************************************************/
const _Menu Menu_Submenu1 = { 1, 1, 3, 7, &Languages, { Submenu_00, Submenu_01, Submenu_02, Submenu_03, Submenu_04, Submenu_05, Submenu_06 } };

const _Strings String_Submenu1 = { 0, 0, 0, Menu_0, &Languages, NULL };

const _Screen_Ptrs_Masks Screen_Submenu1 = { &String_Submenu1, &Menu_Submenu1, NULL, NULL, NULL, NULL };


/*******************************************************************************
* Settings screen objects definition - SCREEN 3.1
*******************************************************************************/
//const _Menu Menu_Submenu2 = { 1, 1, 3, 5, &Languages, { Submenu_10, Submenu_11, Submenu_12, Submenu_13, Submenu_14 } };

const _Variables Var_Submenu2_3 = { 2, 14,  3, &Controlling_Variables_Set.Ctrl_Vars.Freq2, TRUE, &Param_Freq, &Languages, NULL };
const _Variables Var_Submenu2_2 = { 1, 14,  2, &Controlling_Variables_Set.Ctrl_Vars.Freq1, TRUE, &Param_Freq, &Languages, &Var_Submenu2_3 };
const _Variables Var_Submenu2_1 = { 0, 15,  1, &Controlling_Variables_Set.Ctrl_Vars.Gate_Opened_Time, TRUE, &Param_Opened_Time, &Languages, &Var_Submenu2_2 };

const _Strings String_Submenu2_6 = { 5, 0, 3, Speed2, &Languages, NULL };
const _Strings String_Submenu2_5 = { 4, 0, 2, Speed1, &Languages, &String_Submenu2_6 };
const _Strings String_Submenu2_4 = { 3, 0, 1, Open_Time, &Languages, &String_Submenu2_5 };
const _Strings String_Submenu2_3 = { 2, 18, 0, z4, &Languages, &String_Submenu2_4 };
const _Strings String_Submenu2_2 = { 1, 16, 0, _1z, &Languages, &String_Submenu2_3 };
const _Strings String_Submenu2_1 = { 0, 0, 0, Menu_1, &Languages, &String_Submenu2_2 };

const _Screen_Ptrs_Masks Screen_Submenu2 = { &String_Submenu2_1, NULL, &Var_Submenu2_1, NULL, NULL, NULL };

/*******************************************************************************
* Settings screen objects definition - SCREEN 3.1
*******************************************************************************/
//const _Menu Menu_Submenu2 = { 1, 1, 3, 5, &Languages, { Submenu_10, Submenu_11, Submenu_12, Submenu_13, Submenu_14 } };
//const _Variables Var_Submenu2_3 = { 2, 14,  3, &Controlling_Variables_Set.Ctrl_Vars.Freq2, TRUE, &Param_Freq, &Languages, NULL };

//const _Variables Var_Submenu2_4a = { 3, 14,  3, &Controlling_Variables_Set.Ctrl_Vars.Freq_Slow, TRUE, &Param_Freq, &Languages, NULL };
const _Variables Var_Submenu2_3a = { 2, 16,  3, &Controlling_Variables_Set.Ctrl_Vars.Time_Slow, TRUE, &Param_SoftStartStop, &Languages, NULL };
const _Variables Var_Submenu2_2a = { 1, 16,  2, &Controlling_Variables_Set.Ctrl_Vars.SoftStop , TRUE, &Param_SoftStartStop, &Languages, &Var_Submenu2_3a };
const _Variables Var_Submenu2_1a = { 0, 16,  1, &Controlling_Variables_Set.Ctrl_Vars.SoftStart, TRUE, &Param_SoftStartStop, &Languages, &Var_Submenu2_2a };

const _Strings String_Submenu2_6a = { 4, 0, 3, Czas_Ham, &Languages, NULL };
const _Strings String_Submenu2_5a = { 4, 0, 2, Soft_stop, &Languages, &String_Submenu2_6a };
const _Strings String_Submenu2_4a = { 3, 0, 1, Soft_start, &Languages, &String_Submenu2_5a };
const _Strings String_Submenu2_3a = { 2, 18, 0, z4, &Languages, &String_Submenu2_4a };
const _Strings String_Submenu2_2a = { 1, 16, 0, _2z, &Languages, &String_Submenu2_3a };
const _Strings String_Submenu2_1a = { 0, 0, 0, Menu_1, &Languages, &String_Submenu2_2a };

const _Screen_Ptrs_Masks Screen_Submenu2a = { &String_Submenu2_1a, NULL, &Var_Submenu2_1a, NULL, NULL, NULL };

/*******************************************************************************
* Settings screen objects definition - SCREEN 3.2
*******************************************************************************/
//const _Menu Menu_Submenu2 = { 1, 1, 3, 5, &Languages, { Submenu_10, Submenu_11, Submenu_12, Submenu_13, Submenu_14 } };
//const _Variables Var_Submenu2_3 = { 2, 14,  3, &Controlling_Variables_Set.Ctrl_Vars.Freq2, TRUE, &Param_Freq, &Languages, NULL };

//const _Variables Var_Submenu2_4a = { 3, 17,  3, &Controlling_Variables_Set.Ctrl_Vars.Freq_Slow, TRUE, &Param_Freq, &Languages, NULL };
const _Variables Var_Submenu2_3b = { 2, 17,  3, &Service_Variables_Set.Serv_Vars.Serwis_020, TRUE, &Param_2_Dot_Digits, &Languages, NULL };
const _Variables Var_Submenu2_2b = { 1, 15,  2, &Controlling_Variables_Set.Ctrl_Vars.Braking_Angle , TRUE, &Param_Braking_Angle, &Languages, &Var_Submenu2_3b };
const _Variables Var_Submenu2_1b = { 0, 14,  1, &Controlling_Variables_Set.Ctrl_Vars.Freq_Slow, TRUE, &Param_Freq, &Languages, &Var_Submenu2_2b };

//const _Strings String_Submenu2_6a = { 4, 0, 2, Czas_Ham, &Languages, NULL };
const _Strings String_Submenu2_6b = { 5, 0, 3, Pre_Worning, &Languages, NULL};//&String_Submenu2_6a };
const _Strings String_Submenu2_5b = { 4, 0, 2, Kat_Ham, &Languages, &String_Submenu2_6b };
const _Strings String_Submenu2_4b = { 3, 0, 1, Predk_Ham, &Languages, &String_Submenu2_5b };
const _Strings String_Submenu2_3b = { 2, 18, 0, z4, &Languages, &String_Submenu2_4b };
const _Strings String_Submenu2_2b = { 1, 16, 0, _3z, &Languages, &String_Submenu2_3b };
const _Strings String_Submenu2_1b = { 0, 0, 0, Menu_1, &Languages, &String_Submenu2_2b };

const _Screen_Ptrs_Masks Screen_Submenu2b = { &String_Submenu2_1b, NULL, &Var_Submenu2_1b, NULL, NULL, NULL };


/*******************************************************************************
* Settings screen objects definition - SCREEN 3.3
*******************************************************************************/
//const _Menu Menu_Submenu2 = { 1, 1, 3, 5, &Languages, { Submenu_10, Submenu_11, Submenu_12, Submenu_13, Submenu_14 } };
//const _Variables Var_Submenu2_3 = { 2, 14,  3, &Controlling_Variables_Set.Ctrl_Vars.Freq2, TRUE, &Param_Freq, &Languages, NULL };

//const _Variables Var_Submenu2_4a = { 3, 14,  3, &Controlling_Variables_Set.Ctrl_Vars.Freq_Slow, TRUE, &Param_Freq, &Languages, NULL };
const _Variables Var_Submenu2_3c = { 2, 8,  3, &Controlling_Variables_Set.Ctrl_Vars.Photo_Closing_Fun, TRUE, &Param_Photo_Opening_Closing, &Languages, NULL };
const _Variables Var_Submenu2_2c = { 1, 8,  2, &Controlling_Variables_Set.Ctrl_Vars.Photo_Opening_Fun, TRUE, &Param_Photo_Opening_Closing, &Languages, &Var_Submenu2_3c };
const _Variables Var_Submenu2_1c = { 0, 8,  1, &Controlling_Variables_Set.Ctrl_Vars.Photo_Opened, TRUE, &Param_Photo_Opened, &Languages, &Var_Submenu2_2c };

//const _Strings String_Submenu2_6a = { 4, 0, 2, Czas_Ham, &Languages, NULL };
const _Strings String_Submenu2_6c = { 5, 0, 3, Photo_Closing, &Languages, NULL};//&String_Submenu2_6a };
const _Strings String_Submenu2_5c = { 4, 0, 2, Photo_Opening, &Languages, &String_Submenu2_6c };
const _Strings String_Submenu2_4c = { 3, 0, 1, Photo_Opened, &Languages, &String_Submenu2_5c };
const _Strings String_Submenu2_3c = { 2, 18, 0, z4, &Languages, &String_Submenu2_4c };
const _Strings String_Submenu2_2c = { 1, 16, 0, _4z, &Languages, &String_Submenu2_3c };
const _Strings String_Submenu2_1c = { 0, 0, 0, Photo_sett, &Languages, &String_Submenu2_2c };

const _Screen_Ptrs_Masks Screen_Submenu2c = { &String_Submenu2_1c, NULL, &Var_Submenu2_1c, NULL, NULL, NULL };





/*******************************************************************************
* Settings screen objects definition - SCREEN 4
*******************************************************************************/
const _Menu Menu_Submenu3 = { 1, 1, 3, 5, &Languages, { Submenu_10, Submenu_11, Submenu_12, Submenu_13, Submenu_14 } };

const _Strings String_Submenu3 = { 0, 0, 0, Menu_2, &Languages, NULL };

const _Screen_Ptrs_Masks Screen_Submenu3 = { &String_Submenu3, &Menu_Submenu3, NULL, NULL, NULL, NULL };


/*******************************************************************************
* Funckcje1 screen objects definition - SCREEN 5
*******************************************************************************/
/*
const _Variables Var_Fun3 = { 2, 14,  3, &Service_Variables_Set.Serv_Vars.Szybkie_wejscie, TRUE, &TN_Param, &Languages, NULL };
const _Variables Var_Fun2 = { 1, 14,  2, &Service_Variables_Set.Serv_Vars.W_wyjscie, TRUE, &Wowy_param, &Languages, &Var_Fun3 };
const _Variables Var_Fun1 = { 0, 14,  1, &Service_Variables_Set.Serv_Vars.Sap, TRUE, &Sap_param, &Languages, &Var_Fun2 };

const _Strings String_Fun6 = { 5, 0, 3, Szybkie, &Languages, NULL};
const _Strings String_Fun5 = { 4, 0, 2, Wo_Wy, &Languages, &String_Fun6};
const _Strings String_Fun4 = { 3, 0, 1, Sap, &Languages, &String_Fun5};
const _Strings String_Fun3 = { 2, 18, 0, z4, &Languages, &String_Fun4};
const _Strings String_Fun2 = { 1, 16, 0, _1z, &Languages, &String_Fun3};
*/
const _Strings String_Fun1 = { 0, 0, 0, Menu_3, &Languages, NULL};//&String_Fun2};

const _Screen_Ptrs_Masks Screen_Funkcje1 = { &String_Fun1, NULL, NULL,/*&Var_Fun1*/ NULL, NULL, NULL };

/*******************************************************************************
* Funkcje2 screen objects definition - SCREEN 5-1
*******************************************************************************/
/*
const _Variables Var_Fun6 = { 2, 15,  3, &Service_Variables_Set.Serv_Vars.Priority, TRUE, &Priorytet_Param, &Languages, NULL };
const _Variables Var_Fun5 = { 1, 17,  2, &Service_Variables_Set.Serv_Vars.Standby_No_Brake_Wait, TRUE, &SNBW_Param, &Languages, &Var_Fun6 };
const _Variables Var_Fun4 = { 0, 17,  1, &Service_Variables_Set.Serv_Vars.Standby_No_Brake, TRUE, &TN_Param, &Languages, &Var_Fun5 };

const _Strings String_Fun12 = { 3, 0, 3, Priorytet_przejscia, &Languages, NULL};
const _Strings String_Fun11 = { 3, 0, 2, SP_Hamulec_Czas, &Languages, &String_Fun12};
const _Strings String_Fun10 = { 3, 0, 1, SP_Hamulec, &Languages, &String_Fun11};
const _Strings String_Fun9 = { 2, 18, 0, z4, &Languages, &String_Fun10};
const _Strings String_Fun8 = { 1, 16, 0, _2z, &Languages, &String_Fun9};
*/
const _Strings String_Fun7 = { 0, 0, 0, Menu_3, &Languages, NULL};//&String_Fun8};

const _Screen_Ptrs_Masks Screen_Funkcje2 = { &String_Fun7, NULL, NULL/*&Var_Fun4*/, NULL, NULL, NULL };
/*******************************************************************************
* Funkcje3 screen objects definition - SCREEN 5-2
*******************************************************************************/
/*
const _Variables Var_Fun16 = { 10, 18, 3, &Service_Variables_Set.Serv_Vars.Free_Minute_22, TRUE, &Clock_Minute, &Languages, NULL };
const _Variables Var_Fun15 = { 8, 15,  3, &Service_Variables_Set.Serv_Vars.Free_Hour_22, TRUE, &Clock_Hour, &Languages, &Var_Fun16 };
const _Variables Var_Fun14 = { 7, 10,  3, &Service_Variables_Set.Serv_Vars.Free_Minute_21, TRUE, &Clock_Minute, &Languages, &Var_Fun15 };
const _Variables Var_Fun13 = { 6, 7,  3, &Service_Variables_Set.Serv_Vars.Free_Hour_21, TRUE, &Clock_Hour, &Languages, &Var_Fun14 };
const _Variables Var_Fun12 = { 5, 1,  3, &Service_Variables_Set.Serv_Vars.Free_Marker_2, TRUE, &Wowy_param, &Languages, &Var_Fun13 };
const _Variables Var_Fun11 = { 4, 18,  2, &Service_Variables_Set.Serv_Vars.Free_Minute_12, TRUE, &Clock_Minute, &Languages, &Var_Fun12 };
const _Variables Var_Fun10 = { 3, 15,  2, &Service_Variables_Set.Serv_Vars.Free_Hour_12, TRUE, &Clock_Hour, &Languages, &Var_Fun11 };
const _Variables Var_Fun9 = { 2, 10,  2, &Service_Variables_Set.Serv_Vars.Free_Minute_11, TRUE, &Clock_Minute, &Languages, &Var_Fun10 };
const _Variables Var_Fun8 = { 1, 7,  2, &Service_Variables_Set.Serv_Vars.Free_Hour_11, TRUE, &Clock_Hour, &Languages, &Var_Fun9 };
const _Variables Var_Fun7 = { 0, 1,  2, &Service_Variables_Set.Serv_Vars.Free_Marker_1, TRUE, &Wowy_param, &Languages, &Var_Fun8 };

const _Strings String_Fun18 = { 3, 9, 3, Kropki_1, &Languages, NULL};
const _Strings String_Fun17 = { 3, 9, 2, Kropki_1, &Languages, &String_Fun18};
const _Strings String_Fun16 = { 3, 0, 1, Czas_WW, &Languages, &String_Fun17};
const _Strings String_Fun15 = { 2, 18, 0, z4, &Languages, &String_Fun16};
const _Strings String_Fun14 = { 1, 16, 0, _3z, &Languages, &String_Fun15};
*/
const _Strings String_Fun13 = { 0, 0, 0, Menu_3, &Languages, NULL };//&String_Fun14};

const _Screen_Ptrs_Masks Screen_Funkcje3 = { &String_Fun13, NULL, NULL/*&Var_Fun7*/, NULL, NULL, NULL };



/*******************************************************************************
* Funkcje4 screen objects definition - SCREEN 5-3
*******************************************************************************/
/*
const _Variables Var_Fun26 = { 10, 18, 3, &Service_Variables_Set.Serv_Vars.Fast_Minute_22, TRUE, &Clock_Minute, &Languages, NULL };
const _Variables Var_Fun25 = { 8, 15,  3, &Service_Variables_Set.Serv_Vars.Fast_Hour_22, TRUE, &Clock_Hour, &Languages, &Var_Fun26 };
const _Variables Var_Fun24 = { 7, 10,  3, &Service_Variables_Set.Serv_Vars.Fast_Minute_21, TRUE, &Clock_Minute, &Languages, &Var_Fun25 };
const _Variables Var_Fun23 = { 6, 7,  3, &Service_Variables_Set.Serv_Vars.Fast_Hour_21, TRUE, &Clock_Hour, &Languages, &Var_Fun24 };
const _Variables Var_Fun22 = { 5, 1,  3, &Service_Variables_Set.Serv_Vars.Fast_Marker_2, TRUE, &TN_Param, &Languages, &Var_Fun23 };
const _Variables Var_Fun21 = { 4, 18,  2, &Service_Variables_Set.Serv_Vars.Fast_Minute_12, TRUE, &Clock_Minute, &Languages, &Var_Fun22 };
const _Variables Var_Fun20 = { 3, 15,  2, &Service_Variables_Set.Serv_Vars.Fast_Hour_12, TRUE, &Clock_Hour, &Languages, &Var_Fun21 };
const _Variables Var_Fun19 = { 2, 10,  2, &Service_Variables_Set.Serv_Vars.Fast_Minute_11, TRUE, &Clock_Minute, &Languages, &Var_Fun20 };
const _Variables Var_Fun18 = { 1, 7,  2, &Service_Variables_Set.Serv_Vars.Fast_Hour_11, TRUE, &Clock_Hour, &Languages, &Var_Fun19 };
const _Variables Var_Fun17 = { 0, 1,  2, &Service_Variables_Set.Serv_Vars.Fast_Marker_1, TRUE, &TN_Param, &Languages, &Var_Fun18 };

const _Strings String_Fun24 = { 3, 9, 3, Kropki_1, &Languages, NULL};
const _Strings String_Fun23 = { 3, 9, 2, Kropki_1, &Languages, &String_Fun24};
const _Strings String_Fun22 = { 3, 0, 1, Czas_SP, &Languages, &String_Fun23};
const _Strings String_Fun21 = { 2, 18, 0, z4, &Languages, &String_Fun22};
const _Strings String_Fun20 = { 1, 16, 0, _4z, &Languages, &String_Fun21};
*/
const _Strings String_Fun19 = { 0, 0, 0, Menu_3, &Languages, NULL};//&String_Fun20};

const _Screen_Ptrs_Masks Screen_Funkcje4 = { &String_Fun19, NULL, NULL/*&Var_Fun17*/, NULL, NULL, NULL };

/*******************************************************************************
* Data screen objects definition - SCREEN 6
*******************************************************************************/

const _Variables Var_Data6 = { 5, 11,  3, &Date_Set.Date_Vars.Year, TRUE, &Clock_Year, &Languages,NULL };
const _Variables Var_Data5 = { 4, 8,  3, &Date_Set.Date_Vars.Month, TRUE, &Clock_Month, &Languages, &Var_Data6 };
const _Variables Var_Data4 = { 3, 5,  3, &Date_Set.Date_Vars.Day, TRUE, &Clock_Day, &Languages, &Var_Data5 };
const _Variables Var_Data3 = { 2, 11,  2, &Time_Set.Time_Vars.Minute, TRUE, &Clock_Minute, &Languages,&Var_Data4 };
const _Variables Var_Data2 = { 1, 8,  2, &Time_Set.Time_Vars.Hour, TRUE, &Clock_Hour, &Languages, &Var_Data3 };
const _Variables Var_Data1 = { 0, 5,  2, &Date_Set.Date_Vars.Day_Of_Week, TRUE, &Clock_DOW, &Languages, &Var_Data2 };

const _Strings String_Data4 = { 3, 10, 3, Kropka, &Languages, NULL };
const _Strings String_Data3 = { 2, 7, 3, Kropka, &Languages, &String_Data4 };
const _Strings String_Data2 = { 1, 10, 2, Dwukropek, &Languages, &String_Data3 };
const _Strings String_Data1 = { 0, 0, 0, Menu_4, &Languages, &String_Data2 };

const _Screen_Ptrs_Masks Screen_Data = { &String_Data1, NULL, &Var_Data1, NULL, NULL, NULL };

/*******************************************************************************
* Licence screen objects definition - SCREEN 7
*******************************************************************************/
const _Strings String_Lic7 = { 6, 14, 2, Kropka, &Languages, NULL };
const _Strings String_Lic6 = { 5, 11, 2, Kropka, &Languages, &String_Lic7 };
const _Strings String_Lic5 = { 4, 0, 3, Odblokuj, &Languages, &String_Lic6 };
const _Strings String_Lic4 = { 3, 0, 2, Bezterminowo, &Languages, &String_Lic5 };
const _Strings String_Lic3 = { 2, 0, 2, Do_dnia, &Languages, &String_Lic4 };
const _Strings String_Lic2 = { 1, 0, 1, Lic_Programu, &Languages, &String_Lic3 };
const _Strings String_Lic1 = { 0, 0, 0, Menu_11, &Languages, &String_Lic2 };

const _Variables Var_Lic3 = { 2, 15, 2, &Service_Variables_Set.Serv_Vars.Blokada_rok, FALSE, &Clock_Year, &Languages, NULL };
const _Variables Var_Lic2 = { 1, 12, 2, &Service_Variables_Set.Serv_Vars.Blokada_miesiac, FALSE, &Clock_Month, &Languages, &Var_Lic3 };
const _Variables Var_Lic1 = { 0, 9, 2, &Service_Variables_Set.Serv_Vars.Blokada_dzien, FALSE, &Clock_Day, &Languages, &Var_Lic2 };

const _Screen_Ptrs_Masks Screen_Licencja = { &String_Lic1, NULL, &Var_Lic1, &String_Lic_Mask, NULL, &Var_Lic_Mask };

/*******************************************************************************
* Submenu3 screen objects definition - SCREEN 8
*******************************************************************************/
const _Menu Menu_Submenu4 = { 1, 1, 3, 5, &Languages, { Submenu_20, Submenu_21, Submenu_22, Submenu_23, Submenu_24 } };

const _Strings String_Submenu4 = { 0, 0, 0, Menu_5, &Languages, NULL };

const _Screen_Ptrs_Masks Screen_Submenu4 = { &String_Submenu4, &Menu_Submenu4, NULL, NULL, NULL, NULL };


/*******************************************************************************
* Restore factory sets screen objects definition - SCREEN 9
*******************************************************************************/
const _Strings String_Fabryczne3 = { 2, 0, 3, ESC_Nie, &Languages, NULL};
const _Strings String_Fabryczne2 = { 1, 0, 2, OK_Tak, &Languages, &String_Fabryczne3};
const _Strings String_Fabryczne1 = { 0, 0, 0, Menu_8, &Languages, &String_Fabryczne2};

const _Screen_Ptrs_Masks Screen_Fabryczne = { &String_Fabryczne1, NULL, NULL, NULL, NULL, NULL };

/*******************************************************************************
* Kontakt screen objects definition - SCREEN 10
*******************************************************************************/
const _Strings String_Kontakt4 = { 3, 0, 3, Kontakt_Text3, &Languages, NULL};
const _Strings String_Kontakt3 = { 2, 0, 2, Kontakt_Text2, &Languages, &String_Kontakt4};
const _Strings String_Kontakt2 = { 1, 0, 1, Kontakt_Text1, &Languages, &String_Kontakt3};
const _Strings String_Kontakt1 = { 0, 0, 0, Menu_9, &Languages, &String_Kontakt2};

const _Screen_Ptrs_Masks Screen_Kontakt1 = { &String_Kontakt1, NULL, NULL, NULL, NULL, NULL };
/*******************************************************************************
* Info screen objects definition - SCREEN 10-1
*******************************************************************************/
const _Variables Var_Info7 = { 6, 12, 3, &Controller_Variables.Controller_Vars.Serial_Number, FALSE, &Param_5_Digits, &Languages, NULL };
const _Variables Var_Info6 = { 5, 15,2, &Controller_Variables.Controller_Vars.Controller_Date[2], FALSE, &Param_Serial, &Languages, &Var_Info7 };
const _Variables Var_Info5 = { 4, 12,2, &Controller_Variables.Controller_Vars.Controller_Date[1], FALSE, &Param_Serial, &Languages, &Var_Info6 };
const _Variables Var_Info4 = { 3, 9, 2, &Controller_Variables.Controller_Vars.Controller_Date[0], FALSE, &Param_Serial, &Languages, &Var_Info5 };
const _Variables Var_Info3 = { 2, 15,1, &Controller_Variables.Controller_Vars.Software_Version[2], FALSE, &Param_Serial, &Languages, &Var_Info4 };
const _Variables Var_Info2 = { 1, 12,1, &Controller_Variables.Controller_Vars.Software_Version[1], FALSE, &Param_Serial, &Languages, &Var_Info3 };
const _Variables Var_Info1 = { 0, 9, 1, &Controller_Variables.Controller_Vars.Software_Version[0], FALSE, &Param_Serial, &Languages, &Var_Info2 };

const _Strings String_Info4 = { 3, 0, 3, S_N, &Languages, NULL};
const _Strings String_Info3 = { 2, 0, 2, Manufactured, &Languages, &String_Info4};
const _Strings String_Info2 = { 1, 0, 1, Soft_Version, &Languages, &String_Info3};
const _Strings String_Info1 = { 0, 0, 0, Menu_10, &Languages, &String_Info2};


const _Screen_Ptrs_Masks Screen_Info = { &String_Info1, NULL, &Var_Info1, NULL, NULL, NULL };

/*******************************************************************************
* Haslo screen objects definition - SCREEN 11
*******************************************************************************/
const _Variables Var_Password2 = { 0, 18,  3, &Service_Variables_Set.Serv_Vars.Blok_Dostep_Pozostalo, FALSE, &Param_2_Digits, &Languages, NULL };
const _Variables Var_Password1 = { 0, 7,  2, &Password_Set, TRUE, &Passwd, &Languages, &Var_Password2 };

const _Strings String_Password2 = { 1, 0, 3, Ilosc_prob, &Languages, NULL};
const _Strings String_Password1 = { 0, 0, 0, Haslo_menu, &Languages, &String_Password2};

const _Screen_Ptrs_Masks Screen_Haslo = { &String_Password1, NULL, &Var_Password1, NULL, NULL, NULL };

/*******************************************************************************
* Bramy motor1 screen objects definition - SCREEN 12-1
*******************************************************************************/

const _Variables Var_BM3 = { 2, 8,  3, &Controlling_Variables_Set.Ctrl_Vars.Sensor_Type, TRUE, &Param_Sensor_Type, &Languages, NULL };
const _Variables Var_BM2 = { 1, 8,  2, &Controlling_Variables_Set.Ctrl_Vars.Motor_Type, TRUE, &Param_Motor_Type, &Languages, &Var_BM3 };
const _Variables Var_BM1 = { 0, 8,  1, &Controlling_Variables_Set.Ctrl_Vars.Fast_Gate_Type, TRUE, &Param_Gate_Type, &Languages, &Var_BM2 };
const _Strings String_BM6 = { 5, 18, 0, z1, &Languages, NULL};
const _Strings String_BM5 = { 4, 17, 0, _1z, &Languages, &String_BM6};
const _Strings String_BM4 = { 3, 0, 3, Typ_czujnika, &Languages, &String_BM5};
const _Strings String_BM3 = { 2, 0, 2, Typ_silnika, &Languages, &String_BM4};
const _Strings String_BM2 = { 1, 0, 1, Typ_bramy, &Languages, &String_BM3};
const _Strings String_BM1 = { 0, 0, 0, Submenu_00, &Languages, &String_BM2};

const _Screen_Ptrs_Masks Screen_Brama_Motor1 = { &String_BM1, NULL, &Var_BM1, NULL, NULL, NULL };

/*******************************************************************************
* Prad screen objects definition - SCREEN 13-1
*******************************************************************************/

const _Variables Var_Prad6 = { 5, 18,  3, &Controlling_Variables_Set.Ctrl_Vars.F2_Current_Counter, TRUE, &Param_Current_Counter, &Languages, NULL };
const _Variables Var_Prad5 = { 4, 9 ,  3, &Controlling_Variables_Set.Ctrl_Vars.F2_Current_Limit, TRUE, &Param_Current, &Languages, &Var_Prad6 };
const _Variables Var_Prad4 = { 3, 3 ,  3, &Controller_Variables.Controller_Vars.F2_Current, FALSE, &Param_Current, &Languages, &Var_Prad5 };
const _Variables Var_Prad3 = { 2, 18,  2, &Controlling_Variables_Set.Ctrl_Vars.F1_Current_Counter, TRUE, &Param_Current_Counter, &Languages, &Var_Prad4 };
const _Variables Var_Prad2 = { 1, 9 ,  2, &Controlling_Variables_Set.Ctrl_Vars.F1_Current_Limit, TRUE, &Param_Current, &Languages, &Var_Prad3 };
const _Variables Var_Prad1 = { 0, 3 ,  2, &Controller_Variables.Controller_Vars.F1_Current, FALSE, &Param_Current, &Languages, &Var_Prad2 };

const _Strings String_Prad4 = { 3, 0, 3, Ampery2, &Languages, NULL};
const _Strings String_Prad3 = { 2, 0, 2, Ampery1, &Languages, &String_Prad4};
const _Strings String_Prad2 = { 1, 0, 1, Pom_ust, &Languages, &String_Prad3};
const _Strings String_Prad1 = { 0, 0, 0, Ust_pradu, &Languages, &String_Prad2};

const _Screen_Ptrs_Masks Screen_Prad1 = { &String_Prad1, NULL, &Var_Prad1, NULL, NULL, NULL };

/*******************************************************************************
* Listwy1 bezpieczenstwa screen objects definition - SCREEN 13-2
*******************************************************************************/

const _Variables Var_Listwy6 = { 5, 15,  3, &Service_Variables_Set.Serv_Vars.In7_Type, TRUE, &Param_Inputs4, &Languages, NULL };
const _Variables Var_Listwy5 = { 4, 15,  2, &Service_Variables_Set.Serv_Vars.In6_Type, TRUE, &Param_Inputs1, &Languages, &Var_Listwy6 };
const _Variables Var_Listwy4 = { 3, 15,  1, &Service_Variables_Set.Serv_Vars.In5_Type, TRUE, &Param_Inputs1, &Languages, &Var_Listwy5 };
const _Variables Var_Listwy3 = { 2, 6 ,  3, &Service_Variables_Set.Serv_Vars.In7_Fun, TRUE, &Param_Inputs3, &Languages, &Var_Listwy4 };
const _Variables Var_Listwy2 = { 1, 6 ,  2, &Service_Variables_Set.Serv_Vars.In6_Fun, FALSE, &Param_Inputs5, &Languages, &Var_Listwy3 };
const _Variables Var_Listwy1 = { 0, 6 ,  1, &Service_Variables_Set.Serv_Vars.In5_Fun, FALSE, &Param_Inputs5, &Languages, &Var_Listwy2 };

const _Strings String_Listwy6 = { 5, 18, 0, z2, &Languages, NULL};
const _Strings String_Listwy5 = { 4, 16, 0, _1z, &Languages, &String_Listwy6};
const _Strings String_Listwy4 = { 3, 0,  3, In7, &Languages, &String_Listwy5};
const _Strings String_Listwy3 = { 2, 0,  2, In6, &Languages, &String_Listwy4};
const _Strings String_Listwy2 = { 1, 0,  1, In5, &Languages, &String_Listwy3};
const _Strings String_Listwy1 = { 0, 0,  0, Submenu_02, &Languages, &String_Listwy2};

const _Screen_Ptrs_Masks Screen_Listwy1 = { &String_Listwy1, NULL, &Var_Listwy1, NULL, NULL, NULL };

/*******************************************************************************
* Listwy2 bezpieczenstwa screen objects definition - SCREEN 13-3
*******************************************************************************/

const _Variables Var_Listwy26 = { 5, 15,  3, &Service_Variables_Set.Serv_Vars.In10_Type, TRUE, &Param_Inputs4, &Languages, NULL };
const _Variables Var_Listwy25 = { 4, 15,  2, &Service_Variables_Set.Serv_Vars.In9_Type, TRUE, &Param_Inputs4, &Languages, &Var_Listwy26 };
const _Variables Var_Listwy24 = { 3, 15,  1, &Service_Variables_Set.Serv_Vars.In8_Type, TRUE, &Param_Inputs4, &Languages, &Var_Listwy25 };
const _Variables Var_Listwy23 = { 2, 6 ,  3, &Service_Variables_Set.Serv_Vars.In10_Fun, TRUE, &Param_Inputs3, &Languages, &Var_Listwy24 };
const _Variables Var_Listwy22 = { 1, 6 ,  2, &Service_Variables_Set.Serv_Vars.In9_Fun, TRUE, &Param_Inputs3, &Languages, &Var_Listwy23 };
const _Variables Var_Listwy21 = { 0, 6 ,  1, &Service_Variables_Set.Serv_Vars.In8_Fun, TRUE, &Param_Inputs3, &Languages, &Var_Listwy22 };

const _Strings String_Listwy26 = { 5, 18, 0, z2, &Languages, NULL};
const _Strings String_Listwy25 = { 4, 16, 0, _2z, &Languages, &String_Listwy26};
const _Strings String_Listwy24 = { 3, 0,  3, In10, &Languages, &String_Listwy25};
const _Strings String_Listwy23 = { 2, 0,  2, In9 , &Languages, &String_Listwy24};
const _Strings String_Listwy22 = { 1, 0,  1, In8 , &Languages, &String_Listwy23};
const _Strings String_Listwy21 = { 0, 0,  0, Submenu_02, &Languages, &String_Listwy22};

const _Screen_Ptrs_Masks Screen_Listwy2 = { &String_Listwy21, NULL, &Var_Listwy21, NULL, NULL, NULL };


/*******************************************************************************
* Ustaw_wejsc1 screen objects definition - SCREEN 13-4
*******************************************************************************/
const _Variables Var_Wejscie6 = { 5, 15,  3, &Service_Variables_Set.Serv_Vars.In13_Type, TRUE, &Param_Inputs1, &Languages, NULL };
const _Variables Var_Wejscie5 = { 4, 15,  2, &Service_Variables_Set.Serv_Vars.In12_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie6 };
const _Variables Var_Wejscie4 = { 3, 15,  1, &Service_Variables_Set.Serv_Vars.In11_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie5 };
const _Variables Var_Wejscie3 = { 2, 6 ,  3, &Service_Variables_Set.Serv_Vars.In13_Fun, FALSE, &Param_Inputs2, &Languages, &Var_Wejscie4 };
const _Variables Var_Wejscie2 = { 1, 6 ,  2, &Service_Variables_Set.Serv_Vars.In12_Fun, FALSE, &Param_Inputs2, &Languages, &Var_Wejscie3 };
const _Variables Var_Wejscie1 = { 0, 6 ,  1, &Service_Variables_Set.Serv_Vars.In11_Fun, FALSE, &Param_Inputs2, &Languages, &Var_Wejscie2 };

const _Strings String_Wejscia6 = { 5, 18, 0, z4, &Languages, NULL};
const _Strings String_Wejscia5 = { 4, 16, 0, _1z, &Languages, &String_Wejscia6};
const _Strings String_Wejscia4 = { 3, 0, 3, In13, &Languages, &String_Wejscia5 };
const _Strings String_Wejscia3 = { 2, 0, 2, In12, &Languages, &String_Wejscia4 };
const _Strings String_Wejscia2 = { 1, 0, 1, In11, &Languages, &String_Wejscia3 };
const _Strings String_Wejscia1 = { 0, 0, 0, Submenu_03, &Languages, &String_Wejscia2 };

const _Screen_Ptrs_Masks Screen_Ustaw_Wejsc1 = { &String_Wejscia1, NULL, &Var_Wejscie1, NULL, NULL, NULL };
/*******************************************************************************
* Ustaw_wejsc2 screen objects definition - SCREEN 13-5
*******************************************************************************/
const _Variables Var_Wejscie26 = { 5, 15,  3, &Service_Variables_Set.Serv_Vars.In16_Type, TRUE, &Param_Inputs1, &Languages, NULL };
const _Variables Var_Wejscie25 = { 4, 15,  2, &Service_Variables_Set.Serv_Vars.In15_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie26 };
const _Variables Var_Wejscie24 = { 3, 15,  1, &Service_Variables_Set.Serv_Vars.In14_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie25 };
const _Variables Var_Wejscie23 = { 2, 6 ,  3, &Service_Variables_Set.Serv_Vars.In16_Fun, TRUE, &Param_Inputs2, &Languages, &Var_Wejscie24 };
const _Variables Var_Wejscie22 = { 1, 6 ,  2, &Service_Variables_Set.Serv_Vars.In15_Fun, TRUE, &Param_Inputs2, &Languages, &Var_Wejscie23 };
const _Variables Var_Wejscie21 = { 0, 6 ,  1, &Service_Variables_Set.Serv_Vars.In14_Fun, TRUE, &Param_Inputs2, &Languages, &Var_Wejscie22 };

const _Strings String_Wejscia26 = { 5, 18, 0, z4, &Languages, NULL};
const _Strings String_Wejscia25 = { 4, 16, 0, _2z, &Languages, &String_Wejscia26};
const _Strings String_Wejscia24 = { 3, 0, 3, In16, &Languages, &String_Wejscia25 };
const _Strings String_Wejscia23 = { 2, 0, 2, In15, &Languages, &String_Wejscia24 };
const _Strings String_Wejscia22 = { 1, 0, 1, In14, &Languages, &String_Wejscia23 };
const _Strings String_Wejscia21 = { 0, 0, 0, Submenu_03, &Languages, &String_Wejscia22 };

const _Screen_Ptrs_Masks Screen_Ustaw_Wejsc2 = { &String_Wejscia21, NULL, &Var_Wejscie21, NULL, NULL, NULL };
/*******************************************************************************
* Ustaw_wejsc3 screen objects definition - SCREEN 13-6
*******************************************************************************/
const _Variables Var_Wejscie36 = { 5, 15,  3, &Service_Variables_Set.Serv_Vars.In19_Type, TRUE, &Param_Inputs1, &Languages, NULL };
const _Variables Var_Wejscie35 = { 4, 15,  2, &Service_Variables_Set.Serv_Vars.In18_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie36 };
const _Variables Var_Wejscie34 = { 3, 15,  1, &Service_Variables_Set.Serv_Vars.In17_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie35 };
const _Variables Var_Wejscie33 = { 2, 6 ,  3, &Service_Variables_Set.Serv_Vars.In19_Fun, TRUE, &Param_Inputs2, &Languages, &Var_Wejscie34 };
const _Variables Var_Wejscie32 = { 1, 6 ,  2, &Service_Variables_Set.Serv_Vars.In18_Fun, TRUE, &Param_Inputs2, &Languages, &Var_Wejscie33 };
const _Variables Var_Wejscie31 = { 0, 6 ,  1, &Service_Variables_Set.Serv_Vars.In17_Fun, TRUE, &Param_Inputs2, &Languages, &Var_Wejscie32 };

const _Strings String_Wejscia36 = { 5, 18, 0, z4, &Languages, NULL};
const _Strings String_Wejscia35 = { 4, 16, 0, _3z, &Languages, &String_Wejscia36};
const _Strings String_Wejscia34 = { 3, 0, 3, In19, &Languages, &String_Wejscia35 };
const _Strings String_Wejscia33 = { 2, 0, 2, In18, &Languages, &String_Wejscia34 };
const _Strings String_Wejscia32 = { 1, 0, 1, In17, &Languages, &String_Wejscia33 };
const _Strings String_Wejscia31 = { 0, 0, 0, Submenu_03, &Languages, &String_Wejscia32 };

const _Screen_Ptrs_Masks Screen_Ustaw_Wejsc3 = { &String_Wejscia31, NULL, &Var_Wejscie31, NULL, NULL, NULL };

/*******************************************************************************
* Ustaw_wejsc4 screen objects definition - SCREEN 13-7
*******************************************************************************/
//const _Variables Var_Wejscie46 = { 5, 15,  3, &Service_Variables_Set.Serv_Vars.In19_Type, TRUE, &Param_Inputs1, &Languages, NULL };
//const _Variables Var_Wejscie45 = { 4, 15,  2, &Service_Variables_Set.Serv_Vars.In18_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie36 };
const _Variables Var_Wejscie44 = { 3, 15,  1, &Service_Variables_Set.Serv_Vars.In20_Type, TRUE, &Param_Inputs1, &Languages, NULL};//&Var_Wejscie35 };
//const _Variables Var_Wejscie43 = { 2, 6 ,  3, &Service_Variables_Set.Serv_Vars.In19_Fun, TRUE, &Param_Inputs2, &Languages, &Var_Wejscie34 };
//const _Variables Var_Wejscie42 = { 1, 6 ,  2, &Service_Variables_Set.Serv_Vars.In18_Fun, TRUE, &Param_Inputs2, &Languages, &Var_Wejscie33 };
const _Variables Var_Wejscie41 = { 0, 6 ,  1, &Service_Variables_Set.Serv_Vars.In20_Fun, TRUE, &Param_Inputs2, &Languages, &Var_Wejscie44 };

const _Strings String_Wejscia46 = { 5, 18, 0, z4, &Languages, NULL};
const _Strings String_Wejscia45 = { 4, 16, 0, _4z, &Languages, &String_Wejscia36};
//const _Strings String_Wejscia44 = { 3, 0, 3, In3, &Languages, &String_Wejscia35 };
//const _Strings String_Wejscia43 = { 2, 0, 2, In2, &Languages, &String_Wejscia34 };
const _Strings String_Wejscia42 = { 1, 0, 1, In20, &Languages, &String_Wejscia45 };
const _Strings String_Wejscia41 = { 0, 0, 0, Submenu_03, &Languages, &String_Wejscia42 };

const _Screen_Ptrs_Masks Screen_Ustaw_Wejsc4 = { &String_Wejscia41, NULL, &Var_Wejscie41, NULL, NULL, NULL };

/*******************************************************************************
* Ustaw_wejsc_ster1 screen objects definition - SCREEN 13-8
*******************************************************************************/

const _Variables Var_Wejscie_Ster6 = { 5, 16,  3, &Service_Variables_Set.Serv_Vars.In3_Type, TRUE, &Param_Inputs1, &Languages, NULL };
const _Variables Var_Wejscie_Ster5 = { 4, 16,  2, &Service_Variables_Set.Serv_Vars.In2_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie_Ster6 };
const _Variables Var_Wejscie_Ster4 = { 3, 16,  1, &Service_Variables_Set.Serv_Vars.In1_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie_Ster5 };
const _Variables Var_Wejscie_Ster3 = { 2, 4 ,  3, &Service_Variables_Set.Serv_Vars.In3_Fun, TRUE, &Param_In_3, &Languages, &Var_Wejscie_Ster4 };
const _Variables Var_Wejscie_Ster2 = { 1, 4 ,  2, &Service_Variables_Set.Serv_Vars.In2_Fun, TRUE, &Param_In_2, &Languages, &Var_Wejscie_Ster3 };
const _Variables Var_Wejscie_Ster1 = { 0, 4 ,  1, &Service_Variables_Set.Serv_Vars.In1_Fun, TRUE, &Param_In_1, &Languages, &Var_Wejscie_Ster2 };

const _Strings String_Wejscia_Ster6 = { 5, 18, 0, z2, &Languages, NULL};
const _Strings String_Wejscia_Ster5 = { 4, 16, 0, _1z, &Languages, &String_Wejscia_Ster6};
const _Strings String_Wejscia_Ster4 = { 3, 0, 3, In3, &Languages, &String_Wejscia_Ster5 };
const _Strings String_Wejscia_Ster3 = { 2, 0, 2, In2, &Languages, &String_Wejscia_Ster4 };
const _Strings String_Wejscia_Ster2 = { 1, 0, 1, In1, &Languages, &String_Wejscia_Ster3 };
const _Strings String_Wejscia_Ster1 = { 0, 0, 0, Submenu_04, &Languages, &String_Wejscia_Ster2 };

const _Screen_Ptrs_Masks Screen_Ustaw_Wejsc_Ster1 = { &String_Wejscia_Ster1, NULL, &Var_Wejscie_Ster1, NULL, NULL, NULL };

/*******************************************************************************
* Ustaw_wejsc_ster2 screen objects definition - SCREEN 13-9
*******************************************************************************/

//const _Variables Var_Wejscie_Ster26 = { 5, 16,  3, &Service_Variables_Set.Serv_Vars.In3_Type, TRUE, &Param_Inputs1, &Languages, NULL };
//const _Variables Var_Wejscie_Ster25 = { 4, 16,  2, &Service_Variables_Set.Serv_Vars.In2_Type, TRUE, &Param_Inputs1, &Languages, &Var_Wejscie_Ster26 };
const _Variables Var_Wejscie_Ster24 = { 3, 16,  1, &Service_Variables_Set.Serv_Vars.In4_Type, TRUE, &Param_Inputs1, &Languages, NULL};//&Var_Wejscie_Ster25 };
//const _Variables Var_Wejscie_Ster23 = { 2, 4 ,  3, &Service_Variables_Set.Serv_Vars.In3_Fun, FALSE, &Param_Inputs2, &Languages, &Var_Wejscie_Ster24 };
//const _Variables Var_Wejscie_Ster22 = { 1, 4 ,  2, &Service_Variables_Set.Serv_Vars.In2_Fun, FALSE, &Param_Inputs2, &Languages, &Var_Wejscie_Ster23 };
const _Variables Var_Wejscie_Ster21 = { 0, 4 ,  1, &Service_Variables_Set.Serv_Vars.In4_Fun, TRUE, &Param_In_4, &Languages, &Var_Wejscie_Ster24 };

const _Strings String_Wejscia_Ster26 = { 5, 18, 0, z2, &Languages, NULL};
const _Strings String_Wejscia_Ster25 = { 4, 16, 0, _2z, &Languages, &String_Wejscia_Ster26};
//const _Strings String_Wejscia_Ster24 = { 3, 0, 3, In3, &Languages, &String_Wejscia_Ster25 };
//const _Strings String_Wejscia_Ster23 = { 2, 0, 2, In2, &Languages, &String_Wejscia_Ster24 };
const _Strings String_Wejscia_Ster22 = { 1, 0, 1, In4, &Languages, &String_Wejscia_Ster25 };
const _Strings String_Wejscia_Ster21 = { 0, 0, 0, Submenu_04, &Languages, &String_Wejscia_Ster22 };

const _Screen_Ptrs_Masks Screen_Ustaw_Wejsc_Ster2 = { &String_Wejscia_Ster21, NULL, &Var_Wejscie_Ster21, NULL, NULL, NULL };

/*******************************************************************************
* Ustaw_wyjsc1 screen objects definition - SCREEN 13-10
*******************************************************************************/
const _Variables Var_Wyjscia3 = { 2, 7 ,  3, &Service_Variables_Set.Serv_Vars.Out3_Fun, TRUE, &Param_Outputs1, &Languages, NULL };
const _Variables Var_Wyjscia2 = { 1, 7 ,  2, &Service_Variables_Set.Serv_Vars.Out2_Fun, TRUE, &Param_Outputs1, &Languages, &Var_Wyjscia3 };
const _Variables Var_Wyjscia1 = { 0, 7 ,  1, &Service_Variables_Set.Serv_Vars.Out1_Fun, TRUE, &Param_Outputs1, &Languages, &Var_Wyjscia2 };

const _Strings String_Wyjscia6 = { 5, 18, 0, z2, &Languages, NULL};
const _Strings String_Wyjscia5 = { 4, 16, 0, _1z, &Languages, &String_Wyjscia6};
const _Strings String_Wyjscia4 = { 3, 0, 3, Out3, &Languages, &String_Wyjscia5 };
const _Strings String_Wyjscia3 = { 2, 0, 2, Out2, &Languages, &String_Wyjscia4 };
const _Strings String_Wyjscia2 = { 1, 0, 1, Out1, &Languages, &String_Wyjscia3 };
const _Strings String_Wyjscia1 = { 0, 0, 0, Submenu_05, &Languages, &String_Wyjscia2 };

const _Screen_Ptrs_Masks Screen_Ustaw_Wyjsc_Przek1 = { &String_Wyjscia1, NULL, &Var_Wyjscia1, NULL, NULL, NULL };

/*******************************************************************************
* Ustaw_wyjsc2 screen objects definition - SCREEN 13-11
*******************************************************************************/
const _Variables Var_Wyjscia23 = { 2, 7 ,  3, &Service_Variables_Set.Serv_Vars.Out6_Fun, TRUE, &Param_Outputs1, &Languages, NULL };
const _Variables Var_Wyjscia22 = { 1, 7 ,  2, &Service_Variables_Set.Serv_Vars.Out5_Fun, TRUE, &Param_Outputs1, &Languages, &Var_Wyjscia23 };
const _Variables Var_Wyjscia21 = { 0, 7 ,  1, &Service_Variables_Set.Serv_Vars.Out4_Fun, TRUE, &Param_Outputs1, &Languages, &Var_Wyjscia22 };

const _Strings String_Wyjscia26 = { 5, 18, 0, z2, &Languages, NULL};
const _Strings String_Wyjscia25 = { 4, 16, 0, _2z, &Languages, &String_Wyjscia26};
const _Strings String_Wyjscia24 = { 3, 0, 3, Out6, &Languages, &String_Wyjscia25 };
const _Strings String_Wyjscia23 = { 2, 0, 2, Out5, &Languages, &String_Wyjscia24 };
const _Strings String_Wyjscia22 = { 1, 0, 1, Out4, &Languages, &String_Wyjscia23 };
const _Strings String_Wyjscia21 = { 0, 0, 0, Submenu_05, &Languages, &String_Wyjscia22 };

const _Screen_Ptrs_Masks Screen_Ustaw_Wyjsc_Przek2 = { &String_Wyjscia21, NULL, &Var_Wyjscia21, NULL, NULL, NULL };

/*******************************************************************************
* Czujniki Menu screen objects definition - SCREEN 14-1
*******************************************************************************/
const _Menu Menu_Czujniki1 = { 1, 1, 2, 2, &Languages, { Menu_Sens_Magnetic, Menu_Sens_Encoder } };

const _Strings String_Czujniki_Menu = { 0, 0, 0, Submenu_06, &Languages, NULL};

const _Screen_Ptrs_Masks Screen_Czujniki_Menu = { &String_Czujniki_Menu, &Menu_Czujniki1, NULL, NULL, NULL, NULL };

/*******************************************************************************
* Czujniki1 screen objects definition - SCREEN 14-2
*******************************************************************************/
const _Variables Var_Czujniki1_6 = { 5, 15, 3, &Controller_Variables.Controller_Vars.Deg_MSens2_Angle, FALSE, &Param_4_Dot_Digits, &Languages, NULL };
const _Variables Var_Czujniki1_5 = { 4, 15, 2, &Controller_Variables.Controller_Vars.Deg_Angle2_Op, TRUE, &Param_4_Dot_Digits, &Languages, &Var_Czujniki1_6 };
const _Variables Var_Czujniki1_4 = { 3, 15, 1, &Controller_Variables.Controller_Vars.Deg_Angle2_Cl, TRUE, &Param_4_Dot_Digits, &Languages, &Var_Czujniki1_5 };
const _Variables Var_Czujniki1_3 = { 2, 7, 3, &Controller_Variables.Controller_Vars.Deg_MSens1_Angle, FALSE, &Param_4_Dot_Digits, &Languages, &Var_Czujniki1_4 };
const _Variables Var_Czujniki1_2 = { 1, 7, 2, &Controller_Variables.Controller_Vars.Deg_Angle1_Op, TRUE, &Param_4_Dot_Digits, &Languages, &Var_Czujniki1_3 };
const _Variables Var_Czujniki1_1 = { 0, 7, 1, &Controller_Variables.Controller_Vars.Deg_Angle1_Cl, TRUE, &Param_4_Dot_Digits, &Languages, &Var_Czujniki1_2 };

const _Strings String_Czujniki1_4 = { 3, 0, 3, Sensors_Text4, &Languages, NULL};
const _Strings String_Czujniki1_3 = { 2, 0, 2, Sensors_Text3, &Languages, &String_Czujniki1_4};
const _Strings String_Czujniki1_2 = { 1, 0, 1, Sensors_Text2, &Languages, &String_Czujniki1_3};
const _Strings String_Czujniki1_1 = { 0, 0, 0, Sensors_Text1, &Languages, &String_Czujniki1_2};

const _Screen_Ptrs_Masks Screen_Czujniki1 = { &String_Czujniki1_1, NULL, &Var_Czujniki1_1, NULL, NULL, NULL };
/*******************************************************************************
* Czujniki2 screen objects definition - SCREEN 14-2
*******************************************************************************/
const _Strings String_Czujniki2_1 = { 0, 0, 0, Submenu_06, &Languages, NULL};

const _Screen_Ptrs_Masks Screen_Czujniki2 = { &String_Czujniki2_1, NULL, NULL, NULL, NULL, NULL };

/*******************************************************************************
* Podglad1 screen objects definition - SCREEN 15-1
*******************************************************************************/

const _Variables Var_Podglad3 = { 2, 18,  3, &Controlling_Variables_Set.Ctrl_Vars.Speed_Opening, FALSE, &Param_0_50, &Languages, NULL };
const _Variables Var_Podglad2 = { 1, 18,  2, &Controlling_Variables_Set.Ctrl_Vars.Start_Speed_Opening, FALSE, &Param_0_50, &Languages, &Var_Podglad3 };
const _Variables Var_Podglad1 = { 0, 18,  1, &Controlling_Variables_Set.Ctrl_Vars.High_Speed_Opening, FALSE, &Param_0_50, &Languages, &Var_Podglad2 };

const _Strings String_Podglad6 = { 5, 18, 0, z6, &Languages, NULL};
const _Strings String_Podglad5 = { 4, 16, 0, _1z, &Languages, &String_Podglad6};
const _Strings String_Podglad4 = { 3, 0, 3, Opening_Speed_Max, &Languages, &String_Podglad5};
const _Strings String_Podglad3 = { 2, 0, 2, Opening_Speed_Min, &Languages, &String_Podglad4};
const _Strings String_Podglad2 = { 1, 0, 1, Opening_Speed_HS, &Languages, &String_Podglad3};
const _Strings String_Podglad1 = { 0, 0, 0, Submenu_00, &Languages, &String_Podglad2};

const _Screen_Ptrs_Masks Screen_Podglad1 = { &String_Podglad1, NULL, &Var_Podglad1, NULL, NULL, NULL };

/*******************************************************************************
* Language screen objects definition - SCREEN 16
*******************************************************************************/
const _Variables Var_Language1 = { 0, 7,  2, &Service_Variables_Set.Serv_Vars.Jezyk, TRUE, &Lang_Param, &Languages, NULL };

const _Strings String_Language1 = { 0, 0, 0, Submenu_10, &Languages, NULL};

const _Screen_Ptrs_Masks Screen_Jezyk = { &String_Language1, NULL, &Var_Language1, NULL, NULL, NULL };
/*******************************************************************************
* Zmiana hasel screen objects definition - SCREEN 17
*******************************************************************************/
const _Variables Var_Passwd4 = { 3, 18, 3, &Service_Variables_Set.Serv_Vars.Ilosc_Prob_Dostepu, TRUE, &Param_Prob, &Languages, NULL };
const _Variables Var_Passwd3 = { 2, 8,  3, &Service_Variables_Set.Serv_Vars.Haslo_Dostepu, TRUE, &Passwd, &Languages, &Var_Passwd4 };
const _Variables Var_Passwd2 = { 1, 18, 2, &Service_Variables_Set.Serv_Vars.Ilosc_Prob_Blokady, TRUE, &Param_Prob, &Languages, &Var_Passwd3 };
const _Variables Var_Passwd1 = { 0, 8,  2, &Service_Variables_Set.Serv_Vars.Haslo_Blokady, TRUE, &Passwd, &Languages, &Var_Passwd2 };

const _Strings String_Passwd5 = { 4, 0, 3, Dostepu, &Languages, NULL};
const _Strings String_Passwd4 = { 3, 0, 2, Blokady, &Languages, &String_Passwd5};
const _Strings String_Passwd3 = { 2, 15, 1, Proby, &Languages, &String_Passwd4};
const _Strings String_Passwd2 = { 1, 8, 1, Haslo, &Languages, &String_Passwd3};
const _Strings String_Passwd1 = { 0, 0, 0, Submenu_11, &Languages, &String_Passwd2};

const _Screen_Ptrs_Masks Screen_Zmiana_Hasel = { &String_Passwd1, NULL, &Var_Passwd1, NULL, NULL, NULL };
/*******************************************************************************
* Passwords settings screen objects definition - SCREEN 18
*******************************************************************************/
const _Variables Var_Lock4 = { 3, 16, 3, &Service_Variables_Set.Serv_Vars.Blokada_rok, TRUE, &Clock_Year, &Languages, NULL };
const _Variables Var_Lock3 = { 2, 13, 3, &Service_Variables_Set.Serv_Vars.Blokada_miesiac, TRUE, &Clock_Month, &Languages, &Var_Lock4 };
const _Variables Var_Lock2 = { 1, 10, 3, &Service_Variables_Set.Serv_Vars.Blokada_dzien, TRUE, &Clock_Day, &Languages, &Var_Lock3 };
const _Variables Var_Lock1 = { 0, 10, 2, &Service_Variables_Set.Serv_Vars.Blokada, TRUE, &TN_Param, &Languages, &Var_Lock2 };

const _Strings String_Lock5 = { 3, 15, 3, Kropka, &Languages, NULL};
const _Strings String_Lock4 = { 3, 12, 3, Kropka, &Languages, &String_Lock5};
const _Strings String_Lock3 = { 2, 0, 3, Blok_data, &Languages, &String_Lock4};
const _Strings String_Lock2 = { 1, 0, 2, Blok, &Languages, &String_Lock3};
const _Strings String_Lock1 = { 0, 0, 0, Submenu_12, &Languages, &String_Lock2};

const _Screen_Ptrs_Masks Screen_Ust_Blokady = { &String_Lock1, NULL, &Var_Lock1, NULL, NULL, NULL };

/*******************************************************************************
* CAL_RTC settings screen objects definition - SCREEN 19
*******************************************************************************/
const _Variables Var_RTC1 = { 0, 8, 2, &Service_Variables_Set.Serv_Vars.RTC_Cal_Var, TRUE, &Param_RTC, &Languages, NULL };

const _Strings String_RTC1 = { 0, 0, 0, Submenu_13, &Languages, NULL};

const _Screen_Ptrs_Masks Screen_RTC = { &String_RTC1, NULL, &Var_RTC1, NULL, NULL, NULL };

/*******************************************************************************
* Reset counters screen objects definition - SCREEN 20
*******************************************************************************/
const _Strings String_Zerowanie3 = { 2, 0, 3, ESC_Nie, &Languages, NULL};
const _Strings String_Zerowanie2 = { 1, 0, 2, OK_Tak, &Languages, &String_Zerowanie3};
const _Strings String_Zerowanie1 = { 0, 0, 0, Submenu_14, &Languages, &String_Zerowanie2};

const _Screen_Ptrs_Masks Screen_Zer_Licznikow = { &String_Zerowanie1, NULL, NULL, NULL, NULL, NULL };

/*******************************************************************************
* Licznik pracy settings screen objects definition - SCREEN 21
*******************************************************************************/
const _Variables Var_LP6 = { 5, 16, 3, &Service_Variables_Set.Serv_Vars.Insp_Year, TRUE, &Clock_Year, &Languages, NULL };
const _Variables Var_LP5 = { 4, 13, 3, &Service_Variables_Set.Serv_Vars.Insp_Month, TRUE, &Clock_Month, &Languages, &Var_LP6 };
const _Variables Var_LP4 = { 3, 10, 3, &Service_Variables_Set.Serv_Vars.Insp_Day, TRUE, &Clock_Day, &Languages, &Var_LP5 };
const _Variables Var_LP3 = { 2, 1, 3, &Service_Variables_Set.Serv_Vars.Insp_Counter, TRUE, &Param_LP_Counter, &Languages, &Var_LP4 };
const _Variables Var_LP2 = { 1, 10, 2, &Service_Variables_Set.Serv_Vars.Insp_Marker, TRUE, &Param_LP_Marker, &Languages, &Var_LP3 };
const _Variables Var_LP1 = { 0, 8, 1, &Counters_Variables_Set.Counters_Vars.Service_Counter, FALSE, &Counters, &Languages, &Var_LP2 };

const _Strings String_LP7 = { 6, 5, 3, Godz, &Languages, NULL};
const _Strings String_LP6 = { 5, 16, 1, Godz, &Languages, &String_LP7 };
const _Strings String_LP5 = { 4, 15, 3, Kropka, &Languages, &String_LP6 };
const _Strings String_LP4 = { 3, 12, 3, Kropka, &Languages, &String_LP5 };
const _Strings String_LP3 = { 2, 0, 2, Przeglad, &Languages, &String_LP4 };
const _Strings String_LP2 = { 1, 0, 1, Przeglad_licznik, &Languages, &String_LP3 };
const _Strings String_LP1 = { 0, 0, 0, Submenu_20, &Languages, &String_LP2};

const _Screen_Ptrs_Masks Screen_Licznik_Pracy = { &String_LP1, NULL, &Var_LP1, NULL, NULL, NULL };
/*******************************************************************************
* Test screen objects definition - SCREEN 22
*******************************************************************************/

const _Strings String_Test_Prog3 = { 2, 2, 2, Test_Stop_Text, &Languages, NULL};
const _Strings String_Test_Prog2 = { 1, 2, 2, Test_Start_Text, &Languages, &String_Test_Prog3 };
const _Strings String_Test_Prog1 = { 0, 0, 0, Submenu_21, &Languages, &String_Test_Prog2 };

const _Screen_Ptrs_Masks Screen_Prog_Testowy = { &String_Test_Prog1, NULL, NULL, &Test_String_Mask, NULL, NULL };

/*******************************************************************************
* Inputs outputs sensors test screen objects definition - SCREEN 22-1
*******************************************************************************/
const _Variables Var_WeWy1 = { 0, 1, 1, &Controller_Variables.Controller_Vars.Test_Status, TRUE, &TestWeWy_Param, &Languages, NULL};//&Var_WeWy2 };

const _Strings String_WeWy9 = { 8, 0, 0, Submenu_22, &Languages, NULL };//&String_weWy10};
const _Strings String_WeWy8 = { 7, 0, 2, In8, &Languages, &String_WeWy9};
const _Strings String_WeWy7 = { 6, 4, 2, In7, &Languages, &String_WeWy8};
const _Strings String_WeWy6 = { 5, 8, 2, In6, &Languages, &String_WeWy7};
const _Strings String_WeWy5 = { 4, 12,2, In5, &Languages, &String_WeWy6};
const _Strings String_WeWy4 = { 3, 16,2, In4, &Languages, &String_WeWy5};
const _Strings String_WeWy3 = { 2, 0, 3, In3, &Languages, &String_WeWy4};
const _Strings String_WeWy2 = { 1, 4, 3, In2, &Languages, &String_WeWy3};
const _Strings String_WeWy1 = { 0, 8, 3, In1, &Languages, &String_WeWy2};

const _Screen_Ptrs_Masks Screen_Test_WeWy = { &String_WeWy1, NULL, &Var_WeWy1, &Manual_Test_Mask, NULL, NULL };
/*******************************************************************************
* Ust. Serwisowe (1/4) screen objects definition - SCREEN 23-1
*******************************************************************************/
const _Variables Var_Ust_Serwisowe6 = { 5, 14,  3, &Service_Variables_Set.Serv_Vars.Serwis_006, TRUE, &Param_Serwis, &Languages, NULL };
const _Variables Var_Ust_Serwisowe5 = { 4, 14,  2, &Service_Variables_Set.Serv_Vars.Serwis_005, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe6 };
const _Variables Var_Ust_Serwisowe4 = { 3, 14,  1, &Service_Variables_Set.Serv_Vars.Serwis_004, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe5 };
const _Variables Var_Ust_Serwisowe3 = { 2, 4,  3, &Service_Variables_Set.Serv_Vars.Serwis_003, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe4 };
const _Variables Var_Ust_Serwisowe2 = { 1, 4,  2, &Service_Variables_Set.Serv_Vars.Serwis_002, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe3 };
const _Variables Var_Ust_Serwisowe1 = { 0, 4,  1, &Service_Variables_Set.Serv_Vars.Serwis_001, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe2 };

const _Strings String_Ust_Serwisowe6 = { 5, 0, 3, Par3, &Languages, NULL};
const _Strings String_Ust_Serwisowe5 = { 4, 0, 2, Par2, &Languages, &String_Ust_Serwisowe6};
const _Strings String_Ust_Serwisowe4 = { 3, 0, 1, Par1, &Languages, &String_Ust_Serwisowe5};
const _Strings String_Ust_Serwisowe3 = { 2, 18, 0, z4, &Languages, &String_Ust_Serwisowe4};
const _Strings String_Ust_Serwisowe2 = { 1, 16, 0, _1z, &Languages, &String_Ust_Serwisowe3};
const _Strings String_Ust_Serwisowe1 = { 0, 0, 0, Submenu_23, &Languages, &String_Ust_Serwisowe2};

const _Screen_Ptrs_Masks Screen_Ust_Serwisowe1 = { &String_Ust_Serwisowe1, NULL, &Var_Ust_Serwisowe1, NULL, NULL, NULL };
/*******************************************************************************
* Ust. serwisowe (2/4) screen objects definition - SCREEN 23-2
*******************************************************************************/
const _Variables Var_Ust_Serwisowe12 = { 5, 14,  3, &Service_Variables_Set.Serv_Vars.Serwis_012, TRUE, &Param_Serwis, &Languages, NULL };
const _Variables Var_Ust_Serwisowe11 = { 4, 14,  2, &Service_Variables_Set.Serv_Vars.Serwis_011, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe12 };
const _Variables Var_Ust_Serwisowe10 = { 3, 14,  1, &Service_Variables_Set.Serv_Vars.Serwis_010, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe11 };
const _Variables Var_Ust_Serwisowe9 = { 2, 4,  3, &Service_Variables_Set.Serv_Vars.Serwis_009, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe10 };
const _Variables Var_Ust_Serwisowe8 = { 1, 4,  2, &Service_Variables_Set.Serv_Vars.Serwis_008, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe9 };
const _Variables Var_Ust_Serwisowe7 = { 0, 4,  1, &Service_Variables_Set.Serv_Vars.Serwis_007, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe8 };

const _Strings String_Ust_Serwisowe12 = { 5, 0, 3, Par6, &Languages, NULL};
const _Strings String_Ust_Serwisowe11 = { 4, 0, 2, Par5, &Languages, &String_Ust_Serwisowe12};
const _Strings String_Ust_Serwisowe10 = { 3, 0, 1, Par4, &Languages, &String_Ust_Serwisowe11};
const _Strings String_Ust_Serwisowe9 = { 2, 18, 0, z4, &Languages, &String_Ust_Serwisowe10};
const _Strings String_Ust_Serwisowe8 = { 1, 16, 0, _2z, &Languages, &String_Ust_Serwisowe9};
const _Strings String_Ust_Serwisowe7 = { 0, 0, 0, Submenu_23, &Languages, &String_Ust_Serwisowe8};

const _Screen_Ptrs_Masks Screen_Ust_Serwisowe2 = { &String_Ust_Serwisowe7, NULL, &Var_Ust_Serwisowe7, NULL, NULL, NULL };
/*******************************************************************************
* Ust. serwisowe (3/4) screen objects definition - SCREEN 23-3
*******************************************************************************/
const _Variables Var_Ust_Serwisowe18 = { 5, 14,  3, &Service_Variables_Set.Serv_Vars.Serwis_018, TRUE, &Param_Serwis, &Languages, NULL };
const _Variables Var_Ust_Serwisowe17 = { 4, 14,  2, &Service_Variables_Set.Serv_Vars.Serwis_017, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe18 };
const _Variables Var_Ust_Serwisowe16 = { 3, 14,  1, &Service_Variables_Set.Serv_Vars.Serwis_016, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe17 };
const _Variables Var_Ust_Serwisowe15 = { 2, 4,  3, &Service_Variables_Set.Serv_Vars.Serwis_015, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe16 };
const _Variables Var_Ust_Serwisowe14 = { 1, 4,  2, &Service_Variables_Set.Serv_Vars.Serwis_014, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe15 };
const _Variables Var_Ust_Serwisowe13 = { 0, 4,  1, &Service_Variables_Set.Serv_Vars.Serwis_013, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe14 };

const _Strings String_Ust_Serwisowe18 = { 5, 0, 3, Par9, &Languages, NULL};
const _Strings String_Ust_Serwisowe17 = { 4, 0, 2, Par8, &Languages, &String_Ust_Serwisowe18};
const _Strings String_Ust_Serwisowe16 = { 3, 0, 1, Par7, &Languages, &String_Ust_Serwisowe17};
const _Strings String_Ust_Serwisowe15 = { 2, 18, 0, z4, &Languages, &String_Ust_Serwisowe16};
const _Strings String_Ust_Serwisowe14 = { 1, 16, 0, _3z, &Languages, &String_Ust_Serwisowe15};
const _Strings String_Ust_Serwisowe13 = { 0, 0, 0, Submenu_23, &Languages, &String_Ust_Serwisowe14};

const _Screen_Ptrs_Masks Screen_Ust_Serwisowe3 = { &String_Ust_Serwisowe13, NULL, &Var_Ust_Serwisowe13, NULL, NULL, NULL };
/*******************************************************************************
* Ust. serwisowe (4/4) screen objects definition - SCREEN 23-4
*******************************************************************************/
const _Variables Var_Ust_Serwisowe24 = { 5, 14,  3, &Service_Variables_Set.Serv_Vars.Serwis_024, TRUE, &Param_Serwis, &Languages, NULL };
const _Variables Var_Ust_Serwisowe23 = { 4, 14,  2, &Service_Variables_Set.Serv_Vars.Serwis_023, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe24 };
const _Variables Var_Ust_Serwisowe22 = { 3, 14,  1, &Service_Variables_Set.Serv_Vars.Serwis_022, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe23 };
const _Variables Var_Ust_Serwisowe21 = { 2, 4,  3, &Service_Variables_Set.Serv_Vars.Serwis_021, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe22 };
const _Variables Var_Ust_Serwisowe20 = { 1, 4,  2, &Service_Variables_Set.Serv_Vars.Serwis_020, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe21 };
const _Variables Var_Ust_Serwisowe19 = { 0, 4,  1, &Service_Variables_Set.Serv_Vars.Serwis_019, TRUE, &Param_Serwis, &Languages, &Var_Ust_Serwisowe20 };

const _Strings String_Ust_Serwisowe24 = { 5, 0, 3, Par12, &Languages, NULL};
const _Strings String_Ust_Serwisowe23 = { 4, 0, 2, Par11, &Languages, &String_Ust_Serwisowe24};
const _Strings String_Ust_Serwisowe22 = { 3, 0, 1, Par10, &Languages, &String_Ust_Serwisowe23};
const _Strings String_Ust_Serwisowe21 = { 2, 18, 0, z4, &Languages, &String_Ust_Serwisowe22};
const _Strings String_Ust_Serwisowe20 = { 1, 16, 0, _4z, &Languages, &String_Ust_Serwisowe21};
const _Strings String_Ust_Serwisowe19 = { 0, 0, 0, Submenu_23, &Languages, &String_Ust_Serwisowe20};

const _Screen_Ptrs_Masks Screen_Ust_Serwisowe4 = { &String_Ust_Serwisowe19, NULL, &Var_Ust_Serwisowe19, NULL, NULL, NULL };

/*******************************************************************************
* Odczyt serwisowy (1/3) screen objects definition - SCREEN 24-1
*******************************************************************************/
const _Variables Var_Odczyt_Serwis11_1 = { 11, 17, 3, &Keyboards_Level, FALSE, &Param_3_Digits,&Languages, NULL};//&Var_Odczyt_Serwis11 };
const _Variables Var_Odczyt_Serwis11 = { 10, 11, 3, &Controller_Variables.Controller_Vars.Inputs_Error, FALSE, &Param_5_Digits,&Languages, &Var_Odczyt_Serwis11_1 };
const _Variables Var_Odczyt_Serwis10 = { 9, 0, 3, &Inputs_Level, FALSE, &Param_10_Digits,&Languages, &Var_Odczyt_Serwis11 };

const _Variables Var_Odczyt_Serwis9 = { 8, 18, 2, &Controller_Variables.Controller_Vars.Machine_State_Var, FALSE, &Param_2_Digits,&Languages, &Var_Odczyt_Serwis10 };
const _Variables Var_Odczyt_Serwis8 = { 7, 15, 2, &Controller_Variables.Controller_Vars.Internal_Temperature, FALSE, &Param_2_Digits, &Languages, &Var_Odczyt_Serwis9 };
const _Variables Var_Odczyt_Serwis7 = { 6, 10, 2, &Controller_Variables.Controller_Vars.AD_16, FALSE, &Param_4_Digits,&Languages, &Var_Odczyt_Serwis8 };
const _Variables Var_Odczyt_Serwis6 = { 5, 5,  2, &Controller_Variables.Controller_Vars.AD_1, FALSE, &Param_4_Digits,&Languages, &Var_Odczyt_Serwis7 };
const _Variables Var_Odczyt_Serwis5 = { 4, 0,  2, &Controller_Variables.Controller_Vars.AD_0, FALSE, &Param_4_Digits,&Languages, &Var_Odczyt_Serwis6 };

const _Variables Var_Odczyt_Serwis4 = { 3, 15, 1, &Controller_Variables.Controller_Vars.AD_9, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis5 };
const _Variables Var_Odczyt_Serwis3 = { 2, 10, 1, &Controller_Variables.Controller_Vars.AD_8, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis4 };
const _Variables Var_Odczyt_Serwis2 = { 1, 5,  1, &Controller_Variables.Controller_Vars.AD_15, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3 };
const _Variables Var_Odczyt_Serwis1 = { 0, 0,  1, &Controller_Variables.Controller_Vars.AD_14, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis2 };

const _Strings String_Odczyt_Serwis3 = { 2, 18, 0, z3, &Languages, NULL};
const _Strings String_Odczyt_Serwis2 = { 1, 16, 0, _1z, &Languages, &String_Odczyt_Serwis3};

const _Strings String_Odczyt_Serwis1 = { 0, 0, 0, Submenu_24, &Languages, &String_Odczyt_Serwis2};

const _Screen_Ptrs_Masks Screen_Odczyt_Serwisowy1 = { &String_Odczyt_Serwis1, NULL, &Var_Odczyt_Serwis1, NULL, NULL, NULL };
/*******************************************************************************
* Osczyt serwisowy (2/3) screen objects definition - SCREEN 24-2
*******************************************************************************/
const _Variables Var_Odczyt_Serwis26 = { 14,16, 3, &bytes_received, FALSE, &Param_3_Digits, &Languages, NULL};//&Var_Odczyt_Serwis20 };
const _Variables Var_Odczyt_Serwis25 = { 13,12, 3, &bytes_received, FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis26 };
const _Variables Var_Odczyt_Serwis24 = { 12,8 , 3, &RS485_Comm_Err_Counter2, FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis25 };
const _Variables Var_Odczyt_Serwis23 = { 11,4 , 3, &RS485_Comm_Err_Counter1, FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis24 };
const _Variables Var_Odczyt_Serwis22 = { 10,0 , 3, &RS485_Inverter_Counter, FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis23 };
const _Variables Var_Odczyt_Serwis21 = { 9, 16, 2, &Uart_Rx_Packet.Uart_Buffer[9], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis22 };
const _Variables Var_Odczyt_Serwis20 = { 8, 12, 2, &Uart_Rx_Packet.Uart_Buffer[8], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis21 };
const _Variables Var_Odczyt_Serwis19 = { 7, 8 , 2, &Uart_Rx_Packet.Uart_Buffer[7], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis20 };
const _Variables Var_Odczyt_Serwis18 = { 6, 4 , 2, &Uart_Rx_Packet.Uart_Buffer[6], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis19 };
const _Variables Var_Odczyt_Serwis17 = { 5, 0 , 2, &Uart_Rx_Packet.Uart_Buffer[5], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis18 };
const _Variables Var_Odczyt_Serwis16 = { 4, 16, 1, &Uart_Rx_Packet.Uart_Buffer[4], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis17 };
const _Variables Var_Odczyt_Serwis15 = { 3, 12, 1, &Uart_Rx_Packet.Uart_Buffer[3], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis16 };
const _Variables Var_Odczyt_Serwis14 = { 2, 8 , 1, &Uart_Rx_Packet.Uart_Buffer[2], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis15 };
const _Variables Var_Odczyt_Serwis13 = { 1, 4 , 1, &Uart_Rx_Packet.Uart_Buffer[1], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis14 };
const _Variables Var_Odczyt_Serwis12 = { 0, 0 , 1, &Uart_Rx_Packet.Uart_Buffer[0], FALSE, &Param_3_Digits, &Languages, &Var_Odczyt_Serwis13 };

const _Strings String_Odczyt_Serwis6 = { 2, 18, 0, z3, &Languages, NULL};
const _Strings String_Odczyt_Serwis5 = { 1, 16, 0, _2z, &Languages, &String_Odczyt_Serwis6};
const _Strings String_Odczyt_Serwis4 = { 0, 0, 0, Submenu_24, &Languages, &String_Odczyt_Serwis5};

const _Screen_Ptrs_Masks Screen_Odczyt_Serwisowy2 = { &String_Odczyt_Serwis4, NULL, &Var_Odczyt_Serwis12, NULL, NULL, NULL };
/*******************************************************************************
* Osczyt serwisowy (3/3) screen objects definition - SCREEN 24-3
*******************************************************************************/
const _Variables Var_Odczyt_Serwis3_12 ={ 11, 14, 3, &Controller_Variables.Controller_Vars.MSens2_Angle, FALSE, &Param_4_Digits, &Languages, NULL };
const _Variables Var_Odczyt_Serwis3_11 ={ 10, 14, 2, &Controlling_Variables.Ctrl_Vars.Angle2_Op, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_12 };
const _Variables Var_Odczyt_Serwis3_10 ={ 9, 14, 1, &Controlling_Variables.Ctrl_Vars.Angle2_Cl, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_11 };
const _Variables Var_Odczyt_Serwis3_9 = { 8, 9, 3, &Controller_Variables.Controller_Vars.MSens1_Angle, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_10 };
const _Variables Var_Odczyt_Serwis3_8 = { 7, 9, 2, &Controlling_Variables.Ctrl_Vars.Angle1_Op, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_9 };
const _Variables Var_Odczyt_Serwis3_7 = { 6, 9, 1, &Controlling_Variables.Ctrl_Vars.Angle1_Cl, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_8 };


const _Variables Var_Odczyt_Serwis3_6 = { 5, 4, 3, &Controller_Variables.Controller_Vars.MSens2_Angle, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_7 };
const _Variables Var_Odczyt_Serwis3_5 = { 4, 4, 2, &Controller_Variables.Controller_Vars.MSens2_Pulse_High, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_6 };
const _Variables Var_Odczyt_Serwis3_4 = { 3, 4, 1, &Controller_Variables.Controller_Vars.MSens2_Pulse_Low, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_5 };
const _Variables Var_Odczyt_Serwis3_3 = { 2, 0, 3, &Controller_Variables.Controller_Vars.MSens1_Angle, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_4 };
const _Variables Var_Odczyt_Serwis3_2 = { 1, 0, 2, &Controller_Variables.Controller_Vars.MSens1_Pulse_High, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_3 };
const _Variables Var_Odczyt_Serwis3_1 = { 0, 0, 1, &Controller_Variables.Controller_Vars.MSens1_Pulse_Low, FALSE, &Param_4_Digits, &Languages, &Var_Odczyt_Serwis3_2 };

const _Strings String_Odczyt_Serwis9 = { 2, 18, 0, z3, &Languages, NULL};
const _Strings String_Odczyt_Serwis8 = { 1, 16, 0, _3z, &Languages, &String_Odczyt_Serwis9};
const _Strings String_Odczyt_Serwis7 = { 0, 0, 0, Submenu_24, &Languages, &String_Odczyt_Serwis8};

const _Screen_Ptrs_Masks Screen_Odczyt_Serwisowy3 = { &String_Odczyt_Serwis7, NULL, &Var_Odczyt_Serwis3_1, NULL, NULL, NULL };

/*******************************************************************************
* Blok calkowita screen objects definition - SCREEN 25
*******************************************************************************/
const _Strings String_Blok_Calkowita1 = { 0, 1, 1, Blokada_calkowita, &Languages, NULL};

const _Screen_Ptrs_Masks Screen_Blok_Calkowita = { &String_Blok_Calkowita1, NULL, NULL, NULL, NULL, NULL };


/*******************************************************************************
* Ster blokowany screen objects definition - SCREEN 26
*******************************************************************************/
const _Strings String_Ster_Blok3 = { 2, 1, 3, Odblokuj, &Languages, NULL };
const _Strings String_Ster_Blok2 = { 1, 1, 1, Zablokowany, &Languages, &String_Ster_Blok3 };
const _Strings String_Ster_Blok1 = { 0, 1, 0, Sterownik, &Languages, &String_Ster_Blok2 };

const _Screen_Ptrs_Masks Screen_Ster_Blokowany = { &String_Ster_Blok1, NULL, NULL, NULL, NULL, NULL };

/*******************************************************************************
* Odblokuj screen objects definition - SCREEN 27
*******************************************************************************/
const _Variables Var_Odblokuj2 = { 0, 18,  3, &Service_Variables_Set.Serv_Vars.Blok_Prog_Pozostalo, FALSE, &Param_2_Digits, &Languages, NULL };
const _Variables Var_Odblokuj1 = { 0, 7,  2, &Password_Set, TRUE, &Passwd, &Languages, &Var_Odblokuj2 };

const _Strings String_Odblokuj2 = { 1, 0, 3, Ilosc_prob, &Languages, NULL};
const _Strings String_Odblokuj1 = { 0, 0, 0, Haslo_blokady, &Languages, &String_Odblokuj2};

const _Screen_Ptrs_Masks Screen_Odblokuj = { &String_Odblokuj1, NULL, &Var_Odblokuj1, NULL, NULL, NULL };

/*******************************************************************************
* Error alarm screen objects definition - SCREEN 28
*******************************************************************************/
const _Strings String_AE1 = { 0, 1, 1, Error_Text, &Languages, NULL};

const _Screen_Ptrs_Masks Screen_Alert_Error = { &String_AE1, NULL, NULL, NULL, NULL, NULL };


/*******************************************************************************
* Screen object main structure definition
*******************************************************************************/
const _Screen_Lcd Screen_Lcd[] = {
/*STANDBY*/            { Keyboard_Standby, &Screen_Standby, FALSE, 0 },
/*ENABLE*/             { Keyboard_Enable, &Screen_Enable, TRUE, 50 },
/*MENU*/               { Keyboard_Menu, &Screen_Menu1, FALSE, 0 },
/*SUBMENU1*/           { Keyboard_Submenu1, &Screen_Submenu1, FALSE, 0 },
/*SUBMENU2*/           { Keyboard_Submenu2, &Screen_Submenu2, FALSE, 0 },
/*SUBMENU2*/           { Keyboard_Submenu2, &Screen_Submenu2a, FALSE, 0 },
/*SUBMENU2*/           { Keyboard_Submenu2, &Screen_Submenu2b, FALSE, 0 },
/*SUBMENU2*/           { Keyboard_Submenu2, &Screen_Submenu2c, FALSE, 0 },

/*SUBMENU3*/           { Keyboard_Submenu3, &Screen_Submenu3, FALSE, 0 },

/*FUNKCJE1*/           { Keyboard_Funkcje1, &Screen_Funkcje1, FALSE, 0 },
/*FUNKCJE2*/           { Keyboard_Funkcje1, &Screen_Funkcje2, FALSE, 0 },
/*FUNKCJE3*/           { Keyboard_Funkcje1, &Screen_Funkcje3, FALSE, 0 },
/*FUNKCJE3*/           { Keyboard_Funkcje1, &Screen_Funkcje4, FALSE, 0 },
/*DATA_I_CZAS*/        { Keyboard_Data, &Screen_Data, FALSE, 0 },
/*LICENCJA*/           { Keyboard_Licencja, &Screen_Licencja, FALSE, 0 },
/*SUBMENU4*/           { Keyboard_Submenu4, &Screen_Submenu4, FALSE, 0 },
/*UST_FABRYCZNE*/      { Keyboard_Fabryczne, &Screen_Fabryczne, FALSE, 0 },
/*KONTAKT*/            { Keyboard_Kontakt, &Screen_Kontakt1, FALSE, 0 },
/*INFO*/               { Keyboard_Info, &Screen_Info, FALSE, 0 },

/*HASLO*/              { Keyboard_Haslo, &Screen_Haslo, FALSE, 0 },

/*BRAMA_MOTOR1*/       { Keyboard_Brama_Motor, &Screen_Brama_Motor1, FALSE, 0 },
/*PRAD1*/              { Keyboard_Prad, &Screen_Prad1, TRUE, 30 },
/*LISTWY1*/            { Keyboard_Listwy, &Screen_Listwy1, FALSE, 0 },
/*LISTWY2*/            { Keyboard_Listwy, &Screen_Listwy2, FALSE, 0 },
/*USTAW_WEJSC1*/       { Keyboard_Ustaw_Wejsc, &Screen_Ustaw_Wejsc1 , FALSE, 0 },
/*USTAW_WEJSC2*/       { Keyboard_Ustaw_Wejsc, &Screen_Ustaw_Wejsc2 , FALSE, 0 },
/*USTAW_WEJSC3*/       { Keyboard_Ustaw_Wejsc, &Screen_Ustaw_Wejsc3 , FALSE, 0 },
/*USTAW_WEJSC4*/       { Keyboard_Ustaw_Wejsc, &Screen_Ustaw_Wejsc4 , FALSE, 0 },
/*WE_STER1*/           { Keyboard_Ustaw_Wejsc_Ster, &Screen_Ustaw_Wejsc_Ster1 , FALSE, 0 },
/*WE_STER1*/           { Keyboard_Ustaw_Wejsc_Ster, &Screen_Ustaw_Wejsc_Ster2 , FALSE, 0 },
/*WY_PRZ1*/            { Keyboard_Ustaw_Wyjsc_Przek, &Screen_Ustaw_Wyjsc_Przek1 , FALSE, 0 },
/*WY_PRZ2*/            { Keyboard_Ustaw_Wyjsc_Przek, &Screen_Ustaw_Wyjsc_Przek2 , FALSE, 0 },
/*CZUJNIKI_MENU*/      { Keyboard_Czujniki_Menu, &Screen_Czujniki_Menu, FALSE, 0 },
/*CZUJNIKI1*/          { Keyboard_Czujniki1, &Screen_Czujniki1, FALSE, 0 },
/*CZUJNIKI2*/          { Keyboard_Czujniki2, &Screen_Czujniki2, FALSE, 0 },

/*WYB_JEZ*/            { Keyboard_Jezyk, &Screen_Jezyk, FALSE, 0 },
/*UST_HASEL*/          { Keyboard_Zmiana_Hasel, &Screen_Zmiana_Hasel, FALSE, 0 },
/*UST_BLOKADY*/        { Keyboard_Ust_Blokady, &Screen_Ust_Blokady, FALSE, 0 },
/*ZER_LICZNIKI*/       { Keyboard_Zer_Licznikow, &Screen_Zer_Licznikow, FALSE, 0 },
/*KAL_RTC*/            { Keyboard_RTC, &Screen_RTC, FALSE, 0 },

/*LICZNIK_PRACY*/      { Keyboard_Licznik_Pracy, &Screen_Licznik_Pracy, FALSE, 0 },
/*PROG_TESTOWY*/       { Keyboard_Prog_Testowy, &Screen_Prog_Testowy, FALSE, 0 },
/*TEST_WEWY*/          { Keyboard_Test_WeWy, &Screen_Test_WeWy, TRUE, 50 },

/*UST.SERWISOWE1*/     { Keyboard_Ust_Serwisowe, &Screen_Ust_Serwisowe1, FALSE, 0 },
/*UST.SERWISOWE2*/     { Keyboard_Ust_Serwisowe, &Screen_Ust_Serwisowe2, FALSE, 0 },
/*UST.SERWISOWE3*/     { Keyboard_Ust_Serwisowe, &Screen_Ust_Serwisowe3, FALSE, 0 },
/*UST.SERWISOWE4*/     { Keyboard_Ust_Serwisowe, &Screen_Ust_Serwisowe4, FALSE, 0 },

/*ODCZ.SERWISOWY1*/    { Keyboard_Odczyt_Serwisowy, &Screen_Odczyt_Serwisowy1, TRUE, 50 },
/*ODCZ.SERWISOWY2*/    { Keyboard_Odczyt_Serwisowy, &Screen_Odczyt_Serwisowy2, TRUE, 50 },
/*ODCZ.SERWISOWY3*/    { Keyboard_Odczyt_Serwisowy, &Screen_Odczyt_Serwisowy3, TRUE, 50 },

/*BLOK_CALKOWITA*/     { NULL, &Screen_Blok_Calkowita, FALSE, 0 },
/*STEROWNIK_BLOKOWANY*/{ Keyboard_Ster_Blokowany, &Screen_Ster_Blokowany, FALSE, 0 },
/*ODBLOKUJ*/           { Keyboard_Odblokuj, &Screen_Odblokuj, FALSE, 0 },
/*ALERT_ERROR*/        { Keyboard_Alert_Error, &Screen_Alert_Error, FALSE, 0 },




};

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
* Function Name  : Display_On_Screen
* Description    : Displaying data on LCD screen - strings/variables/images/Menu list
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Display_On_Screen ( void )
{
    static bool Var_Underline;
    static volatile uint8_t i;
    static int32_t Digit_Conv;
    static uint8_t Variable_Tab[11];
    static uint32_t Mask_Shift_Reg;
    const  uint32_t Mask_Shift_Bit = 0x00000001;

    _String_Number String_Number;

    const _Strings * Str_Ptr;
    const _Variables * Var_Ptr;

    Str_Ptr = Screen_Lcd[Screen_Number].Screen_Objects->String_Ptr;
    Var_Ptr = Screen_Lcd[Screen_Number].Screen_Objects->Variable_Ptr;

/******************************Displaying strings*****************************/
    if ( Reload_Screen == TRUE )
    {
        Lcd_Clear_Buffer ( &Lcd_Buffer );

        if ( Str_Ptr != NULL )
        {
            if ( Screen_Lcd[Screen_Number].Screen_Objects->String_Mask == NULL )
            {
                Mask_Shift_Reg = 0xffffffff;
            }
            else
            {
                Mask_Shift_Reg = *Screen_Lcd[Screen_Number].Screen_Objects->String_Mask;
            }

            while ( Str_Ptr != NULL )
            {
                Lcd_Set_Address (Str_Ptr->String_X_Pos,Str_Ptr->String_Y_Pos);
                String_Number = Str_Ptr->String_Num;
 
                if ( Mask_Shift_Reg & ( Mask_Shift_Bit<<Str_Ptr->String_Index ) )
                {
                    Lcd_Write_Buffer ( &Lcd_Buffer, *(String_Number+Str_Ptr->Languages_Ptr->Languages_Tab[Language_Num]) );
                }

                Str_Ptr = Str_Ptr->Next_String;
            };
        }
/******************************************************************************/

/****************************Displaying menu list******************************/

        if ( Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr != NULL )
        {
            if ( Screen_Lcd[Screen_Number].Screen_Objects->Menu_Mask == NULL )
            {
                Mask_Shift_Reg = 0xffffffff;
            }
            else
            {
                Mask_Shift_Reg = *Screen_Lcd[Screen_Number].Screen_Objects->Menu_Mask;
            }

            for ( i = 0; i < Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Lines_On_Screen; i++ )
            {
                String_Number = Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Menu_String_Num[(i+Menu_Keys.First_On_Screen)];

                Lcd_Set_Address( Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Menu_X_Pos, Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Menu_Y_Pos + i);

                if ( Mask_Shift_Reg & ( Mask_Shift_Bit<<i ) )
                {
                    Lcd_Write_Buffer ( &Lcd_Buffer, *(String_Number+Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Languages_Ptr->Languages_Tab[Language_Num]) );
                }
            }
            String_Number = St_R;
            Lcd_Set_Address ( 0, Menu_Keys.Active_On_Screen+1);
            Lcd_Write_Buffer ( &Lcd_Buffer, *(String_Number+Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Languages_Ptr->Languages_Tab[Language_Num]) );
            String_Number = St_L;
            Lcd_Set_Address ( 19, Menu_Keys.Active_On_Screen+1);
            Lcd_Write_Buffer ( &Lcd_Buffer, *(String_Number+Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Languages_Ptr->Languages_Tab[Language_Num]) );

        }

/******************************************************************************/

/****************************Displaying Variables******************************/
        if ( Var_Ptr != NULL )
        {
            if ( Screen_Lcd[Screen_Number].Screen_Objects->Variable_Mask == NULL )
            {
                Mask_Shift_Reg = 0xffffffff;
            }
            else
            {
                Mask_Shift_Reg = *Screen_Lcd[Screen_Number].Screen_Objects->Variable_Mask;
            }
 
            while ( Var_Ptr != NULL )
            {
                Lcd_Set_Address ( Var_Ptr->Variable_X_Pos, Var_Ptr->Variable_Y_Pos);
           
                if ( Var_Ptr->Var_Param_Ptr->Variable_Type == TEXT_VAR )
                {
                    if ( String_Number > STRINGS_COUNT )
                    {
                        String_Number = STRINGS_COUNT;  
                    }                
                    String_Number = Var_Ptr->Var_Param_Ptr->Variable_String_Num[*(uint8_t *)(Var_Ptr->Var_Ptr)];
                    Lcd_Write_Buffer ( &Lcd_Buffer, *(String_Number+Var_Ptr->Languages_Ptr->Languages_Tab[Language_Num]) );
 
                }
                else
                {
                    if ( Mask_Shift_Reg & ( Mask_Shift_Bit<<Var_Ptr->Variable_Index ) )
                    {
                        if ( Var_Ptr->Var_Param_Ptr->Variable_Type == DIGITS_VAR )
                        {
                            switch ( Var_Ptr->Var_Param_Ptr->Variable_Size )
                            {
                            case VAR_U8:
                                Digit_Conv = *(uint8_t*)Var_Ptr->Var_Ptr;//Bin2String ( *(uint8_t*)Var_Ptr->Var_Ptr, Variable_Tab, Var_Ptr->Var_Param_Ptr->Variable_Digits_Count, Var_Ptr->Var_Param_Ptr->Variable_Resolution, Var_Ptr->Var_Param_Ptr->Variable_Hide_Zeros );
                            break;

                            case VAR_U16:
                                Digit_Conv = *(uint16_t*)Var_Ptr->Var_Ptr;//Bin2String ( *(uint16_t*)Var_Ptr->Var_Ptr, Variable_Tab, Var_Ptr->Var_Param_Ptr->Variable_Digits_Count, Var_Ptr->Var_Param_Ptr->Variable_Resolution, Var_Ptr->Var_Param_Ptr->Variable_Hide_Zeros );
                            break;

                            case VAR_U32:
                                Digit_Conv = *(uint32_t*)Var_Ptr->Var_Ptr;//Bin2String ( *(uint32_t*)Var_Ptr->Var_Ptr, Variable_Tab, Var_Ptr->Var_Param_Ptr->Variable_Digits_Count, Var_Ptr->Var_Param_Ptr->Variable_Resolution, Var_Ptr->Var_Param_Ptr->Variable_Hide_Zeros );
                            break;
  
                            case VAR_S8:
                                Digit_Conv = *(int8_t*)Var_Ptr->Var_Ptr;//Bin2String ( *(int8_t*)Var_Ptr->Var_Ptr, Variable_Tab, Var_Ptr->Var_Param_Ptr->Variable_Digits_Count, Var_Ptr->Var_Param_Ptr->Variable_Resolution, Var_Ptr->Var_Param_Ptr->Variable_Hide_Zeros );
                            break;

                            case VAR_S16:
                                Digit_Conv = *(int16_t*)Var_Ptr->Var_Ptr;//Bin2String ( *(int16_t*)Var_Ptr->Var_Ptr, Variable_Tab, Var_Ptr->Var_Param_Ptr->Variable_Digits_Count, Var_Ptr->Var_Param_Ptr->Variable_Resolution, Var_Ptr->Var_Param_Ptr->Variable_Hide_Zeros );
                            break;

                            case VAR_S32:
                                Digit_Conv = *(int32_t*)Var_Ptr->Var_Ptr;//Bin2String ( *(int32_t*)Var_Ptr->Var_Ptr, Variable_Tab, Var_Ptr->Var_Param_Ptr->Variable_Digits_Count, Var_Ptr->Var_Param_Ptr->Variable_Resolution, Var_Ptr->Var_Param_Ptr->Variable_Hide_Zeros );
                            break;
                            }

                            Bin2String ( Digit_Conv, Variable_Tab, Var_Ptr->Var_Param_Ptr->Variable_Digits_Count, Var_Ptr->Var_Param_Ptr->Variable_Resolution, Var_Ptr->Var_Param_Ptr->Variable_Hide_Zeros );
                        }
                    
                        Lcd_Write_Buffer ( &Lcd_Buffer, Variable_Tab);
                    }
                }       

                if ( Variable_Editing_Ptr != NULL )
                {
                   String_Number = St_R;
                   Lcd_Set_Address ( (Variable_Editing_Ptr->Variable_X_Pos)-1, Variable_Editing_Ptr->Variable_Y_Pos);
                   Lcd_Write_Buffer ( &Lcd_Buffer, *(String_Number+Var_Ptr->Languages_Ptr->Languages_Tab[Language_Num]) );

                   i = Variable_Editing_Ptr->Variable_X_Pos+(Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count-1)-Count_Add;

                   if ( Variable_Editing_Ptr->Var_Param_Ptr->Variable_Resolution != 0 )
                   {
                       if ( Count_Add < Variable_Editing_Ptr->Var_Param_Ptr->Variable_Resolution )
                       {
                           i++;
                       }    
                   }
               
                   Object_Pos_Temp.Object_X_Pos = i;
                   Object_Pos_Temp.Object_Y_Pos = Variable_Editing_Ptr->Variable_Y_Pos;
                   Var_Underline = TRUE;    
                }
                else
                {
                    Var_Underline = FALSE;
                }

                Var_Ptr = Var_Ptr->Next_Variable;
            };
        }
/******************************************************************************/
        Reload_Screen = FALSE;

        Enable_Lcd_Write = TRUE;
        Lcd_Write_Strobe = FALSE;
        Lcd_Write_Ptr = 0;
    }

    if ( Enable_Lcd_Write == TRUE )
    {
        Lcd_Load_Buffer ( &Lcd_Buffer );           
    }

    if ( Var_Underline == TRUE && Enable_Lcd_Write == FALSE )
    {
        Lcd_Cmd(Lcd_Address_Base[Object_Pos_Temp.Object_Y_Pos]+Object_Pos_Temp.Object_X_Pos);    

        Lcd_Cmd ( 0x0E);  
        Var_Underline = FALSE;    
    }
}

/*******************************************************************************
* Function Name  : Bin2String
* Description    : Converting binary count to table of strings
* Input          : Source_Count - Pointer to binary count, Result - pointer to table of result, Resolution - digits after dot, Digit_Count - number of counts to convert, Zero_Blank - dont display zero at front of digit
* Output         : None
* Return         : None
*******************************************************************************/
void Bin2String ( int32_t Source_Count, uint8_t * Result, uint8_t Digits_Count, uint8_t Resolution, uint8_t Zero_Blank )
{
    static uint8_t i;
    static uint8_t Result_Table[9];   
    static uint8_t Zero_Ptr;
    static uint32_t Divider;

    Divider = 100000000;
    Zero_Ptr = 0;
    
    if ( Source_Count < 0 )
    {
        Source_Count *= (-1);
        *Result++ = '-';
    }

    if ( Digits_Count > 9 )
    {
        Digits_Count = 9;
    }

    if ( Resolution > 3 )
    {
        Digits_Count = 3;
    }

    for ( i=0; i<9; i++ )
    {
        Result_Table[i] = (uint8_t)((Source_Count / Divider) | 0x30);
        Source_Count %= Divider;
        Divider /= 10;
    }

    if ( Zero_Blank == 0 )
    {
        for ( i=(9-Digits_Count); i<9; i++ )
        {
            *Result++ = Result_Table[i];
            if ( Resolution != 0 && i == (8-Resolution) )
            {
                *Result++ = '.';
            }          
        }
    }
    else
    {
        for ( i=0; i<(8-Resolution); i++ )
        {
            if ( Result_Table[i] == '0' )
            {
//Dla spacji
                Result_Table[i] = ' ';
//koniec dla spacji
                Zero_Ptr++;
            }
            else
                break;
        }
//Dla spacji
        for ( i=(9-Digits_Count); i<9; i++ )
//Koniec dla spacji
//        for ( i=Zero_Ptr; i<9; i++ )
        {
            *Result++ = Result_Table[i];
            if ( Resolution != 0 && i == (8-Resolution) )
            {
                *Result++ = '.';
            }          
        }
    }

    *Result = 0;
}
/*******************************************************************************
* Function Name  : Menu_Keyboard
* Description    : Handling UP and DOWN keys of keyborad
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Menu_Keyboard ( void )
{

        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_UP:
                if ( (Menu_Keys.Active_String+1) == Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Total_Lines )
                {
                    Menu_Keys.First_On_Screen = 0;
                    Menu_Keys.Active_String = 0;
                    Menu_Keys.Active_On_Screen = 0;
                }
                else
                {
                    Menu_Keys.Active_String++;
                    if ( (Menu_Keys.Active_On_Screen+1) == Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Lines_On_Screen )
                    {
                        Menu_Keys.First_On_Screen++;
                    }
                    else
                    {
                        Menu_Keys.Active_On_Screen++;
                    }
                }
                Reload_Screen = TRUE;

            break;

            case KEY_DOWN:
                if ( Menu_Keys.Active_String == 0 )               {
                    Menu_Keys.First_On_Screen = Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Total_Lines - Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Lines_On_Screen;
                    Menu_Keys.Active_String = Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Total_Lines-1;
                    Menu_Keys.Active_On_Screen = Screen_Lcd[Screen_Number].Screen_Objects->Menu_Ptr->Lines_On_Screen-1;
                }
                else
                {
                    Menu_Keys.Active_String--;
                    if ( Menu_Keys.Active_On_Screen == 0 )
                    {
                        Menu_Keys.First_On_Screen--;
                    }
                    else
                    {
                        Menu_Keys.Active_On_Screen--;
                    }
                }
                Reload_Screen = TRUE;
            break;
        }

}

/*******************************************************************************
* Function Name  : Keyboard_Edit_Variable
* Description    : Keys handling for variables edition
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Edit_Variable ( void )
{
    volatile static int32_t Edit_Variable;
    static int32_t Edit_Variable_Min;
    static int32_t Edit_Variable_Max;

    Edit_Variable_Min = Variable_Editing_Ptr->Var_Param_Ptr->Ranges->Var_min;
    Edit_Variable_Max = Variable_Editing_Ptr->Var_Param_Ptr->Ranges->Var_max;

    switch ( Variable_Editing_Ptr->Var_Param_Ptr->Variable_Size )
    {
        case VAR_U8:
            Edit_Variable = *(uint8_t*)(Variable_Editing_Ptr->Var_Ptr);
        break;

        case VAR_U16:
            Edit_Variable = *(uint16_t*)(Variable_Editing_Ptr->Var_Ptr);
        break;
 
        case VAR_U32:
            Edit_Variable = *(uint32_t*)(Variable_Editing_Ptr->Var_Ptr);
        break;

        case VAR_S8:
            Edit_Variable = *(int8_t*)(Variable_Editing_Ptr->Var_Ptr);
        break;

        case VAR_S16:
            Edit_Variable = *(int16_t*)(Variable_Editing_Ptr->Var_Ptr);
        break;

        case VAR_S32:
            Edit_Variable = *(int32_t*)(Variable_Editing_Ptr->Var_Ptr);
        break;
    }
    switch ( Keyboard.Keyboard_Memory )
    {
        case KEY_RIGHT:
            if ( (Edit_Variable_Max - Edit_Variable) < Add_Tab[Count_Add] )
            {
                Edit_Variable = Edit_Variable_Min;
            }
            else
            {
                Edit_Variable += Add_Tab[Count_Add];
            }
            Reload_Screen = TRUE;
        break;

        case KEY_LEFT:
            if ( (Edit_Variable - Edit_Variable_Min) < Add_Tab[Count_Add] )
            {
                Edit_Variable = Edit_Variable_Max;
            }
            else
            {
                Edit_Variable -= Add_Tab[Count_Add];
            }
            Reload_Screen = TRUE;
        break;
    }

    switch ( Variable_Editing_Ptr->Var_Param_Ptr->Variable_Size )
    {
        case VAR_U8:
            *(uint8_t*)(Variable_Editing_Ptr->Var_Ptr) = Edit_Variable;
        break;

        case VAR_U16:
            *(uint16_t*)(Variable_Editing_Ptr->Var_Ptr) = Edit_Variable;
        break;

        case VAR_U32:
            *(uint32_t*)(Variable_Editing_Ptr->Var_Ptr) = Edit_Variable;
        break;

        case VAR_S8:
            *(int8_t*)(Variable_Editing_Ptr->Var_Ptr) = Edit_Variable;
        break;

        case VAR_S16:
            *(int16_t*)(Variable_Editing_Ptr->Var_Ptr) = Edit_Variable;
        break;

        case VAR_S32:
            *(int32_t*)(Variable_Editing_Ptr->Var_Ptr) = Edit_Variable;
        break;
    }

}

/*******************************************************************************
* Function Name  : Init_Gui
* Description    : General user interface initialization
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Gui_Init ( void )
{
    Read_Settings();
    Update_Lock_Counter ( Controller_Variables.Controller_Vars.Lock_Counter );
    Lock_Init();
    Reload_Screen = TRUE;
}



/*******************************************************************************
* Function Name  : First_Editable_Variable
* Description    : Setting a pointer on first editable variable in variables list
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void First_Editable_Variable ( void )
{
    Variable_Editing_Ptr = Screen_Lcd[Screen_Number].Screen_Objects->Variable_Ptr;

    while ( Variable_Editing_Ptr != NULL )
    {

        if ( Variable_Editing_Ptr->Edit_Var == TRUE )
        {
            break;
        }
        else
        {
            Variable_Editing_Ptr = Variable_Editing_Ptr->Next_Variable;
        }
    }
}
/*******************************************************************************
* Function Name  : Next_Editable_Variable
* Description    : Setting a pointer on next editable variable in variables list
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static uint8_t Next_Editable_Variable ( void )
{
//    Variable_Editing_Ptr = Screen_Lcd[Screen_Number].Screen_Objects->Variable_Ptr->Next_Variable;

    Variable_Editing_Ptr = Variable_Editing_Ptr->Next_Variable;

    while ( Variable_Editing_Ptr != NULL )
    {
        if ( Variable_Editing_Ptr->Edit_Var == TRUE )
        {
            return TRUE;
        }
        else
        {
            Variable_Editing_Ptr = Variable_Editing_Ptr->Next_Variable;
        }
    }
    return FALSE;
}

/*******************************************************************************
* Function Name  : Gui
* Description    : General user interface handling - screen keys etc.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Gui ( void )
{

/**************************************************************/
/**************************************************************/
//Lock Handling function
    Lock_Handling();

/**************************************************************/
/**************************************************************/
//Keyboard handling function call
    if ( Screen_Lcd[Screen_Number].Keybord_Ptr != NULL )
    {
        (*Screen_Lcd[Screen_Number].Keybord_Ptr)();
    }
/**************************************************************/
/**************************************************************/
//One second pulse timer reload screen in selected screen
	if ( System_Timer_Check ( &Screen_Reload_Timer.Timer, T_10msec ) == TRUE )
	{
        SCREEN_PULSE ^= 1;
    
        if ( Screen_Number == STANDBY_SCR || Screen_Number == CONTROLLER_ON || Screen_Number == ODCZYT_SERWISOWY1 || Screen_Number == ODCZYT_SERWISOWY2 || Screen_Number == ODCZYT_SERWISOWY3 || Screen_Number == TEST_WEWY || Screen_Number == PRAD1 || Screen_Number == CZUJNIKI1 )
        {
            Reload_Screen = TRUE;
        }
		System_Timer_Setting ( &Screen_Reload_Timer.Timer, SCREEN_RELOAD_TIME, T_10msec );
	}
/**************************************************************/
/**************************************************************/
//LICENCE STRING MASK HANDLING
    if ( Service_Variables.Serv_Vars.Blokada == 0 )
    {
        String_Lic_Mask = STRING_LICENCE_LOCKED;
        Var_Lic_Mask = VAR_LICENCE_LOCKED;
    }
    else
    {
        String_Lic_Mask = STRING_LICENCE_UNLOCKED;
        Var_Lic_Mask = VAR_LICENCE_UNLOCKED; 
    }
/**************************************************************/
/**************************************************************/
//ENABLE SCREEN STRING MASK HANDLING
    Enable_String_Mask = ENABLE_STRING;

    Inputs_Error_Mask |= Controller_Variables.Controller_Vars.Inputs_Error;

    if ( Inputs_Error_Mask & INPUT_STOP )
    {
        if ( SCREEN_PULSE == 1 )
            Enable_String_Mask &= ~ENABLE_STRING_STOP;
        else
            Enable_String_Mask |= ENABLE_STRING_STOP;     
    }
    else
    {
        Enable_String_Mask |= ENABLE_STRING_STOP;     
    }




    if ( Inputs_Error_Mask & INPUT_PHOTO1 )
    {
        if ( SCREEN_PULSE == 1 )
            Enable_String_Mask &= ~ENABLE_STRING_PHOTO;
        else
            Enable_String_Mask |= ENABLE_STRING_PHOTO;
    }
    else
    {
        Enable_String_Mask |= ENABLE_STRING_PHOTO;     
    } 



    if ( Service_Variables.Serv_Vars.In7_Fun != 0 ) //Not disabled
    {
        if ( Inputs_Error_Mask & INPUT_SE1 )
        {
            if ( SCREEN_PULSE == 1 )
                Enable_String_Mask &= ~ENABLE_STRING_SE1;
            else
                Enable_String_Mask |= ENABLE_STRING_SE1;
        }
        else
        {
            Enable_String_Mask |= ENABLE_STRING_SE1;     
        } 
    }
    else
    {
        Enable_String_Mask &= ~ENABLE_STRING_SE1;        
    }

    if ( Service_Variables.Serv_Vars.In8_Fun != 0 ) //Not disabled
    {
        if ( Inputs_Error_Mask & INPUT_SE2 )
        {
            if ( SCREEN_PULSE == 1 )
                Enable_String_Mask &= ~ENABLE_STRING_SE2;
            else
                Enable_String_Mask |= ENABLE_STRING_SE2;
        }
        else
        {
            Enable_String_Mask |= ENABLE_STRING_SE2;     
        }
    }
    else
    {
        Enable_String_Mask &= ~ENABLE_STRING_SE2;        
    }

    if ( Service_Variables.Serv_Vars.In9_Fun != 0 ) //Not disabled
    {
        if ( Inputs_Error_Mask & INPUT_SE3 )
        {
            if ( SCREEN_PULSE == 1 )
                Enable_String_Mask &= ~ENABLE_STRING_SE3;
            else
                Enable_String_Mask |= ENABLE_STRING_SE3;
        }
        else
        {
            Enable_String_Mask |= ENABLE_STRING_SE3;     
        }
    }
    else
    {
        Enable_String_Mask &= ~ENABLE_STRING_SE3;        
    }

    if ( Service_Variables.Serv_Vars.In10_Fun != 0 ) //Not disabled
    {
        if ( Inputs_Error_Mask & INPUT_SE4 )
        {
            if ( SCREEN_PULSE == 1 )
                Enable_String_Mask &= ~ENABLE_STRING_SE4;
            else
                Enable_String_Mask |= ENABLE_STRING_SE4;
        }
        else
        {
            Enable_String_Mask |= ENABLE_STRING_SE4;     
        }
    }
    else
    {
        Enable_String_Mask &= ~ENABLE_STRING_SE4;        
    }


    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Inverters
    {
        if ( Inputs_Error_Mask & F1_DISCONNECTED )
        {
            if ( SCREEN_PULSE == 1 )
                Enable_String_Mask &= ~ENABLE_STRING_F1;
            else
                Enable_String_Mask |= ENABLE_STRING_F1;
        }
        else
        {
            Enable_String_Mask |= ENABLE_STRING_F1;     
        } 
    }
    else
    {
        Enable_String_Mask &= ~ENABLE_STRING_F1;    
    }

    if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 0 ) // Two wings gate
    {   
        if ( Inputs_Error_Mask & F2_DISCONNECTED )
        {
            if ( SCREEN_PULSE == 1 )
                Enable_String_Mask &= ~ENABLE_STRING_F2;
            else
                Enable_String_Mask |= ENABLE_STRING_F2;
        }
        else
        {
            Enable_String_Mask |= ENABLE_STRING_F2;     
        } 
    }
    else if ( Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 1  || // One wing gate
              Controlling_Variables.Ctrl_Vars.Fast_Gate_Type == 2  ) // sliding

    {
        Enable_String_Mask &= ~ENABLE_STRING_F2;
    }
    
    if ( Inputs_Error_Mask & CURRENT_OV1 )
    {
        if ( SCREEN_PULSE == 1 )
            Enable_String_Mask &= ~ENABLE_STRING_COV1;
        else
            Enable_String_Mask |= ENABLE_STRING_COV1;
    }
    else
    {
        Enable_String_Mask |= ENABLE_STRING_COV1;     
    } 
 
    if ( Inputs_Error_Mask & CURRENT_OV2 )
    {
        if ( SCREEN_PULSE == 1 )
            Enable_String_Mask &= ~ENABLE_STRING_COV2;
        else
            Enable_String_Mask |= ENABLE_STRING_COV2;
    }
    else
    {
        Enable_String_Mask |= ENABLE_STRING_COV2;     
    }

/**************************************************************/
/**************************************************************/
//Manual test string mask
    Manual_Test_Mask = 0x00000100 | (uint32_t)Inputs_Level_Test;

/**************************************************************/
/**************************************************************/
/**************************************************************/

/**************************************************************/
/**************************************************************/
/**************************************************************/
//Display on screen function

    Display_On_Screen();
/**************************************************************/
/**************************************************************/
/**************************************************************/
}

/*******************************************************************************
* Function Name  : Keyboard_Standby
* Description    : Keyboard handling in STANDBY screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Standby ( void )
{
        static uint8_t i;

    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ENTER:
                Screen_Number = CONTROLLER_ON;
                Reload_Screen = TRUE;         
            break; 
                       
            default:
            break;
            }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Enable
* Description    : Keyboard handling in ENABLE screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Enable ( void )
{

    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Screen_Number = STANDBY_SCR;
                    Reload_Screen = TRUE;
            break;

            case KEY_UP:
                Inputs_Error_Mask = 0;
            break;
  
            case KEY_DOWN:
                Inputs_Error_Mask = 0;
            break;
            
            case KEY_ENTER:
                    Menu_Keys.First_On_Screen = 0;
                    Menu_Keys.Active_String = 0;
                    Menu_Keys.Active_On_Screen = 0;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            break;

            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Menu
* Description    : Keyboard handling in MENU screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Menu ( void )
{
    _Screen_Number Next_Screen[] = {
        SUBMENU1,
        SUBMENU2,
        SUBMENU3,
        FUNKCJE_DODATKOWE1,
        DATA_I_CZAS,
        SUBMENU4,
        SUBMENU4,
        SUBMENU4,
        HASLO,
        KONTAKT,
        INFO,
        LICENCJA,
    };

    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                Variable_Editing_Ptr = NULL;
                Screen_Number = CONTROLLER_ON;
                Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                Menu_Backup_Keys = Menu_Keys;
                Menu_Backup_Keys_Set = Menu_Keys;
                
if (
Menu_Keys.Active_String == 0 ||    
Menu_Keys.Active_String == 1 ||
Menu_Keys.Active_String == 2 ||
Menu_Keys.Active_String == 4 ||
Menu_Keys.Active_String == 5 ||
Menu_Keys.Active_String == 8 ||
Menu_Keys.Active_String == 9 ||
Menu_Keys.Active_String == 10 ||
Menu_Keys.Active_String == 11 )
{
                Screen_Number = Next_Screen[Menu_Keys.Active_String];

                if ( Screen_Number == SUBMENU2 )
                {
                    Count_Add = 0;
                    First_Editable_Variable();
                }
            
                if ( Screen_Number == DATA_I_CZAS )
                {
                    Time_Set = Time;
                    Date_Set = Date;
                    Count_Add = 0;
                    First_Editable_Variable();
                }
    
                if ( Screen_Number == FUNKCJE_DODATKOWE1 )
                {
                    Count_Add = 0;
                    First_Editable_Variable();
                }
            
                if ( Screen_Number == SUBMENU1 || Screen_Number == SUBMENU2 || Screen_Number == SUBMENU3 || Screen_Number == SUBMENU4 )
                {
                    Menu_Keys.First_On_Screen = 0;
                    Menu_Keys.Active_String = 0;
                    Menu_Keys.Active_On_Screen = 0;    
                }
            
                if ( Screen_Number == HASLO )
                {
                   Password_Set = 0;
                   Count_Add = 0;
                   First_Editable_Variable();
                   Screen_Before_Password = MENU;
                   Screen_After_Password = UST_FABRYCZNE;
                }
}            
                Reload_Screen = TRUE;  

            break;
            
            default:
                Menu_Keyboard();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Data
* Description    : Setting the date and time
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Data ( void )
{

    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Write_Date ( &Date_Set );
                    Update_Time ( &Time_Set );
                    Menu_Keys = Menu_Backup_Keys;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
/*
                   Count_Add = 0;
                   if ( Next_Editable_Variable() == FALSE )
                   {
                        First_Editable_Variable();
                   }
                   Reload_Screen = TRUE;
*/
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Param
* Description    : Parameters screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Submenu1 ( void )
{
    _Screen_Number Next_Param_Screen[] = {
        HASLO,
        PRAD1,//HASLO,
        HASLO,
        HASLO,
        HASLO,
        HASLO,
        CZUJNIKI_MENU,
    };

    _Screen_Number After_Pass_Screen[] = {
        BRAMA_MOTOR1,
        PRAD1,
        LISTWY1,
        USTAW_WEWY1,
        WE_STER1,
        WY_PRZEK1,
        CZUJNIKI_MENU,

    };

    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                Variable_Editing_Ptr = NULL;
                Menu_Keys = Menu_Backup_Keys;
                Screen_Number = MENU;
                Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                Edit_Parameter_Counter = 0;
                Menu_Backup_Keys_Set = Menu_Keys;
                Menu_Backup_Keys_Sensors = Menu_Keys;
            
                Screen_Number = Next_Param_Screen[Menu_Keys.Active_String];

                if ( Screen_Number == HASLO )
                {
                    Password_Set = 0;
                }

                if ( Screen_Number == CZUJNIKI_MENU )
                {
                    Menu_Keys.First_On_Screen = 0;
                    Menu_Keys.Active_String = 0;
                    Menu_Keys.Active_On_Screen = 0;    
                }
            
                Screen_Before_Password = SUBMENU1;
                Screen_After_Password = After_Pass_Screen[Menu_Keys.Active_String];
                Count_Add = 0;
                First_Editable_Variable();
                Reload_Screen = TRUE;
            break;

            default:
                Menu_Keyboard();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_gate_PArameters
* Description    : gate parameters settings
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Submenu2 ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            
                    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                        Machine_State = INVERTER_PROG;
                    else // 24V sliding gate
                        Machine_State = WG_POWER_ON;
                    
                     WG_TIMER_FLAG = FALSE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

                      case KEY_ENTER:
                   if ( ++Screen_Number > SUBMENU2c )
                   {
                       Screen_Number = SUBMENU2;
                   }
                   First_Editable_Variable();
                   Reload_Screen = TRUE;
            break;
               
            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}


/*******************************************************************************
* Function Name  : Keyboard_Ust
* Description    : Settings screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Submenu3 ( void )
{
    _Screen_Number Next_Set_Screen[] = {
        WYB_JEZ,
        HASLO,
        HASLO,
        HASLO, 
        HASLO,    
    };

    _Screen_Number After_Pass_Screen[] = {
        WYB_JEZ,
        UST_HASEL,
        UST_BLOKADY,
        KAL_RTC, 
        ZER_LICZNIKI,
    };



    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                   Menu_Backup_Keys_Set = Menu_Keys;
                   Screen_Number = Next_Set_Screen[Menu_Keys.Active_String];
            
                   if ( Screen_Number == HASLO )
                   {
                       Password_Set = 0;
                   }
            
                   Screen_Before_Password = SUBMENU3;
                   Screen_After_Password = After_Pass_Screen[Menu_Keys.Active_String];
                   Reload_Screen = TRUE;
                   Count_Add = 0;
                   First_Editable_Variable();
            
                    if ( Screen_After_Password == UST_BLOKADY )
                    {
                        Service_Variables_Set.Serv_Vars.Blokada_rok = Date.Date_Vars.Year;
                        Service_Variables_Set.Serv_Vars.Blokada_miesiac = Date.Date_Vars.Month;
                        Service_Variables_Set.Serv_Vars.Blokada_dzien = Date.Date_Vars.Day;
                    }
            break;

            default:
                   Menu_Keyboard();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}


/*******************************************************************************
* Function Name  : Keyboard_Functions1
* Description    : Parameters screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Funkcje1 ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    WG_TIMER_FLAG = FALSE;
                    
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            
                    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                        Machine_State = INVERTER_PROG;
                    else // 24V sliding gate
                        Machine_State = WG_POWER_ON;
            break;
/*
            case KEY_ENTER:
                   if ( ++Screen_Number > FUNKCJE_DODATKOWE4 )
                   {
                       Screen_Number = FUNKCJE_DODATKOWE1;
                   }
                   First_Editable_Variable();
                   Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;
*/
            default:
//                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}


/*******************************************************************************
* Function Name  : Keyboard_Lic
* Description    : Licence screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Licencja ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            
                    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                        Machine_State = INVERTER_PROG;
                    else // 24V sliding gate
                        Machine_State = WG_POWER_ON;
                    
                    WG_TIMER_FLAG = FALSE;
            break;

            case KEY_ENTER:
                    if ( Service_Variables.Serv_Vars.Blokada == 0 )
                    {
                        Screen_Number = ODBLOKUJ;
                        Count_Add = 0;
                        Screen_After_Password = CONTROLLER_ON;
                        First_Editable_Variable();
                        Reload_Screen = TRUE;
                    }
            break;

            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Submenu3
* Description    : Test screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Submenu4 ( void )
{
    _Screen_Number Next_Param_Screen[] = {
        HASLO,
        HASLO,
        HASLO,
        HASLO,
        ODCZYT_SERWISOWY1,
    };

    _Screen_Number After_Pass_Screen[] = {
        LICZNIK_PRACY, 
        PROG_TESTOWY,
        TEST_WEWY,
        UST_SERWISOWE1,
        ODCZYT_SERWISOWY1,
    };

    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                    Menu_Backup_Keys_Set = Menu_Keys;
                    Screen_Number = Next_Param_Screen[Menu_Keys.Active_String];
                    if ( Screen_Number == HASLO )
                    {
                        Password_Set = 0;
                    }
                    Screen_Before_Password = SUBMENU4;
                    Screen_After_Password = After_Pass_Screen[Menu_Keys.Active_String];            Reload_Screen = TRUE;
                    Count_Add = 0;
                    First_Editable_Variable();
            
                    if ( Screen_After_Password == PROG_TESTOWY )
                    {
                       Test_String_Mask = TEST_STOPPED;
                    ;
                    }
                    if ( Screen_After_Password == LICZNIK_PRACY )
                    {
                        Service_Variables_Set.Serv_Vars.Insp_Year = Date.Date_Vars.Year;
                        Service_Variables_Set.Serv_Vars.Insp_Month = Date.Date_Vars.Month;
                        Service_Variables_Set.Serv_Vars.Insp_Day = Date.Date_Vars.Day;
                    }
                
                    if ( Screen_After_Password == TEST_WEWY )
                    {
                        Controller_Variables.Controller_Vars.Test_Status = 0;
                        Machine_State = MANUAL_TEST;
                        Enable_Manual_Control();
                    }

            break;

            default:
                    Menu_Keyboard();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Haslo
* Description    : Password screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Haslo ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                   if ( Service_Variables.Serv_Vars.Haslo_Dostepu == Password_Set || Password_Set == SERVICE_PASSWORD )
                   {
                        Password_Set = 0;
                        Count_Add = 0;
                        Service_Variables_Set.Serv_Vars.Blok_Dostep_Pozostalo = Service_Variables_Set.Serv_Vars.Ilosc_Prob_Dostepu;                  
                        Screen_Number = Screen_After_Password;
                        First_Editable_Variable();                        
                   }
                   else
                   {
                        Password_Set = 0;
                        Count_Add = 0; 
               
                        if ( --Service_Variables_Set.Serv_Vars.Blok_Dostep_Pozostalo == 0 )
                        {
                            Service_Variables_Set.Serv_Vars.Marker_Blokady = STER_BLOKADA_CALKOWITA;
                            Screen_Number = BLOK_CALKOWITA;
                        }
                   }
                   Write_Settings();   
                   Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Jezyk
* Description    : Select Language screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Jezyk ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = SUBMENU3;
                    Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Brama_Motor
* Description    : Parameters setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Brama_Motor ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            
                    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                        Machine_State = INVERTER_PROG;
                    else // 24V sliding gate
                        Machine_State = WG_POWER_ON;
                    
                     WG_TIMER_FLAG = FALSE;
            break;

            case KEY_ENTER:
                   if ( ++Screen_Number > BRAMA_MOTOR1 )
                   {
                       Screen_Number = BRAMA_MOTOR1;
                   }
                   First_Editable_Variable();
                   Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Prad
* Description    : Parameters setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Prad ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                   if ( ++Screen_Number > PRAD1 )
                   {
                       Screen_Number = PRAD1;
                   }
                   First_Editable_Variable();
                   Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Listwy
* Description    : Parameters setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Listwy ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            
            break;

            case KEY_ENTER:
                   if ( ++Screen_Number > LISTWY2 )
                   {
                       Screen_Number = LISTWY1;
                   }
                   First_Editable_Variable();
                   Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}



/*******************************************************************************
* Function Name  : Keyboard_czujniki_Menu
* Description    : Parameters setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Czujniki_Menu ( void )
{
    _Screen_Number Next_Param_Screen[] = {
        HASLO,
        HASLO,

    };

    _Screen_Number After_Pass_Screen[] = {
        CZUJNIKI1, 
        CZUJNIKI2,

    };

    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Sensors;
                    Screen_Number = SUBMENU1;
                    Reload_Screen = TRUE;
            break;
               
            case KEY_ENTER:
                Machine_State = SENSOR_SETTING;
                Menu_Backup_Keys_Set = Menu_Keys;
                Screen_Before_Password = CZUJNIKI_MENU;
                Screen_After_Password = After_Pass_Screen[Menu_Keys.Active_String];            Reload_Screen = TRUE;
                Edit_Parameter_Counter = 0;
            
                if (Screen_After_Password == CZUJNIKI1 )
                {                
                    Screen_Number = Next_Param_Screen[Menu_Keys.Active_String];
      
                    Menu_Backup_Keys_Set = Menu_Keys;
                    Screen_Number = Next_Param_Screen[Menu_Keys.Active_String];
                    if ( Screen_Number == HASLO )
                    {
                        Password_Set = 0;
                    }
                    Count_Add = 0;
                    First_Editable_Variable();
              
                    Reload_Screen = TRUE; 
                }
            
            break;

            default:
                    Menu_Keyboard();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}
/*******************************************************************************
* Function Name  : Keyboard_czujniki
* Description    : Parameters setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Czujniki1 ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Machine_State = INVERTER_PROG;
            
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            
                    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                        Machine_State = INVERTER_PROG;
                    else // 24V sliding gate
                        Machine_State = WG_POWER_ON;
                    
                     WG_TIMER_FLAG = FALSE;
            break;

            case KEY_ENTER:
                if ( Edit_Parameter_Counter == 0 )
                {
                    Controlling_Variables_Set.Ctrl_Vars.Angle1_Cl = Controller_Variables.Controller_Vars.MSens1_Angle;
                }
                if ( Edit_Parameter_Counter == 1 )
                {
                    Controlling_Variables_Set.Ctrl_Vars.Angle1_Op = Controller_Variables.Controller_Vars.MSens1_Angle;
                }
                if ( Edit_Parameter_Counter == 2 )
                {
                    Controlling_Variables_Set.Ctrl_Vars.Angle2_Cl = Controller_Variables.Controller_Vars.MSens2_Angle;
                }
                if ( Edit_Parameter_Counter == 3 )
                {
                    Controlling_Variables_Set.Ctrl_Vars.Angle2_Op = Controller_Variables.Controller_Vars.MSens2_Angle;
                }
                Controlling_Variables = Controlling_Variables_Set;
            break;

            case KEY_DOWN:
  
            break;
          
            case KEY_UP:
                  Count_Add = 0;
                  Edit_Parameter_Counter++;
                
                  if ( Next_Editable_Variable() == FALSE )
                  {
                      Edit_Parameter_Counter = 0;
                      First_Editable_Variable();
                  }
                  Reload_Screen = TRUE;
            break;

            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}
/*******************************************************************************
* Function Name  : Keyboard_czujniki2
* Description    : Parameters setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Czujniki2 ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Sensors;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            
                    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                        Machine_State = INVERTER_PROG;
                    else // 24V sliding gate
                        Machine_State = WG_POWER_ON;
                    
                     WG_TIMER_FLAG = FALSE;
            break;

            case KEY_ENTER:
                   if ( ++Screen_Number > CZUJNIKI1 )
                   {
                       Screen_Number = CZUJNIKI1;
                   }
                   First_Editable_Variable();
                   Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}
/*******************************************************************************
* Function Name  : Keyboard_Ustaw_Wejsc
* Description    : Inputs setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Ustaw_Wejsc ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                    if ( ++Screen_Number > USTAW_WEWY4 )
                    {   
                        Screen_Number = USTAW_WEWY1;
                    }
                    First_Editable_Variable();
                    Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}


/*******************************************************************************
* Function Name  : Keyboard_Ustaw_Wejsc_Ster
* Description    : Inputs setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Ustaw_Wejsc_Ster ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                    if ( ++Screen_Number > WE_STER2 )
                    {   
                        Screen_Number = WE_STER1;
                    }
                    First_Editable_Variable();
                    Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Ustaw_Wyjsc_Przek
* Description    : Inputs setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Ustaw_Wyjsc_Przek ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                    if ( ++Screen_Number > WY_PRZEK2 )
                    {   
                        Screen_Number = WY_PRZEK1;
                    }
                    First_Editable_Variable();
                    Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}


/*******************************************************************************
* Function Name  : Keyboard_Zmiana_Hasel
* Description    : Select Passwd screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Zmiana_Hasel ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
            
                    Service_Variables.Serv_Vars.Blok_Dostep_Pozostalo = Service_Variables.Serv_Vars.Ilosc_Prob_Dostepu;
                    Service_Variables.Serv_Vars.Blok_Prog_Pozostalo = Service_Variables.Serv_Vars.Ilosc_Prob_Blokady;
            
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = SUBMENU3;
                    Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}


/*******************************************************************************
* Function Name  : Keyboard_Ust_Blokady
* Description    : Select Passwd screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Ust_Blokady ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Lock_Date_Now_Tmp = Date_2_Days ( Date.Date_Vars.Year, Date.Date_Vars.Month, Date.Date_Vars.Day );
                    Lock_Date_Set_Tmp = Date_2_Days ( Service_Variables_Set.Serv_Vars.Blokada_rok, Service_Variables_Set.Serv_Vars.Blokada_miesiac, Service_Variables_Set.Serv_Vars.Blokada_dzien );
                    Lock_Interval_Tmp = Lock_Date_Set_Tmp - Lock_Date_Now_Tmp;; 

                    if ( Lock_Date_Set_Tmp < Lock_Date_Now_Tmp )
                    {
                        Service_Variables_Set.Serv_Vars.Marker_Blokady = STER_ODBLOKOWANY;
                        Service_Variables_Set.Serv_Vars.Blokada = 1;
                    }
                    else
                    {
                        Service_Variables_Set.Serv_Vars.Lock_Counter = 0;
                        Service_Variables_Set.Serv_Vars.Lock_Interval = Lock_Interval_Tmp;
                        Service_Variables_Set.Serv_Vars.Marker_Blokady = STER_BLOKOWANY;
                    }
                
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = SUBMENU3;
                    Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_RTC
* Description    : Select RTC screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_RTC ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = SUBMENU3;
                    Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}


/*******************************************************************************
* Function Name  : Keyboard_Licznik_Pracy
* Description    : Service counters settings
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Licznik_Pracy ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();           
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}


/*******************************************************************************
* Function Name  : Keyboard_Prog_Test
* Description    : Prog_Teast screen habdling
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Prog_Testowy ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                        Machine_State = INVERTER_PROG;
                    else // 24V sliding gate
                        Machine_State = WG_POWER_ON;

                    WG_TIMER_FLAG = FALSE;
                    
                    TEST_ENABLE = FALSE;
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                    if ( TEST_ENABLE == TRUE )
                    {
                        Test_String_Mask = TEST_STOPPED;
                        Machine_State = WG_POWER_ON;
                        TEST_ENABLE = FALSE;
                    }
                    else
                    {
                        Test_String_Mask = TEST_STARTED;
                        Controller_Variables.Controller_Vars.Test_Counter = 0;
                        //Machine_State = TEST_START;
                        TEST_ENABLE = TRUE;
                    }
                    Reload_Screen = TRUE;
            break;

           default:
           break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Ster_Blok
* Description    : Handling keys in STER_BLOK screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Ster_Blokowany ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ENTER:
                   Screen_Number = ODBLOKUJ;
                   Count_Add = 0;
                   First_Editable_Variable();
                   Reload_Screen = TRUE;
            break;

            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : KKeyboard_Odblokuj
* Description    : Handling keys in ODBLOKUJ screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Odblokuj ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_BLOKOWANY || Service_Variables.Serv_Vars.Marker_Blokady == STER_ODBLOKOWANY )
                    {
                        Screen_Number = LICENCJA;
                    }
                    else if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_ZABLOKOWANY )
                    {
                        Screen_Number = STEROWNIK_BLOKOWANY;
                    }
                    Variable_Editing_Ptr = NULL;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                   if ( Service_Variables.Serv_Vars.Haslo_Blokady == Password_Set || Password_Set == SERVICE_PASSWORD )
                   {
                        Password_Set = 0;
                   
                        if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                            Machine_State = INVERTER_PROG;
                        else // 24V sliding gate
                            Machine_State = WG_POWER_ON;

                        WG_TIMER_FLAG = FALSE;
                        
                        Service_Variables_Set.Serv_Vars.Blok_Prog_Pozostalo = Service_Variables_Set.Serv_Vars.Ilosc_Prob_Blokady;                  
                        Service_Variables_Set.Serv_Vars.Marker_Blokady = STER_ODBLOKOWANY;
                        Service_Variables_Set.Serv_Vars.Blokada = 1;
                        Variable_Editing_Ptr = NULL;                   
                        Screen_Number = Screen_After_Password;
                   }
                   else
                   {
                        Password_Set = 0;
                        Count_Add = 0; 
               
                        if ( --Service_Variables_Set.Serv_Vars.Blok_Prog_Pozostalo == 0 )
                        {
                            Service_Variables_Set.Serv_Vars.Marker_Blokady = STER_BLOKADA_CALKOWITA;
                            Screen_Number = BLOK_CALKOWITA;
                        }
                   }
               
                   Write_Settings();  
                   Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Fabryczne
* Description    : Handling keys in UST_ FABRYCZNE screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Fabryczne ( void )
{
    uint32_t i;
    uint32_t NoOfWords;

    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            
                    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                        Machine_State = INVERTER_PROG;
                    else // 24V sliding gate
                        Machine_State = WG_POWER_ON;
                    
                     WG_TIMER_FLAG = FALSE;
            break;

            case KEY_ENTER:
                    NoOfWords = (sizeof ( Service_Variables.Service_Tab )>>2);

                    for ( i = 0; i < NoOfWords; i++ )
                    {
                        Service_Variables.Service_Tab[i] = Settings_Default[i];
                    }
    
                    NoOfWords = (sizeof ( Controlling_Variables.Variables_Tab )>>2);
   
                    for ( i = 0; i < NoOfWords; i++ )
                    {
                        Controlling_Variables.Variables_Tab[i] = Controlling_Default[i];
                    } 
                    Service_Variables_Set = Service_Variables;
                    Controlling_Variables_Set = Controlling_Variables;
                    Write_Settings();

                    if ( Service_Variables.Serv_Vars.Jezyk > NUM_OF_LANG )
                    {
                        Language_Num = 0;
                    }
                    else
                    {
                        Language_Num = Service_Variables.Serv_Vars.Jezyk;
                    }  

                    Screen_Number = CONTROLLER_ON;
                
                    WG_TIMER_FLAG = FALSE;
                    
                    Reload_Screen = TRUE;
            break;

            default:
                    Menu_Keyboard();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Zer_Licznikow
* Description    : Handling keys in ZEROWANIE_LICZNIKOW screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Zer_Licznikow ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Write_Settings();
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = SUBMENU3;
                    Reload_Screen = TRUE;
            break;
            
            case KEY_ENTER:
                   Counters_Variables.Counters_Vars.Service_Counter = 0;
                   Update_Counters();
                   Screen_Number = CONTROLLER_ON;
                   Reload_Screen = TRUE;
            break;

            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}




/*******************************************************************************
* Function Name  : Keyboard_Ust_Serwisowe
* Description    : Parameters setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Ust_Serwisowe ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Write_Settings();
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;
                    Reload_Screen = TRUE;

                    if ( Controlling_Variables.Ctrl_Vars.Motor_Type == 0 ) //Freqw_Inverter
                        Machine_State = INVERTER_PROG;
                    else // 24V sliding gate
                        Machine_State = WG_POWER_ON;
                    
                    WG_TIMER_FLAG = FALSE;

            break;

            case KEY_ENTER:
                   if ( ++Screen_Number > UST_SERWISOWE4 )
                   {
                       Screen_Number = UST_SERWISOWE1;
                   }
                   First_Editable_Variable();
                   Reload_Screen = TRUE;
            break;

            case KEY_DOWN:
              if ( ++Count_Add == Variable_Editing_Ptr->Var_Param_Ptr->Variable_Digits_Count )
              {
                  Count_Add = 0;
              }
              Reload_Screen = TRUE;  
            break;
          
            case KEY_UP:
              Count_Add = 0;
              if ( Next_Editable_Variable() == FALSE )
              {
                  First_Editable_Variable();
              }
              Reload_Screen = TRUE;
            break;

            default:
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}



/*******************************************************************************
* Function Name  : Keyboard_Odczyt_Serwisowy
* Description    : Parameters setting
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Odczyt_Serwisowy ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;
                    Reload_Screen = TRUE;
            break;

            case KEY_ENTER:
                   if ( ++Screen_Number > ODCZYT_SERWISOWY3 )
                   {
                       Screen_Number = ODCZYT_SERWISOWY1;
                   }
                   First_Editable_Variable();
                   Reload_Screen = TRUE;
            break;
               
            case KEY_LEFT:
            break;
  
            case KEY_RIGHT:
            break;
            
            case KEY_UP:
            break;               
               
             case KEY_DOWN:
            break;              
               
            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}



/*******************************************************************************
* Function Name  : Keyboard_Kontakt
* Description    : Licence screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Kontakt ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            break;

            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Info
* Description    : Info screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Info ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Menu_Keys = Menu_Backup_Keys;
                    Screen_Number = MENU;
                    Reload_Screen = TRUE;
            break;

            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Alert_Error
* Description    : Licence screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Alert_Error ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    Variable_Editing_Ptr = NULL;
                    Screen_Number = CONTROLLER_ON;
                    Reload_Screen = TRUE;
            break;

            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Keyboard_Ind_Test
* Description    : Inductive sensor testing
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Ind_Test ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    WG_TIMER_FLAG = FALSE;
                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;
                    Reload_Screen = TRUE;
            break;

            default:
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}
/*******************************************************************************
* Function Name  : Keyboard_Test_WeWy
* Description    : Inputs outputs testing
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Keyboard_Test_WeWy ( void )
{
    if ( Keyboard.Keyboard_Memory != 0 && Keyboard.Keyboard_Flag == 1 )
    {
        switch ( Keyboard.Keyboard_Memory )
        {
            case KEY_ESCAPE:
                    WG_TIMER_FLAG = FALSE;

                    Menu_Keys = Menu_Backup_Keys_Set;
                    Screen_Number = Screen_Before_Password;
                    Reload_Screen = TRUE;
                    Disable_Manual_Control();
            break;

            default:
                Disable_Manual_Values();
                Keyboard_Edit_Variable();
            break;
        }
        Keyboard.Keyboard_Flag = 0;
    }

    if ( Keyboard.Keyboard_State == 0 )
    {
        Keyboard.Keyboard_Memory = 0;
    }
}

/*******************************************************************************
* Function Name  : Write_Settings
* Description    : Load_variables to flash/eeprom memory
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Write_Settings ( void )
{
    uint32_t i;
    uint32_t NoOfWords;

    Flash_Address = EEPROM_BASE_ADDRESS;

    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	
    FLASH_ErasePage(Flash_Address);

    NoOfWords = (sizeof ( Service_Variables_Set.Service_Tab )>>2);

    for ( i = 0; i < NoOfWords; i++ )
    {
        FLASH_ProgramWord(Flash_Address, Service_Variables_Set.Service_Tab[i] );
        Flash_Address+=4;    
    }

    Flash_Address = EEPROM_BASE_ADDRESS + sizeof ( Service_Variables.Service_Tab );
    NoOfWords = (sizeof ( Controlling_Variables_Set.Variables_Tab ) >> 2);

    for ( i = 0; i < NoOfWords; i++ )
    {
        FLASH_ProgramWord(Flash_Address, Controlling_Variables_Set.Variables_Tab[i] );
        Flash_Address += 4;
    }

    Controlling_Variables = Controlling_Variables_Set;
    Service_Variables = Service_Variables_Set;

     Language_Num = Service_Variables.Serv_Vars.Jezyk;
}

/*******************************************************************************
* Function Name  : Read_Settings
* Description    : Read variables from flash/eeprom memory
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Read_Settings ( void )
{
    uint32_t i;
    uint32_t NoOfWords;

    Flash_Address = EEPROM_BASE_ADDRESS;
    NoOfWords = (sizeof ( Service_Variables.Service_Tab )>>2);

    for ( i = 0; i < NoOfWords; i++ )
    {
        Service_Variables.Service_Tab[i] = *(uint32_t*)Flash_Address;
        Flash_Address += 4;
    }

    Flash_Address = EEPROM_BASE_ADDRESS + sizeof ( Service_Variables.Service_Tab );
    NoOfWords = (sizeof ( Controlling_Variables.Variables_Tab ) >> 2);

    for ( i = 0; i < NoOfWords; i++ )
    {
        Controlling_Variables.Variables_Tab[i] = *(uint32_t*)Flash_Address;
        Flash_Address += 4;
    }


    if ( Service_Variables.Serv_Vars.First_On_Marker != CONTROLLER_PROGRAMMED )
    {
        NoOfWords = (sizeof ( Service_Variables.Service_Tab )>>2);
   
        for ( i = 0; i < NoOfWords; i++ )
        {
            Service_Variables.Service_Tab[i] = Settings_Default[i];
        }
    
        NoOfWords = (sizeof ( Controlling_Variables.Variables_Tab )>>2);
   
        for ( i = 0; i < NoOfWords; i++ )
        {
            Controlling_Variables.Variables_Tab[i] = Controlling_Default[i];
        } 
        Service_Variables_Set = Service_Variables;
        Controlling_Variables_Set = Controlling_Variables;
        Write_Settings();
    }

    Counters_Variables.Counters_Vars.Service_Counter = 0;
    Counters_Variables.Counters_Vars.Service_Counter = BKP_ReadBackupRegister(BKP_DR5);
    Counters_Variables.Counters_Vars.Service_Counter <<= 16;
    Counters_Variables.Counters_Vars.Service_Counter += BKP_ReadBackupRegister(BKP_DR6);

    Controller_Variables.Controller_Vars.Software_Version[0] = 2;//(BKP_ReadBackupRegister(BKP_DR9) & 0xFF00) >> 8;
    Controller_Variables.Controller_Vars.Software_Version[1] = 3;//BKP_ReadBackupRegister(BKP_DR9) & 0x00FF;
    Controller_Variables.Controller_Vars.Software_Version[2] = 1;//(BKP_ReadBackupRegister(BKP_DR10) & 0xFF00) >> 8;
    Controller_Variables.Controller_Vars.Controller_Date[0] = 29;//BKP_ReadBackupRegister(BKP_DR10) & 0x00FF;
    Controller_Variables.Controller_Vars.Controller_Date[1] = 9;//(BKP_ReadBackupRegister(BKP_DR11) & 0xFF00) >> 8;
    Controller_Variables.Controller_Vars.Controller_Date[2] = 17;//BKP_ReadBackupRegister(BKP_DR11) & 0x00FF;
    Controller_Variables.Controller_Vars.Serial_Number = 0;//BKP_ReadBackupRegister(BKP_DR12);

    if ( Service_Variables.Serv_Vars.Jezyk > NUM_OF_LANG )
    {
        Language_Num = 0;
    }
    else
    {
        Language_Num = Service_Variables.Serv_Vars.Jezyk;
    }  

    Controlling_Variables_Set = Controlling_Variables;
    Service_Variables_Set = Service_Variables;
}

/*******************************************************************************
* Function Name  : Update_Counters
* Description    : Update gtate counters in backup registers
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Update_Counters ( void )
{
    uint32_t Bkp_Tmp;

    Bkp_Tmp = (Counters_Variables.Counters_Vars.Service_Counter >> 16);
    BKP_WriteBackupRegister(BKP_DR5, Bkp_Tmp);
    Bkp_Tmp = Counters_Variables.Counters_Vars.Service_Counter;
    BKP_WriteBackupRegister(BKP_DR6, Bkp_Tmp);
//    Bkp_Tmp = (Counters_Variables.Counters_Vars.No_Goout >> 16);
//    BKP_WriteBackupRegister(BKP_DR7, Bkp_Tmp);
//    Bkp_Tmp = Counters_Variables.Counters_Vars.No_Goout;
//    BKP_WriteBackupRegister(BKP_DR8, Bkp_Tmp);
}

/*******************************************************************************
* Function Name  : Update_Lock_Counter
* Description    : Updates lock counters in flash memory during software lock function is enabled
* Input          : Count to update
* Output         : None
* Return         : None
*******************************************************************************/
void Update_Lock_Counter ( uint16_t Update_Counter )
{
    if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_BLOKOWANY )
    {
        Service_Variables_Set.Serv_Vars.Lock_Counter += Update_Counter;
        Write_Settings();
    }
}

/*******************************************************************************
* Function Name  : Lock_Init
* Description    : Lock initialization
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Lock_Init ( void )
{
    if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_ODBLOKOWANY )
    {
        Screen_Number = CONTROLLER_ON;  
    }
    else if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_BLOKOWANY )
    {
        Screen_Number = CONTROLLER_ON;      
    }
    else if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_ZABLOKOWANY )
    {
        Screen_Number = STEROWNIK_BLOKOWANY;  
    }
    else if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_BLOKADA_CALKOWITA )
    {
        Screen_Number = BLOK_CALKOWITA;
    }

//Screen_Number = ODCZYT_SERWISOWY1;
//Screen_Number = CZUJNIKI1;

}

/*******************************************************************************
* Function Name  : Lock_Handling
* Description    : Lock handling
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Lock_Handling ( void )
{
    if ( Service_Variables.Serv_Vars.Marker_Blokady == STER_BLOKOWANY )
    {
        if ( Service_Variables.Serv_Vars.Lock_Counter > Service_Variables.Serv_Vars.Lock_Interval )
        {
            Screen_Number = STER_BLOKOWANY;
            Machine_State = SW_LOCKED;
            Screen_After_Password = CONTROLLER_ON;
            Service_Variables_Set.Serv_Vars.Marker_Blokady = STER_ZABLOKOWANY;
            Write_Settings();
        }
    }
}



/*******************************************************************************
* End file main.c
*******************************************************************************/









