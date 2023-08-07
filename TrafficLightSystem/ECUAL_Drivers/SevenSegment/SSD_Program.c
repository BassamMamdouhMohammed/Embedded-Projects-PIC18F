/* 
 * File:   SevenSegment_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 13, 2022, 1:50 PM
 */
#include "SSD_Interface.h"

STD_RETURN_t ECUAL_SSD_Init(const SSD_t *ssd){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == ssd){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status  = MCAL_GPIO_Pin_Initialize(&(ssd->SSD_PINs[Segment_PIN0]));
        Return_Status  = MCAL_GPIO_Pin_Initialize(&(ssd->SSD_PINs[Segment_PIN1]));
        Return_Status  = MCAL_GPIO_Pin_Initialize(&(ssd->SSD_PINs[Segment_PIN2]));
        Return_Status  = MCAL_GPIO_Pin_Initialize(&(ssd->SSD_PINs[Segment_PIN3]));
    }
    return Return_Status;
}
STD_RETURN_t ECUAL_SSD_Update(const SSD_t *ssd, uint8 value){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == ssd) || (value > 9)){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status  = MCAL_GPIO_Pin_Write_Logic(&(ssd->SSD_PINs[Segment_PIN0]),value & 0x01);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(ssd->SSD_PINs[Segment_PIN1]),(value>>1) & 0x01);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(ssd->SSD_PINs[Segment_PIN2]),(value>>2) & 0x01);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(ssd->SSD_PINs[Segment_PIN3]),(value>>3) & 0x01);
    }
    return Return_Status;
}
