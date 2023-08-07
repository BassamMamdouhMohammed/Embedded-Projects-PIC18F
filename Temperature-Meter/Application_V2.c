/* 
 * File       : Application.c
 * Author     : Bassam Mamdouh Mohammed
 * LinkedIn   : https://www.linkedin.com/in/bassam-mamdouh
 * Created on : 19 July, 2023, 10:30
 * Description: Traffic Light System Logic without interrupt main code
 * Version    : 1.0.0
 */

#include "Application.h"

#define division (0.51) /* division between sensor resolution and PIC ADC resoution */
uint8 resultBuffer[6];
sint16 temperature;
ADC_t LM35 = {
    .Channel = ADC_CHANNEL_0,
    .Aquisition_Time = ADC_TAD_12,
    .Clock = ADC_SAMPLING_FOSC_16,
    .Result_Format = ADC_RIGHT_JUSTIFIED,
    .Voltage_Ref = ADC_VOLTAGE_REF_DISABLE,
    .ADC_InterruptHandler = NULL,
};

MOTOR_t heater = {
    .Motor_Pin[0].PORT = GPIO_portD, .Motor_Pin[0].PIN = GPIO_pin0,
    .Motor_Pin[0].DIRECTION = GPIO_OUTPUT, .Motor_Pin[0].LOGIC = GPIO_HIGH,
    .Motor_Pin[1].PORT = GPIO_portD, .Motor_Pin[1].PIN = GPIO_pin1,
    .Motor_Pin[1].DIRECTION = GPIO_OUTPUT, .Motor_Pin[1].LOGIC = GPIO_HIGH,
};

MOTOR_t airConditioner = {
    .Motor_Pin[0].PORT = GPIO_portD, .Motor_Pin[0].PIN = GPIO_pin2,
    .Motor_Pin[0].DIRECTION = GPIO_OUTPUT, .Motor_Pin[0].LOGIC = GPIO_HIGH,
    .Motor_Pin[1].PORT = GPIO_portD, .Motor_Pin[1].PIN = GPIO_pin3,
    .Motor_Pin[1].DIRECTION = GPIO_OUTPUT, .Motor_Pin[1].LOGIC = GPIO_HIGH,
};
LCD_4BIT_t lcd = {
    .RS_Pin.PORT = GPIO_portC, .RS_Pin.PIN = GPIO_pin0,
    .RS_Pin.DIRECTION = GPIO_OUTPUT, .RS_Pin.LOGIC = GPIO_LOW,
    .EN_Pin.PORT = GPIO_portC, .EN_Pin.PIN = GPIO_pin2,
    .EN_Pin.DIRECTION = GPIO_OUTPUT, .EN_Pin.LOGIC = GPIO_LOW,
    .Data[0].PORT = GPIO_portC, .Data[0].PIN = GPIO_pin3,
    .Data[0].DIRECTION = GPIO_OUTPUT, .Data[0].LOGIC = GPIO_LOW,
    .Data[1].PORT = GPIO_portC, .Data[1].PIN = GPIO_pin4,
    .Data[1].DIRECTION = GPIO_OUTPUT, .Data[1].LOGIC = GPIO_LOW,
    .Data[2].PORT = GPIO_portC, .Data[2].PIN = GPIO_pin5,
    .Data[2].DIRECTION = GPIO_OUTPUT, .Data[2].LOGIC = GPIO_LOW,
    .Data[3].PORT = GPIO_portC, .Data[3].PIN = GPIO_pin6,
    .Data[3].DIRECTION = GPIO_OUTPUT, .Data[3].LOGIC = GPIO_LOW,
};

int main(void) {
    Application_Initialize();
    ECUAL_LCD_4BIT_Write_String_Position(&lcd, "Temperature: ", 1, 3);
    ECUAL_LCD_4BIT_Write_String_Position(&lcd, "Celsius", 2, 10);
    while (1) {
        MCAL_ADC_SelectChannel(&LM35, ADC_CHANNEL_0);
        MCAL_ADC_StartConversion(&LM35);
        while (MCAL_ADC_PollForConversion(&LM35) != ADC_IDLE);
        temperature = .51 * MCAL_ADC_GetConversionResult(&LM35);
        Convert_U16toString(temperature, resultBuffer);
        ECUAL_LCD_4BIT_Write_String_Position(&lcd, resultBuffer, 2, 5);
        if (temperature >= 30) {
            ECUAL_Motor_MoveLeft(&airConditioner);
        } else if (temperature <= 19) {
            ECUAL_Motor_MoveLeft(&heater);
        } else {
            ECUAL_Motor_Stop(&heater);
            ECUAL_Motor_Stop(&airConditioner);
        }
    }
    return (EXIT_SUCCESS);
}

void Application_Initialize(void) {
    ECUAL_Motor_Init(&heater);
    ECUAL_Motor_Init(&airConditioner);
    ECUAL_LCD_4BIT_Init(&lcd);
    MCAL_ADC_Init(&LM35);
}