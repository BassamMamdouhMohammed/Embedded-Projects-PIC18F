/* 
 * File:   ADC_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:42 PM
 */
#include "ADC_Interface.h"

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*ADC_Interrupt_Handler)(void) = NULL;
#endif
/* ------------------ Static helper Functions Declaration ----------------- */
static inline void ADC_ResultFormatSelect(const ADC_t *_ADC);
static inline void ADC_VolatageRefSelect(const ADC_t *_ADC);
static inline void ADC_PortConfigurationSelect(const ADC_t *_ADC);
/* ------------------ ADC Configuration Registers Static APIs Declaration ----------------- */
static void ADC_SelectAcquisitionTime(const ADC_t *adc);
static void ADC_SelectClockConversion(const ADC_t *adc);
static void ADC_SelectChannel(const ADC_t *adc);
static void ADC_Enable(void);
static void ADC_Disable(void);

STD_RETURN_t MCAL_ADC_Init(const ADC_t *_ADC) {
    STD_RETURN_t Return_Status = STD_OK;
    if (NULL == _ADC) {
        Return_Status = STD_NOT_OK;
    } else {
        ADC_Disable();
        ADC_SelectAcquisitionTime(_ADC);
        ADC_SelectClockConversion(_ADC);
        ADC_SelectChannel(_ADC);
        ADC_PortConfigurationSelect(_ADC);
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_GLOBAL_ENABLE();
        INTERRUPT_PERIPHERAL_ENABLE();
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_CLEAR_FLAG();
        
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVELS_ENABLE();
        if (Low_Priority == _ADC->ADC_Priority) {
            INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
            ADC_INTERRUPT_LOW_PRIORITY();
        } else if (High_Priority == _ADC->ADC_Priority) {
            INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            ADC_INTERRUPT_HIGH_PRIORITY();
        } else {
            /* if you are here then you don't select Priority Levels */
        }
#endif   
        ADC_Interrupt_Handler = _ADC->ADC_InterruptHandler;
#endif            
        ADC_ResultFormatSelect(_ADC);
        ADC_VolatageRefSelect(_ADC);
        ADC_Enable();
    }
    return Return_Status;
}
STD_RETURN_t MCAL_ADC_DeInit(const ADC_t *_ADC) {
    STD_RETURN_t Return_Status = STD_OK;
    if (NULL == _ADC) {
        Return_Status = STD_NOT_OK;
    } else {
        ADC_Disable();
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
#endif        
    }
    return Return_Status;
}

STD_RETURN_t MCAL_ADC_SelectChannel(const ADC_t *_ADC, uint8 channel) {
    STD_RETURN_t Return_Status = STD_OK;
    if (NULL == _ADC) {
        Return_Status = STD_NOT_OK;
    } else {
        ADC_SelectChannel(_ADC);
        ADC_PortConfigurationSelect(_ADC);
    }
    return Return_Status;
}
STD_RETURN_t MCAL_ADC_StartConversion(const ADC_t *_ADC) {
    STD_RETURN_t Return_Status = STD_OK;
    if (NULL == _ADC) {
        Return_Status = STD_NOT_OK;
    } else {
        ADCON0bits.GODONE = 1;
    }
    return Return_Status;
}
STD_RETURN_t MCAL_ADC_PollForConversion(const ADC_t *_ADC, uint8 *conversion_status) {
    STD_RETURN_t Return_Status = STD_OK;
    if ((NULL == _ADC) || (NULL == conversion_status)) {
        Return_Status = STD_NOT_OK;
    } else {
        *conversion_status = (uint8) (!(ADCON0bits.GO_nDONE));
    }
    return Return_Status;
}
uint16 MCAL_ADC_GetConversionResult(const ADC_t *_ADC) {
    static uint16 result = STD_OK;
    if (ADC_RIGHT_JUSTIFIED == _ADC->Result_Format) {
        result = (uint16) ((ADRESH << 8) + ADRESL);
    } else if (ADC_LEFT_JUSTIFIED == _ADC->Result_Format) {
        result = (uint16) (((ADRESH << 8) + ADRESL) >> 6);
    } else {
        result = (uint16) (((ADRESH << 8) + ADRESL) >> 6);
    }
    return result;
}
STD_RETURN_t MCAL_ADC_GetConversion_Blocking(const ADC_t *_ADC, uint8 channel, uint8 *conversion_result) {
    STD_RETURN_t Return_Status = STD_OK;
    if ((NULL == _ADC) || (NULL == conversion_result)) {
        Return_Status = STD_NOT_OK;
    } else {
        Return_Status = MCAL_ADC_SelectChannel(_ADC, channel);
        Return_Status = MCAL_ADC_StartConversion(_ADC);
        while (ADCON0bits.GO_nDONE);
        Return_Status = MCAL_ADC_PollForConversion(_ADC, conversion_result);
    }
    return Return_Status;
}
STD_RETURN_t MCAL_ADC_StartConversion_IT(const ADC_t *_ADC, uint8 channel) {
    STD_RETURN_t Return_Status = STD_OK;
    if (NULL == _ADC) {
        Return_Status = STD_NOT_OK;
    } else {
        Return_Status = MCAL_ADC_SelectChannel(_ADC, channel);
        Return_Status = MCAL_ADC_StartConversion(_ADC);
    }
    return Return_Status;
}

static inline void ADC_VolatageRefSelect(const ADC_t *_ADC) {
    if (ADC_VOLTAGE_REF_ENABLE == _ADC->Voltage_Ref) {
        ADCON1bits.VCFG1 = 1 ;
        ADCON1bits.VCFG0 = 1 ;
    } else if (ADC_VOLTAGE_REF_DISABLE == _ADC->Voltage_Ref) {
        ADCON1bits.VCFG1 = 0 ;
        ADCON1bits.VCFG0 = 0 ;
    } else {
        ADCON1bits.VCFG1 = 0 ;
        ADCON1bits.VCFG0 = 0 ;
    }
}
static inline void ADC_ResultFormatSelect(const ADC_t *_ADC) {
    if (ADC_RIGHT_JUSTIFIED == _ADC->Result_Format) {
        ADCON2bits.ADFM = 1;
    } else if (ADC_LEFT_JUSTIFIED == _ADC->Result_Format) {
        ADCON2bits.ADFM = 0;
    } else {
        ADCON2bits.ADFM = 0;
    }
}
static inline void ADC_PortConfigurationSelect(const ADC_t *_ADC) {
    switch (_ADC->Channel) {
        case ADC_CHANNEL_0:
            Set_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_1:
            Set_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_2:
            Set_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_3:
            Set_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_4:
            Set_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_5:
            Set_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_6:
            Set_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_7:
            Set_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_8:
            Set_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_9:
            Set_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_10:
            Set_BIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_11:
            Set_BIT(TRISB, _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_12:
            Set_BIT(TRISB, _TRISB_RB0_POSN);
            break;
        default:             
            Set_BIT(TRISA, _TRISA_RA0_POSN);
            break;
    }
}
/*---------------- ADC Configuration Registers Static APIs --------------*/

static void ADC_Disable(void)
{
    ADCON0bits.ADON = 0;
}
static void ADC_Enable(void)
{
    ADCON0bits.ADON = 1;
}
static void ADC_SelectChannel(const ADC_t *adc)
{
    ADCON0bits.CHS = adc->Channel;
}
static void ADC_SelectClockConversion(const ADC_t *adc)
{
    ADCON2bits.ADCS = adc->Clock;
}
static void ADC_SelectAcquisitionTime(const ADC_t *adc)
{
    ADCON2bits.ACQT = adc->Aquisition_Time;
}


void ADC_ISR(void) {
    ADC_INTERRUPT_CLEAR_FLAG();
    if (ADC_Interrupt_Handler) {
        ADC_Interrupt_Handler();
    }
}