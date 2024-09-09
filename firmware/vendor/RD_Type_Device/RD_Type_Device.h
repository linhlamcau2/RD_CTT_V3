/*
 * RD_Type_Device.h
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#ifndef RD_TYPE_DEVICE_H_
#define RD_TYPE_DEVICE_H_

#include "proj/tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#include "../RD_Mess_Data/RD_Mess_Data.h"
#include "../mesh/RD_Lib.h"

typedef struct{
	unsigned char Header[2];
	unsigned char MainType;
	unsigned char Feature;
	unsigned char Name;
	unsigned char Future[8];
}RD_Type_Device_Message;

typedef struct{
	unsigned char GWID[2];
}RD_Save_Gateway_Address;

typedef struct{
	unsigned char Header[2];
	unsigned char GWID[2];
	unsigned char Future[4];
}RD_Rsp_Gateway_Address;

typedef struct{
	unsigned char Used[4];
	unsigned char GwID[2];
	unsigned char MainType;
	unsigned char Feature;
	unsigned char Name;
	unsigned char Future[7];
}Flash_Save_Type_Gw;

typedef struct{
	unsigned char Used[4];
	unsigned char step;
	unsigned char cnt_cycle;
}Flash_Save_Training;

typedef struct{
	unsigned char Header;
	unsigned char Remote_ctl;
	unsigned char Up_down;
	unsigned char Vrs_delta;
	unsigned char Future[4];
}RD_Rsp_Remote;

typedef struct{
	unsigned char Header;
	unsigned char Status_mode;
	unsigned char Data[6];
}RD_Rsp_GW_Info;

//RD_EDIT: SEC : RD_Type_Device.h-------------------------------------
typedef struct{
	u8     Used[4];
	_Bool  Process_AES;
	_Bool  Check_mess;
	_Bool  Process_security;
	u8 	   Future;
}Flash_Save_Security;

#define FLASH_SAVE_SECURE_SIZE   8
#define RD_SECURE_FLASH_AREA (0x7a000)		//RD_EDIT: SEC : AREA SAVE FLASH NOTE CCT-RGB !!!!!
#define ENABLE_SECURE 		0	//RD_EDIT: ENA OR DIS SER
//--------------------------------------------------------------------

#define FLASH_SAVE_TYPE_SIZE   		 16
#define FLASH_SAVE_TRAINING_SIZE     6
#define RD_GATEWAY_FLASH_AREA  		(0x78000)
#define RD_TRAINING_FLASH_AREA 		(0x79000)
#define RD_CHECK_FLASH_H	0x55
#define RD_CHECK_FLASH_L	0xAA

extern Flash_Save_Type_Gw Flash_Save_Type_Val;
void RD_Flash_Type_Init(void);
void RD_Flash_CleanTypeFlash(void);
void RD_Flash_SaveGW(uint16_t GW_ADD);
void RD_Flash_SaveType(unsigned char MainType_In, unsigned char Feature_In, unsigned char Name_In );

extern Flash_Save_Training Flash_Save_Training_Val;
void RD_Flash_Training_Init(void);
void RD_Flash_CleanTraining(void);
void RD_Flash_SaveTraining(unsigned char step, unsigned char cycle );

//RD_EDIT: SEC : RD_Type_Device.h function---------------------------------------
extern Flash_Save_Security Flash_Save_Security_Val;
void RD_Flash_Security_Init(void);
void RD_Flash_CleanSecurityFlash(void);
void RD_Flash_SaveSecurity(_Bool unicast_id, _Bool process_security, _Bool check_mess);

#endif /* RD_TYPE_DEVICE_H_ */
