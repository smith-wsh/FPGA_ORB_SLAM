// ==============================================================
// File generated on Wed Jan 23 19:40:24 +0800 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XIMAGE_ORB_H
#define XIMAGE_ORB_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "ximage_orb_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Ctrl_bus_BaseAddress;
    u32 Matrix_bus_BaseAddress;
} XImage_orb_Config;
#endif

typedef struct {
    u32 Ctrl_bus_BaseAddress;
    u32 Matrix_bus_BaseAddress;
    u32 IsReady;
} XImage_orb;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XImage_orb_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XImage_orb_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XImage_orb_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XImage_orb_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XImage_orb_Initialize(XImage_orb *InstancePtr, u16 DeviceId);
XImage_orb_Config* XImage_orb_LookupConfig(u16 DeviceId);
int XImage_orb_CfgInitialize(XImage_orb *InstancePtr, XImage_orb_Config *ConfigPtr);
#else
int XImage_orb_Initialize(XImage_orb *InstancePtr, const char* InstanceName);
int XImage_orb_Release(XImage_orb *InstancePtr);
#endif

void XImage_orb_Start(XImage_orb *InstancePtr);
u32 XImage_orb_IsDone(XImage_orb *InstancePtr);
u32 XImage_orb_IsIdle(XImage_orb *InstancePtr);
u32 XImage_orb_IsReady(XImage_orb *InstancePtr);
void XImage_orb_EnableAutoRestart(XImage_orb *InstancePtr);
void XImage_orb_DisableAutoRestart(XImage_orb *InstancePtr);

u32 XImage_orb_Get_matrix_BaseAddress(XImage_orb *InstancePtr);
u32 XImage_orb_Get_matrix_HighAddress(XImage_orb *InstancePtr);
u32 XImage_orb_Get_matrix_TotalBytes(XImage_orb *InstancePtr);
u32 XImage_orb_Get_matrix_BitWidth(XImage_orb *InstancePtr);
u32 XImage_orb_Get_matrix_Depth(XImage_orb *InstancePtr);
u32 XImage_orb_Write_matrix_Words(XImage_orb *InstancePtr, int offset, int *data, int length);
u32 XImage_orb_Read_matrix_Words(XImage_orb *InstancePtr, int offset, int *data, int length);
u32 XImage_orb_Write_matrix_Bytes(XImage_orb *InstancePtr, int offset, char *data, int length);
u32 XImage_orb_Read_matrix_Bytes(XImage_orb *InstancePtr, int offset, char *data, int length);

void XImage_orb_InterruptGlobalEnable(XImage_orb *InstancePtr);
void XImage_orb_InterruptGlobalDisable(XImage_orb *InstancePtr);
void XImage_orb_InterruptEnable(XImage_orb *InstancePtr, u32 Mask);
void XImage_orb_InterruptDisable(XImage_orb *InstancePtr, u32 Mask);
void XImage_orb_InterruptClear(XImage_orb *InstancePtr, u32 Mask);
u32 XImage_orb_InterruptGetEnabled(XImage_orb *InstancePtr);
u32 XImage_orb_InterruptGetStatus(XImage_orb *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
