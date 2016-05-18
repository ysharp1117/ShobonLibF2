/**
 * @file    DMADriver.c
 * @author  \@y_sharp
 * @date    2016/05/18
 * @brief   DMAを柔軟に扱うためのドライバです。
 */ 
#include "DMADriver.h"

uint32_t dma_table[2] = {DMA1_BASE,DMA2_BASE};
uint32_t dma_stream_table[2][8] = {{
	DMA1_Stream0_BASE,
	DMA1_Stream1_BASE,
	DMA1_Stream2_BASE,
	DMA1_Stream3_BASE,
	DMA1_Stream4_BASE,
	DMA1_Stream5_BASE,
	DMA1_Stream6_BASE,
	DMA1_Stream7_BASE
},{
	DMA2_Stream0_BASE,
	DMA2_Stream1_BASE,
	DMA2_Stream2_BASE,
	DMA2_Stream3_BASE,
	DMA2_Stream4_BASE,
	DMA2_Stream5_BASE,
	DMA2_Stream6_BASE,
	DMA2_Stream7_BASE
}};

DMA_IRQ_FNC dma_irq_func_table[2][8]={{0}};

void setDMAIRQ_Func(DMA_TypeDef* dma,int stream,DMA_IRQ_FNC func){
	int dma_index;
	if(dma==DMA1){
		dma_index=0;
	}else if(dma==DMA2){
		dma_index=1;
	}else{
		return;
	}
	
	dma_irq_func_table[dma_index][stream]=func;
	
}

__weak void DMA1_Stream0_IRQHandler(){
	if(dma_irq_func_table[0][0]!=0)dma_irq_func_table[0][0](1,0);
}

__weak void DMA1_Stream1_IRQHandler(){
	if(dma_irq_func_table[0][1]!=0)dma_irq_func_table[0][1](1,1);
}

__weak void DMA1_Stream2_IRQHandler(){
	if(dma_irq_func_table[0][2]!=0)dma_irq_func_table[0][2](1,2);
}

__weak void DMA1_Stream3_IRQHandler(){
	if(dma_irq_func_table[0][3]!=0)dma_irq_func_table[0][3](1,3);
}

__weak void DMA1_Stream4_IRQHandler(){
	if(dma_irq_func_table[0][4]!=0)dma_irq_func_table[0][4](1,4);
}

__weak void DMA1_Stream5_IRQHandler(){
	if(dma_irq_func_table[0][5]!=0)dma_irq_func_table[0][5](1,5);
}

__weak void DMA1_Stream6_IRQHandler(){
	if(dma_irq_func_table[0][6]!=0)dma_irq_func_table[0][6](1,6);
}

__weak void DMA1_Stream7_IRQHandler(){
	if(dma_irq_func_table[0][7]!=0)dma_irq_func_table[0][7](1,7);
}

__weak void DMA2_Stream0_IRQHandler(){
	if(dma_irq_func_table[1][0]!=0)dma_irq_func_table[1][0](2,0);
}

__weak void DMA2_Stream1_IRQHandler(){
	if(dma_irq_func_table[1][1]!=0)dma_irq_func_table[1][1](2,1);
}

__weak void DMA2_Stream2_IRQHandler(){
	if(dma_irq_func_table[1][2]!=0)dma_irq_func_table[1][2](2,2);
}

__weak void DMA2_Stream3_IRQHandler(){
	if(dma_irq_func_table[1][3]!=0)dma_irq_func_table[1][3](2,3);
}

__weak void DMA2_Stream4_IRQHandler(){
	if(dma_irq_func_table[1][4]!=0)dma_irq_func_table[1][4](2,4);
}

__weak void DMA2_Stream5_IRQHandler(){
	if(dma_irq_func_table[1][5]!=0)dma_irq_func_table[1][5](2,5);
}

__weak void DMA2_Stream6_IRQHandler(){
	if(dma_irq_func_table[1][6]!=0)dma_irq_func_table[1][6](2,6);
}

__weak void DMA2_Stream7_IRQHandler(){
	if(dma_irq_func_table[1][7]!=0)dma_irq_func_table[1][7](2,7);
}

