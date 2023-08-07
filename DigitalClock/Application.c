/* 
 * File       : Application.c
 * Author     : Bassam Mamdouh Mohammed
 * LinkedIn   : https://www.linkedin.com/in/bassam-mamdouh
 * Created on : 19 July, 2023, 10:30
 * Description: Traffic Light System Logic main code
 * Version    : 1.0.0
 */

#include "Application.h"

PB_t set = {
    .PushButton_Pin.PORT = GPIO_portD, .PushButton_Pin.PIN = GPIO_pin0,
    .PushButton_Pin.DIRECTION = GPIO_INPUT, .State = Released,
    .Connection = Active_High
};
PB_t dec = {
    .PushButton_Pin.PORT = GPIO_portD, .PushButton_Pin.PIN = GPIO_pin1,
    .PushButton_Pin.DIRECTION = GPIO_INPUT, .State = Released,
    .Connection = Active_High
};
PB_t inc = {
    .PushButton_Pin.PORT = GPIO_portD, .PushButton_Pin.PIN = GPIO_pin2,
    .PushButton_Pin.DIRECTION = GPIO_INPUT, .State = Released,
    .Connection = Active_High
};
SSD_t digitalclockSSD = {
    .Common = Common_Anode,
    .SSD_PINs[0].PORT = GPIO_portC, .SSD_PINs[0].PIN = GPIO_pin0,
    .SSD_PINs[0].DIRECTION = GPIO_OUTPUT, .SSD_PINs[0].LOGIC = GPIO_LOW,
    .SSD_PINs[1].PORT = GPIO_portC, .SSD_PINs[1].PIN = GPIO_pin1,
    .SSD_PINs[1].DIRECTION = GPIO_OUTPUT, .SSD_PINs[1].LOGIC = GPIO_LOW,
    .SSD_PINs[2].PORT = GPIO_portC, .SSD_PINs[2].PIN = GPIO_pin2,
    .SSD_PINs[2].DIRECTION = GPIO_OUTPUT, .SSD_PINs[2].LOGIC = GPIO_LOW,
    .SSD_PINs[3].PORT = GPIO_portC, .SSD_PINs[3].PIN = GPIO_pin3,
    .SSD_PINs[3].DIRECTION = GPIO_OUTPUT, .SSD_PINs[3].LOGIC = GPIO_LOW
};

PIN_t SSD1_E = {
    .PORT = GPIO_portC, .PIN = GPIO_pin4, .DIRECTION = GPIO_OUTPUT, .LOGIC = GPIO_LOW
};
PIN_t SSD2_E = {
    .PORT = GPIO_portC, .PIN = GPIO_pin5, .DIRECTION = GPIO_OUTPUT, .LOGIC = GPIO_LOW
};
PIN_t SSD3_E = {
    .PORT = GPIO_portC, .PIN = GPIO_pin6, .DIRECTION = GPIO_OUTPUT, .LOGIC = GPIO_LOW
};
PIN_t SSD4_E = {
    .PORT = GPIO_portC, .PIN = GPIO_pin7, .DIRECTION = GPIO_OUTPUT, .LOGIC = GPIO_LOW
};
PIN_t SSD5_E = {
    .PORT = GPIO_portD, .PIN = GPIO_pin3, .DIRECTION = GPIO_OUTPUT, .LOGIC = GPIO_LOW
};
PIN_t SSD6_E = {
    .PORT = GPIO_portD, .PIN = GPIO_pin4, .DIRECTION = GPIO_OUTPUT, .LOGIC = GPIO_LOW
};
PIN_t SSD_DP = {
    .PORT = GPIO_portD, .PIN = GPIO_pin5, .DIRECTION = GPIO_OUTPUT, .LOGIC = GPIO_LOW
};
volatile uint32 cnt;
volatile uint8 seconds;
volatile uint8 minutes;
volatile uint8 hours;
void TMR2_Update(void){
    ++cnt;
    if(1000 == cnt){
        ++seconds;
        cnt=0;
    }
    if(60 == seconds){
        seconds = 0;
        ++minutes;
    }
    if(60 == minutes){
        minutes = 0;
        ++hours;
    }
    if(24 == hours){
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
}
TIMER2_t TMR = {
  .TMR2_InterruptHandler = TMR2_Update,
  .Preloaded_Value = 249,
  .Prescaler_Value = TMR2_PRESCALER_DIVIDED_BY_1,
  .Postscaler_Value = TMR2_POSTSCALER_DIVIDED_BY_8,
};
PB_State set_logic = Released;
PB_State dec_logic = Released;
PB_State inc_logic = Released;
uint8 setFlag = 0;
int main(void) {
    /*---------------------- System Initialization -------------------------- */
    Application_Initialize();
    /*---------------------- Input Process ---------------------------------- */
    
    while (1) {
        /*------------------ Seconds Process -------------------------------- */
        ECUAL_SSD_Update(&digitalclockSSD,seconds%10);
        MCAL_GPIO_Pin_Write_Logic(&SSD6_E,GPIO_HIGH);
        __delay_ms(5);
        MCAL_GPIO_Pin_Write_Logic(&SSD6_E,GPIO_LOW);
        ECUAL_SSD_Update(&digitalclockSSD,seconds/10);
        MCAL_GPIO_Pin_Write_Logic(&SSD5_E,GPIO_HIGH);
        __delay_ms(5);
        MCAL_GPIO_Pin_Write_Logic(&SSD5_E,GPIO_LOW);
        /*------------------ Minutes Process -------------------------------- */
        ECUAL_SSD_Update(&digitalclockSSD,minutes%10);
        MCAL_GPIO_Pin_Write_Logic(&SSD4_E,GPIO_HIGH);
        __delay_ms(5);
        MCAL_GPIO_Pin_Write_Logic(&SSD4_E,GPIO_LOW);
        ECUAL_SSD_Update(&digitalclockSSD,minutes/10);
        MCAL_GPIO_Pin_Write_Logic(&SSD3_E,GPIO_HIGH);
        __delay_ms(5);
        MCAL_GPIO_Pin_Write_Logic(&SSD3_E,GPIO_LOW);
        /*------------------ Hours Process -------------------------------- */
        ECUAL_SSD_Update(&digitalclockSSD,hours%10);
        MCAL_GPIO_Pin_Write_Logic(&SSD2_E,GPIO_HIGH);
        __delay_ms(5);
        MCAL_GPIO_Pin_Write_Logic(&SSD2_E,GPIO_LOW);
        ECUAL_SSD_Update(&digitalclockSSD,hours/10);
        MCAL_GPIO_Pin_Write_Logic(&SSD1_E,GPIO_HIGH);
        __delay_ms(5);
        MCAL_GPIO_Pin_Write_Logic(&SSD1_E,GPIO_LOW);
        /*------------------ Check Buttons   -------------------------------- */
    }
    return (EXIT_SUCCESS);
}

void Application_Initialize(void) {
    ECUAL_PB_Init(&set);
    ECUAL_PB_Init(&dec);
    ECUAL_PB_Init(&inc);
    ECUAL_SSD_Init(&digitalclockSSD);
    MCAL_GPIO_Pin_Initialize(&SSD1_E);
    MCAL_GPIO_Pin_Initialize(&SSD2_E);
    MCAL_GPIO_Pin_Initialize(&SSD3_E);
    MCAL_GPIO_Pin_Initialize(&SSD4_E);
    MCAL_GPIO_Pin_Initialize(&SSD5_E);
    MCAL_GPIO_Pin_Initialize(&SSD6_E);
    MCAL_GPIO_Pin_Initialize(&SSD_DP);
    MCAL_TIM2_Start(&TMR);
}