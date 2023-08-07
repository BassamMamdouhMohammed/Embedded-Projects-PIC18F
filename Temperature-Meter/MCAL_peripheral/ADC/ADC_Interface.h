/* 
 * File:   ADC_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:42 PM
 */

#ifndef ADC_INTERFACE_H
#define	ADC_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
#include "../Interrupt/Interrupt_Internal_Interface.h"
/********************************* Macro Definitions ************************/
#define ADC_CHANNEL_0  0
#define ADC_CHANNEL_1  1
#define ADC_CHANNEL_2  2
#define ADC_CHANNEL_3  3
#define ADC_CHANNEL_4  4
#define ADC_CHANNEL_5  5
#define ADC_CHANNEL_6  6
#define ADC_CHANNEL_7  7
#define ADC_CHANNEL_8  8
#define ADC_CHANNEL_9  9
#define ADC_CHANNEL_10 10
#define ADC_CHANNEL_11 11
#define ADC_CHANNEL_12 12

#define ADC_TAD_0   0
#define ADC_TAD_2   1
#define ADC_TAD_4   2
#define ADC_TAD_6   3
#define ADC_TAD_8   4
#define ADC_TAD_12  5
#define ADC_TAD_16  6
#define ADC_TAD_20  7

#define ADC_SAMPLING_FOSC_2   0
#define ADC_SAMPLING_FOSC_8   1
#define ADC_SAMPLING_FOSC_32  2
#define ADC_SAMPLING_FRC      3
#define ADC_SAMPLING_FOSC_4   4
#define ADC_SAMPLING_FOSC_16  5
#define ADC_SAMPLING_FOSC_64  6

#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F

#define ADC_STILL                  0x01U
#define ADC_IDLE                   0x00U

#define ADC_VOLTAGE_REF_ENABLE     0x01U
#define ADC_VOLTAGE_REF_DISABLE    0X00U
#define ADC_RIGHT_JUSTIFIED        0x01U
#define ADC_LEFT_JUSTIFIED         0x00U
/********************************* Macro Functions  *************************/

/********************************* User-Defined Data Types ******************/
typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* ADC_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
    Priority_t ADC_Priority;
#endif
#endif
    uint8 Port_Control :4;
    uint8 Channel  :3;
    uint8 Aquisition_Time :3;
    uint8 Clock :3;
    uint8 Voltage_Ref  :1;
    uint8 Result_Format :1;
    uint8 Reserved :1;
}ADC_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_ADC_Init(const ADC_t *_ADC);
STD_RETURN_t MCAL_ADC_DeInit(const ADC_t *_ADC);
STD_RETURN_t MCAL_ADC_SelectChannel(const ADC_t *_ADC, uint8 channel);
STD_RETURN_t MCAL_ADC_StartConversion(const ADC_t *_ADC);
STD_RETURN_t MCAL_ADC_PollForConversion(const ADC_t *_ADC, uint8 *conversion_status);
uint16 MCAL_ADC_GetConversionResult(const ADC_t *_ADC);
STD_RETURN_t MCAL_ADC_GetConversion_Blocking(const ADC_t *_ADC, uint8 channel, uint8 *conversion_result);
STD_RETURN_t MCAL_ADC_StartConversion_IT(const ADC_t *_ADC, uint8 channel);
#endif	/* ADC_INTERFACE_H */

