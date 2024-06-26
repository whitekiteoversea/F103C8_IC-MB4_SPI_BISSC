#ifndef __SPI_H
#define __SPI_H

#include "stm32f1xx_hal.h"
#include "mb4_1sf_driver.h"
#include "stdio.h"	
	 				    
#define HAL_BISSC_ENABLE    (1)
#define HAL_BISSC_TEST      (1)

#ifdef HAL_BISSC_ENABLE
// SPI2 BISS-C Operation
#define	GPIO_SPI_BISSC_CS_SET  	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define	GPIO_SPI_BISSC_SCLK_SET  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
#define	GPIO_SPI_BISSC_MISO_SET  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)   
#define	GPIO_SPI_BISSC_MOSI_SET  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET)  

#define	GPIO_SPI_BISSC_CS_RESET  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define	GPIO_SPI_BISSC_SCLK_RESET  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
#define	GPIO_SPI_BISSC_MISO_RESET  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)   
#define	GPIO_SPI_BISSC_MOSI_RESET  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET)  

enum BISSC_CMD {
    WriteData = 0x02,
    ReadData = 0x03,
    ReadStatus = 0x05,
    WriteInstruction = 0x07,
    ReadData0 = 0x09,
    WriteData0 = 0x0b 
};

#endif

#ifdef HAL_BISSC_ENABLE
    void HAL_BISSC_Setup(void);
    uint8_t HAL_SG_SenSorAcquire(uint8_t *SG_Data); 
    void HAL_CTLRegsWrite_Slave0(uint8_t reg_addr, uint8_t reg_data); // 写寄存器
    uint8_t HAL_CTLRegs_Read_Slave0(uint8_t readAddr);
#endif

// 毫秒延时
void HAL_Delay_us(uint32_t nus);

extern SPI_HandleTypeDef hspi1;
		 
#endif

