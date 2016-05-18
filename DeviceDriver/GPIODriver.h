/**
 * @file    GPIODriver.h
 * @author  \@y_sharp
 * @date    2016/05/18
 * @brief   GPIOペリフェラルへのアクセスを行います。
 */ 

#ifndef GPIO_DRIVER
#define GPIO_DRIVER

enum{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	PORT_NUM,
};

extern GPIO_TypeDef* gpio_base_table[PORT_NUM];
extern const uint32_t gpio_clock_table[PORT_NUM];

extern void GPIO_SetInput(GPIO_TypeDef* gpio,int pin);
extern void GPIO_SetOutput(GPIO_TypeDef* gpio,int pin);
extern void GPIO_SetAFMode(GPIO_TypeDef* gpio,int pin);
extern void GPIO_SetAnalogMode(GPIO_TypeDef* gpio,int pin);
extern void GPIO_SetPullUp(GPIO_TypeDef* gpio,int pin);
extern void GPIO_SetPullDown(GPIO_TypeDef* gpio,int pin);
extern void GPIO_ResetPullUpDown(GPIO_TypeDef* gpio,int pin);
extern void GPIO_SetAFR(GPIO_TypeDef* gpio,int pin,uint8_t afr);

#endif
