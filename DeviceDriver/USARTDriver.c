/**
 * @file    USARTDriver.c
 * @author  \@y_sharp
 * @date    2016/05/18
 * @brief   USARTを用いたマルチバッファ送信のドライバです。
 * syscalls.c 内で標準出力の出力先として利用されています。ユーザが利用する必要はありません。
 */ 

#include "stm32f2xx.h"
#include "System.h"
#include "GPIODriver.h"
#include "DMADriver.h"
#include "USARTDriver.h"
#include "USARTIRQDriver.h"
#include "Board/USARTSettings.def"

//GPIOテーブル→GPIOポート参照マクロ
#define GPIO(port) ((GPIO_TypeDef*) gpio_base_table[port])

//USARTテーブル
const uint32_t usart_list[]={
	USART1_BASE,
	USART2_BASE,
#ifdef USART3
	USART3_BASE,
#endif
#ifdef UART4
	UART4_BASE,
#endif
#ifdef UART5
	UART5_BASE,
#endif
	USART6_BASE,
};

//USARTクロックテーブル(APB1)
const uint32_t usart_clock_apb1[]={
	0,
	RCC_APB1ENR_USART2EN,
#ifdef USART3
	RCC_APB1ENR_USART3EN,
#else
	0,
#endif
#ifdef UART4
	RCC_APB1ENR_UART4EN,
#else
	0,
#endif
#ifdef UART5
	RCC_APB1ENR_UART5EN,
#else
	0,
#endif
	0,
};

//USARTクロックテーブル(APB2)
const uint32_t usart_clock_apb2[]={
	RCC_APB2ENR_USART1EN,
	0,
	0,
	0,
	0,
	RCC_APB2ENR_USART6EN,
};

const uint32_t uart_irqn_table[] = {
	USART1_IRQn,
	USART2_IRQn,
#ifdef USART3
	USART3_IRQn,
#else
	0,
#endif
#ifdef UART4
	UART4_IRQn,
#else
	0,
#endif
#ifdef UART5
	UART5_IRQn,
#else
	0,
#endif
	USART6_IRQn,
};

uint8_t getAFR(USART_TypeDef* usart){
	if((usart==USART1)|(usart==USART2)
#ifdef USART3
		|(usart==USART3)
#endif
	){
		return 7;
	}else if(0x00
#ifdef UART4
		|(usart==UART4)
#endif
#ifdef UART5
		|(usart==UART5)
#endif
		|(usart==USART6)
	){
		return 8;
	}
	return 0;
}

void setBaudRate(USART_TypeDef* usart,float baudrate){
	uint32_t usart_clk=0x00;
	
	if((usart==USART1)|(usart==USART6)){
		usart_clk = getAPB2CLK();
	}else if((usart==USART2)
#ifdef USART3
		|(usart==USART3)
#endif
#ifdef UART4
		|(usart==UART4)
#endif
#ifdef UART5
		|(usart==UART5)
#endif
	){
		usart_clk = getAPB1CLK();
	}
	
	usart->BRR = usart_clk/(8*(2-(usart->CR1&USART_CR1_OVER8?1:0))*baudrate)*16;
	
}

static void pc_send_dma_callback_func(int call_dma,int call_stream_no);

static void DMA_USARTx_TX_Init(){
	uint32_t temp;
	USART_TypeDef* USARTx = (USART_TypeDef*)usart_list[USART-1];

	//割り込みの登録
	setDMAIRQ_Func(USARTx_TX_DMA,USARTx_TX_DMA_Stream_No,pc_send_dma_callback_func);
	//優先度4bitをグループ優先度2bit,サブ優先度2bitに設定
	NVICGroupInit();
	//割り込み設定(グループ優先度1に設定)
	NVIC_SetPriority(USARTx_TX_DMA_Stream_IRQn,(1<<2)|(0<<0));
	NVIC_EnableIRQ(USARTx_TX_DMA_Stream_IRQn);
	
	//DMAにクロック供給
	if(USARTx_TX_DMA==DMA1){
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	}else if(USARTx_TX_DMA==DMA2){
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	}
	
	//ペリフェラルのアドレスを代入
	USARTx_TX_DMA_Stream->PAR = (uint32_t)&USARTx->DR;
	
	//CRレジスタの設定
	temp = 0x00;//初期化
	//メモリインクリメントモードに設定
	temp |= DMA_SxCR_MINC;
	
	//ペリフェラルへの書き込みに設定
	temp |= DMA_SxCR_DIR_0;
	
	//転送完了割り込みを有効
	temp |= DMA_SxCR_TCIE;
	
	//ペリフェラルからのデータとメモリのサイズを指定
	temp &= ~(DMA_SxCR_MSIZE|DMA_SxCR_PSIZE);
	temp |= 0x00|0x00;//双方共に8bitに指定
	
	//Chanellを USARTx_TXに設定
	temp |= USARTx_TX_DMA_Ch<<25;
	
	//CRレジスタの設定を反映
	USARTx_TX_DMA_Stream->CR = temp;
	
}

static uint8_t initialized = 0;

void USART_Init(){
	USART_TypeDef* USARTx = (USART_TypeDef*)usart_list[USART-1];
	
	if(initialized)return;
	initialized=1;
	
	//GPIOにクロックを供給
	RCC->AHB1ENR |= gpio_clock_table[TX_PORT] | gpio_clock_table[RX_PORT];
	//利用するUSARTにクロックを供給
	RCC->APB1ENR |= usart_clock_apb1[USART-1];
	RCC->APB2ENR |= usart_clock_apb2[USART-1];
	
	//TXピンの設定
	GPIO_SetAFMode(GPIO(TX_PORT),1<<TX_PIN);//AF Modeに設定
	GPIO(TX_PORT)->OTYPER &= ~(0x1<<TX_PIN);//プッシュプルに設定
	GPIO(TX_PORT)->OSPEEDR |= 0x3<<(TX_PIN*2);//最大100MHz出力に設定
	GPIO_ResetPullUpDown(GPIO(TX_PORT),1<<TX_PIN);//プルダウン、プルアップ無し
	GPIO_SetAFR(GPIO(TX_PORT),1<<TX_PIN,getAFR(USARTx));
	
	//RXピンの設定
	GPIO_SetAFMode(GPIO(RX_PORT),1<<RX_PIN);//AF Modeに設定
	GPIO_ResetPullUpDown(GPIO(RX_PORT),1<<RX_PIN);//プルダウン、プルアップ無し
	GPIO_SetAFR(GPIO(RX_PORT),1<<RX_PIN,getAFR(USARTx));
	
	//DMAの初期化
	DMA_USARTx_TX_Init();
	
	//USARTを有効化
	USARTx->CR1 |= USART_CR1_UE;
	
	//データ長は8bit
	USARTx->CR1 &= ~USART_CR1_M;
	
	//ストップビットは1
	USARTx->CR2 &= ~USART_CR2_STOP;
	
	//トランスミッタはDMAを用いる
	USARTx->CR3 |= USART_CR3_DMAT;
	
	//ボーレートの設定(クロックから自動計算)
	setBaudRate(USARTx,BaudRate);
	
	//トランスミッタの有効化
	USARTx->CR1 |= USART_CR1_TE;
	
	//受信割り込み有効
	setUART_IRQ_Func(USARTx,uart_rx_irq_callback_func);
	USARTx->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(uart_irqn_table[USART-1]);
	
	//レシーバの有効化
	USARTx->CR1 |= USART_CR1_RE;
	
	//DMA受信の有効化
	//USARTx->CR3 |= USART_CR3_DMAR;
}

#define UART_NUM 8//UARTの個数
#define TRNS_CNT (1<<TRNS_CNT_BIT)//バッファの個数

typedef struct{
	uint8_t enable;
	uint8_t trns_buf[TRNS_CNT][TRNS_BUF];
	uint32_t trns_cnt[TRNS_CNT];
	uint32_t trns_data_cnt;
	uint32_t trns_proc_now;
}UART_SEND_DMA_QUEUE;

static volatile UART_SEND_DMA_QUEUE uart_send_queue[UART_NUM]={0};

static volatile uint8_t trns_buf[TRNS_CNT][TRNS_BUF]={{0}};
static volatile uint8_t trns_cnt[TRNS_CNT]={0};
static uint16_t trns_data_cnt=0;
static uint16_t trns_proc_now=0;

static void setTransmitStatus(int state){
	if(state){
		//DMA Streamを有効化
		USARTx_TX_DMA_Stream->CR |= DMA_SxCR_EN;
	}else{
		//DMA Streamを無効化
		USARTx_TX_DMA_Stream->CR &= ~DMA_SxCR_EN;
	}
}

static void setTransmitData(uint32_t* addr,int size){
	USARTx_TX_DMA_Stream->M0AR = (uint32_t)addr;
	USARTx_TX_DMA_Stream->NDTR = size;
	setTransmitStatus(1);
}

int send_str_DMA(char str[],uint16_t size){
	int i;
	
	__disable_irq();
	
	//キューが満タンの場合はエラーを返す
	if(trns_data_cnt>=TRNS_CNT){
		i=-1;
	}else{
		//バッファサイズを超える場合はバッファサイズまで格納
		if(size>TRNS_BUF)size=TRNS_BUF;
		
		for(i=0;i<size;i++){
			trns_buf[trns_proc_now][i] = *str++;
			if(trns_buf[trns_proc_now][i]=='\0')break;
		}
		
		if(i!=0){//0バイト送信はしない
			//送信バイト数を格納
			trns_cnt[trns_proc_now] = i;
			
			//キューにタスクが現在の1個の場合は直ちにDMA送信
			trns_data_cnt++;//キューの個数をインクリメント
			if(trns_data_cnt==1){
				setTransmitData((uint32_t*)trns_buf[trns_proc_now],trns_cnt[trns_proc_now]);
			}
			
			//バッファ管理カウンタをインクリメント
			trns_proc_now++;
			trns_proc_now &= TRNS_CNT-1;
		}
	}
	
	__enable_irq();
	
	return i;
}

static void pc_send_dma_callback_func(int call_dma,int call_stream_no){
	DMA_TypeDef* DMAx = (DMA_TypeDef*)dma_table[call_dma-1];
	
	__disable_irq();
	
	//DMA Streamを無効化
	setTransmitStatus(0);
	//DMA送信終了したので割り込みフラグを消してDMAを無効にする
	if(call_stream_no>5){
		DMAx->HIFCR = DMA_HIFCR_CTCIF6<<((call_stream_no-6)*6);
	}else if(call_stream_no>3){
		DMAx->HIFCR = DMA_HIFCR_CTCIF4<<((call_stream_no-4)*6);
	}else if(call_stream_no>1){
		DMAx->LIFCR = DMA_LIFCR_CTCIF2<<((call_stream_no-2)*6);
	}else{
		DMAx->LIFCR = DMA_LIFCR_CTCIF0<<(call_stream_no*6);
	}
	
	//カウンタを1減らす
	trns_data_cnt--;
	
	//キューに残っているタスクがある場合は続いて送信
	if(trns_data_cnt>0){
		int index = (trns_proc_now-trns_data_cnt+TRNS_CNT)&(TRNS_CNT-1);
		setTransmitData((uint32_t*)trns_buf[index],trns_cnt[index]);
	}
	
	__enable_irq();
}

#define RX_BUF_SIZE_BIT 7
#define RX_BUF_SIZE (1<<RX_BUF_SIZE_BIT)
static volatile char usart_rx_buf[UART_NUM][RX_BUF_SIZE]={{0}};
static volatile int rx_in_ptr[UART_NUM]={0};
static volatile int rx_out_ptr[UART_NUM]={0};

int8_t getUARTBuffer(int no,uint8_t *dat){
	if(rx_in_ptr[no]==rx_out_ptr[no]){
		return -1;
	}
	*dat = usart_rx_buf[no][rx_out_ptr[no]];
	rx_out_ptr[no] = (rx_out_ptr[no]+1)&(RX_BUF_SIZE-1);
	return 0;
}

void uart_rx_irq_callback_func(int call_uart){
	USART_TypeDef* USARTx = (USART_TypeDef*)usart_list[call_uart-1];
	uint32_t sr;
	
	__disable_irq();
	
	sr = USARTx->SR;
	
	if((sr&USART_SR_RXNE)||(sr&USART_SR_ORE)){
		usart_rx_buf[call_uart-1][rx_in_ptr[call_uart-1]] = USARTx->DR;
		rx_in_ptr[call_uart-1] = (rx_in_ptr[call_uart-1]+1)&(RX_BUF_SIZE-1);
	}
	
	__enable_irq();
}
