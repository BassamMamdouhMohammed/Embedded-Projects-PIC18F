/* 
 * File:   Application.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on 03 Sep, 2022, 05:05 ?
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/********************************* Includes *********************************/
#include "ECUAL_Drivers/LED/LED_Interface.h"
#include "MCAL_peripheral/GPIO/GPIO_Interface.h"
#include "MCAL_peripheral/ADC/ADC_Interface.h"
#include "ECUAL_Drivers/DC_Motor/DC_Motor_Interface.h"
#include "ECUAL_Drivers/LCD/LCD_Interface.h"
/********************************* Macro Definitions ************************/

/********************************* Macro Functions  *************************/

/********************************* User-Defined Data Types ******************/

/********************************* Functions Declaration ********************/
void Application_Initialize(void);
STD_RETURN_t Convert_U8toString(uint8 val, uint8 *str);
STD_RETURN_t Convert_U16toString(uint16 val, uint8 *str);
STD_RETURN_t Convert_U32toString(uint32 val, uint8 *str);
#endif	/* APPLICATION_H */



