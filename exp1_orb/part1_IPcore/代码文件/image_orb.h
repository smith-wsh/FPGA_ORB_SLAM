#ifndef __TEST_HEAD_H__
#define __TEST_HEAD_H__

#include <hls_video.h>
#include <ap_axi_sdata.h>


#define MATRIX_DIM 7
#define IMG_WIDTH 1024
#define IMG_HEIGHT 768
//#define IMG_WIDTH 1366
//#define IMG_HEIGHT 768
#define INPUT_IMAGE "image.bmp"
#define OUTPUT_IMAGE "outimage.bmp"


//定义数据流中的数据
typedef ap_axiu<24,1,1,1> 	uint_side_channel;
typedef ap_axis<24,1,1,1> 	int_side_channel;
//定义AXI—Stream数据流
typedef hls::stream<uint_side_channel> 							AXI_STREAM;
//定义char类型的卷积窗口
typedef hls::Window<MATRIX_DIM,MATRIX_DIM,char> 				CHAR_WINDOW;
//定义short类型的卷积窗口
typedef hls::Window<MATRIX_DIM,MATRIX_DIM,unsigned int> 		SHORT_WINDOW;
//定义LineBuffer用于延时
typedef hls::LineBuffer<MATRIX_DIM,IMG_WIDTH,unsigned int> 	BUFFER;

//short convolved2d(CHAR_WINDOW * window,char kernel[MATRIX_DIM * MATRIX_DIM]);//参考函数

short computerWindow(SHORT_WINDOW *window, int matrix);//求卷积和
//顶层函数
void image_sobel(AXI_STREAM & inStream,AXI_STREAM & outStream, char matrix[3*3]);

#endif
