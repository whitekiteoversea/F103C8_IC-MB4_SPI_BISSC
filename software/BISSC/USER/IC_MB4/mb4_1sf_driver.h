/**
 ******************************************************************************
 * @file    mb4_1sf_driver.h
 * @author  iC-Haus GmbH
 * @version 1.1.0
 * @note Designed according to iC-MB4 datasheet release D2 for chip revision Y.
 ******************************************************************************
 * @attention
 *
 *	Software and its documentation is provided by iC-Haus GmbH or contributors "AS IS" and is
 *	subject to the ZVEI General Conditions for the Supply of Products and Services with iC-Haus
 *	amendments and the ZVEI Software clause with iC-Haus amendments (http://www.ichaus.de/EULA).
 *
 ******************************************************************************
 */

#ifndef MB4_1SF_DRIVER_H
#define MB4_1SF_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

/**
 * @defgroup Wrapper_Functions
 * @brief Functions declared as `extern` are to be defined by the user according to the individual MCU.
 *
 * @note The definition of those functions is mandatory for proper use of this driver.
 * @{
 */
/**
 * @brief This function is a wrapper to be defined with the hardware-related SPI-transmit-receive-function.
 *
 * @param data_tx is a pointer to the data buffer that is transmitted.
 * @param data_rx is a pointer to the buffer the received data is written to.
 * @param datasize is the length of all bytes transmitted.
 * @retval None
 */
extern void mb4_spi_transfer(uint8_t *data_tx, uint8_t *data_rx, uint16_t datasize);
/**
 * @}
 */

/**
 * @defgroup MB4_Parameters
 * @{
 */
/**
 * @addtogroup MB4_Parameters_Struct
 * @brief Structure implemented to represent iC-MB4 parameters.
 * @{
 */
struct mb4_param {
	uint8_t addr;
	uint8_t pos;
	uint8_t len;
};
/**
 * @}
 */

/**
 * @addtogroup MB4_Parameters_List
 * @brief List of parameters according to iC-MB4 register map represented as @ref MB4_Parameters_Struct.
 * @{
 */
/* Sensor and Actuator Data */
extern const struct mb4_param MB4_SCDATA1;
extern const struct mb4_param MB4_SCDATA2;
extern const struct mb4_param MB4_SCDATA3;
extern const struct mb4_param MB4_SCDATA4;
extern const struct mb4_param MB4_SCDATA5;
extern const struct mb4_param MB4_SCDATA6;
extern const struct mb4_param MB4_SCDATA7;
extern const struct mb4_param MB4_SCDATA8;

/* Register Data */
extern const struct mb4_param MB4_RDATA1;
extern const struct mb4_param MB4_IDS;
extern const struct mb4_param MB4_RDATA2;
extern const struct mb4_param MB4_RDATA3;
extern const struct mb4_param MB4_RDATA4;
extern const struct mb4_param MB4_RDATA5;
extern const struct mb4_param MB4_RDATA6;
extern const struct mb4_param MB4_RDATA7;
extern const struct mb4_param MB4_RDATA8;
extern const struct mb4_param MB4_RDATA9;
extern const struct mb4_param MB4_RDATA10;
extern const struct mb4_param MB4_RDATA11;
extern const struct mb4_param MB4_RDATA12;
extern const struct mb4_param MB4_RDATA13;
extern const struct mb4_param MB4_RDATA14;
extern const struct mb4_param MB4_RDATA15;
extern const struct mb4_param MB4_RDATA16;
extern const struct mb4_param MB4_RDATA17;
extern const struct mb4_param MB4_RDATA18;
extern const struct mb4_param MB4_RDATA19;
extern const struct mb4_param MB4_RDATA20;
extern const struct mb4_param MB4_RDATA21;
extern const struct mb4_param MB4_RDATA22;
extern const struct mb4_param MB4_RDATA23;
extern const struct mb4_param MB4_RDATA24;
extern const struct mb4_param MB4_RDATA25;
extern const struct mb4_param MB4_RDATA26;
extern const struct mb4_param MB4_RDATA27;
extern const struct mb4_param MB4_RDATA28;
extern const struct mb4_param MB4_RDATA29;
extern const struct mb4_param MB4_RDATA30;
extern const struct mb4_param MB4_RDATA31;
extern const struct mb4_param MB4_RDATA32;
extern const struct mb4_param MB4_RDATA33;
extern const struct mb4_param MB4_RDATA34;
extern const struct mb4_param MB4_RDATA35;
extern const struct mb4_param MB4_RDATA36;
extern const struct mb4_param MB4_RDATA37;
extern const struct mb4_param MB4_RDATA38;
extern const struct mb4_param MB4_RDATA39;
extern const struct mb4_param MB4_RDATA40;
extern const struct mb4_param MB4_RDATA41;
extern const struct mb4_param MB4_RDATA42;
extern const struct mb4_param MB4_RDATA43;
extern const struct mb4_param MB4_RDATA44;
extern const struct mb4_param MB4_RDATA45;
extern const struct mb4_param MB4_RDATA46;
extern const struct mb4_param MB4_RDATA47;
extern const struct mb4_param MB4_RDATA48;
extern const struct mb4_param MB4_RDATA49;
extern const struct mb4_param MB4_RDATA50;
extern const struct mb4_param MB4_RDATA51;
extern const struct mb4_param MB4_RDATA52;
extern const struct mb4_param MB4_RDATA53;
extern const struct mb4_param MB4_RDATA54;
extern const struct mb4_param MB4_RDATA55;
extern const struct mb4_param MB4_RDATA56;
extern const struct mb4_param MB4_RDATA57;
extern const struct mb4_param MB4_RDATA58;
extern const struct mb4_param MB4_RDATA59;
extern const struct mb4_param MB4_RDATA60;
extern const struct mb4_param MB4_RDATA61;
extern const struct mb4_param MB4_RDATA62;
extern const struct mb4_param MB4_RDATA63;
extern const struct mb4_param MB4_RDATA64;

/* Configuration Slave 1 */
extern const struct mb4_param MB4_SCDLEN1;
extern const struct mb4_param MB4_ENSCD1;
extern const struct mb4_param MB4_GRAYS1;
extern const struct mb4_param MB4_LSTOP1;
extern const struct mb4_param MB4_SCRCLEN1;
extern const struct mb4_param MB4_SCRCPOLY1;
extern const struct mb4_param MB4_SELCRCS1;
extern const struct mb4_param MB4_SCRCSTART1;

/* Configuration Slave 2 */
extern const struct mb4_param MB4_SCDLEN2;
extern const struct mb4_param MB4_ENSCD2;
extern const struct mb4_param MB4_GRAYS2;
extern const struct mb4_param MB4_LSTOP2;
extern const struct mb4_param MB4_SCRCLEN2;
extern const struct mb4_param MB4_SCRCPOLY2;
extern const struct mb4_param MB4_SELCRCS2;
extern const struct mb4_param MB4_SCRCSTART2;

/* Configuration Slave 3 */
extern const struct mb4_param MB4_SCDLEN3;
extern const struct mb4_param MB4_ENSCD3;
extern const struct mb4_param MB4_GRAYS3;
extern const struct mb4_param MB4_LSTOP3;
extern const struct mb4_param MB4_SCRCLEN3;
extern const struct mb4_param MB4_SCRCPOLY3;
extern const struct mb4_param MB4_SELCRCS3;
extern const struct mb4_param MB4_SCRCSTART3;

/* Configuration Slave 4 */
extern const struct mb4_param MB4_SCDLEN4;
extern const struct mb4_param MB4_ENSCD4;
extern const struct mb4_param MB4_GRAYS4;
extern const struct mb4_param MB4_LSTOP4;
extern const struct mb4_param MB4_SCRCLEN4;
extern const struct mb4_param MB4_SCRCPOLY4;
extern const struct mb4_param MB4_SELCRCS4;
extern const struct mb4_param MB4_SCRCSTART4;

/* Configuration Slave 5 */
extern const struct mb4_param MB4_SCDLEN5;
extern const struct mb4_param MB4_ENSCD5;
extern const struct mb4_param MB4_GRAYS5;
extern const struct mb4_param MB4_LSTOP5;
extern const struct mb4_param MB4_SCRCLEN5;
extern const struct mb4_param MB4_SCRCPOLY5;
extern const struct mb4_param MB4_SELCRCS5;
extern const struct mb4_param MB4_SCRCSTART5;

/* Configuration Slave 6 */
extern const struct mb4_param MB4_SCDLEN6;
extern const struct mb4_param MB4_ENSCD6;
extern const struct mb4_param MB4_GRAYS6;
extern const struct mb4_param MB4_LSTOP6;
extern const struct mb4_param MB4_SCRCLEN6;
extern const struct mb4_param MB4_SCRCPOLY6;
extern const struct mb4_param MB4_SELCRCS6;
extern const struct mb4_param MB4_SCRCSTART6;

/* Configuration Slave 7 */
extern const struct mb4_param MB4_SCDLEN7;
extern const struct mb4_param MB4_ENSCD7;
extern const struct mb4_param MB4_GRAYS7;
extern const struct mb4_param MB4_LSTOP7;
extern const struct mb4_param MB4_SCRCLEN7;
extern const struct mb4_param MB4_SCRCPOLY7;
extern const struct mb4_param MB4_SELCRCS7;
extern const struct mb4_param MB4_SCRCSTART7;

/* Configuration Slave 8 */
extern const struct mb4_param MB4_SCDLEN8;
extern const struct mb4_param MB4_ENSCD8;
extern const struct mb4_param MB4_GRAYS8;
extern const struct mb4_param MB4_LSTOP8;
extern const struct mb4_param MB4_SCRCLEN8;
extern const struct mb4_param MB4_SCRCPOLY8;
extern const struct mb4_param MB4_SELCRCS8;
extern const struct mb4_param MB4_SCRCSTART8;

/* Control Communication Configuration */
extern const struct mb4_param MB4_REGADR;
extern const struct mb4_param MB4_WNR;
extern const struct mb4_param MB4_REGNUM;
extern const struct mb4_param MB4_CHSEL;
extern const struct mb4_param MB4_HOLDCDM;
extern const struct mb4_param MB4_EN_MO;
extern const struct mb4_param MB4_SLAVEID;
extern const struct mb4_param MB4_IDA_TEST;
extern const struct mb4_param MB4_CMD;
extern const struct mb4_param MB4_REGVERS;
extern const struct mb4_param MB4_CTS;

/* Master Configuration */
extern const struct mb4_param MB4_FREQS;
extern const struct mb4_param MB4_FREQR;
extern const struct mb4_param MB4_SINGLEBANK;
extern const struct mb4_param MB4_NOCRC;
extern const struct mb4_param MB4_FREQAGS;
extern const struct mb4_param MB4_MO_BUSY;
extern const struct mb4_param MB4_REVISION;
extern const struct mb4_param MB4_VERSION;

/* Channel Configuration */
extern const struct mb4_param MB4_SLAVELOC5;
extern const struct mb4_param MB4_CFGCH1;
extern const struct mb4_param MB4_CFGCH2;

/* Slave Configuration 2 */
extern const struct mb4_param MB4_ACTnSENS;

/* Status Information */
extern const struct mb4_param MB4_EOT;
extern const struct mb4_param MB4_REGEND;
extern const struct mb4_param MB4_nREGERR;
extern const struct mb4_param MB4_nSCDERR;
extern const struct mb4_param MB4_nDELAYERR;
extern const struct mb4_param MB4_nAGSERR;
extern const struct mb4_param MB4_nERR;
extern const struct mb4_param MB4_SVALID1;
extern const struct mb4_param MB4_SVALID2;
extern const struct mb4_param MB4_SVALID3;
extern const struct mb4_param MB4_SVALID4;
extern const struct mb4_param MB4_SVALID5;
extern const struct mb4_param MB4_SVALID6;
extern const struct mb4_param MB4_SVALID7;
extern const struct mb4_param MB4_SVALID8;
extern const struct mb4_param MB4_REGBYTES;
extern const struct mb4_param MB4_CDSSEL;
extern const struct mb4_param MB4_CDMTIMEOUT;

/* Instruction Register */
extern const struct mb4_param MB4_AGS;
extern const struct mb4_param MB4_INSTR;
extern const struct mb4_param MB4_INIT;
extern const struct mb4_param MB4_SWBANK;
extern const struct mb4_param MB4_HOLDBANK;
extern const struct mb4_param MB4_BREAK;
extern const struct mb4_param MB4_CLKENI;
extern const struct mb4_param MB4_ENTEST;
extern const struct mb4_param MB4_CFGIF;
extern const struct mb4_param MB4_MAFS;
extern const struct mb4_param MB4_MAVS;
extern const struct mb4_param MB4_MAFO;
extern const struct mb4_param MB4_MAVO;

/* Status Information 2 */
extern const struct mb4_param MB4_SL1;
extern const struct mb4_param MB4_CDS1;
extern const struct mb4_param MB4_SL2;
extern const struct mb4_param MB4_CDS2;
extern const struct mb4_param MB4_SWBANKFAIL;
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup MB4_Functions
 * @{
 */
/**
 * @addtogroup MB4_Functions_Basic
 * @brief Functions according to iC-MB4 SPI opcodes.
 * @{
 */
void mb4_write_registers(uint8_t start_addr, uint8_t *data_tx, uint8_t datasize);
void mb4_read_registers(uint8_t start_addr, uint8_t *data_rx, uint8_t datasize);
void mb4_read_status(uint8_t *data_rx, uint8_t datasize);
void mb4_write_instruction(uint8_t *data_tx, uint8_t datasize);

// Consecutive W/R Operation
void mb4_read_registers_0(uint8_t *data_rx, uint8_t datasize);
void mb4_write_registers_0(uint8_t *data_tx, uint8_t datasize);
/**
 * @}
 */

/**
 * @addtogroup MB4_Functions_Advanced
 * @brief Functions going through a sequence of @ref MB4_Functions_Basic with enhanced data handling.
 * @{
 */
uint64_t mb4_read_param(const struct mb4_param *param);
void mb4_write_param(const struct mb4_param *param, uint64_t param_val);
/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* MB4_1SF_DRIVER_H */
