#include "spi.h"
#include "usart.h"

// 毫秒延时
void HAL_Delay_us(uint32_t nus);


/* SPI1 BISS-C*/
#ifdef HAL_BISSC_ENABLE

static void HAL_BISSC_reStartAGS(void);

// MB4 Wrap_Function
void mb4_spi_transfer(uint8_t *data_tx, uint8_t *data_rx, uint16_t datasize)
{
	uint16_t sendCnt = 0;
	HAL_StatusTypeDef retStatus = HAL_OK;

	GPIO_SPI_BISSC_CS_RESET; 
	
	for (sendCnt=0; sendCnt < datasize; sendCnt++) {
		retStatus = HAL_SPI_TransmitReceive(&hspi1, &data_tx[sendCnt], &data_rx[sendCnt], 1, 5);
		if (retStatus != HAL_OK) {
			printf("SPI1 Send Failed! \n\r");
		}
	}
	GPIO_SPI_BISSC_CS_SET;
}

// 配置 SPI1 BISS-C 基本参数
void HAL_BISSC_Setup(void)
{
	//BiSS/SSI Interface
	uint8_t txData[3] = {0};
	uint8_t rData = 0;
	uint8_t curStatus = 0x00;
	uint8_t readAddr = 0x00;
	
	txData[0] = 0x01;
	mb4_write_registers(0xED, txData, 1); //CFGCH1=0x01 (BiSS C)
	HAL_Delay_us(40);
	txData[0] = 0x08; 
	mb4_write_registers(0xF5, txData, 1); //CFGIF=0x02  (RS422) + external clock Source CLKIN =0
	HAL_Delay_us(40);
	//Single-Cycle Data: Data channel configuration
	txData[0] = 0x5B;
	mb4_write_registers(0xC0, txData, 1); // bit6:ENSCD1=1, bit5-0：SCD data len 26+2= 28, SCDLEN = 0x1C
	HAL_Delay_us(40);
	// CRC Para Setup
	txData[0] = 0x06;
	mb4_write_registers(0xC1, txData, 1); //SELCRCS1=0x00, SCRCLEN1=0x06 (6-bit CRC polynomial 0x43)
	HAL_Delay_us(40);
	txData[0] = 0x00;
	mb4_write_registers(0xC2, txData, 1); //SCRCSTART1(7:0)=0x00 (CRC start value)
	HAL_Delay_us(40);
	txData[0] = 0x00;
	mb4_write_registers(0xC3, txData, 1); //SCRCSTART1(15:8)=0x00 (CRC start value)
	HAL_Delay_us(40);

	//Frame Control: Master configuration
	txData[0] = 0x4;
	mb4_write_registers(0xE6, txData, 1); //FREQS=0x04 (2MHz) SPI Bandwidth
	HAL_Delay_us(40);
	//txData[0] = 0x63;
	txData[0] = 0x63; // 1KHz
	mb4_write_registers(0xE8, txData, 1); //FREQAGS=10KHz 控制RS422的最小循环周期 
	HAL_Delay_us(40);

	for (readAddr = 0xC0; readAddr < 0xFB; readAddr++) {
		mb4_read_registers(readAddr, &rData, 1);
		printf("BISS-C: readAddr 0x%x is 0x%x \r\n", readAddr, rData);
	HAL_Delay_us(40);
	}

	txData[0] = 0x10;
	mb4_write_registers(0xF4, txData, 1);
	HAL_Delay_us(200);

	//Reset SVALID flags
	txData[0] = 0x00;
	mb4_write_registers(0xF1, txData, 1);
	HAL_Delay_us(40);
	//Start AGS
	txData[0] = 0x01;
	mb4_write_registers(0xF4, txData, 1);
	HAL_Delay_us(40);
}

static void HAL_BISSC_reStartAGS(void)
{
	uint8_t txData= 0;
	txData = 0x80;
	mb4_write_registers(0xF4, &txData, 1);// BREAK INSTR
	HAL_Delay_us(40);
	txData = 0x01;
	mb4_write_registers(0xF4, &txData, 1);// AGS RESET
	HAL_Delay_us(40);
}


// 获取传感器过程数据
uint8_t HAL_SG_SenSorAcquire(uint8_t *SG_Data) 
{
	uint8_t cnt = 0;
	uint8_t curStatus = 0;
	uint8_t TxData[8] = {0};
	uint8_t RxData[8] = {0};
	uint8_t StatusInformationF0 = 0x00;
	uint8_t StatusInformationF1 = 0x00;
	uint8_t ret = 0;

	//Read Status Information register 0xF0, wait for end of transmission EOT=1
	mb4_read_status(&StatusInformationF0, 1);
	if (StatusInformationF0 & 0x01 == 0) { 
		printf("BISS-C: Step 1 EOT != 1 \n\r");
		goto __end;
	}

	if (StatusInformationF0 & 0x70 != 0x70 ) { // SCDERR OR AGSERR
		printf("BISS-C: Step 2 ERR Occur! nAGSERR is %d nSCDERR is %d, reStart AGS! \n\r", ((StatusInformationF0 & 0x40) >> 6), ((StatusInformationF0 & 0x10) >> 4));
		HAL_BISSC_reStartAGS();	
		goto __end;	
	}

	mb4_read_registers(0xF1, &StatusInformationF1, 1);
	if (StatusInformationF1 & 0x02 != 0x02) {  // CRC校验未通过 SVALID0 = 0
		printf("BISS-C: Step 3 SVALID1 not set 1! reStart AGS! \n\r");
		HAL_BISSC_reStartAGS();
		goto __end;
	}
	printf("BISS-C:  Step 4 Read 0xF1 Value: %x \n\r", StatusInformationF1);
	
	// NO Error Occur
	if ((StatusInformationF0 & 0x70) == 0x70) {  
		if (StatusInformationF1 & 0x02 == 0) { // if SVALID1 != 1 ReStart AGS
			printf(" BISS-C:Step 5 Acquire SG Data Failed! StatusInformationF1 is %d \n\r", StatusInformationF1);
			HAL_BISSC_reStartAGS();
		} else { 
			for (cnt = 0; cnt<4; cnt++) {
				mb4_read_registers(cnt, &SG_Data[cnt], 1);
				printf(" BISS-C: Step 6 SGData[%d]: %d \n\r", cnt, SG_Data[cnt]);
			}
		}
	} else {
		printf("BISS-C: Step 7 ERROR Occur! Now StatusInformationF0 is 0x%x \n\r", StatusInformationF0);
		HAL_BISSC_reStartAGS();
	}
__end:
	return ret;
}

void HAL_CTLRegsWrite_Slave0(uint8_t reg_addr, uint8_t reg_data)
{
	uint8_t TxData = 0x00;
	uint8_t MasterRegisterValue = 0x00;
	
	mb4_read_registers(0xF0, &MasterRegisterValue, 1);
	printf("Acquire regs 0xF0: %2x", MasterRegisterValue);
	
	TxData = (0x01 << 7) | reg_addr;  
	mb4_write_registers(0xE2, &TxData, 1); //写操作 写的Slave传感器目的寄存器地址:
	TxData = 0x00;
	mb4_write_registers(0xE3, &TxData, 1); //REGNUM=0x00 (only 1 slave registers) 向0xE3写0代表传输单个寄存器的设置值 

	TxData = 0x01;
	mb4_write_registers(0xE4, &TxData, 1); //CHSEL(1)=1 (selects channel 1 for control communication)
	TxData = 0xC0;
	mb4_write_registers(0xE5, &TxData, 1); //CTS=1 (register access), REGVERS=1 (BiSS C), SLAVEID=0 这里就已经决定了是向 Slave0的寄存器进行控制数据传输
	mb4_write_registers(0x80, &reg_data, 1); //RDATA=BankAddress 从0x80开始到0xBF 一共64字节，是MB4芯片的临时数据存储区域

	//Start register communication with slave
	TxData = 0x09;
	mb4_write_registers(0xF4, &TxData, 1); //AGS=1, INSTR=4 (start control communication) instruction = 4, 传感器数据自动获取 AutoGetSensorData =1
	
	mb4_read_registers(0xF4, &MasterRegisterValue, 1);
	
	//wait until INSTR (address 0xF4) is reset (AGS remains 1) （等待INSTR置位，除错处理）
	while (MasterRegisterValue > 1) {
		mb4_read_registers(0xF4, &MasterRegisterValue, 1); // 写入后读取当前寄存器值以验证是否写入成功
	}

	//Read status register
	//Register communication successful if nREGERR=1 (bit3) and REGEND=1 (bit2)
	mb4_read_registers(0xF0, &MasterRegisterValue, 1);
	if (!(MasterRegisterValue & 0xC0)){
		printf(" BISS-C Write Regs Failed!\n\r");
	}
}

// 单通信周期内1个寄存器内容的实例
uint8_t HAL_CTLRegs_Read_Slave0(uint8_t readAddr)
{
	uint8_t SlaveRegValue = 0x00;
	uint8_t MasterRegisterValue = 0x00;
	uint8_t txData[8] = {0};

	//Configuration for reading slave register
	txData[0] = 0x7E;
	mb4_write_registers(0xE2, txData, 1); //WNR=0 / REGADR=0x7E 选择为读：
	txData[0] = 0x01;
	mb4_write_registers(0xE3, txData, 1); //REGNUM=0x01 (2 consecutive slave registers)
	txData[0] = 0x01;
	mb4_write_registers(0xE4, txData, 1); //CHSEL(1)=1 (selects channel 1 for control communication)
	txData[0] = 0xC0;
	mb4_write_registers(0xE5, txData, 1); //CTS=1 (register access), REGVERS=1 (BiSS C), SLAVEID=0

	//Start slave register communication
	txData[0] = 0x09;
	mb4_write_registers(0xF4, txData, 1); //AGS=1 / INSTR=4 (start control communication)

	mb4_read_registers(0xF4, &MasterRegisterValue, 1);
	while (MasterRegisterValue > 1) {//wait until INSTR (address 0xF4) is reset (AGS remains 1)
		mb4_read_registers(0xF4, &MasterRegisterValue, 1);
	} 

	//Read status register
	//Register communication successful if nREGERR=1 (bit3) and REGEND=1 (bit2)
	mb4_read_registers(0xF0, &MasterRegisterValue, 1);

	//Read slave register values
	mb4_read_registers(readAddr, &SlaveRegValue, 1);

	return SlaveRegValue;
}

#endif

// 毫秒延时
void HAL_Delay_us(uint32_t nus)
{
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000000);
    //调用系统自带的延时函函数
	HAL_Delay(nus - 1);
    //将定时中断恢复为1ms中断
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
}