// ==============================================================
// File generated on Wed Jan 23 19:40:24 +0800 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "ximage_orb.h"

extern XImage_orb_Config XImage_orb_ConfigTable[];

XImage_orb_Config *XImage_orb_LookupConfig(u16 DeviceId) {
	XImage_orb_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XIMAGE_ORB_NUM_INSTANCES; Index++) {
		if (XImage_orb_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XImage_orb_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XImage_orb_Initialize(XImage_orb *InstancePtr, u16 DeviceId) {
	XImage_orb_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XImage_orb_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XImage_orb_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

