/*
 * RD_Mess_Data.h
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#ifndef RD_MESS_DATA_H_
#define RD_MESS_DATA_H_
#include "../RD_Type_Device/RD_Type_Device.h"
#include "vendor/common/lighting_model.h"
#include "drivers/8258/flash.h"
#include "../../proj_lib/sig_mesh/app_mesh.h"
#include "vendor/Training_CCT/Training_CCT.h"

#define RD_SET_TYPE_DEVICE 		(0x0001)
#define RD_SAVE_GATEWAY_ADDRESS (0x0002)
#define RD_TYPE_DEVICE			(0x0003)
#define RD_KICKOUT_ALL          (0xffff)
#define RD_MAXRESPONESEND 		(2)
#define RD_CODE_PRODONE_L 		 0x06
#define RD_CODE_PRODONE_H 		 0x13

#define RD_REMOTE_CONTROL		 0x01
#define RD_HC_REQUEST_INFO		 0x02
#define RD_REMOTE_CTL_MODE		 0x03
#define RD_REMOTE_SCHED			 0x04

#define REMOTE_CONTROL_DIM		 0x00
#define REMOTE_CONTROL_CCT		 0x01
#define REMOTE_CONTROL_RGB		 0x02

#define REMOTE_CONTROL_UP		 0x01
#define REMOTE_CONTROL_DOWN		 0x02

#define RD_REMOTE_DISNABLE_SCHED 0x00
#define RD_REMOTE_ENABLE_SCHED   0x01

//PROVIDER-SC---------------------------------
#define RD_PROVIDER				 0		//RD_EDIT: Provider	//RD_EDIT: SEC :  RD_Mess_Data.h: Provider DEFINE
#define FPT_PROVIDER             1

#define PROJECT_PROVIDER		RD_PROVIDER

#if(PROJECT_PROVIDER == RD_PROVIDER)
#define PROVIDER_MAIN 			 0x00
#define PROVIDER_SUB			 0x01
#endif
//--------------------------------------------

#define mesh_cmd_sig_RD_respone_status_type      (0)

extern u16 RD_GATEWAYADDRESS ;
extern int flag_kickout;
extern int flag_training_test2;

//RD_EDIT: SEC : RD_Mess_Data.h
extern _Bool flag_process_aes;
extern _Bool flag_check_mess;
extern _Bool flag_process_security;

extern char UART_TempSend[128];
extern u16 time_sched_set;

/**
 * @brief: Nhan dieu khien tu remote M4, bang canh M3.
 * @param[in] *par: tro den param duoc gui thong qua ban tin mesh
 * @param[in] par_len: do dai param.
 * @param[in] *cb_par: tro den noi luu tru cac thong so di kem cua ban tin mesh
 * @return Always 0
 */
int RD_mesh_cmd_sig_lightness_linear_set(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);
void Counter_Sched (u16 time_sched);
void Remote_Sched(u8 enable);
void Answer_Info(u8 Status_Onoff, u8 Mode_ct_rgb, u16 vrs_DIM, u16 vrs_CCT, u16 adr_src);
void Remote_Control(u8 Mode_Ctl, u8 Up_Down, u8 Delta);
void Process_Lightness(u16 light_present, u8 Up_Down, u8 Delta);
void Process_Temp(u16 temp_CCT, u8 Up_Down, u8 Delta);

/**
 * @brief: Nhan ban tin thuc hien bao mat, phan hoi loai, ver, kickoutAll.
 * @param[in] *par: tro den param duoc gui thong qua ban tin mesh
 * @param[in] par_len: do dai param.
 * @param[in] *cb_par: tro den noi luu tru cac thong so di kem cua ban tin mesh
 * @return Always 0
 */
int RD_Messenger_ProcessCommingProcess_Type(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);

/**
 * @brief: Nhan ban tin chay qua trinh test luyen voi HC.
 * @param[in] *par: tro den param duoc gui thong qua ban tin mesh
 * @param[in] par_len: do dai param.
 * @param[in] *cb_par: tro den noi luu tru cac thong so di kem cua ban tin mesh
 * @return Always 0
 */
int RD_Messenger_Training_Test2(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);
int RD_Messenger_BindAll(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);


void KickoutALL(void);

//RD_EDIT: SEC : RD_Mess_Data.h: FUNCTION
void Process_Kickout_Security();
unsigned char rdAesreCheck(unsigned short unicast,unsigned char *dataIn);

unsigned short saveGatewayAddr(unsigned char *param,unsigned short srcAddr);
void checkDoneProvision(void);

#endif /* RD_MESS_DATA_H_ */
