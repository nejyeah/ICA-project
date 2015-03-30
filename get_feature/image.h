#ifndef IMAGE
#define IMAGE
#include"image.h"
#include<iostream>
#include<fstream>
#include<string>
#include"opencv/cv.h"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
extern "C"{
#include"cblas.h"
}
using namespace cv;
using namespace std;

void sort2(float* w1,float* sort_w1,int index,int filter,int row,int input_channel,int hidden_channel,int hidden_block,int block1);
void storeImage2(float* out,int index,int relate_size,int input_channel,int hidden_block,string path,int picture_row,int picture_col);
void storeImage(float *Weight,int input,int input_channel,int filter,int hidden_block,string outpath,int picture_row,int picture_col);
void storeImage_onemap(float *Weight,int block_row,int input_channel,int filter,int hidden_block,int hidden_channel,string outpath);
void change_size(float *Weight,float *Weight_full,int block_row,int input_channel,int filter,int hidden_block,int hidden_channel,int input_row);
void normalization(float* w,int filter,int input_channel,int size_w);
void loadlayer3();
void loadlayer2();
void loadlayer1();


void storeImage_onemap1(float *Weight,int input_channel,int input_row,int input_col,int picture_row,int picture_col,int hidden_channel,string outpath);
#endif
