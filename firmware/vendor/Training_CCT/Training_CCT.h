/*
 * Training_CCT.h
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#ifndef TRAINING_CCT_H_
#define TRAINING_CCT_H_
#include "vendor/common/light.h"
#include "vendor/common/lighting_model.h"
#include "vendor/RD_Mess_Data/RD_Mess_Data.h"
#include "vendor/RD_Type_Device/RD_Type_Device.h"
#include "vendor/common/fast_provision_model.h"

extern unsigned char step;
extern unsigned char cnt_cycle;
extern unsigned char Flag_Factory_Mode;

#define ENABLE_TRAINING_1		0	//RD_EDIT: ENA OR DIS TRAINING

void Time_kickout();
void Process_Test2();
void Process_1();
void Process_2();
void Process_3();
void Process_4();
void Process_5();
void Process_6();
void Training_Run();
void Init_Training_1();
#endif /* TRAINING_CCT_H_ */
