/**
 * @file    USARTDriver.h
 * @author  \@y_sharp
 * @date    2016/11/08
 * @brief   USARTを用いたマルチバッファ送信のドライバです。
 * syscalls.c 内で標準出力の出力先として利用されています。ユーザが利用する必要はありません。
 * ShobonDeviceDriver.hを介してincludeされるので単体でincludeする必要はありません。
 */ 

#ifndef __SHOBON_USART_DRIVER__
#define __SHOBON_USART_DRIVER__

#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup USARTDriver USARTドライバ
 * @par
 * USARTドライバですが現在単一のUSARTのマルチバッファ通信のみ実装しています。
 * @par
 * ユーザが自由に利用することは出来ません。初期化はSystemInit()で呼び出されているので不要です。
 */

extern const uint32_t usart_list[];
extern const uint32_t usart_clock_apb1[];
extern const uint32_t usart_clock_apb2[];
extern const uint32_t uart_irqn_table[];

extern uint8_t getAFR(USART_TypeDef* usart);
extern void setBaudRate(USART_TypeDef* usart,float baudrate);

extern void USART_Init();
extern int send_str_DMA(char str[],size_t size);
extern int8_t getUARTBuffer(int no,uint8_t *dat);
extern void uart_rx_irq_callback_func(int call_uart);

#ifdef __cplusplus
}
#endif

#endif
