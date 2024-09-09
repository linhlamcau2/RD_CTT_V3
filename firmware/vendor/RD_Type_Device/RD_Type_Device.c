/*
 * RD_Type_Device.c
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#include "RD_Type_Device.h"

Flash_Save_Type_Gw Flash_Save_Type_Val;
Flash_Save_Training Flash_Save_Training_Val;
Flash_Save_Security Flash_Save_Security_Val;	//RD_EDIT: SEC : Struct : Flash_Save_Security

void RD_Flash_Training_Init(void)
{
	flash_read_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, (unsigned char *) (&Flash_Save_Training_Val.Used[0]));

	if((Flash_Save_Training_Val.Used[0] != RD_CHECK_FLASH_H) && (Flash_Save_Training_Val.Used[1] != RD_CHECK_FLASH_L)  && (Flash_Save_Training_Val.Used[2] != RD_CHECK_FLASH_H)	&& (Flash_Save_Training_Val.Used[3] != RD_CHECK_FLASH_L) )														// fist time to read reset memory
	{
		RD_Flash_CleanTraining();
	}
	else{
#if(!ENABLE_TRAINING_1)		//RD_EDIT: 0.THANH : SPM: TRAINING
		if((Flash_Save_Training_Val.step != 6)||(Flash_Save_Training_Val.cnt_cycle != 6)){
			RD_Flash_CleanTraining();
		}
#endif
	}
}

void RD_Flash_SaveTraining(unsigned char step, unsigned char cycle )
{
	Flash_Save_Training_Val.step		=  step;
	Flash_Save_Training_Val.cnt_cycle	=  cycle;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Training_Val.Used[0]);

   	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, Flash_Data_Buff );

	flash_read_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, (unsigned char *)(&Flash_Save_Training_Val.Used[0]));
}

void RD_Flash_CleanTraining(void)
{
	Flash_Save_Training_Val.Used[0] = RD_CHECK_FLASH_H;
	Flash_Save_Training_Val.Used[1] = RD_CHECK_FLASH_L;
	Flash_Save_Training_Val.Used[2] = RD_CHECK_FLASH_H;
	Flash_Save_Training_Val.Used[3] = RD_CHECK_FLASH_L;

#if(ENABLE_TRAINING_1)		//RD_EDIT: 0.THANH : SPM: TRAINING
		Flash_Save_Training_Val.step			=  0;
		Flash_Save_Training_Val.cnt_cycle		=  0;
#else
		Flash_Save_Training_Val.step			=  6;
		Flash_Save_Training_Val.cnt_cycle		=  6;
#endif

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Training_Val.Used[0]);

   	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, Flash_Data_Buff );

	flash_read_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, (unsigned char *) (&Flash_Save_Training_Val.Used[0]));
}


void RD_Flash_Type_Init(void)
{
	flash_read_page(RD_GATEWAY_FLASH_AREA, FLASH_SAVE_TYPE_SIZE, (unsigned char *) (&Flash_Save_Type_Val.Used[0]));

	if((Flash_Save_Type_Val.Used[0] != RD_CHECK_FLASH_H) && (Flash_Save_Type_Val.Used[1] != RD_CHECK_FLASH_L)  && (Flash_Save_Type_Val.Used[2] != RD_CHECK_FLASH_H)	&& (Flash_Save_Type_Val.Used[3] != RD_CHECK_FLASH_L) )														// fist time to read reset memory
	{
		RD_Flash_CleanTypeFlash();
	}
	else
	{
		RD_GATEWAYADDRESS   = ((Flash_Save_Type_Val.GwID[0] << 8) | (Flash_Save_Type_Val.GwID[1] ));
	}
}

void RD_Flash_SaveGW(uint16_t GW_ADD)
{
	Flash_Save_Type_Val.GwID[0]	= (uint8_t) ((GW_ADD >> 8) & 0xff);
	Flash_Save_Type_Val.GwID[1]	= (uint8_t) ((GW_ADD     ) & 0xff);

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Type_Val.Used[0]);

   	flash_erase_sector(RD_GATEWAY_FLASH_AREA);
	flash_write_page(RD_GATEWAY_FLASH_AREA, FLASH_SAVE_TYPE_SIZE, Flash_Data_Buff );

	flash_read_page(RD_GATEWAY_FLASH_AREA, FLASH_SAVE_TYPE_SIZE, (unsigned char *) (&Flash_Save_Type_Val.Used[0]));
	RD_GATEWAYADDRESS   = ((Flash_Save_Type_Val.GwID[0] << 8) | (Flash_Save_Type_Val.GwID[1] ));
}

void RD_Flash_SaveType(unsigned char MainType_In, unsigned char Feature_In, unsigned char Name_In )
{
	Flash_Save_Type_Val.MainType	=  MainType_In;
	Flash_Save_Type_Val.Name		=  Name_In;
	Flash_Save_Type_Val.Feature     =  Feature_In;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Type_Val.Used[0]);

   	flash_erase_sector(RD_GATEWAY_FLASH_AREA);
	flash_write_page(RD_GATEWAY_FLASH_AREA, FLASH_SAVE_TYPE_SIZE, Flash_Data_Buff );
}

void RD_Flash_CleanTypeFlash(void)
{
	Flash_Save_Type_Val.Used[0] = RD_CHECK_FLASH_H;
	Flash_Save_Type_Val.Used[1] = RD_CHECK_FLASH_L;
	Flash_Save_Type_Val.Used[2] = RD_CHECK_FLASH_H;
	Flash_Save_Type_Val.Used[3] = RD_CHECK_FLASH_L;

	Flash_Save_Type_Val.GwID[0]	= (uint8_t) ((RD_GATEWAYADDRESS >> 8) & 0xff);
	Flash_Save_Type_Val.GwID[1]	= (uint8_t) ((RD_GATEWAYADDRESS     ) & 0xff);

	Flash_Save_Type_Val.MainType	=  0x01;
	Flash_Save_Type_Val.Feature     =  0x02;
	Flash_Save_Type_Val.Name		=  0x01;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Type_Val.Used[0]);

   	flash_erase_sector(RD_GATEWAY_FLASH_AREA);
	flash_write_page(RD_GATEWAY_FLASH_AREA, FLASH_SAVE_TYPE_SIZE, Flash_Data_Buff);

	flash_read_page(RD_GATEWAY_FLASH_AREA, FLASH_SAVE_TYPE_SIZE, (unsigned char *) (&Flash_Save_Type_Val.Used[0]));
	RD_GATEWAYADDRESS   = ((Flash_Save_Type_Val.GwID[0] << 8) | (Flash_Save_Type_Val.GwID[1] ));
}

//RD_EDIT: SEC : FLASH MEMORY
void RD_Flash_Security_Init(void)
{
	flash_read_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE, (unsigned char *) (&Flash_Save_Security_Val.Used[0]));
	if((Flash_Save_Security_Val.Used[0] != RD_CHECK_FLASH_H) && (Flash_Save_Security_Val.Used[1] != RD_CHECK_FLASH_L)  && (Flash_Save_Security_Val.Used[2] != RD_CHECK_FLASH_H)	&& (Flash_Save_Security_Val.Used[3] != RD_CHECK_FLASH_L) )														// fist time to read reset memory
	{
		RD_Flash_CleanSecurityFlash();
	}
	else
	{

#if(!ENABLE_SECURE)
		if((get_provision_state() == STATE_DEV_PROVED)
		  &&(Flash_Save_Security_Val.Check_mess != FALSE || Flash_Save_Security_Val.Process_AES != FALSE || Flash_Save_Security_Val.Process_security != TRUE))
		{
			Flash_Save_Security_Val.Check_mess				=  FALSE;
			Flash_Save_Security_Val.Process_security		=  TRUE;
			Flash_Save_Security_Val.Process_AES     		=  FALSE;

			unsigned char *Flash_Data_Buff;
			Flash_Data_Buff = (unsigned char *) (&Flash_Save_Security_Val.Used[0]);

		   	flash_erase_sector(RD_SECURE_FLASH_AREA);
			flash_write_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE,Flash_Data_Buff );
			flash_read_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE, (unsigned char *) (&Flash_Save_Security_Val.Used[0]));
		}
#endif

		flag_check_mess       = Flash_Save_Security_Val.Check_mess;
		flag_process_security = Flash_Save_Security_Val.Process_security;
		flag_process_aes	  = Flash_Save_Security_Val.Process_AES;

#if(ENABLE_SECURE)	//RD_EDIT: 0.THANH : SPM: ENABLE_SECURE
		if((flag_process_security == TRUE) && (flag_check_mess == FALSE)){
//			uart_CSend("on off nguon\n");
			kick_out(0);
		}
		else{

		}
#endif
	}
}

void RD_Flash_CleanSecurityFlash(void)
{
	Flash_Save_Security_Val.Used[0] = RD_CHECK_FLASH_H;
	Flash_Save_Security_Val.Used[1] = RD_CHECK_FLASH_L;
	Flash_Save_Security_Val.Used[2] = RD_CHECK_FLASH_H;
	Flash_Save_Security_Val.Used[3] = RD_CHECK_FLASH_L;

	Flash_Save_Security_Val.Check_mess				=  FALSE;
	Flash_Save_Security_Val.Process_security		=  FALSE;
	Flash_Save_Security_Val.Process_AES     		=  FALSE;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Security_Val.Used[0]);

   	flash_erase_sector(RD_SECURE_FLASH_AREA);
	flash_write_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE,Flash_Data_Buff );

	flash_read_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE, (unsigned char *) (&Flash_Save_Security_Val.Used[0]));

	flag_check_mess       = Flash_Save_Security_Val.Check_mess;
	flag_process_security = Flash_Save_Security_Val.Process_security;
	flag_process_aes	  = Flash_Save_Security_Val.Process_AES;
}

void RD_Flash_SaveSecurity(_Bool process_AES, _Bool process_security, _Bool check_mess)
{
	Flash_Save_Security_Val.Process_security	= process_security;
	Flash_Save_Security_Val.Process_AES			= process_AES;
	Flash_Save_Security_Val.Check_mess			= check_mess;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Security_Val.Used[0]);

   	flash_erase_sector(RD_SECURE_FLASH_AREA);
	flash_write_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE, Flash_Data_Buff );

	flash_read_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE, (unsigned char *) (&Flash_Save_Security_Val.Used[0]));

	flag_check_mess       = Flash_Save_Security_Val.Check_mess;
	flag_process_security = Flash_Save_Security_Val.Process_security;
	flag_process_aes	  = Flash_Save_Security_Val.Process_AES;
}
