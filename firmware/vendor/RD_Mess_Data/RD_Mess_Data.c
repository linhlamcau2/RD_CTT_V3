/*
 * RD_Mess_Data.c
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#include "RD_Mess_Data.h"
#include "../RD_Add_RoomSceen/RD_Add_RoomSceen.h"

RD_Type_Device_Message RD_Mess_Receive;
RD_Type_Device_Message *RD_Mess_TempReceive;
RD_Save_Gateway_Address RD_Save_Gw_Address;
RD_Save_Gateway_Address *RD_TempSave_Gw_Address;
RD_Type_Device_Message RD_Flash_Save_Data[256];
RD_Rsp_Gateway_Address RD_Rsp_Gw_Address;

RD_Rsp_Remote RD_Rsp_Remote_Control;
RD_Rsp_GW_Info RD_Rsp_GW_Info_Answer;

u8 Status_Onoff = 0;
u8 Mode_ct_rgb = 0;
u16 vrs_DIM = 0;
u16 vrs_CCT = 0;
u16 Remote_rsp_address = 0;
u32 OP_rsp_Remote = 0;
int vrs_count_sched = 0;
static unsigned long TimeNewSched, TimeOldSched;
_Bool flag_sched_set = FALSE;
u16 time_sched_set = 0;
char UART_TempSend[128];

u16 RD_GATEWAYADDRESS = 0x0001;
int flag_training_test2 = 0;
int vr_count = 1;
int flag_kickout = 0;
unsigned char *BuffData;

//RD_EDIT: SEC : A VAL SECURETY-----------------------------------------------------------
int vrs_time_bindall = 0;
int vrs_time_error_aes = 0;
_Bool flag_process_aes = FALSE;
_Bool flag_check_mess = FALSE;
_Bool flag_process_security = FALSE;

unsigned char rangDongKey[16] = {0x44, 0x69, 0x67, 0x69, 0x74, 0x61, 0x6c, 0x40, 0x32, 0x38, 0x31, 0x31, 0x32, 0x38, 0x30, 0x34};
unsigned char aesEncrypt[16] = {0};
//--------------------------------------------------------------------

int RD_Messenger_Training_Test2(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
	if(get_provision_state() == STATE_DEV_UNPROV) {
		flag_training_test2 = 1;
		gatt_adv_send_flag  = 0;
		beacon_send.en = 0;
	}
	else{
		flag_training_test2 = 0;
		gatt_adv_send_flag  = 1;
		beacon_send.en = 1;
	}
	return 0;
}

int RD_Messenger_ProcessCommingProcess_Type(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
	// Type_Device
	uint16_t RD_GW_ADR_Buff = 0x0001;
	RD_Mess_TempReceive = (RD_Type_Device_Message *)(&par[0]);
	RD_Mess_Receive = *RD_Mess_TempReceive;
	u16 Header = RD_Mess_Receive.Header[1] << 8 | RD_Mess_Receive.Header[0];

  switch (Header) {
    case RD_SET_TYPE_DEVICE:
    	RD_Mess_Receive.Header[0] =  0x01;
    	RD_Mess_Receive.Header[1] =  0x00;
       	RD_Mess_Receive.MainType  =  0x01;
		RD_Mess_Receive.Feature   =  0x02;
		RD_Mess_Receive.Name  	  =  NAME;
    	RD_Mess_Receive.Future[1] =  VERSION_MAIN;			//RD_EDIT: SEC : PROVIDER - SET TYPE
    	RD_Mess_Receive.Future[2] =  VERSION_SUB;

    	BuffData = (unsigned char *)(&RD_Mess_Receive.Header[0]);
    	RD_Flash_SaveType(RD_Mess_Receive.MainType, RD_Mess_Receive.Feature, RD_Mess_Receive.Name);
    	mesh_tx_cmd2normal_primary(cb_par ->op_rsp, BuffData, 8, cb_par->adr_src, 2);
      break;
		//RD_EDIT: SEC : PROCESS
		case RD_SAVE_GATEWAY_ADDRESS:
			// Save Gateway Address	//RD_EDIT: 0.THANH : SPM: CHANGE SAVE GW
			RD_GW_ADR_Buff = saveGatewayAddr(&par[2],cb_par->adr_src);
			RD_Save_Gw_Address.GWID[1]	= (uint8_t) ((RD_GW_ADR_Buff >> 8) & 0xff);
			RD_Save_Gw_Address.GWID[0]	= (uint8_t) ((RD_GW_ADR_Buff     ) & 0xff);
			RD_Flash_SaveGW(RD_GW_ADR_Buff);
			RD_GATEWAYADDRESS = RD_GW_ADR_Buff;
			RD_Rsp_Gw_Address.Header[0] = 0x02;
			RD_Rsp_Gw_Address.Header[1] = 0x00;
			RD_Rsp_Gw_Address.GWID[0]   = RD_Save_Gw_Address.GWID[0];
			RD_Rsp_Gw_Address.GWID[1]   = RD_Save_Gw_Address.GWID[1];
	    	RD_Rsp_Gw_Address.Future[0] = PROVIDER_SUB;						//RD_EDIT: SEC : PROVIDER - SAVE GATEWAY
	    	RD_Rsp_Gw_Address.Future[1] = PROVIDER_MAIN;
			RD_Rsp_Gw_Address.Future[2] = 0x00;
			RD_Rsp_Gw_Address.Future[3] = 0x00;

			BuffData = (unsigned char *)(&RD_Rsp_Gw_Address.Header[0]);
			mesh_tx_cmd2normal_primary(cb_par ->op_rsp, BuffData, 8, cb_par->adr_src, 2);
		  break;

		case RD_TYPE_DEVICE:
			if(is_provision_success()){
				flag_check_mess = TRUE;
				if(rdAesreCheck(cb_par->adr_dst,&par[2])){	//RD_EDIT: SEC : BIT NHAN TU BIT 2 VI 2 BIT HEADER
					flag_process_aes 		  =  TRUE;
					flag_process_security 	  =  FALSE;

					RD_Mess_Receive.Header[0] =  0x03;
					RD_Mess_Receive.Header[1] =  0x00;
					RD_Mess_Receive.MainType  =  0x01;
					RD_Mess_Receive.Feature   =  0x02;
					RD_Mess_Receive.Name  	  =  NAME;
					RD_Mess_Receive.Future[0] =  0x00;
					RD_Mess_Receive.Future[1] =  VERSION_MAIN;
					RD_Mess_Receive.Future[2] =  VERSION_SUB;

					BuffData = (unsigned char *)(&RD_Mess_Receive.Header[0]);
	//            	RD_Flash_SaveType(RD_Mess_Receive.MainType, RD_Mess_Receive.Feature, RD_Mess_Receive.Name);
					mesh_tx_cmd2normal_primary(cb_par ->op_rsp, BuffData, 8, cb_par->adr_src, 2);
//					uart_CSend("Ma hoa dung\n");
				}
				else{
					flag_process_aes 		  =  FALSE;

					RD_Mess_Receive.Header[0] =  0x03;
					RD_Mess_Receive.Header[1] =  0x00;
					RD_Mess_Receive.MainType  =  0xff;		//RD_EDIT: SEC : RSP WHEN ERR
					RD_Mess_Receive.Feature   =  0xfe;
					RD_Mess_Receive.Name  	  =  0xff;
					RD_Mess_Receive.Future[0] =  0xfe;
					RD_Mess_Receive.Future[1] =  0xff;
					RD_Mess_Receive.Future[2] =  0xfe;
					BuffData = (unsigned char *)(&RD_Mess_Receive.Header[0]);
					mesh_tx_cmd2normal_primary(cb_par ->op_rsp, BuffData, 8, cb_par->adr_src, 2);

					vrs_time_error_aes = clock_time_s();
//					uart_CSend("Ma hoa sai\n");
				}
				//RD_EDIT: SEC : PROCESS-FLASH
				RD_Flash_SaveSecurity(flag_process_aes, flag_process_security, flag_check_mess);
			}
			else if(get_provision_state() == STATE_DEV_UNPROV){
				//RD_EDIT: SEC : STATE_DEV_UNPROV
				RD_Mess_Receive.Header[0] =  0x03;
				RD_Mess_Receive.Header[1] =  0x00;
				RD_Mess_Receive.MainType  =  0x01;
				RD_Mess_Receive.Feature   =  0x02;
				RD_Mess_Receive.Name  	  =  NAME;
				RD_Mess_Receive.Future[0] =  0x00;
				RD_Mess_Receive.Future[1] =  VERSION_MAIN;
				RD_Mess_Receive.Future[2] =  VERSION_SUB;

				BuffData = (unsigned char *)(&RD_Mess_Receive.Header[0]);
				mesh_tx_cmd2normal_primary(cb_par ->op_rsp, BuffData, 8, cb_par->adr_src, 2);
			}
		  break;

		case RD_KICKOUT_ALL:
			if(get_provision_state() == STATE_DEV_PROVED){
				flag_kickout = 1;
				mesh_tx_cmd2normal_primary(cb_par ->op_rsp, par, par_len, cb_par->adr_src, 2);
			}
		break;
  }
  return 0;
}

int RD_Messenger_BindAll(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par) {
  extern int mesh_cmd_sig_cfg_bind(u8 * par, int par_len, mesh_cb_fun_par_t *cb_par);

  //RD_EDIT: SEC : BINALL-------------------------------------------
    vrs_time_bindall = clock_time_s();	//RD_EDIT: SEC : BINALL : DEM 2P DE KICH OUT NEU KHONG CO AES
    flag_process_security = TRUE;
    flag_check_mess		= FALSE;
  //---------------------------------------------

  if ((par[4] == RD_CODE_PRODONE_L) && (par[5] == RD_CODE_PRODONE_H) && (vr_count == 1)) {

	RD_Flash_SaveSecurity(flag_process_aes, flag_process_security, flag_check_mess);	//RD_EDIT: SEC : BINALL: LUU FLASH CAC CO CUA PHAN BAO MAT

    RD_GATEWAYADDRESS = 0x0001;
    vr_count++;
    RD_light_ev_with_sleep(3, 500 * 1000);
    sleep_ms(100);
    st_pub_list_t pub_list = {{0}};
    mesh_cmd_light_ctl_set_t p_set ;
    mesh_cmd_lightness_set_t p_set_light;
    p_set.temp = 0x0320;
    p_set.lightness = 0xffff;
	p_set_light.lightness = 0xffff;
	light_ctl_temp_set(&p_set, 2, 0, 0, 0, &pub_list);
	lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
  }
  return (mesh_cmd_sig_cfg_bind(par, par_len,  cb_par));
}

int RD_mesh_cmd_sig_lightness_linear_set(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
	u8 Header = par[0];
	Remote_rsp_address = cb_par ->adr_src;
	OP_rsp_Remote = cb_par->op_rsp;

    foreach(i, LIGHT_CNT){
    	Status_Onoff = light_g_onoff_present_get(i);
    }

	Mode_ct_rgb = ct_flag;

    foreach(i, LIGHT_CNT){
    	vrs_DIM = light_g_level_present_get_u16(i, 0);
    }

    foreach(i, LIGHT_CNT){
    	vrs_CCT = light_ctl_temp_prensent_get(i);
    }

	switch(Header){
		case RD_REMOTE_CONTROL:
			Remote_Control(par[1], par[3], par[4]);
		break;

		case RD_HC_REQUEST_INFO:
			Answer_Info(Status_Onoff, Mode_ct_rgb, vrs_DIM, vrs_CCT, Remote_rsp_address);
		break;

		case RD_REMOTE_CTL_MODE:
			par[1] = 0;
		    if(OP_rsp_Remote != STATUS_NONE){
				mesh_tx_cmd2normal_primary(LIGHTNESS_LINEAR_STATUS, par, 8, Remote_rsp_address, 2);
		    }
		break;

		case RD_REMOTE_SCHED:
			time_sched_set = par[3] << 8 | par[4];
			vrs_count_sched = 0;
			TimeNewSched = 0;
			TimeOldSched = 0;
			Remote_Sched(par[1]);
		    if(OP_rsp_Remote != STATUS_NONE){
				mesh_tx_cmd2normal_primary(LIGHTNESS_LINEAR_STATUS, par, 8, Remote_rsp_address, 2);
		    }
		    else{}
			break;
	}
	return 0;
}

void Remote_Sched(u8 enable){
	switch (enable){
	case RD_REMOTE_DISNABLE_SCHED:
		//huy hen gio
		flag_sched_set = FALSE;
		break;
	case RD_REMOTE_ENABLE_SCHED:
		//hen gio
		flag_sched_set = TRUE;
		break;
	}
}

void Counter_Sched (u16 time_sched){
	if(flag_sched_set == TRUE){
		TimeNewSched = clock_time_s();

		if(TimeNewSched > 0xfffffff0){
			TimeNewSched = 0;
			TimeOldSched = 0;
		}

		if (TimeNewSched - TimeOldSched > 0) {
			TimeOldSched = TimeNewSched;
			vrs_count_sched++;
			if (vrs_count_sched > (60*time_sched)) {
				vrs_count_sched = 0;
				flag_sched_set = FALSE;
				st_pub_list_t pub_list = {{0}};
				mesh_cmd_g_onoff_set_t p_set;
				p_set.onoff = 0;

				g_onoff_set(&p_set, 2, 0, 0, 0, &pub_list);
			}
		}
	}
}

void Answer_Info(u8 Status_Onoff, u8 Mode_ct_rgb, u16 vrs_DIM, u16 vrs_CCT, u16 adr_src){ 	//RD_EDIT: 1..: SAVE GATEWAY: PHAN HOI

	RD_Rsp_GW_Info_Answer.Header      = RD_HC_REQUEST_INFO;
	RD_Rsp_GW_Info_Answer.Status_mode = Status_Onoff << 4 | 0x01;
	RD_Rsp_GW_Info_Answer.Data[0]     = vrs_DIM & 0x00ff;
	RD_Rsp_GW_Info_Answer.Data[1]	  = vrs_DIM >> 8;
	RD_Rsp_GW_Info_Answer.Data[2]     = vrs_CCT & 0x00ff;
	RD_Rsp_GW_Info_Answer.Data[3]	  = vrs_CCT >> 8;

	switch(Mode_ct_rgb){
		case 0:
			//RGB
		break;
		case 1:
			//CCT
	    	BuffData = (unsigned char *)(&RD_Rsp_GW_Info_Answer.Header);
	    	mesh_tx_cmd2normal_primary(LIGHTNESS_LINEAR_STATUS, BuffData, 8, adr_src, 2);	//RD_EDIT: 1..: SAVE GATEWAY: PHAN HOI
		break;
	}
}

void Remote_Control(u8 Mode_Ctl, u8 Up_Down, u8 Delta){
	switch(Mode_Ctl){
		case REMOTE_CONTROL_DIM:
			Process_Lightness(vrs_DIM, Up_Down, Delta);
			break;

		case REMOTE_CONTROL_CCT:
			Process_Temp(vrs_CCT, Up_Down, Delta);
			break;
	}
}

void Process_Lightness(u16 light_present, u8 Up_Down, u8 Delta){

    int RD_lightness = 0;

    if(Up_Down == REMOTE_CONTROL_UP){
    	RD_lightness = light_present + ((Delta*65535)/100);
    }
    else if(Up_Down == REMOTE_CONTROL_DOWN){
    	RD_lightness = light_present - ((Delta*65535)/100);
    }

    if(RD_lightness > 0xffff){
    	RD_lightness = 0xffff;
    }
    else if(RD_lightness < 0x3333){
    	RD_lightness = 0x3333;
    }

    RD_Rsp_Remote_Control.Header 	 = RD_REMOTE_CONTROL;
    RD_Rsp_Remote_Control.Remote_ctl = Mode_ct_rgb;
    RD_Rsp_Remote_Control.Up_down    = Up_Down;
    RD_Rsp_Remote_Control.Vrs_delta	 = Delta;
    RD_Rsp_Remote_Control.Future[0]	 = RD_lightness & 0x00ff;
    RD_Rsp_Remote_Control.Future[1]	 = RD_lightness >> 8;
    RD_Rsp_Remote_Control.Future[2]	 = vrs_CCT & 0x00ff;
    RD_Rsp_Remote_Control.Future[3]	 = vrs_CCT >> 8;

    if(OP_rsp_Remote != STATUS_NONE){
		BuffData = (unsigned char *)(&RD_Rsp_Remote_Control.Header);
		mesh_tx_cmd2normal_primary(LIGHTNESS_LINEAR_STATUS, BuffData, 8, Remote_rsp_address, 2);
    }
    else{}

    st_pub_list_t pub_list = {{0}};
    mesh_cmd_lightness_set_t p_set_light;
	p_set_light.lightness = RD_lightness;

	lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
}

void Process_Temp(u16 temp_CCT, u8 Up_Down, u8 Delta){
	int RD_temp_CCT = 0;

    if(Up_Down == REMOTE_CONTROL_UP){
    	RD_temp_CCT = temp_CCT + ((Delta * 19200) / 100);
    }
    else if(Up_Down == REMOTE_CONTROL_DOWN){
    	RD_temp_CCT = temp_CCT - ((Delta * 19200) / 100);
    }

    if(RD_temp_CCT > 0x4e20){
    	RD_temp_CCT = 0x4e20;
    }
    else if(RD_temp_CCT < 0x0320){
       	RD_temp_CCT = 0x0320;
    }

    RD_Rsp_Remote_Control.Header 	 = RD_REMOTE_CONTROL;
    RD_Rsp_Remote_Control.Remote_ctl = Mode_ct_rgb;
    RD_Rsp_Remote_Control.Up_down    = Up_Down;
    RD_Rsp_Remote_Control.Vrs_delta	 = Delta;
    RD_Rsp_Remote_Control.Future[0]	 = vrs_DIM & 0x00ff;
    RD_Rsp_Remote_Control.Future[1]	 = vrs_DIM >> 8;
    RD_Rsp_Remote_Control.Future[2]	 = RD_temp_CCT & 0x00ff;
    RD_Rsp_Remote_Control.Future[3]	 = RD_temp_CCT >> 8;

    if(OP_rsp_Remote != STATUS_NONE){
		BuffData = (unsigned char *)(&RD_Rsp_Remote_Control.Header);
		mesh_tx_cmd2normal_primary(LIGHTNESS_LINEAR_STATUS, BuffData, 8, Remote_rsp_address, 2);
    }
    else{}

    st_pub_list_t pub_list = {{0}};
    mesh_cmd_light_ctl_set_t p_set ;
    p_set.temp = RD_temp_CCT;
    light_ctl_temp_set(&p_set, 2, 0, 0, 0, &pub_list);
}

void KickoutALL(void){
    if(flag_kickout == 1){
    	Time_kickout();
    }
}

//RD_EDIT: SEC : KICKOUT
void Process_Kickout_Security(){		//RD_EDIT: 0.THANH : SPM: ENABLE_SECURE
#if(ENABLE_SECURE)
	if((flag_process_security == TRUE) && (clock_time_s() - vrs_time_bindall > 120)){
		if((flag_check_mess == FALSE) || (flag_process_aes == FALSE)){
//			uart_CSend("co bindall ko nhan ban tin ma hoa, qua 2p\n");
			flag_process_security = FALSE;
			kick_out(0);
		}
		else{
			flag_process_security = FALSE;
		}
	}

	if((flag_process_security == TRUE) && (clock_time_s() - vrs_time_error_aes > 10)){
		if((flag_check_mess == TRUE) && (flag_process_aes == FALSE)){
//			uart_CSend("co bindall nhan ma hoa sai key\n");
			flag_process_security = FALSE;
			kick_out(0);
		}
	}
#endif
}

//RD_EDIT: SEC : FUNCTION AES
unsigned char rdAesreCheck(unsigned short unicast,unsigned char *dataIn){
	unsigned char compareBuff[16] = {0x24, 0x02, 0x28, 0x04, 0x28, 0x11, 0x20, 0x20, 0, 0, 0, 0, 0, 0, 0, 0};
	for(unsigned char i=0; i<6; i++){
		compareBuff[8+i] = tbl_mac[i];
	}
	compareBuff[14] = unicast;
	compareBuff[15] = unicast>>8;
	aes_encrypt(rangDongKey,compareBuff,aesEncrypt);

	for(unsigned char i=0;i< 6;i++){
		if(aesEncrypt[10+i] != dataIn[i]){
			return 0;
		}
	}
	return 1;
}

//RD_EDIT: 1..: SAVE GATEWAY
unsigned short saveGatewayAddr(unsigned char *param,unsigned short srcAddr){
	unsigned short gw_add = 0x0001;
	if(param[0] || param[1]){
		gw_add = ((param[1] << 8) | (param[0]));
	}
	else {
		gw_add = srcAddr;
	}
	return gw_add;
}

void checkDoneProvision(void){		//RD_EDIT: 0.THANH : SPM: checkDoneProvision
	static u8 first = 0;

	if((get_provision_state() == STATE_DEV_PROVED) && (flag_process_aes == FALSE) && (flag_process_security == FALSE) && (flag_check_mess == FALSE) && (first == 0))
	{
		vrs_time_bindall = clock_time_s();
		flag_process_security = TRUE;
		flag_check_mess		= FALSE;
		flag_process_aes  = FALSE;
		first = 1;

		RD_Flash_SaveSecurity(flag_process_aes, flag_process_security, flag_check_mess);		//RD_EDIT: 1.THANH SEC
	//	uart_CSend("bat dau tinh gio \n");
	    RD_GATEWAYADDRESS = 0x0001;
	    RD_light_ev_with_sleep(3, 500 * 1000);
	    sleep_ms(100);
	    st_pub_list_t pub_list = {{0}};
	    mesh_cmd_light_ctl_set_t p_set ;
	    mesh_cmd_lightness_set_t p_set_light;
	    p_set.temp = 0x0320;
	    p_set.lightness = 0xffff;
		p_set_light.lightness = 0xffff;
	    light_ctl_temp_set(&p_set, 2, 0, 0, 0, &pub_list);
		lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
	}
}
