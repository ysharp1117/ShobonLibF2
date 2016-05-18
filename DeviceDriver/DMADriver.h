/**
 * @file    DMADriver.h
 * @author  \@y_sharp
 * @date    2016/05/18
 * @brief   DMAを柔軟に扱うためのドライバです。
 */ 

#ifndef ___SHOBON_DMA_DRIVER__
#define ___SHOBON_DMA_DRIVER__

#include "stm32f2xx.h"

#ifdef __cplusplus
extern "C"{
#endif

extern uint32_t dma_table[2];
extern uint32_t dma_stream_table[2][8];

typedef void (*DMA_IRQ_FNC)(int, int);

extern void setDMAIRQ_Func(DMA_TypeDef* dma,int stream,DMA_IRQ_FNC func);

#ifdef __cplusplus
}
#endif

#endif
