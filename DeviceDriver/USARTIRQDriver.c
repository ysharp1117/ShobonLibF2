/**
 * @file    USARTIRQDriver.c
 * @author  \@y_sharp
 * @date    2016/05/18
 * @brief   USART割り込み関数登録のドライバです。
 */ 

#include "stm32f2xx.h"
#include "USARTIRQDriver.h"

#define UART_NUM 6

UART_IRQ_FNC uart_irq_func_table[UART_NUM]={NULL};

void setUART_IRQ_Func(USART_TypeDef* USARTx,UART_IRQ_FNC func){
	int uart_index;
	if(USARTx==USART1){
		uart_index=0;
	}else if(USARTx==USART2){
		uart_index=1;
#ifdef USART3
	}else if(USARTx==USART3){
		uart_index=2;
#endif
#ifdef UART4
	}else if(USARTx==UART4){
		uart_index=3;
#endif
#ifdef UART5
	}else if(USARTx==UART5){
		uart_index=4;
#endif
	}else if(USARTx==USART6){
		uart_index=5;
	}else{
		return;
	}
	
	uart_irq_func_table[uart_index]=func;
	
}

__weak void USART1_IRQHandler(){
	if(uart_irq_func_table[0]!=NULL)uart_irq_func_table[0](1);
}

__weak void USART2_IRQHandler(){
	if(uart_irq_func_table[1]!=NULL)uart_irq_func_table[1](2);
}

#ifdef USART3
__weak void USART3_IRQHandler(){
	if(uart_irq_func_table[2]!=NULL)uart_irq_func_table[2](3);
}
#endif

#ifdef UART4
__weak void UART4_IRQHandler(){
	if(uart_irq_func_table[3]!=NULL)uart_irq_func_table[3](4);
}
#endif

#ifdef UART5
__weak void UART5_IRQHandler(){
	if(uart_irq_func_table[4]!=NULL)uart_irq_func_table[4](5);
}
#endif

__weak void USART6_IRQHandler(){
	if(uart_irq_func_table[5]!=NULL)uart_irq_func_table[5](6);
}
