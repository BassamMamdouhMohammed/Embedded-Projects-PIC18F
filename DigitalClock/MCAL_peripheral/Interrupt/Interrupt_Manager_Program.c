/* 
 * File        : Interrupt_Manager_Interface.h
 * Author      : Bassam Mamdouh Mohammed
 * LinkedIn    : https://www.linkedin.com/in/bassam-mamdouh
 * Created on  : September 14, 2022, 2:15 PM
 * Description : source code to handle every MCU ISR with or without priority
 */

#include "Interrupt_Manager_Interface.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    
}
void __interrupt(low_priority) InterruptManagerLow(void){
    
}

#else

void __interrupt() InterruptManager(void){
    /*
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCURE == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{  }
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCURE == INTCON3bits.INT1F)){
        INT1_ISR(); 
    }
    else{  }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCURE == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{  }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB4 == GPIO_HIGH) && (RB4_Flag == 1)){
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else{  }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB4 == GPIO_LOW) && (RB4_Flag == 0)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    else{  }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB5 == GPIO_HIGH) && (RB5_Flag == 1)){
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    else{  }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB5 == GPIO_LOW) && (RB5_Flag == 0)){
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    else{  }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB6 == GPIO_HIGH) && (RB6_Flag == 1)){
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    else{  }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB6 == GPIO_LOW) && (RB6_Flag == 0)){
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    else{ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB7 == GPIO_HIGH) && (RB7_Flag == 1)){
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    else{  }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURE == INTCONbits.RBIF) && 
       (PORTBbits.RB7 == GPIO_LOW) && (RB7_Flag == 0)){
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    else{  }
    */
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCURE == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else{ }

    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCURE == INTCONbits.TMR0IF)){
        TIM0_ISR();
    }
    else{  }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCURE == PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
    else{  }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCURE == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
    else{  }
    /*
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCURE == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
    else{  }
    
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCURE == PIR1bits.TXIF)){
        UART_TX_ISR();
    }
    else{  }
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCURE == PIR1bits.RCIF)){
        UART_RX_ISR();
    }
    else{  }
    */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCURE == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    else{  }
    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCURE == PIR2bits.CCP2IF)){
        CCP2_ISR();
    }
    else{  }
}
#endif