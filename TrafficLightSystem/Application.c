/* 
 * File       : Application.c
 * Author     : Bassam Mamdouh Mohammed
 * LinkedIn   : https://www.linkedin.com/in/bassam-mamdouh
 * Created on : 19 July, 2023, 10:30
 * Description: Traffic Light System Logic main code
 * Version    : 1.0.0
 */

#include "Application.h"
#define GO_TIME    (45)
#define READY_TIME (5)
#define STOP_TIME  (30)

int main(void) {
    Application_Initialize();
    ECUAL_SSD_Update(&LSeconds, 0);
    ECUAL_SSD_Update(&RSeconds, 0);
    while (1) {
        while (flag == 0) {
            ECUAL_LED_Turn_On(&Green_Led);
            ECUAL_SSD_Update(&RSeconds, TIM0_cnt / 10);
            ECUAL_SSD_Update(&LSeconds, TIM0_cnt % 10);
            if (TIM0_cnt < 0) {
                TIM0_cnt = STOP_TIME;
                flag = 1;
                ECUAL_LED_Turn_Off(&Green_Led);
            }
        }

        while (flag == 1) {
            ECUAL_LED_Turn_On(&Red_Led);
            ECUAL_SSD_Update(&RSeconds, TIM0_cnt / 10);
            ECUAL_SSD_Update(&LSeconds, TIM0_cnt % 10);
            if (TIM0_cnt < 0) {
                TIM0_cnt = READY_TIME;
                flag = 2;
                ECUAL_LED_Turn_Off(&Red_Led);
            }
        }

        while (flag == 2) {
            ECUAL_LED_Turn_On(&Yellow_Led);
            ECUAL_SSD_Update(&RSeconds, TIM0_cnt / 10);
            ECUAL_SSD_Update(&LSeconds, TIM0_cnt % 10);
            if (TIM0_cnt < 0) {
                TIM0_cnt = GO_TIME;
                flag = 0;
                ECUAL_LED_Turn_Off(&Yellow_Led);
            }
        }
    }
    return (EXIT_SUCCESS);
}

volatile sint8 TIM0_cnt = GO_TIME;
uint8 flag = 0; // 0 -> Go,   1 -> Stop,   2 -> Ready

void TMR0_Update() {
    TIMER0_INTERRUPT_CLEAR_FLAG();
    --TIM0_cnt;
}
TIMER0_t traffic_TIM = {
    .Mode = TMR0_TIMER_MODE_ENABLE,
    .Preloaded_Value = 3036,
    .Prescaler_Enable = TMR0_PRESCALER_ENABLE,
    .Prescaler_Value = Prescaler_Divided_By_32,
    .Register_Size = TMR0_16BIT_CONTROL_REG,
    .TMR0_InterruptHandler = TMR0_Update,
};

LED_t Green_Led = {
    .Port = GPIO_portD, .Pin = GPIO_pin0, .DIRECTION = GPIO_OUTPUT, .Logic = GPIO_LOW
};
LED_t Yellow_Led = {
    .Port = GPIO_portD, .Pin = GPIO_pin1, .DIRECTION = GPIO_OUTPUT, .Logic = GPIO_LOW
};
LED_t Red_Led = {
    .Port = GPIO_portD, .Pin = GPIO_pin2, .DIRECTION = GPIO_OUTPUT, .Logic = GPIO_LOW
};
SSD_t LSeconds = {
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
SSD_t RSeconds = {
    .Common = Common_Anode,
    .SSD_PINs[0].PORT = GPIO_portC, .SSD_PINs[0].PIN = GPIO_pin4,
    .SSD_PINs[0].DIRECTION = GPIO_OUTPUT, .SSD_PINs[0].LOGIC = GPIO_LOW,
    .SSD_PINs[1].PORT = GPIO_portC, .SSD_PINs[1].PIN = GPIO_pin5,
    .SSD_PINs[1].DIRECTION = GPIO_OUTPUT, .SSD_PINs[1].LOGIC = GPIO_LOW,
    .SSD_PINs[2].PORT = GPIO_portC, .SSD_PINs[2].PIN = GPIO_pin6,
    .SSD_PINs[2].DIRECTION = GPIO_OUTPUT, .SSD_PINs[2].LOGIC = GPIO_LOW,
    .SSD_PINs[3].PORT = GPIO_portC, .SSD_PINs[3].PIN = GPIO_pin7,
    .SSD_PINs[3].DIRECTION = GPIO_OUTPUT, .SSD_PINs[3].LOGIC = GPIO_LOW
};

void Application_Initialize(void) {
    ECUAL_LED_Initialize(&Green_Led);
    ECUAL_LED_Initialize(&Yellow_Led);
    ECUAL_LED_Initialize(&Red_Led);
    ECUAL_SSD_Init(&LSeconds);
    ECUAL_SSD_Init(&RSeconds);
    MCAL_TIM0_Start(&traffic_TIM);
}