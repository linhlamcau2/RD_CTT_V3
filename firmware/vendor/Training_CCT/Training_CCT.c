/*
 * Training_CCT.c
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#include"Training_CCT.h"

unsigned long TimeNew, TimeOld;
unsigned char cnt_cycle = 0;
unsigned char step = 0;
unsigned char Flag_Factory_Mode = 1;
int vrs_count = 0;
int vrs_cycle = 0;

void Time_kickout() {
	TimeNew = clock_time();

	if(TimeNew > 0xfffffff0){
		TimeNew = 0;
		TimeOld = 0;
	}

	if (TimeNew - TimeOld > 1600000) {
		TimeOld = TimeNew;
		vrs_count++;
		if (vrs_count > 600) {
			vrs_count = 0;
			kick_out(1);
			flag_kickout = 0;
		}
	}
}

void set_CCT(u16 val_lightness, u16 val_temp) {
	st_pub_list_t pub_list = { { 0 } };
	mesh_cmd_light_ctl_set_t p_set;
	mesh_cmd_lightness_set_t p_set_light;
	p_set_light.lightness = val_lightness;
	lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
	p_set.temp = val_temp;
	light_ctl_temp_set(&p_set, 7, 0, 0, 0, &pub_list);
}

void Process_Test2() {
	TimeNew = clock_time();

	if(TimeNew > 0xfffffff0){
		TimeNew = 0;
		TimeOld = 0;
	}

	if (TimeNew - TimeOld > 160000) {
		TimeOld = TimeNew;
		vrs_count++;

		if (vrs_count == 100) {
			set_CCT(0xffff, 0x4e20);
		}

		if (vrs_count == 200) {
			set_CCT(0xffff, 0x0320);
		}

		if (vrs_count == 300) {
			set_CCT(0x2828, 0x4e20);
		}

		if (vrs_count == 400) {
			set_CCT(0x2828, 0x0320);
		}

		if (vrs_count == 500) {			//RD_EDIT: 1. THANH : v.2.1 : TEST 2 ONOFF
			set_CCT(0x0000, 0x0320);
		}

		if (vrs_count > 600) {			//RD_EDIT: 1. THANH : v.2.1 : TEST 2 ONOFF	// cu:400
			vrs_count = 0;
		}
	}
}

void Process_1() {
	TimeNew = clock_time();

	if(TimeNew > 0xfffffff0){
		TimeNew = 0;
		TimeOld = 0;
	}

	if (TimeNew - TimeOld > 160000) {
		TimeOld = TimeNew;
		vrs_count++;
		if (vrs_count == 100) {
			set_CCT(0xffff, 0x4e20);
		}
		if (vrs_count == 200) {
			set_CCT(0xffff, 0x0320);
		}
		if (vrs_count == 300) {
			set_CCT(0x2828, 0x4e20);
		}
		if (vrs_count == 400) {
			set_CCT(0x2828, 0x0320);
		}
		if (vrs_count > 400) {
			vrs_count = 0;
			vrs_cycle++;
			if (vrs_cycle > 12) //=13
			{
				vrs_cycle = 0;
				cnt_cycle++;
				step = 0;
				RD_Flash_SaveTraining(step, cnt_cycle);
			}
		}
	}
	if (cnt_cycle > 9) //>4
	{
		step = 1;
		cnt_cycle = 0;
		RD_Flash_SaveTraining(step, cnt_cycle);
		set_CCT(0xffff, 0x4e20);
		vrs_count = 0;
		vrs_cycle = 0;
	}
}

void Process_2() {
	TimeNew = clock_time();

	if(TimeNew > 0xfffffff0){
		TimeNew = 0;
		TimeOld = 0;
	}

	if (TimeNew - TimeOld > 160000) {
		TimeOld = TimeNew;
		vrs_count++;
		if (vrs_count > 500) {
			vrs_count = 0;
			vrs_cycle++;
			if (vrs_cycle > 11) //>11
			{
				vrs_cycle = 0;
				cnt_cycle++;
				step = 1;
				RD_Flash_SaveTraining(step, cnt_cycle);
				if (cnt_cycle < 15) //<10
				{
					set_CCT(0xffff, 0x4e20);
				} else { //=10
					step = 2;
					cnt_cycle = 0;
					RD_Flash_SaveTraining(step, cnt_cycle);
					set_CCT(0xffff, 0x0320);
					vrs_count = 0;
					vrs_cycle = 0;
				}
			}
		}
	}
}

void Process_3() {
	TimeNew = clock_time();

	if(TimeNew > 0xfffffff0){
		TimeNew = 0;
		TimeOld = 0;
	}

	if (TimeNew - TimeOld > 160000) {
		TimeOld = TimeNew;
		vrs_count++;
		if (vrs_count > 500) {
			vrs_count = 0;
			vrs_cycle++;
			if (vrs_cycle > 11) //>11
			{
				vrs_cycle = 0;
				cnt_cycle++;
				step = 2;
				RD_Flash_SaveTraining(step, cnt_cycle);
				if (cnt_cycle < 15) //<10
				{
					set_CCT(0xffff, 0x0320);
				} else { //=10
					step = 3;
					cnt_cycle = 0;
					RD_Flash_SaveTraining(step, cnt_cycle);
					set_CCT(0xffff, 0x2710);
					vrs_count = 0;
					vrs_cycle = 0;
				}
			}
		}
	}
}

void Process_4() {
	TimeNew = clock_time();

	if(TimeNew > 0xfffffff0){
		TimeNew = 0;
		TimeOld = 0;
	}

	if (TimeNew - TimeOld > 160000) {
		TimeOld = TimeNew;
		vrs_count++;
		if (vrs_count > 500) {
			vrs_count = 0;
			vrs_cycle++;
			if (vrs_cycle > 11) //>11
			{
				vrs_cycle = 0;
				cnt_cycle++;
				step = 3;
				RD_Flash_SaveTraining(step, cnt_cycle);
				if (cnt_cycle < 15) //<5
				{
					set_CCT(0xffff, 0x2710);
				} else { //=5
					step = 4;
					cnt_cycle = 0;
					RD_Flash_SaveTraining(step, cnt_cycle);
					set_CCT(0x2828, 0x2710);
					vrs_count = 0;
					vrs_cycle = 0;
				}
			}
		}
	}
}

void Process_5() {
	step = 4;
//	set_CCT(0x2828, 0x2710);
}

void Process_6() {
	TimeNew = clock_time();

	if(TimeNew > 0xfffffff0){
		TimeNew = 0;
		TimeOld = 0;
	}

	if (TimeNew - TimeOld > 160000) {
		TimeOld = TimeNew;
		vrs_count++;
		if (vrs_count < 400) {
			set_CCT(0xffff, 0x4e20);
		} else {
			step 	  = Flash_Save_Training_Val.step;
			cnt_cycle = Flash_Save_Training_Val.cnt_cycle;

			if (step == 0 || step == 1) {
				set_CCT(0xffff, 0x4e20);
				vrs_count = 0;
			}
			if (step == 2) {
				set_CCT(0xffff, 0x0320);
				vrs_count = 0;
			}
			if (step == 3) {
				set_CCT(0xffff, 0x2710);
				vrs_count = 0;
			}
		}
	}
}

void Init_Training_1() {
	step 	   = Flash_Save_Training_Val.step;
	cnt_cycle  = Flash_Save_Training_Val.cnt_cycle;

	if (get_provision_state() == STATE_DEV_PROVED) {
		if (step != 6) {
			Flag_Factory_Mode = 1;
			step = 6;
			cnt_cycle = 6;
			RD_Flash_SaveTraining(step, cnt_cycle);
		}
	} else if ((get_provision_state() == STATE_DEV_UNPROV) && (step < 6)) {
		gatt_adv_send_flag = 0;
		beacon_send.en = 0;
		Flag_Factory_Mode = 0;
	}

	else if((get_provision_state() == STATE_DEV_UNPROV) && (step > 5)){
		Flag_Factory_Mode = 1;
	}

	if (step == 0 || step == 1 || step == 2 || step == 3) {
		step = 5;
	}

	if (step == 4) {
		Flag_Factory_Mode = 1;
		gatt_adv_send_flag = 1;
		beacon_send.en = 1;
		step = 6;
		cnt_cycle = 6;
		RD_Flash_SaveTraining(step, cnt_cycle);
		st_pub_list_t pub_list = { { 0 } };
		mesh_cmd_light_ctl_set_t p_set;
		mesh_cmd_lightness_set_t p_set_light;
		p_set_light.lightness = 0xffff;
		lightness_set(&p_set_light, 3, 0, 0, 0, &pub_list);
		p_set.temp = 0x4e20;
		light_ctl_temp_set(&p_set, 7, 0, 0, 0, &pub_list);
		sleep_ms(10);
		factory_reset();
		start_reboot();
	}
}
// DuanLC: Edit
void Training_Run (void){
	if (step < 6){
		switch (step) {
			case 0:
				Process_1();
				break;
			case 1:
				Process_2();
				break;
			case 2:
				Process_3();
				break;
			case 3:
				Process_4();
				break;
			case 4:
				Process_5();
				break;
			case 5:
				Process_6();
				break;
			default:
				break;
		}
	}
	else if((flag_training_test2 == 1) && (step == 6)){
		Process_Test2();
	 }
}

