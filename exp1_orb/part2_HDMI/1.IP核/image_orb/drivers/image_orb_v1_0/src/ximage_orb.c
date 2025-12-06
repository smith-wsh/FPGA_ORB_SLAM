// ==============================================================
// File generated on Wed Jan 23 19:40:24 +0800 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "ximage_orb.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XImage_orb_CfgInitialize(XImage_orb *InstancePtr, XImage_orb_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_bus_BaseAddress = ConfigPtr->Ctrl_bus_BaseAddress;
    InstancePtr->Matrix_bus_BaseAddress = ConfigPtr->Matrix_bus_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XImage_orb_Start(XImage_orb *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImage_orb_ReadReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_AP_CTRL) & 0x80;
    XImage_orb_WriteReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_AP_CTRL, Data | 0x01);
}

u32 XImage_orb_IsDone(XImage_orb *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImage_orb_ReadReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XImage_orb_IsIdle(XImage_orb *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImage_orb_ReadReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XImage_orb_IsReady(XImage_orb *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImage_orb_ReadReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XImage_orb_EnableAutoRestart(XImage_orb *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImage_orb_WriteReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_AP_CTRL, 0x80);
}

void XImage_orb_DisableAutoRestart(XImage_orb *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImage_orb_WriteReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_AP_CTRL, 0);
}

u32 XImage_orb_Get_matrix_BaseAddress(XImage_orb *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Matrix_bus_BaseAddress + XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE);
}

u32 XImage_orb_Get_matrix_HighAddress(XImage_orb *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Matrix_bus_BaseAddress + XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_HIGH);
}

u32 XImage_orb_Get_matrix_TotalBytes(XImage_orb *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_HIGH - XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE + 1);
}

u32 XImage_orb_Get_matrix_BitWidth(XImage_orb *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIMAGE_ORB_MATRIX_BUS_WIDTH_MATRIX;
}

u32 XImage_orb_Get_matrix_Depth(XImage_orb *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIMAGE_ORB_MATRIX_BUS_DEPTH_MATRIX;
}

u32 XImage_orb_Write_matrix_Words(XImage_orb *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_HIGH - XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Matrix_bus_BaseAddress + XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XImage_orb_Read_matrix_Words(XImage_orb *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_HIGH - XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Matrix_bus_BaseAddress + XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE + (offset + i)*4);
    }
    return length;
}

u32 XImage_orb_Write_matrix_Bytes(XImage_orb *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_HIGH - XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Matrix_bus_BaseAddress + XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XImage_orb_Read_matrix_Bytes(XImage_orb *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_HIGH - XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Matrix_bus_BaseAddress + XIMAGE_ORB_MATRIX_BUS_ADDR_MATRIX_BASE + offset + i);
    }
    return length;
}

void XImage_orb_InterruptGlobalEnable(XImage_orb *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImage_orb_WriteReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_GIE, 1);
}

void XImage_orb_InterruptGlobalDisable(XImage_orb *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImage_orb_WriteReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_GIE, 0);
}

void XImage_orb_InterruptEnable(XImage_orb *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XImage_orb_ReadReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_IER);
    XImage_orb_WriteReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_IER, Register | Mask);
}

void XImage_orb_InterruptDisable(XImage_orb *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XImage_orb_ReadReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_IER);
    XImage_orb_WriteReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_IER, Register & (~Mask));
}

void XImage_orb_InterruptClear(XImage_orb *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImage_orb_WriteReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_ISR, Mask);
}

u32 XImage_orb_InterruptGetEnabled(XImage_orb *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XImage_orb_ReadReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_IER);
}

u32 XImage_orb_InterruptGetStatus(XImage_orb *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XImage_orb_ReadReg(InstancePtr->Ctrl_bus_BaseAddress, XIMAGE_ORB_CTRL_BUS_ADDR_ISR);
}

