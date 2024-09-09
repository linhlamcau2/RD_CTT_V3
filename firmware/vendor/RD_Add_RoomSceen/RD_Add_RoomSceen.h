/*
 * RD_Add_RoomSceen.h
 *
 *  Created on: Sep 11, 2023
 *      Author: NV-Smart03
 */

#ifndef RD_ADD_ROOMSCEEN_H_
#define RD_ADD_ROOMSCEEN_H_

#include "../RD_Type_Device/RD_Type_Device.h"
#include "vendor/Training_CCT/Training_CCT.h"
#include "../common/scene.h"

#define ALL_NODE			0xFFFF
#define MAX_TEMP			0x4e20
#define MIN_TEMP			0x0320
#define RD_AUTO_CREATE_GS		(0x0c0a)
#define RD_AUTO_DELETE_GS		(0x0d0a)
#define TSS_DEFAULT 		0x05

extern uint16_t groupType;

#define K9B_HEADER_E2_FIND_K9B			(0x0a0b)
#define K9B_HEADER_E2_SAVE_K9B			(0x0d0b)
#define K9B_HEADER_E2_DELETE_K9B		(0x0e0b)
#define K9B_HEADER_E2_SAVE_SCEEN		(0x0c0b)
#define K9B_HEADER_E2_DELETE_SCEEN		(0x0f0b)
#define K9B_HEADER_E2_RSP_CALLSCEEN_K9B	(0x0b0b)

#define RD_OPCODE_SCENE_SEND			(0xE2)
#define RD_OPCODE_SCENE_RSP				(0xE3)
#define RD_HEADER_SW_PAIR_K9BREMOTE			(0x0A0B)
#define RD_HEADER_SW_SAVESCENE_K9BREMOTE	(0x0C0B)
#define RD_HEADER_SW_K9B_PRESS				(0x0B0B)
#define RD_HEADER_SW_SAVEK9BHC				(0x0D0B)
#define RD_HEADER_SW_DELETEK9BHC			(0x0E0B)
#define RD_HEADER_SW_DELETESCENE_K9BREMOTE	(0x0F0B)
#define RD_HEADER_SW_POWUP_CONFIG			(0x100B)

#define K9B_SUPPORT_ENABLE		1
#define K9B_VID					0x09e2
#define K9B_TYPE_ADV			0xff
#define K9B_TYPE_DEVICE			1
#define K9B_TYPE_DATA_RD		0x0c
#define K9B_TYPE_DATA_TEMP		0x00
#define K9B_LENGTH_DATA			0x0e

#define K9B_TIMEOUT_SCAN		(10)	//uint: s
#define K9B_PAR_START_SCAN		(1)

#define RD_K9B_FLASH_AREA 		(0x7b000)
#define RD_K9B_FLASH_SIZE 		(4+51*5)
#define RD_CHECK_FLASH_K9B_H	0x55
#define RD_CHECK_FLASH_K9B_L	0xAA
#define RD_NUM_MAX_K9B			0x05
#define RD_NUM_KEY_MAX_ONE_K9B	0x0f

#	define MAX_NUM_K9BHC				5
#	define MAX_NUM_K9ONOFF				5
#	define MAX_MUM_K9BPRESSTYPE			12

#define RD_START_SCAN_PAR		0x01
#define RD_STOP_SCAN_PAR		0x00
#define RD_RSP_SAVEK9B_SUCC		0x01
#define RD_RSP_SAVEK9B_FULL		0x00
#define RD_RSP_DELK9B_SUCC		0x01
#define RD_RSP_DELEK9B_ADDNULL	0x00


#define TIME_PAIR_K9B_LOCAL_MS      10000 // 10s
#define CLOCK_TIME_OUT_PRESS_K9B_MS	500
#define mesh_cmd_sig_RD_respone_status_type_E3   (0)

//RD_Edit: K9B Remote Receive
typedef struct {
	u8 lengt;
	u8 type;
	u16 Vid;
	u8 frame;
	u32 Counter;
	u8 type_device;
	u8 key;
	u32 signature;
}switchK9B_proxy_t;

typedef struct{
	uint32_t countLastOfMacID[MAX_NUM_K9BHC];
} K9bHc_countLast_st;

typedef struct {
	u8 *mac;
	s8 rssi;
	switchK9B_proxy_t *K9BDataAdv;
}K9B_proxy_inf_all;

typedef struct{
//	u32	mac;
//	u16	addK9B;
//	u8	key[15];
//	u16	sceenForKey[15];

  uint32_t MacK9B;
  uint16_t AddK9B;
  uint16_t Scene_ID_OnePress[MAX_MUM_K9BPRESSTYPE];
  uint8_t Button_ID[MAX_MUM_K9BPRESSTYPE];
  //uint16_t Scene_ID_DoublePress[7];
  uint8_t Num_Of_Button;
}Flash_SaveTemp_K9B;

typedef struct{
	u8 Used[4];
	Flash_SaveTemp_K9B deviceK9B[MAX_NUM_K9BHC];
}Flash_Save_K9B;

typedef struct
{
	uint8_t Pair_K9BOnOff_Flag;
	uint8_t Button_K9BOnOff_Pair;
	uint8_t Pair_K9BHc_Flag;
	uint16_t Add_K9B_HCSet;			// HC set add for K9B remote
	uint32_t ClockTimeSetHc_ms;
	uint32_t Clock_BtK9BStartPress_ms[3];
	uint8_t  Bt_K9B_CountPress[3];
    uint32_t Clock_time_start_pair_onOff_ms;
} Sw_Working_Stt_Str;

typedef struct
{
	uint8_t Scene_ID[2];
	uint8_t Null_Byte;
	uint8_t Tss[2];
	uint8_t Future[3];
} Call_Scene_Str;

int RD_mesh_cmd_sig_cfg_model_sub_set(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);
void RD_GroupAuto(uint16_t groupID, mesh_cb_fun_par_t *cb_par, uint16_t OpGroup);
void RD_SceenAuto(uint16_t sceenID, mesh_cb_fun_par_t *cb_par, uint16_t OpSceen);
u8 RD_mesh_cmd_sig_scene_set_ll(u16 scene_id, mesh_cb_fun_par_t *cb_par, u16 lightness, u16 tempLight);

/**
 * @brief: Nhan ban tin adv.
 * @param[in] *K9B_DataRec: data adv chuyen theo cau truc quy uoc voi CT2CKD (K9B)
 * @param[in] *mac: MAC CT2CKD (K9B).
 * @param[in] rssi: cuong do tin hieu CT2CKD
 */
void RecDataK9B(switchK9B_proxy_t *K9B_DataRec, u8 *mac, s8 rssi);

/**
 * @brief: BAT/TAT TRANG THAI QUET CT2CKD, TINH THOI GIAN.
 * @param[in] sttScan: CO dat trang thai.
 */
void setSttScanK9B(uint8_t sttScan);
void funcK9BInMainLoop(void);
void funcInitK9BMian(void);
void readFlashForTestK9B(void);
void saveDeviceK9BFlash(u32 mac, u16 addrK9B, u16 gwAdd);
void delDeviceK9BFlash(u16 addrK9B, u16 gwAdd);
void saveSceenK9BFlash(u16 addr, u8 valKey, u16 valSceen, u16 gwAdd);
void delSceenK9BFlash(u16 addr, u8 valKey, u16 gwAdd);
void deleteFlashK9B(void);

/**
 * @brief: kiem tra trung lap ban tin ct2ckd, cap nhan danh sach ct2ckd can theo doi
 * @param[in] mac: MAC CT2CKD (K9B).
 * @param[in] counter: so dem cho moi ban tin
 * @param[in] change: flag cho biet cap nhan hau kiem tra
 */
_Bool CheckK9BActive(u32 mac, u32 counter, _Bool change);
void rspAndUpdate_SttScanK9B(u8 *mac, u8 typeRemote, s8 rssi, _Bool ScanDone, u16 gwAdd);
void RD_Call_Scene(uint16_t Scene_ID, uint8_t Mess_ID);
void rspSceen(u16 addK9B, u8 key, u8 modeID, u16 sceenID, u16 gwAdd);


void RD_K9B_TimeOutScan(void);
void RD_K9B_CheckScanK9BHc(uint32_t K9BMac_Buff, uint8_t Num_Of_Button, signed char rssi);
uint8_t RD_K9B_ScanPress2HC(uint32_t macDevice, uint8_t key, uint32_t par_signature);
#endif /* RD_ADD_ROOMSCEEN_H_ */
