/*
 * RD_Add_RoomSceen.c
 *
 *  Created on: Sep 11, 2023
 *      Author: NV-Smart03
 */
#include "RD_Add_RoomSceen.h"
#include "../mesh/RD_Lib.h"
#include "../RD_Mess_Data/RD_Mess_Data.h"
#include "../common/vendor_model.h"

uint8_t parGroup[6] = {0};
uint16_t rd_list_check_scene[50] = {0};
uint8_t numSceen = 0;
Sw_Working_Stt_Str   Sw_Working_Stt_Val = {0};
extern void scene_active_set(int idx, u16 scene_id, int trans_flag);
//RD_EDIT: MANG CHUA THONG TIN NHOM VA GIA TRI CANH CHO TAO PHONG NHANH
#if  (NAME == SMT_121)
	uint16_t groupType 		= 0x0001;
	uint16_t temp[6] 		= {0x4e20,  0x0320, 0x4e20, 0x15c0, 0x15c0, 0x15c0};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x4ccd};
#elif(NAME == COB_122)
	uint16_t groupType 		= 0x002;
	uint16_t temp[6] 		= {0x4e20,  0x0320, 0x4e20, 0x15c0, 0x15c0, 0x15c0};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x4ccd};
#elif(NAME == DOWNLIGHT_TT_124)
	uint16_t groupType 		= 0x0004;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == PN_T_125)
	uint16_t groupType 		= 0x0005;
	uint16_t temp[6] 		= {0x4e20,  0x0320, 0x4e20, 0x15c0, 0x15c0, 0x15c0};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x4ccd};
#elif(NAME == PN_126)
	uint16_t groupType 		= 0x0006;
	uint16_t temp[6] 		= {0x4e20,  0x15c0, 0x4e20, 0x15c0, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x0000};
#elif(NAME == OT_127)
	uint16_t groupType 		= 0x0007;
	uint16_t temp[6] 		= {0x4e20,  0x15c0, 0x4e20, 0x15c0, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x0000};
#elif(NAME == GT_128)
	uint16_t groupType 		= 0x0008;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x15c0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TL_12a)
	uint16_t groupType 		= 0x000a;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x15c0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TT_12b)
	uint16_t groupType 		= 0x000b;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x0320, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == LED_WIRE_CT)
	uint16_t groupType 		= 0x000d;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x15c0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TUBE_12e)
	uint16_t groupType 		= 0x000e;
	uint16_t temp[6] 		= {0x4e20,  0x15c0, 0x4e20, 0x0320, 0x0320, 0x0320};
	uint16_t lightness[6] 	= {0x0000,  0xcccc, 0xffff,	0xcccc, 0xffff, 0x7fff};

//----------------------------------------------------------------------------------------

#elif(NAME == RLT03_12W_12026)
	uint16_t groupType 		= 0x001d;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TRL08_10W_12025)
	uint16_t groupType 		= 0x001c;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == TRL08_20W_12024)
	uint16_t groupType 		= 0x001b;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT01_10W_12023)
	uint16_t groupType 		= 0x001a;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT02_20W_12022)
	uint16_t groupType 		= 0x0019;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT02_10W_12021)
	uint16_t groupType 		= 0x0018;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#elif(NAME == RLT03_06W_12020)
	uint16_t groupType 		= 0x0017;
	uint16_t temp[6] 		= {0x4e20,  0x4e20, 0x4e20, 0x4e20, 0x18e0, 0x4e20};
	uint16_t lightness[6] 	= {0x0000,  0x0000, 0x0000,	0x0000, 0xffff, 0x0000};
#endif

static void RD_Handle_ScanK9BHc(uint8_t par[8], uint16_t Gw_Add_Buff);
static void RD_Handle_SaveK9BHc(uint8_t par[8], uint16_t Gw_Add_Buff);
static void RD_Handle_DeleteK9BHC(uint8_t par[8], uint16_t Gw_Add_Buff);
static void RD_Handle_K9BSaveScene(uint8_t par[8], uint16_t Gw_Add_Buff);
static void RD_Handle_K9BDeleteScene(uint8_t par[8], uint16_t Gw_Add_Buff);

uint8_t RD_Flash_DeleteK9BHC(uint16_t K9BAdd);
uint8_t RD_Flash_SaveK9BHc(uint32_t macDevice, uint8_t Num_Of_Button, uint16_t K9BAdd);
int RD_mesh_cmd_sig_cfg_model_sub_set(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par){
	uint16_t r_header = 0;
	uint16_t id_group = 0;
	uint16_t id_group_type = 0;
	uint16_t id_scene = 0;

	r_header = (par[0] | par[1]<<8);
	uint16_t Gw_Add_Buff =0x00;
	Gw_Add_Buff = cb_par->adr_src;
	switch (r_header) {
		case RD_AUTO_CREATE_GS:
			if(get_provision_state() == STATE_DEV_PROVED){
				char UART_TempSend[64];
				sprintf(UART_TempSend,"oprsp: %x\n", cb_par->op_rsp);
				uart_CSend(UART_TempSend);

				mesh_tx_cmd2normal_primary(cb_par->op_rsp, par, par_len, cb_par ->adr_src, 2);

				id_group = (par[2] | par[3]<<8);
				id_group_type = id_group + groupType;
				id_scene = (par[4] | par[5]<<8);

				RD_GroupAuto(id_group, cb_par, CFG_MODEL_SUB_ADD);
				RD_GroupAuto(id_group_type, cb_par, CFG_MODEL_SUB_ADD);
				RD_SceenAuto(id_scene, cb_par, SCENE_STORE_NOACK);
			}
			break;

		case RD_AUTO_DELETE_GS:
			if(get_provision_state() == STATE_DEV_PROVED){
				mesh_tx_cmd2normal_primary(cb_par->op_rsp, par, par_len, cb_par->adr_src, 2);

				RD_GroupAuto(id_group, cb_par, CFG_MODEL_SUB_DEL_ALL);
				RD_SceenAuto(id_scene, cb_par, SCENE_DEL_NOACK);
			}
			break;

		case RD_HEADER_SW_PAIR_K9BREMOTE:
			RD_Handle_ScanK9BHc(par, Gw_Add_Buff);
			break;
		case RD_HEADER_SW_SAVEK9BHC:
			RD_Handle_SaveK9BHc(par, Gw_Add_Buff);
			break;
		case RD_HEADER_SW_DELETEK9BHC:
			RD_Handle_DeleteK9BHC(par, Gw_Add_Buff);
			break;
		case RD_HEADER_SW_SAVESCENE_K9BREMOTE:
			RD_Handle_K9BSaveScene(par, Gw_Add_Buff);
			break;
		case RD_HEADER_SW_DELETESCENE_K9BREMOTE:
			RD_Handle_K9BDeleteScene(par, Gw_Add_Buff);
			break;
		default:
			uart_CSend("wrong header \n");
			break;
	}

	return 0;
}

void RD_GroupAuto(uint16_t groupID, mesh_cb_fun_par_t *cb_par, uint16_t OpGroup){
	mesh_cb_fun_par_t *cb_par_g = cb_par;
	cb_par_g->op = OpGroup;
	cb_par_g->op_rsp = CFG_MODEL_SUB_STATUS;
	cb_par_g->model_idx = 0;
	if(cb_par_g->adr_dst == ALL_NODE) cb_par_g->adr_dst = ele_adr_primary;

	if(OpGroup == CFG_MODEL_SUB_ADD){
		parGroup[0] = cb_par_g->adr_dst & 0xff ;
		parGroup[1] = cb_par_g->adr_dst >> 8 & 0xff;
		parGroup[2] = groupID & 0xff;
		parGroup[3] = groupID >>8 & 0xff;
		parGroup[4] = 0x00;
		parGroup[5] = 0x10;

		mesh_cmd_sig_cfg_model_sub_set(parGroup, 6, cb_par_g);
	}
	else if(OpGroup == CFG_MODEL_SUB_DEL_ALL){
		parGroup[0] = cb_par_g->adr_dst & 0xff ;
		parGroup[1] = cb_par_g->adr_dst >> 8 & 0xff;
		parGroup[2] = 0x00;
		parGroup[3] = 0x10;

		mesh_cmd_sig_cfg_model_sub_set(parGroup, 4, cb_par_g);
	}
}

void RD_SceenAuto(uint16_t sceenID, mesh_cb_fun_par_t *cb_par, uint16_t OpSceen){
	mesh_cb_fun_par_t *cb_par_s = cb_par;
	cb_par_s->op = OpSceen;
	cb_par_s->op_rsp = STATUS_NONE;
	cb_par_s->model_idx = 0;
	if(cb_par_s->adr_dst == ALL_NODE) cb_par_s->adr_dst = ele_adr_primary;

	if(OpSceen == SCENE_STORE_NOACK){
		for(int i=0; i<6; i++){
			RD_mesh_cmd_sig_scene_set_ll(sceenID+i, cb_par_s, lightness[i], temp[i]);
		}
	}
	else if(OpSceen == SCENE_DEL_NOACK){
		foreach(i,SCENE_CNT_MAX){
			scene_data_t *p = &model_sig_scene.data[0][i];
			if(p->id != 0){
				rd_list_check_scene[numSceen] = p->id;
				numSceen++;
			}
		}
		if(numSceen > 0){
			foreach(i,numSceen){
				RD_mesh_cmd_sig_scene_set_ll(rd_list_check_scene[i], cb_par_s, 0, 0);
				rd_list_check_scene[i] = 0;
			}
			numSceen = 0;
		}
	}
}

//RD_EDIT: 1.THANH: SCEEN AUTO
u8 RD_mesh_cmd_sig_scene_set_ll(u16 scene_id, mesh_cb_fun_par_t *cb_par, u16 lightness, u16 tempLight)
{
    u8 st = SCENE_ST_SUCCESS;
    u16 op = cb_par->op;
    int save = 0;
    if((SCENE_STORE == op)||(SCENE_STORE_NOACK == op)){
		scene_data_t *p_exist = 0;
		scene_data_t *p_null = 0;

		foreach(i,SCENE_CNT_MAX){
			scene_data_t *p = &model_sig_scene.data[cb_par->model_idx][i];
			if((0 == p_null) && (0 == p->id)){
				p_null = p; 	// the first empty
			}
			if(scene_id == p->id){
				p_exist = p;
				break;	// exist
			}
		}

		scene_data_t *p_save = 0;
		if(p_exist){
			p_save = p_exist;
		}else if(p_null){
			p_save = p_null;
		}

		if(p_save){
			save = 1;
			p_save->id = scene_id;
			p_save->lightness_s16 = get_level_from_lightness(lightness);
			#if LIGHT_TYPE_CT_EN
			p_save->temp_s16 = get_level_from_ctl_temp(tempLight, MIN_TEMP, MAX_TEMP);
			p_save->delta_uv_s16 = 0;
			p_save->ct_flag = ct_flag;
			#endif
			#if LIGHT_TYPE_HSL_EN
			p_save->hue_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_HSL_HUE);
			p_save->sat_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_HSL_SAT);
			#endif
			#if (LIGHT_TYPE_SEL == LIGHT_TYPE_XYL)
			p_save->x_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_XYL_X);
			p_save->y_s16 = light_g_level_present_get(cb_par->model_idx, ST_TRANS_XYL_Y);
			#endif
			#if MD_LIGHT_CONTROL_EN
			scene_get_lc_par(p_save, cb_par->model_idx);
			#endif
			CB_NL_PAR_NUM_2(p_nl_get_vendor_scene_data, scene_id, p_save->nl_data);
			scene_active_set(cb_par->model_idx, scene_id, 0);
		}else{
			st = SCENE_ST_REG_FULL;
		}
    }else{	// del
		foreach(i,SCENE_CNT_MAX){
			scene_data_t *p = &model_sig_scene.data[cb_par->model_idx][i];
			if(scene_id == p->id){
				memset(p, 0, sizeof(scene_data_t));
				scene_proc_t *p_scene = &scene_proc[cb_par->model_idx];
				if(scene_id == p_scene->current_scene){
					p_scene->current_scene = 0;
				}

				if(scene_id == p_scene->target_scene){
					p_scene->target_scene = 0;
				}
				save = 1;
				break;	// exist
			}
		}
    }

    if(save){
		mesh_model_store(1, SIG_MD_SCENE_SETUP_S);
	}

    return st;
}

//K9B----------------------------------------------------------------------------------------------------

K9B_proxy_inf_all K9BInforAll = {0};
Flash_Save_K9B dataFlashK9B = {{0}};
_Bool startFindK9B = FALSE;
u32 timeScan = 0;

void setSttScanK9B(uint8_t sttScan){
	startFindK9B = (sttScan==K9B_PAR_START_SCAN)?TRUE:FALSE;
	if(startFindK9B == TRUE){
		timeScan = clock_time_s();
	}else{
		timeScan = 0;
	}
}
_Bool getSttScan(void){
	return startFindK9B;
}

void loopTimeOutScan(void){
	u8 fakeMac[6];

	if(getSttScan()==TRUE){
		if(clock_time_s() >= timeScan){
			if(clock_time_s() - timeScan >= K9B_TIMEOUT_SCAN){
				uart_CSend("het_10s\n");
				setSttScanK9B(!K9B_PAR_START_SCAN);
				rspAndUpdate_SttScanK9B(fakeMac, 0, 0, FALSE, RD_GATEWAYADDRESS);
			}
		}else{
			timeScan = clock_time_s();
		}
	}
}

_Bool callSceenByK9B(u32 mac, u8 key){
	for(int i=0; i<RD_NUM_MAX_K9B; i++){
		if(dataFlashK9B.deviceK9B[i].MacK9B == mac){
			for(int j=0; j<RD_NUM_KEY_MAX_ONE_K9B; j++){
				if(dataFlashK9B.deviceK9B[i].Button_ID[j] == key){
					RD_Call_Scene(dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[j], key);	//goi canh
					rspSceen(dataFlashK9B.deviceK9B[i].AddK9B, key, 1, dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[j], RD_GATEWAYADDRESS);	//phan hoi
					return TRUE;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}

_Bool CheckK9BActive(u32 mac, u32 counter, _Bool change){
//	static u32 CounterTemp[RD_NUM_MAX_K9B] = {0};
//	u8 idx = 0;
//
//	if(change == TRUE){
//		for(int i=0; i<RD_NUM_MAX_K9B; i++){
//			CounterTemp[0] = 0;
//		}
//		return false;
//	}else{
//		for(int i=0; i<RD_NUM_MAX_K9B; i++){
//			if(dataFlashK9B.deviceK9B[i].mac==mac){
//				if(CounterTemp[i]==counter){
//					return FALSE;
//				}else{
//					CounterTemp[i] = counter;
//					return TRUE;
//				}
//			}
//			idx = idx + 1;
//		}
//	}
//
//	return FALSE;
}

void RecDataK9B(switchK9B_proxy_t *K9B_DataRec, u8 *mac, s8 rssi){
	u8 keyTemp = 0;
	u32 macTemp = 0;
	u32 Counter = 0;

	if((K9B_DataRec->type==K9B_TYPE_ADV) && (K9B_DataRec->lengt==K9B_LENGTH_DATA)){
		char UART_TempSend1[128] = {0};
		sprintf(UART_TempSend1,"mac: %x--%x--%x--%x--%x--%x Rssi: %d \n",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], rssi);
		uart_CSend(UART_TempSend1);
		sprintf(UART_TempSend1,"infor: Vid:%4x- Farme %2x--%x--%x--%x--%x \n",K9B_DataRec->Vid, K9B_DataRec->frame, K9B_DataRec->type_device, K9B_DataRec->key, K9B_DataRec->Counter, K9B_DataRec->signature);
		uart_CSend(UART_TempSend1);

		macTemp = macTemp | ((u32)mac[0] << 24) | ((u32)mac[1] << 16) | ((u32)mac[2] << 8) | ((u32)mac[3]);
		Counter = K9B_DataRec->Counter;
		keyTemp = K9B_DataRec->key;

		K9BInforAll.K9BDataAdv = K9B_DataRec;
		K9BInforAll.mac = mac;
		K9BInforAll.rssi = rssi;

		if(getSttScan()==TRUE){
			uart_CSend("send_2hc\n");
			setSttScanK9B(!K9B_PAR_START_SCAN);
			rspAndUpdate_SttScanK9B(K9BInforAll.mac, K9BInforAll.K9BDataAdv->type_device, K9BInforAll.rssi, TRUE, RD_GATEWAYADDRESS);
		}else{
			if((keyTemp&0x80)==0x00){
				if(CheckK9BActive(macTemp, Counter, FALSE)==TRUE){
					uart_CSend("******************************************\n");
					char UART_TempSend1[128] = {0};
					sprintf(UART_TempSend1,"mac: %x--%x--%x--%x--%x--%x Rssi: %d \n",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], rssi);
					uart_CSend(UART_TempSend1);
					sprintf(UART_TempSend1,"infor: Vid:%4x- Farme %2x--%x--%x--%x--%x \n",K9B_DataRec->Vid, K9B_DataRec->frame, K9B_DataRec->type_device, K9B_DataRec->key, K9B_DataRec->Counter, K9B_DataRec->signature);
					uart_CSend(UART_TempSend1);
					uart_CSend("******************************************\n");

					if(callSceenByK9B(macTemp, keyTemp)== FALSE){
						//
					}
				}
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------
void RD_Flash_CleanK9B(void){
	dataFlashK9B.Used[0] = RD_CHECK_FLASH_K9B_H;
	dataFlashK9B.Used[1] = RD_CHECK_FLASH_K9B_L;
	dataFlashK9B.Used[2] = RD_CHECK_FLASH_K9B_H;
	dataFlashK9B.Used[3] = RD_CHECK_FLASH_K9B_L;

	for(int i=0; i<5; i++){
		dataFlashK9B.deviceK9B[i].AddK9B = 0;
		dataFlashK9B.deviceK9B[i].MacK9B = 0;
		for(int j=0; j<15; j++){
			dataFlashK9B.deviceK9B[i].Button_ID[j] = 0;
			dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[j] = 0;
		}
	}

   	flash_erase_sector(RD_K9B_FLASH_AREA);
	flash_write_page(RD_K9B_FLASH_AREA, RD_K9B_FLASH_SIZE, (unsigned char *) (&dataFlashK9B.Used[0]));
}

void initFlashK9B(void){
	flash_read_page(RD_K9B_FLASH_AREA, RD_K9B_FLASH_SIZE, (unsigned char *) (&dataFlashK9B.Used[0]));

	if((dataFlashK9B.Used[0] != RD_CHECK_FLASH_K9B_H) && (dataFlashK9B.Used[1] != RD_CHECK_FLASH_K9B_L)  && (dataFlashK9B.Used[2] != RD_CHECK_FLASH_K9B_H)	&& (dataFlashK9B.Used[3] != RD_CHECK_FLASH_K9B_L) )														// fist time to read reset memory
	{
		RD_Flash_CleanK9B();
	}
	CheckK9BActive(0,0,TRUE);
}

_Bool addSceenArr(u8 *arrKey, u16 *arrSceen, u8 valKey, u16 valSceen){
	u8 idx = RD_NUM_KEY_MAX_ONE_K9B;

	for(int i=0; i<RD_NUM_KEY_MAX_ONE_K9B; i++){
		if(arrKey[i]==valKey){
			arrSceen[i] = valSceen;
			return TRUE;
		}
		if(arrKey[i]==0){
			idx = i;
		}
	}

	if(idx == RD_NUM_KEY_MAX_ONE_K9B){
		return FALSE;
	}else{
		arrKey[idx] = valKey;
		arrSceen[idx] = valSceen;
		return TRUE;
	}
}

_Bool delSceenArr(Flash_SaveTemp_K9B *listDevice, u8 valKey, u16 addr){
//	if(addr != 0){
//		if(addr == 0xffff){
//			for(int i=0; i<RD_NUM_MAX_K9B; i++){
//				for(int j=0; j<RD_NUM_KEY_MAX_ONE_K9B; j++){
//					listDevice[i].Button_ID[j] = 0;
//					listDevice[i].Scene_ID_OnePress[j] = 0;
//				}
//			}
//			return TRUE;
//		}else{
//			for(int i=0; i<RD_NUM_MAX_K9B; i++){
//				if(listDevice[i].addK9B == addr){
//					if(valKey == 0xff){
//						for(int j=0; j<RD_NUM_KEY_MAX_ONE_K9B; j++){
//							listDevice[i].key[j] = 0;
//							listDevice[i].sceenForKey[j] = 0;
//						}
//						return TRUE;
//					}else{
//						for(int j=0; j<RD_NUM_KEY_MAX_ONE_K9B; j++){
//							if(listDevice[i].key[j]==valKey){
//								listDevice[i].key[j] = 0;
//								listDevice[i].sceenForKey[j] = 0;
//								return TRUE;
//							}
//						}
//					}
//				}
//			}
//		}
//	}

	return FALSE;
}

u8 addDeviceK9B(Flash_SaveTemp_K9B *listDevice, u32 mac, u16 addr){
//	u8 idx = RD_NUM_MAX_K9B;
//
//	for(int i=0; i<RD_NUM_MAX_K9B; i++){
//		if(listDevice[i].mac==mac){
//			listDevice[i].mac = mac;
//			listDevice[i].addK9B = addr;
//			for(int j=0; j<RD_NUM_KEY_MAX_ONE_K9B; j++){
//				listDevice[i].key[j] = 0;
//				listDevice[i].sceenForKey[j] = 0;
//			}
//			return RD_RSP_SAVEK9B_SUCC;
//		}
//
//		if(listDevice[i].mac==0){
//			idx = i;
//		}
//	}
//
//	if(idx == RD_NUM_MAX_K9B){
//		return RD_RSP_SAVEK9B_FULL;
//	}else{
//		listDevice[idx].addK9B = addr;
//		listDevice[idx].mac = mac;
//		for(int j=0; j<RD_NUM_KEY_MAX_ONE_K9B; j++){
//			listDevice[idx].key[j] = 0;
//			listDevice[idx].sceenForKey[j] = 0;
//		}
//		return RD_RSP_SAVEK9B_SUCC;
//	}
}

u8 delDeviceK9B(Flash_SaveTemp_K9B *listDevice, u16 addr){

//	if((addr != 0x0000) && (addr != 0xffff)){
//		for(int i=0; i<RD_NUM_MAX_K9B; i++){
//			if(listDevice[i].addK9B==addr){
//				listDevice[i].addK9B = 0x00;
//				listDevice[i].mac = 0x00;
//				for(int j=0; j<RD_NUM_KEY_MAX_ONE_K9B; j++){
//					listDevice[i].key[j] = 0;
//					listDevice[i].sceenForKey[j] = 0;
//				}
//				return RD_RSP_DELK9B_SUCC;
//			}
//		}
//	}else if(addr == 0xffff){
//		for(int i=0; i<RD_NUM_MAX_K9B; i++){
//			listDevice[i].addK9B = 0;
//			listDevice[i].mac = 0;
//			for(int j=0; j<RD_NUM_KEY_MAX_ONE_K9B; j++){
//				listDevice[i].key[j] = 0;
//				listDevice[i].sceenForKey[j] = 0;
//			}
//		}
//		return RD_RSP_DELK9B_SUCC;
//	}
//
//	return RD_RSP_DELEK9B_ADDNULL;
}

//------------------------------------------------------------------------------------------------------
void saveDeviceK9BFlash(u32 mac, u16 addrK9B, u16 gwAdd){
	u8 sttSave = addDeviceK9B((Flash_SaveTemp_K9B *)(&dataFlashK9B.deviceK9B[0]), mac, addrK9B);
	u8 par[7] = {0};
	par[0] = (u8)(K9B_HEADER_E2_SAVE_K9B & 0xff);
	par[1] = (u8)((K9B_HEADER_E2_SAVE_K9B>>8) & 0xff);
	par[2] = (u8)((mac >> 24) & 0xff);
	par[3] = (u8)((mac >> 16) & 0xff);
	par[4] = (u8)((mac >> 8) & 0xff);
	par[5] = (u8)(mac & 0xff);

	if(sttSave==RD_RSP_SAVEK9B_SUCC){
	   	flash_erase_sector(RD_K9B_FLASH_AREA);
		flash_write_page(RD_K9B_FLASH_AREA, RD_K9B_FLASH_SIZE, (unsigned char *) (&dataFlashK9B.Used[0]));

		CheckK9BActive(0,0,TRUE);

		par[6] = RD_RSP_SAVEK9B_SUCC;
		mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
	}else if(sttSave==RD_RSP_SAVEK9B_FULL) {
		par[6] = RD_RSP_SAVEK9B_FULL;
		mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
	}
}

void delDeviceK9BFlash(u16 addrK9B, u16 gwAdd){
	u8 sttSave = delDeviceK9B((Flash_SaveTemp_K9B *)(&dataFlashK9B.deviceK9B[0]), addrK9B);
	u8 par[5] = {0};
	par[0] = (u8)(K9B_HEADER_E2_DELETE_K9B & 0xff);
	par[1] = (u8)((K9B_HEADER_E2_DELETE_K9B>>8) & 0xff);
	par[2] = (u8)((addrK9B >> 8) & 0xff);
	par[3] = (u8)(addrK9B & 0xff);

	if(sttSave==RD_RSP_DELK9B_SUCC){
	   	flash_erase_sector(RD_K9B_FLASH_AREA);
		flash_write_page(RD_K9B_FLASH_AREA, RD_K9B_FLASH_SIZE, (unsigned char *) (&dataFlashK9B.Used[0]));

		CheckK9BActive(0,0,TRUE);

		par[4] = RD_RSP_DELK9B_SUCC;
		mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
	}else if(sttSave==RD_RSP_DELEK9B_ADDNULL){
		par[4] = RD_RSP_DELEK9B_ADDNULL;
		mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
	}
}

void saveSceenK9BFlash(u16 addr, u8 valKey, u16 valSceen, u16 gwAdd){
//	_Bool sttSaveSceen = FALSE;
//	_Bool idxT = FALSE;
//	u8 par[3] = {0};
//	par[0] = (u8)(K9B_HEADER_E2_SAVE_SCEEN & 0xff);
//	par[1] = (u8)((K9B_HEADER_E2_SAVE_SCEEN>>8) & 0xff);
//
//	for(int i=0; i<5; i++){
//		if(dataFlashK9B.deviceK9B[i].addK9B == addr){
//			idxT = TRUE;
//			sttSaveSceen = addSceenArr((u8 *)&dataFlashK9B.deviceK9B[i].key[0], (u16 *)&dataFlashK9B.deviceK9B[i].sceenForKey[0], valKey, valSceen);
//			if(sttSaveSceen == TRUE){
//			   	flash_erase_sector(RD_K9B_FLASH_AREA);
//				flash_write_page(RD_K9B_FLASH_AREA, RD_K9B_FLASH_SIZE, (unsigned char *) (&dataFlashK9B.Used[0]));
//
//				par[2] = 0x01;
//				mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
//			}else{
//				par[2] = 0x00;
//				mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
//			}
//			break;
//		}
//	}
//
//	if(idxT == FALSE){
//		par[2] = 0x00;
//		mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
//	}
}

void delSceenK9BFlash(u16 addr, u8 valKey, u16 gwAdd){
	_Bool sttSaveDel = FALSE;
	u8 par[3] = {0};
	par[0] = (u8)(K9B_HEADER_E2_DELETE_SCEEN & 0xff);
	par[1] = (u8)((K9B_HEADER_E2_DELETE_SCEEN>>8) & 0xff);

	sttSaveDel = delSceenArr((Flash_SaveTemp_K9B *)(&dataFlashK9B.deviceK9B[0]), valKey, addr);

	if(sttSaveDel==TRUE){
	   	flash_erase_sector(RD_K9B_FLASH_AREA);
		flash_write_page(RD_K9B_FLASH_AREA, RD_K9B_FLASH_SIZE, (unsigned char *) (&dataFlashK9B.Used[0]));

		par[2] = 0x01;
		mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
	}else{
		par[2] = 0x00;
		mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
	}
}

void deleteFlashK9B(void){
	flash_erase_sector(RD_K9B_FLASH_AREA);
}

//initAndLoop-----------------------------------------------------------
void funcK9BInMainLoop(void){
	loopTimeOutScan();
}

void funcInitK9BMian(void){
	initFlashK9B();
	readFlashForTestK9B();
}

//test-------------------------------------------
void readFlashForTestK9B(void){
	char UART_TempSend[64];

	flash_read_page(RD_K9B_FLASH_AREA, RD_K9B_FLASH_SIZE, (unsigned char *) (&dataFlashK9B.Used[0]));
	uart_CSend("\n");
	uart_CSend("/*SCEEN----------------------------------------------\n");
	sprintf(UART_TempSend,"Used: %x--%x--%x--%x\n", dataFlashK9B.Used[0], dataFlashK9B.Used[1], dataFlashK9B.Used[2], dataFlashK9B.Used[3]);
	uart_CSend(UART_TempSend);
	for(int i=0; i<5; i++){
		sprintf(UART_TempSend,"dev[%d] (add-mac): %x--%x\n", (i+1), dataFlashK9B.deviceK9B[i].AddK9B, dataFlashK9B.deviceK9B[i].MacK9B);
		uart_CSend(UART_TempSend);
		uart_CSend("key-Sceen: ");
		for(int j=0; j<15; j++){
			sprintf(UART_TempSend,"| %d: %x-%x ", (j+1), dataFlashK9B.deviceK9B[i].Button_ID[j], dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[j]);
			uart_CSend(UART_TempSend);
		}
		uart_CSend("\n");
	}
	uart_CSend("\n----------------------------------------------------*\n");
	uart_CSend("\n");
}

//------------------------------------------------------------
void RD_Call_Scene(uint16_t Scene_ID, uint8_t Mess_ID)
{
	Call_Scene_Str Scene_Mess_Buff;
	Scene_Mess_Buff.Scene_ID[0] = (uint8_t)  ((Scene_ID) & 0xFF );
	Scene_Mess_Buff.Scene_ID[1] = (uint8_t) (((Scene_ID >> 8) ) & 0xFF );
	Scene_Mess_Buff.Null_Byte   = Mess_ID;
	Scene_Mess_Buff.Tss[0]		= (uint8_t) ((TSS_DEFAULT) & 0xFF);
	Scene_Mess_Buff.Tss[1]		= (uint8_t) ((TSS_DEFAULT>>8) & 0xFF);
	Scene_Mess_Buff.Future[0]   = 0x00;
	Scene_Mess_Buff.Future[1]   = 0x00;
	Scene_Mess_Buff.Future[2]   = 0x00;

	uint8_t* Mess_Buff;
	Mess_Buff = (uint8_t *) (&Scene_Mess_Buff);
	mesh_tx_cmd2normal_primary(SCENE_RECALL_NOACK, Mess_Buff, 8, 0xffff, 0); //SENSOR_STATUS
}

void rspAndUpdate_SttScanK9B(u8 *mac, u8 typeRemote, s8 rssi, _Bool ScanDone, u16 gwAdd){
	u8 par[8];

	if(ScanDone == FALSE){
		par[0] = 0x0b;
		par[1] = 0x0a;
		par[2] = 0x00;
		par[3] = 0x00;
		par[4] = 0x00;
		par[5] = 0x00;
		par[6] = 0x00;
		par[7] = 0x00;
	}else{
		par[0] = 0x0b;
		par[1] = 0x0a;
		par[2] = mac[0];
		par[3] = mac[1];
		par[4] = mac[2];
		par[5] = mac[3];
		par[6] = typeRemote;
		par[7] = (u8) rssi;
	}
	mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, 8, gwAdd, RD_MAXRESPONESEND);
}

void rspSceen(u16 addK9B, u8 key, u8 modeID, u16 sceenID, u16 gwAdd){
	u8 par[8];
	par[0] = (u8)(K9B_HEADER_E2_RSP_CALLSCEEN_K9B & 0xff);
	par[1] = (u8)((K9B_HEADER_E2_RSP_CALLSCEEN_K9B>>8) & 0xff);
	par[2] = (u8)(addK9B & 0xff);
	par[3] = (u8)((addK9B>>8) & 0xff);
	par[4] = key;
	par[5] = modeID;
	par[6] = (u8)(sceenID & 0xff);
	par[7] = (u8)((sceenID>>8) & 0xff);

	mesh_tx_cmd2normal_primary(RD_OPCODE_RSP_FOR_E2, par, sizeof(par), gwAdd, RD_MAXRESPONESEND);
}


/*-------------------------------Hao--------------------------------*/
void RD_K9B_PairHCSet(uint8_t pairStt, uint16_t K9BAdd)
{
	Sw_Working_Stt_Val.Add_K9B_HCSet = K9BAdd;
	Sw_Working_Stt_Val.Pair_K9BHc_Flag = pairStt;
	Sw_Working_Stt_Val.ClockTimeSetHc_ms = clock_time_ms();
}

/*
 * Start Scan K9B for HC
 */
static void RD_Handle_ScanK9BHc(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uart_CSend("Start wating K9B HC \n");
	uint8_t  K9BPairHc_Stt = par[2];
	RD_K9B_PairHCSet(K9BPairHc_Stt, 0x0000); // turn on K9B pair Hc
}

/*
 * save Mac and add off K9B HC
 */
static void RD_Handle_SaveK9BHc(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint32_t MacK9B_Buff = (uint32_t) ( (par[5]<<24) | (par[4]<<16) | (par[3]<<8) | (par[2]));
	uint16_t K9BAdd	 	 = (uint16_t) ((par[7] << 8) | par[6]  );
	uint8_t SaveK9B_Stt = RD_Flash_SaveK9BHc(MacK9B_Buff, 3, K9BAdd);// save max button

	uint8_t MessRsp[7];
	for(int i=0; i<6; i++) MessRsp[i] =  par[i];

	MessRsp[6] = SaveK9B_Stt;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &MessRsp[0], 7, Gw_Add_Buff, RD_MAXRESPONESEND);
	uart_CSend("Save Mac K9BHC \n");
}

static void RD_Handle_DeleteK9BHC(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint16_t K9BAdd	 	 = (uint16_t) ((par[3] << 8) | par[2]  );
	uint8_t SaveK9B_Stt = RD_Flash_DeleteK9BHC(K9BAdd);

	uint8_t Mess_RspBuff[5] ={0};
	Mess_RspBuff[0]	= RD_HEADER_SW_DELETEK9BHC 				& 0xFF;
	Mess_RspBuff[1]	= (RD_HEADER_SW_DELETEK9BHC >> 8) 		& 0xFF;
	Mess_RspBuff[2]	= K9BAdd 				& 0xFF;
	Mess_RspBuff[3]	= (K9BAdd >> 8) 		& 0xFF;
	Mess_RspBuff[4] =  SaveK9B_Stt;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &Mess_RspBuff[0], 5, Gw_Add_Buff, RD_MAXRESPONESEND);
	uart_CSend("Delete K9BHC \n");
}

uint8_t RD_Flash_SaveK9BHc(uint32_t macDevice, uint8_t Num_Of_Button, uint16_t K9BAdd)
{
	uint8_t overSave_Flag =0; // resave when duplicate mac
	uint8_t  overSave_ID =0;
	// check duplicate remote saved
	for(int i=0; i<MAX_NUM_K9BHC; i++)
	{
		if(dataFlashK9B.deviceK9B[i].MacK9B == macDevice)
		{
			overSave_Flag =1;
			overSave_ID = i;
			break;
		}
	}

	if(1 == overSave_Flag)
	{
		dataFlashK9B.deviceK9B[overSave_ID].MacK9B = macDevice;
		dataFlashK9B.deviceK9B[overSave_ID].Num_Of_Button = Num_Of_Button;
		dataFlashK9B.deviceK9B[overSave_ID].AddK9B = K9BAdd;
		flash_erase_sector(RD_K9B_FLASH_AREA);
		flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0]);
		//uart_CSend("over Save K9B HC Mac:%x  NumOfButton:%d add: 0x%x\n",macDevice,  Num_Of_Button, K9BAdd);
		uart_CSend("over Save K9B HC\n");
		return 1;
	}
	// check null task memory
	for(int i=0; i<MAX_NUM_K9BHC; i++)
	{
		if(dataFlashK9B.deviceK9B[i].MacK9B == 0x00)		// task memory is ready for new
		{
			dataFlashK9B.deviceK9B[i].MacK9B = macDevice;
			dataFlashK9B.deviceK9B[i].Num_Of_Button = Num_Of_Button;
			dataFlashK9B.deviceK9B[i].AddK9B = K9BAdd;
			flash_erase_sector(RD_K9B_FLASH_AREA);
			//flash_write_page(RD_K9B_FLASH_AREA, sizeof(sw_flash_data_config_val), (uint8_t *) &sw_flash_data_config_val.Factory_Check );
			flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0]);
			//uart_CSend("Save K9B HC Mac:%x  NumOfButton:%d add: 0x%x\n",macDevice,  Num_Of_Button, K9BAdd);
			uart_CSend("Save K9B HC\n");
			return 1;
		}
		if(i == (MAX_NUM_K9BHC-1) ) return 0; // fail full mem
	}
	return 0;
}


void RD_Flash_SetNullK9B(uint8_t numOfArray)
{
	if( 0xFF == numOfArray)
	{
		for(int i=0; i< MAX_NUM_K9BHC; i++)
		{
			dataFlashK9B.deviceK9B[i].MacK9B = 0x00;
			dataFlashK9B.deviceK9B[i].Num_Of_Button = 0x00;
			dataFlashK9B.deviceK9B[i].AddK9B = 0x00;
			for(int j=0; j< MAX_MUM_K9BPRESSTYPE; j++)
			{
				dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[j] = 0;
				dataFlashK9B.deviceK9B[i].Button_ID[j] = 0;
			}
		}
	}
	else
	{
		dataFlashK9B.deviceK9B[numOfArray].MacK9B = 0x00;
		dataFlashK9B.deviceK9B[numOfArray].Num_Of_Button = 0x00;
		dataFlashK9B.deviceK9B[numOfArray].AddK9B = 0x00;
		for(int j=0; j< MAX_MUM_K9BPRESSTYPE; j++)
		{
			dataFlashK9B.deviceK9B[numOfArray].Scene_ID_OnePress[j] = 0;
			dataFlashK9B.deviceK9B[numOfArray].Button_ID[j] = 0;
		}
	}


}


static void RD_Flash_SetNullSceneK9B(uint8_t numOfArray)
{
	if( 0xFF == numOfArray)
	{
		for(int i=0; i< MAX_NUM_K9BHC; i++)
		{
			for(int j=0; j< MAX_MUM_K9BPRESSTYPE; j++)
			{
				dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[j] = 0;
				dataFlashK9B.deviceK9B[i].Button_ID[j] = 0;
			}
		}
	}
	else
	{
		for(int j=0; j < MAX_MUM_K9BPRESSTYPE; j++)
		{
			dataFlashK9B.deviceK9B[numOfArray].Scene_ID_OnePress[j] = 0;
			dataFlashK9B.deviceK9B[numOfArray].Button_ID[j] = 0;
		}
	}


}

uint8_t RD_Flash_DeleteK9BHC(uint16_t K9BAdd)
{
	if(0xFFFF != K9BAdd)
	{
		for(int i=0; i<MAX_NUM_K9BHC; i++)
		{
			if(dataFlashK9B.deviceK9B[i].AddK9B == K9BAdd)
			{
				RD_Flash_SetNullK9B(i);
				flash_erase_sector(RD_K9B_FLASH_AREA);
				flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0] );
				uart_CSend("delete K9B HC\n");
				return 1;
			}
		}
		uart_CSend("don't have  K9B HC to delete");
		return 0; // no data to delete
	}
	else
	{
		RD_Flash_SetNullK9B(0xFF);
		flash_erase_sector(RD_K9B_FLASH_AREA);
		flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0] );
		uart_CSend("delete all remote K9B HC");
		return 1;
	}
}

uint8_t RD_K9B_Pair_OnOffGetFlag(void)
{
	return Sw_Working_Stt_Val.Button_K9BOnOff_Pair;
}
void RD_K9B_Pair_OnOffClearFlag(void){
	Sw_Working_Stt_Val.Button_K9BOnOff_Pair = 0x00;
	Sw_Working_Stt_Val.Pair_K9BOnOff_Flag   = 0x00;
}

static inline void RD_K9B_TimeoutScan_OnOff(void){
	if((0x00 != RD_K9B_Pair_OnOffGetFlag()) &&  (clock_time_exceed_ms(Sw_Working_Stt_Val.Clock_time_start_pair_onOff_ms, TIME_PAIR_K9B_LOCAL_MS)))
	{
		uart_CSend("Time out Pair K9B onOff \n");
		RD_K9B_Pair_OnOffClearFlag();
	}
}
void RD_K9B_TimeOutScan(void){
	RD_K9B_TimeoutScan_OnOff();
}

void RD_Mess_ScanK9BHC_Rsp(uint16_t Gw_Add_Buff, uint32_t K9Bmac, uint8_t type, s8 TxPow)
{
	uint8_t Mess_RspBuff[8] ={0};
	Mess_RspBuff[0]	= RD_HEADER_SW_PAIR_K9BREMOTE 				& 0xFF;
	Mess_RspBuff[1]	= (RD_HEADER_SW_PAIR_K9BREMOTE >> 8) 		& 0xFF;
	Mess_RspBuff[2] = (uint8_t) (K9Bmac      & 0xFF);
	Mess_RspBuff[3] = (uint8_t) ((K9Bmac >> 8) & 0xFF);
	Mess_RspBuff[4] = (uint8_t) ((K9Bmac >> 16) & 0xFF);
	Mess_RspBuff[5] = (uint8_t) ((K9Bmac >> 24) & 0xFF);
	Mess_RspBuff[6] = type;
	Mess_RspBuff[7] = TxPow;
	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &Mess_RspBuff[0], 8, Gw_Add_Buff, RD_MAXRESPONESEND);

}

void RD_MessK9BHc_Press(uint16_t K9B_Add, uint8_t ButtonID, uint8_t ModeID, uint16_t SenceID)
{
	uint8_t Mess_Buff[8] = {0};

	Mess_Buff[0] 	= RD_HEADER_SW_K9B_PRESS & 0xFF ;
	Mess_Buff[1]	= RD_HEADER_SW_K9B_PRESS >>8;
	Mess_Buff[2]  	= K9B_Add & 0xFF;
	Mess_Buff[3]  	= K9B_Add >>8;
	Mess_Buff[4]  	= ButtonID;
	Mess_Buff[5]  	= ModeID;
	Mess_Buff[6]  	= SenceID & 0xFF;
	Mess_Buff[7]  	= SenceID >>8;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP, Mess_Buff, 8, RD_GATEWAYADDRESS, RD_MAXRESPONESEND); //SENSOR_STATUS
	uart_CSend("send K9B Press HC \n");
}

void RD_K9B_CheckScanK9BHc(uint32_t K9BMac_Buff, uint8_t Num_Of_Button, signed char rssi)
{
	if(0x01 == Sw_Working_Stt_Val.Pair_K9BHc_Flag)
	{
		//uart_CSend("send HC mac: %08x, Type: %d, rssi: %d--%x--%x--%x Rssi: %d",K9BMac_Buff, Num_Of_Button, rssi);
		uart_CSend("send K9B mac to HC \n");
		RD_Mess_ScanK9BHC_Rsp(RD_GATEWAYADDRESS, K9BMac_Buff, Num_Of_Button, rssi);
		RD_K9B_PairHCSet(0x00, 0x0000); //clear phase working
	}
}

int RD_CheckButtonPosK9BHC(uint8_t ButtonID_Aray[MAX_MUM_K9BPRESSTYPE], uint8_t ButtonID_Check){
	for(int i=0; i<MAX_MUM_K9BPRESSTYPE; i++){
		if(ButtonID_Aray[i] == ButtonID_Check) {
			uart_CSend("Button Pos \n");
			return i;
		}
	}
	uart_CSend("don't find BID \n");
	return -1;
}

uint8_t RD_K9B_ScanPress2HC(uint32_t macDevice, uint8_t key, uint32_t par_signature)
{
	uint8_t scanSttReturn = 0;
	static uint32_t clockTime_toggleButton_ms[MAX_NUM_K9BHC] ={0};
	static uint32_t signatureLast = 0;

	static uint8_t K9BButton_ID=0;
	uint8_t press_access =0;

	static K9bHc_countLast_st Hc_CountLast = {{0}};
	if( (key>0) && (key <0x80)) // only rising press.
	{
		K9BButton_ID = key;
		press_access = 1;
	}
	if( ((0x00 == par_signature) || (par_signature != signatureLast)) && (1 == press_access) )
	{
		for(int i=0; i< MAX_NUM_K9BHC; i++)
		{

			if(macDevice == dataFlashK9B.deviceK9B[i].MacK9B)
			{
				scanSttReturn = 1;
				if(clock_time_exceed_ms(clockTime_toggleButton_ms[i], CLOCK_TIME_OUT_PRESS_K9B_MS))
				{
					if(Hc_CountLast.countLastOfMacID[i]  != par_signature){
						Hc_CountLast.countLastOfMacID[i] = par_signature;
						clockTime_toggleButton_ms[i] = clock_time_ms();
						uint16_t K9BHC_Add = dataFlashK9B.deviceK9B[i].AddK9B;
						uint16_t SceneID		= 0x0000;

						int ButtonPos_Buff = RD_CheckButtonPosK9BHC(dataFlashK9B.deviceK9B[i].Button_ID, key);
						if(ButtonPos_Buff != -1) SceneID = dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[ButtonPos_Buff];


						RD_MessK9BHc_Press(K9BHC_Add, K9BButton_ID, 1, SceneID);

						if(0x0000 != SceneID) RD_Call_Scene(SceneID, (uint8_t) (K9BButton_ID + SceneID));

						signatureLast = par_signature;
					//	uart_CSend("send K9B HC: 0x%08x, button: %d, Scene: 0x%04x",macDevice, K9BButton_ID, SceneID);
						uart_CSend("send K9B HC: \n");
					}
				}
			}
		}
	}


	for(int i=0; i< MAX_NUM_K9BHC; i++)
	{
		if(macDevice == dataFlashK9B.deviceK9B[i].MacK9B)
		{
			scanSttReturn = 1;
		}
	}
	return scanSttReturn;

}


uint8_t RD_Flash_SaveSceneK9BHC(uint16_t K9BAdd, uint8_t ButtonID, uint16_t SceneID)
{
	for(int i=0; i<MAX_NUM_K9BHC; i++)
	{
		if(dataFlashK9B.deviceK9B[i].AddK9B == K9BAdd)		// task memory is ready for new
		{
			int ButtonPos_Buff = RD_CheckButtonPosK9BHC(&dataFlashK9B.deviceK9B[i].Button_ID[0], ButtonID);

			if(-1 == ButtonPos_Buff){ // new ButtonID //RD_Note
				int ButtonPos_New = RD_CheckButtonPosK9BHC(&dataFlashK9B.deviceK9B[i].Button_ID[0], 0x00);
				dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[ButtonPos_New] = SceneID;
				dataFlashK9B.deviceK9B[i].Button_ID[ButtonPos_New] = ButtonID;
			}
			else{ // duplicate Button ID, over save
				if(0x0000 == SceneID) ButtonID =0; // delete scene
				dataFlashK9B.deviceK9B[i].Scene_ID_OnePress[ButtonPos_Buff] = SceneID;
				dataFlashK9B.deviceK9B[i].Button_ID[ButtonPos_Buff] = ButtonID;
			}

			flash_erase_sector(RD_K9B_FLASH_AREA);
			flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0] );

			//uart_CSend("Save K9B HC scene:%x  BID:%d, ButtonPos_Buff: %d\n",SceneID,  ButtonID, ButtonPos_Buff);
			uart_CSend("Save K9B HC scene \n");
			return 1;
		}
	}
	return 0; // don;t find k9b remote
}


uint8_t RD_Flash_DeleteSceneK9BHC(uint16_t K9BAdd)
{
	if(0xFFFF != K9BAdd)
	{
		for(int i=0; i<MAX_NUM_K9BHC; i++)
		{
			if(dataFlashK9B.deviceK9B[i].AddK9B == K9BAdd)
			{
				RD_Flash_SetNullSceneK9B(i);
				flash_erase_sector(RD_K9B_FLASH_AREA);
				flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0]);
				//uart_CSend("delete all scene K9B add: 0x%x\n",K9BAdd);
				uart_CSend("delete all scene K9B add:\n");
				return 1;
			}
		}
		uart_CSend("don't have  K9B HC to delete Scene");
		return 0; // no data to delete
	}
	else
	{
		RD_Flash_SetNullSceneK9B(0xFF);
		flash_erase_sector(RD_K9B_FLASH_AREA);
		flash_write_page(RD_K9B_FLASH_AREA, sizeof(dataFlashK9B), (uint8_t *) &dataFlashK9B.Used[0] );
		uart_CSend("delete all scene of all K9B \n");
		return 1;
	}
}

static void RD_Handle_K9BSaveScene(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint16_t K9BAdd = (uint16_t) ((par[3] << 8) | par[2] );
	uint8_t ButtonID = par[4];
	uint8_t ModeID = par[5];
	uint16_t Scene_ID	= (uint16_t) ((par[7] << 8) | par[6] );

	//uart_CSend("save Scene add:%x  BID:%d Scene ID: 0x%x\n",K9BAdd,  ButtonID, Scene_ID);
	uart_CSend("save Scene K9B\n");
	uint8_t SaveStt = RD_Flash_SaveSceneK9BHC(K9BAdd, ButtonID, Scene_ID);

	uint8_t Mess_RspBuff[3] ={0};
	Mess_RspBuff[0]	= RD_HEADER_SW_SAVESCENE_K9BREMOTE 				& 0xFF;
	Mess_RspBuff[1]	= (RD_HEADER_SW_SAVESCENE_K9BREMOTE >> 8) 		& 0xFF;
	Mess_RspBuff[2]	= SaveStt;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &Mess_RspBuff[0], 3, Gw_Add_Buff, RD_MAXRESPONESEND);

}

static void RD_Handle_K9BDeleteScene(uint8_t par[8], uint16_t Gw_Add_Buff)
{
	uint16_t K9BAdd 	= (uint16_t) ((par[3] << 8) | par[2] );
	uint8_t ButtonID 	= par[4];
	uint8_t ModeID 		= par[5];
	uint8_t deleteStt=0;
	if( 0xFFFF == K9BAdd ) 		deleteStt = RD_Flash_DeleteSceneK9BHC(K9BAdd); 			// delete all Scene of all remote
	else
	{
		if( 0xff == ButtonID)   deleteStt = RD_Flash_DeleteSceneK9BHC(K9BAdd); 							// delete all scene of 1 remote K9BAdd
		else					deleteStt = RD_Flash_SaveSceneK9BHC(K9BAdd, ButtonID, 0x0000); // delete 1 scene
	}



	uint8_t Mess_RspBuff[3] ={0};
	Mess_RspBuff[0]	= RD_HEADER_SW_DELETESCENE_K9BREMOTE 				& 0xFF;
	Mess_RspBuff[1]	= (RD_HEADER_SW_DELETESCENE_K9BREMOTE >> 8) 		& 0xFF;
	Mess_RspBuff[2]	= deleteStt;

	mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP , &Mess_RspBuff[0], 3, Gw_Add_Buff, RD_MAXRESPONESEND);

}

