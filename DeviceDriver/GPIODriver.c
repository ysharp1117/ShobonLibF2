/**
 * @file    GPIODriver.c
 * @author  \@y_sharp
 * @date    2016/05/18
 * @brief   GPIOペリフェラルへのアクセスを行います。
 */ 

#include "stm32f2xx.h"
#include "GPIODriver.h"

GPIO_TypeDef* gpio_base_table[PORT_NUM]= {
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	GPIOH,
	GPIOI,
};

//GPIOクロックテーブル
const uint32_t gpio_clock_table[PORT_NUM]={
	RCC_AHB1ENR_GPIOAEN,
	RCC_AHB1ENR_GPIOBEN,
	RCC_AHB1ENR_GPIOCEN,
	RCC_AHB1ENR_GPIODEN,
	RCC_AHB1ENR_GPIOEEN,
	RCC_AHB1ENR_GPIOFEN,
	RCC_AHB1ENR_GPIOGEN,
	RCC_AHB1ENR_GPIOHEN,
	RCC_AHB1ENR_GPIOIEN,
};

void GPIO_SetInput(GPIO_TypeDef* gpio,int pin){
	uint32_t temp;
	int i=0;
	int index;
	
	while(pin>>i){
		if((pin>>i)&0x01){
			index=i;
			//格納
			temp = gpio->MODER;
			
			temp &= ~(0x3<<(index*2));
			
			//セット
			gpio->MODER = temp;
		}
		i++;
	}
	
}

void GPIO_SetOutput(GPIO_TypeDef* gpio,int pin){
	uint32_t temp;
	int i=0;
	int index;
	
	while(pin>>i){
		if((pin>>i)&0x01){
			index=i;
			//格納
			temp = gpio->MODER;
			
			temp &= ~(0x3<<(index*2));
			temp |= 0x1<<(index*2);
			
			//セット
			gpio->MODER = temp;
		}
		i++;
	}
	
}

void GPIO_SetAFMode(GPIO_TypeDef* gpio,int pin){
	uint32_t temp;
	int i=0;
	int index;
	
	while(pin>>i){
		if((pin>>i)&0x01){
			index=i;
			//格納
			temp = gpio->MODER;
			
			temp &= ~(0x3<<(index*2));
			temp |= 0x2<<(index*2);
			
			//セット
			gpio->MODER = temp;
		}
		i++;
	}
	
}

void GPIO_SetAnalogMode(GPIO_TypeDef* gpio,int pin){
	uint32_t temp;
	int i=0;
	int index;
	
	while(pin>>i){
		if((pin>>i)&0x01){
			index=i;
			//格納
			temp = gpio->MODER;
			
			temp &= ~(0x3<<(index*2));
			temp |= 0x3<<(index*2);
			
			//セット
			gpio->MODER = temp;
		}
		i++;
	}
	
}

void GPIO_SetPullUp(GPIO_TypeDef* gpio,int pin){
	uint32_t temp;
	int i=0;
	int index;
	
	while(pin>>i){
		if((pin>>i)&0x01){
			index=i;
			//格納
			temp = gpio->PUPDR;
			
			temp &= ~(0x3<<(index*2));
			temp |= 0x1<<(index*2);
			
			//セット
			gpio->PUPDR = temp;
		}
		i++;
	}
	
}

void GPIO_SetPullDown(GPIO_TypeDef* gpio,int pin){
	uint32_t temp;
	int i=0;
	int index;
	
	while(pin>>i){
		if((pin>>i)&0x01){
			index=i;
			//格納
			temp = gpio->PUPDR;
			
			temp &= ~(0x3<<(index*2));
			temp |= 0x2<<(index*2);
			
			//セット
			gpio->PUPDR = temp;
		}
		i++;
	}
	
}

void GPIO_ResetPullUpDown(GPIO_TypeDef* gpio,int pin){
	uint32_t temp;
	int i=0;
	int index;
	
	while(pin>>i){
		if((pin>>i)&0x01){
			index=i;
			//格納
			temp = gpio->PUPDR;
			
			temp &= ~(0x3<<(index*2));
			
			//セット
			gpio->PUPDR = temp;
		}
		i++;
	}
	
}

void GPIO_SetAFR(GPIO_TypeDef* gpio,int pin,uint8_t afr){
	uint32_t temp;
	int i=0;
	int index;
	
	while(pin>>i){
		if((pin>>i)&0x01){
			index=i;
			//格納
			temp = gpio->AFR[index/8];
			
			temp &= ~(0xf<<((index%8)*4));
			temp |= (afr<<((index%8)*4));//AFを設定
			
			//セット
			gpio->AFR[index/8] = temp;
		}
		i++;
	}
	
}
