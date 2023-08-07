/* 
 * File       : Application.c
 * Author     : Bassam Mamdouh Mohammed
 * LinkedIn   : https://www.linkedin.com/in/bassam-mamdouh
 * Created on : 19 July, 2023, 10:30
 * Description: Calculator main code
 * Version    : 1.0.0
 */

#include "Application.h"
#include "ECUAL_Drivers/LCD/LCD_Interface.h"
#include "ECUAL_Drivers/Keypad/Keypad_Interface.h"

KEYPAD_t keypad = {
    .Rows_Pin[0].PORT = GPIO_portC, .Rows_Pin[0].PIN = GPIO_pin6,
    .Rows_Pin[0].DIRECTION = GPIO_OUTPUT, .Rows_Pin[0].LOGIC = GPIO_LOW,
    .Rows_Pin[1].PORT = GPIO_portB, .Rows_Pin[1].PIN = GPIO_pin1,
    .Rows_Pin[1].DIRECTION = GPIO_OUTPUT, .Rows_Pin[1].LOGIC = GPIO_LOW,
    .Rows_Pin[2].PORT = GPIO_portB, .Rows_Pin[2].PIN = GPIO_pin2,
    .Rows_Pin[2].DIRECTION = GPIO_OUTPUT, .Rows_Pin[2].LOGIC = GPIO_LOW,
    .Rows_Pin[3].PORT = GPIO_portB, .Rows_Pin[3].PIN = GPIO_pin3,
    .Rows_Pin[3].DIRECTION = GPIO_OUTPUT, .Rows_Pin[3].LOGIC = GPIO_LOW,
    .Columns_Pin[0].PORT = GPIO_portB, .Columns_Pin[0].PIN = GPIO_pin4,
    .Columns_Pin[0].DIRECTION = GPIO_INPUT,
    .Columns_Pin[1].PORT = GPIO_portB, .Columns_Pin[1].PIN = GPIO_pin5,
    .Columns_Pin[1].DIRECTION = GPIO_INPUT,
    .Columns_Pin[2].PORT = GPIO_portB, .Columns_Pin[2].PIN = GPIO_pin6,
    .Columns_Pin[2].DIRECTION = GPIO_INPUT,
    .Columns_Pin[3].PORT = GPIO_portB, .Columns_Pin[3].PIN = GPIO_pin7,
    .Columns_Pin[3].DIRECTION = GPIO_INPUT,
};
LCD_4BIT_t lcd = {
    .RS_Pin.PORT = GPIO_portC, .RS_Pin.PIN = GPIO_pin5,
    .RS_Pin.DIRECTION = GPIO_OUTPUT, .RS_Pin.LOGIC = GPIO_LOW,
    .EN_Pin.PORT = GPIO_portC, .EN_Pin.PIN = GPIO_pin4,
    .EN_Pin.DIRECTION = GPIO_OUTPUT, .EN_Pin.LOGIC = GPIO_LOW,
    .Data[0].PORT = GPIO_portC, .Data[0].PIN = GPIO_pin3,
    .Data[0].DIRECTION = GPIO_OUTPUT, .Data[0].LOGIC = GPIO_LOW,
    .Data[1].PORT = GPIO_portC, .Data[1].PIN = GPIO_pin2,
    .Data[1].DIRECTION = GPIO_OUTPUT, .Data[1].LOGIC = GPIO_LOW,
    .Data[2].PORT = GPIO_portC, .Data[2].PIN = GPIO_pin1,
    .Data[2].DIRECTION = GPIO_OUTPUT, .Data[2].LOGIC = GPIO_LOW,
    .Data[3].PORT = GPIO_portC, .Data[3].PIN = GPIO_pin0,
    .Data[3].DIRECTION = GPIO_OUTPUT, .Data[3].LOGIC = GPIO_LOW,
};
uint8 operand[6] = {'\0','\0','\0','\0','\0','\0'};
uint8 operand1;
uint8 operand2;
uint8 result;
int main(void) {
    /*---------------------- System Initialization -------------------------- */
    Application_Initialize();
    /*---------------------- Input Process ---------------------------------- */
    ECUAL_LCD_4BIT_Write_String_Position(&lcd,"2D Calculator",1,3);
    while (1) {
        for(int idx=0; idx<6;idx++){
            while(operand[idx] == '\0'){
                ECUAL_KEYPAD_GetValue(&keypad,&operand[idx]);          
            }
            ECUAL_LCD_4BIT_Write_Data_Position(&lcd,operand[idx],2,idx+6);
        }
        if('=' == operand[5]){
            switch(operand[2]){
            case '+' : 
                result = ((operand[0]-48) * 10 + (operand[1]-48)) + ((operand[3]-48) * 10 + (operand[4]-48)); 
            break;
            case '-' : 
                result = ((operand[0]-48) * 10 + (operand[1]-48)) - ((operand[3]-48) * 10 + (operand[4]-48));
            break;
            case '/' : 
                result = ((operand[0]-48) * 10 + (operand[1]-48)) / ((operand[3]-48) * 10 + (operand[4]-48));
            break;
            case '*' : 
                result = ((operand[0]-48) * 10 + (operand[1]-48)) * ((operand[3]-48) * 10 + (operand[4]-48));
            break;
            default : 
                ECUAL_LCD_4BIT_Write_String_Position(&lcd,"Wrong Operation",2,1);
            break;
            }
            ECUAL_LCD_4BIT_Write_Data_Position(&lcd,result/10 + 48,2,12);
            ECUAL_LCD_4BIT_Write_Data_Position(&lcd,result%10 + 48,2,13);
        }else{
            ECUAL_LCD_4BIT_Write_String_Position(&lcd,"Press = ",2,1);
        }
        
    }
    return (EXIT_SUCCESS);
}

void Application_Initialize(void) {
    ECUAL_LCD_4BIT_Init(&lcd);
    ECUAL_KEYPAD_Init(&keypad);
}