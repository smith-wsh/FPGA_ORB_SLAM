#include "image_orb.h"

void image_sobel(AXI_STREAM & inStream,AXI_STREAM & outStream, char matrix[3*3])
{
	#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
	#pragma HLS INTERFACE s_axilite port=matrix bundle=MATRIX_BUS
	#pragma HLS INTERFACE axis register both port=outStream
	#pragma HLS INTERFACE axis register both port=inStream

	BUFFER lineBuf;
	SHORT_WINDOW window;
	int pixConvolved = 0;

	int waitPixel = IMG_WIDTH + 1;
	int cntWait = 0;
	int sentPixel = 0;
	unsigned int pix,pix_raw;//灰度像素变量

	uint_side_channel dataOutChannel;
	uint_side_channel currentChannel;

	//输入像素值取RGB三个分量
	unsigned int B = 0xFF;
	unsigned int G = (0xFF << 8);
	unsigned int R = (0xFF << 16);
	pix = R;//RGB数据计算灰度分量，YCBCR颜色空间的Y分量

	unsigned int val;
	for(int i = 0; i < MATRIX_DIM-1; i++ )
	{
		for(int j = 0; j < IMG_WIDTH; j++)
		{
			#pragma HLS PIPELINE//流水操作，提高效率
			currentChannel = inStream.read();
			pix_raw = currentChannel.data;
			lineBuf.shift_pixels_up(j);
			lineBuf.insert_bottom_row(pix_raw,j);
			if(i <= 2)
			{
				dataOutChannel.data = currentChannel.data;
				dataOutChannel.dest = currentChannel.dest;
				dataOutChannel.id = currentChannel.id;
				dataOutChannel.keep = currentChannel.keep;
				dataOutChannel.strb = currentChannel.strb;
				dataOutChannel.user = currentChannel.user;
				dataOutChannel.last = currentChannel.last;
				outStream.write(dataOutChannel);
				sentPixel++;
			}
		}
	}
	for(int i = MATRIX_DIM-1; i < IMG_HEIGHT; i++ )
	{
		for(int j = 0; j < IMG_WIDTH; j++)
		{
			#pragma HLS PIPELINE//流水操作，提高效率
			currentChannel = inStream.read();

			pix_raw = currentChannel.data;


			lineBuf.shift_pixels_up(j);
			lineBuf.insert_bottom_row(pix_raw,j);

			//put data on the window, and multiply by kernel
			//3x3矩阵运算
			for(int idxWinRow = 0; idxWinRow < MATRIX_DIM; idxWinRow++)
			{
				for(int idxWinCol=0; idxWinCol < MATRIX_DIM; idxWinCol++)
				{
					//#pragma HLS PIPELINE
					//计算矩阵的结果
					val = (unsigned int)lineBuf.getval(idxWinRow, idxWinCol + pixConvolved);
					//val = (short)matrix[(idxWinRow * MATRIX_DIM) + idxWinCol] * val;
					window.insert(val,idxWinRow,idxWinCol);
					if(idxWinRow==3 && idxWinCol==3)
						pix_raw = val;
				}
			}

			//short valOut;
			short flag=0;
			//满足矩阵计算结果打包成数据流输出
			if((i >= MATRIX_DIM-1) && (j >= MATRIX_DIM -1))
			{
				flag = computerWindow(&window,matrix[0]+matrix[1]);
				if(!flag)
					//valOut = pix_raw;
				    dataOutChannel.data = pix_raw;
				else
					dataOutChannel.data = pix;
					//valOut = pix;
					//dataOutChannel.data = (pix >> 16) | (pix >> 8) | pix;
				pixConvolved++;
				//dataOutChannel.data = (valOut << 16) | (valOut << 8) | valOut;
				dataOutChannel.dest = currentChannel.dest;
				dataOutChannel.id = currentChannel.id;
				dataOutChannel.keep = currentChannel.keep;
				dataOutChannel.strb = currentChannel.strb;
				dataOutChannel.user = currentChannel.user;
				dataOutChannel.last = currentChannel.last;
				outStream.write(dataOutChannel);
				sentPixel++;
			}
			else
				if(j <= 2)
				{
					dataOutChannel.data = window.getval(3, 0);
					dataOutChannel.dest = currentChannel.dest;
					dataOutChannel.id = currentChannel.id;
					dataOutChannel.keep = currentChannel.keep;
					dataOutChannel.strb = currentChannel.strb;
					dataOutChannel.user = currentChannel.user;
					dataOutChannel.last = currentChannel.last;
					outStream.write(dataOutChannel);
					sentPixel++;
				}
		}
		pixConvolved = 0;
		for(int k=1;k<4;k++)
		{
			#pragma HLS PIPELINE
			dataOutChannel.data = window.getval(3, 3+k);
			dataOutChannel.dest = currentChannel.dest;
			dataOutChannel.id = currentChannel.id;
			dataOutChannel.keep = currentChannel.keep;
			dataOutChannel.strb = currentChannel.strb;
			dataOutChannel.user = currentChannel.user;
			dataOutChannel.last = currentChannel.last;
			outStream.write(dataOutChannel);
			sentPixel++;
		}
	}
}
//求卷积和
short computerWindow(SHORT_WINDOW *window, int threshold_data){
	short sum=0;

	short num=0;
	short maxnum=0;
	bool flag=0;

	int threshold = threshold_data;
	int offset_row[16] = { -3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3 };//对应height
	int offset_col[16] = { 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3, -3, -3, -2, -1 };

	unsigned int center = (unsigned int)window->getval(3, 3);
	unsigned int neighbor;
	unsigned char R = center & 0xFF;
	unsigned char G = (center >> 8) & 0xFF;
	unsigned char B = (center >> 16) & 0xFF;

	short p1 = (R*305 + G*599 + B*120) >> 8;
	//short p1 = (R*76 + G*150 + B*30) >> 8;
	short p2,p3,p4,p5;

	//1
	neighbor = (unsigned int)window->getval(3+offset_row[8], 3+offset_col[8]);
	R = neighbor & 0xFF;
	G = (neighbor >> 8) & 0xFF;
	B = (neighbor >> 16) & 0xFF;
	p2 = (R*305 + G*599 + B*120) >> 8;
	//p2 = (R*76 + G*150 + B*30) >> 8;
	neighbor = (unsigned int)window->getval(3+offset_row[0], 3+offset_col[0]);
	R = neighbor & 0xFF;
	G = (neighbor >> 8) & 0xFF;
	B = (neighbor >> 16) & 0xFF;
	p3 = (R*305 + G*599 + B*120) >> 8;
	//p3 = (R*76 + G*150 + B*30) >> 8;
	if(abs(p2-p3)<=threshold)
		return sum;

	//2
	neighbor = (unsigned int)window->getval(3+offset_row[4], 3+offset_col[4]);
	R = neighbor & 0xFF;
	G = (neighbor >> 8) & 0xFF;
	B = (neighbor >> 16) & 0xFF;
	p4 = (R*305 + G*599 + B*120) >> 8;
	//p4 = (R*76 + G*150 + B*30) >> 8;
	neighbor = (unsigned int)window->getval(3+offset_row[12], 3+offset_col[12]);
	R = neighbor & 0xFF;
	G = (neighbor >> 8) & 0xFF;
	B = (neighbor >> 16) & 0xFF;
	p5 = (R*305 + G*599 + B*120) >> 8;
	//p5 = (R*76 + G*150 + B*30) >> 8;
	int k=0;
	if(abs(p1-p2)<=threshold)
		k++;
	if(abs(p1-p3)<=threshold)
		k++;
	if(abs(p1-p4)<=threshold)
		k++;
	if(abs(p1-p5)<=threshold)
		k++;
	if(k>1)
		return sum;


	for(int k=0;k<16;k++)
	{
		#pragma HLS PIPELINE
		//3
		neighbor = (unsigned int)window->getval(3+offset_row[k], 3+offset_col[k]);
		R = neighbor & 0xFF;
		G = (neighbor >> 8) & 0xFF;
		B = (neighbor >> 16) & 0xFF;
		p2 = (R*305 + G*599 + B*120) >> 8;
		//p2 = (R*76 + G*150 + B*30) >> 8;
		if(abs(p2-p1)>threshold)
		{
			flag=1;
			num+=1;
		}
		else
		{
			if(flag)
				maxnum=(maxnum>num)?maxnum:num;
			flag=0;
			num=0;
		}

	}
	maxnum=(maxnum>num)?maxnum:num;
	if(maxnum>8)
	{
		sum = 1;
	}

	//for(int idxRow = 0; idxRow < MATRIX_DIM; idxRow++)
	//	for(int idxCol = 0;idxCol < MATRIX_DIM;idxCol++)
	//		sum += (short)window->getval(idxRow, idxCol);

	return sum;
}


