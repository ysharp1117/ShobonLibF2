/**
 * @file    System.c
 * @author  \@y_sharp
 * @date    2016/05/18
 * @brief   他のドライバで共通利用する低水準な領域を扱うドライバです。
 */ 
#include "stm32f2xx.h"
#include "System.h"
#include "GPIODriver.h"
#include "Delay.h"

/**
 * @ingroup System
 * @brief 現在のシステムクロックの値を返します。
 * @return システムクロック[Hz]
 */
uint32_t getSYSCLK(){
	uint32_t temp = RCC->CFGR;
	uint32_t res = HSI_VALUE;
	
	switch((temp>>2)&0x3){
	case 0x00:
		res = HSI_VALUE;
		break;
	case 0x01:
		res = HSE_VALUE;
		break;
	case 0x02:
		{
			int presq_m,presq_n,presq_p;
			uint32_t temp2 = RCC->PLLCFGR;
			uint32_t pll_source=HSI_VALUE;
			
			presq_m = (temp2&RCC_PLLCFGR_PLLM)>>0;
			presq_n = (temp2&RCC_PLLCFGR_PLLN)>>6;
			presq_p = (((temp2&RCC_PLLCFGR_PLLP)>>16)+1)*2;
			
			//外部クロックかつHSE有効の場合
			if((temp2&RCC_PLLCFGR_PLLSRC)&&(RCC->CR&RCC_CR_HSERDY)){
				pll_source = HSE_VALUE;
			}
			
			res = (uint64_t)pll_source*presq_n/(presq_m*presq_p);
		}
		break;
	}
	
	return res;
}

/**
 * @ingroup System
 * @brief 現在のAHBバスのクロックを返します。
 * @return 現在のAHBバスのクロック[Hz]
 */
uint32_t getAHBCLK(){
	uint32_t presq;
	uint32_t temp = (RCC->CFGR&RCC_CFGR_HPRE)>>4&0xf;
	
	if(temp&0x08){
		unsigned int i;
		temp &= ~(0x08);
		presq = 2;
		for(i=0;i<temp;i++){
			presq*=2;
		}
	}else{
		presq = 1;
	}
	
	return getSYSCLK()/presq;
}

/**
 * @ingroup System
 * @brief 現在のAPB1バスのクロックを返します。
 * @return 現在のAPB1バスのクロック[Hz]
 */
uint32_t getAPB1CLK(){
	uint32_t presq;
	uint32_t temp = (RCC->CFGR&RCC_CFGR_PPRE1)>>10&0x7;
	
	if(temp&0x04){
		unsigned int i;
		temp &= ~(0x04);
		presq = 2;
		for(i=0;i<temp;i++){
			presq*=2;
		}
	}else{
		presq = 1;
	}
	
	return getAHBCLK()/presq;
}

/**
 * @ingroup System
 * @brief 現在のAPB2バスのクロックを返します。
 * @return 現在のAPB2バスのクロック[Hz]
 */
uint32_t getAPB2CLK(){
	uint32_t presq;
	uint32_t temp = (RCC->CFGR&RCC_CFGR_PPRE2)>>13&0x7;
	
	if(temp&0x04){
		unsigned int i;
		temp &= ~(0x04);
		presq = 2;
		for(i=0;i<temp;i++){
			presq*=2;
		}
	}else{
		presq = 1;
	}
	
	return getAHBCLK()/presq;
}

/**
 * @ingroup System
 * @brief タイマのクロックを返します。
 * @param TIMx クロックを取得するタイマペリフェラル
 * @return タイマのクロック[Hz]
 */
uint32_t getTIMxCLK(TIM_TypeDef *TIMx){
	uint32_t res=0;
	
	switch((uint32_t)TIMx){
	case TIM1_BASE:
#ifdef TIM8_BASE
	case TIM8_BASE:
#endif
	case TIM9_BASE:
	case TIM10_BASE:
	case TIM11_BASE:
		res = getAPB2CLK();
		if(RCC->CFGR&RCC_CFGR_PPRE2_2)res *= 2;//APB2プリスケーラ比が1以外の時2倍
		break;
	case TIM2_BASE:
	case TIM3_BASE:
	case TIM4_BASE:
	case TIM5_BASE:
#ifdef TIM6_BASE
	case TIM6_BASE:
#endif
#ifdef TIM7_BASE
	case TIM7_BASE:
#endif
#ifdef TIM12_BASE
	case TIM12_BASE:
#endif
#ifdef TIM13_BASE
	case TIM13_BASE:
#endif
#ifdef TIM14_BASE
	case TIM14_BASE:
#endif
		res = getAPB1CLK();
		if(RCC->CFGR&RCC_CFGR_PPRE1_2)res *= 2;//APB1プリスケーラ比が1以外の時2倍
		break;
	}
	return res;
}

/**
 * @ingroup System
 * @brief デバッガ用のピンをSWD接続の2ピン(PA13/14)を除いて一般のピンに設定します。
 * @return 戻り値はありません。
 */
void DebugPinInit(){
	//GPIOA,GPIOBにクロックを供給
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
	
	//オルタネート機能モードからフローティング入力に変更して無効にする
	//JTAG無効
	//PA15(JTDI)
	GPIO_SetInput(GPIOA,1<<15);
	//PB3(JTDO/TRACESWO)/PB4(NJTRST)
	GPIO_SetInput(GPIOB,(1<<4)|(1<<3));
	
	//SWDも無効
	//PA13(JTMS-SWDIO)/PA14(JTCK-SWCLK)
	//GPIO_SetInput(GPIOA,(1<<14)|(1<<13));
}

/**
 * @ingroup System
 * @brief 割り込み優先度グループの設定を行います。4bitの優先度を2bitをグループ優先度，サブ優先度にそれぞれ割り当てています。SystemInit()関数で自動的に呼び出されます。
 * @return 戻り値はありません。
 */
void NVICGroupInit(){
	#define SUB_PRIO_CNT 2//(0~4)
	
	SCB->AIRCR = (0x5FA<<16) | ((SUB_PRIO_CNT+3)<<8);
}
