#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "vdma_api/vdma_api.h"
#include "ximage_sobel.h"
#include "xparameters.h"
#include "xil_cache.h"

#define DISPLAY_VDMA_DEV_ID 	XPAR_AXI_VDMA_1_DEVICE_ID
#define HLS_VDMA_DEV_ID 		XPAR_AXI_VDMA_0_DEVICE_ID
#define SOBEL_DEV_ID 			XPAR_IMAGE_SOBEL_0_DEVICE_ID
#define DISP_BASE_ADDR 			0x08000000
#define HLS_BASE_ADDR			0x03000000
#define SCREEN_X				1024
#define SCREEN_Y				768

static XAxiVdma					Vdma;
static XImage_sobel 				sobel	;
static XImage_sobel_Config 		*sobel_Cfg;

//no process
char no_process_dim[9] =
{
		0, 0, 0,
		0, 1, 0,
		0, 0, 0,
};
//sobel
char sobel_dim[9] =
{
		25, 25, -1,
		 0,  0,  0,
		 1,  2,  1,
};
//edge1
char edge_detect_dim1[9] =
{
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1,
};

int init_sobel()
{
	int status;
	sobel_Cfg = XImage_sobel_LookupConfig(SOBEL_DEV_ID);
	status = XImage_sobel_CfgInitialize(&sobel,sobel_Cfg);
	if(status != XST_SUCCESS)
	{
		printf("initialize erro! \n");
		return status;
	}

	return status;
}

int main()
{
	int status;
    //初始化VDMA
	run_vdma_frame_buffer(&Vdma, HLS_VDMA_DEV_ID, SCREEN_X, SCREEN_Y,HLS_BASE_ADDR,0, 0,BOTH);
	run_vdma_frame_buffer(&Vdma, DISPLAY_VDMA_DEV_ID, SCREEN_X, SCREEN_Y,DISP_BASE_ADDR,0, 0,BOTH);
	status = init_sobel();
	if(status != XST_SUCCESS)
	{
		printf("initialize failed! \n");
		return status;
	}
	//设置卷积运算算子
	XImage_sobel_Write_matrix_Bytes(&sobel,0,sobel_dim,9);
	while(1)
	{
		XImage_sobel_Start(&sobel);
		while(!XImage_sobel_IsDone(&sobel));
	}
    return 0;
}
