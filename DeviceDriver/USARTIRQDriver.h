/**
 * @file    USARTIRQDriver.h
 * @author  \@y_sharp
 * @date    2016/05/18
 * @brief   USART割り込み関数登録のドライバです。
 */ 

#ifndef __SHOBON_USART_IRQ_DRIVER__
#define __SHOBON_USART_IRQ_DRIVER__

#ifdef __cplusplus
extern "C"{
#endif

typedef void (*UART_IRQ_FNC)(int);

extern void setUART_IRQ_Func(USART_TypeDef* USARTx,UART_IRQ_FNC func);

#ifdef __cplusplus
}
#endif

#endif
