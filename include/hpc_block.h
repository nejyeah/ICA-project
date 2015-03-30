#ifndef STL10_H
#define STL10_H

#include<iostream>
#include<vector>
using namespace std;

class hpc_block{
public:
    void free();
    void malloc();
    void loaddata(string filename,int minibatch_index);
    hpc_block(int picture_Number,int nrow_pixel,int ncol_pixel,int Input_channel,int hidden_channel,int stepSize,int filter_row,int filter_col,int hidden_block_row,int hidden_block_col,int process_id,int pSize,int minibatch);

    //the three channel images are stored in one vector ,order by R G B ,each image is col major
    //as is to say ,the first image pixels is R channel and col major
    float *pixelD;//change the pixels value to 0~1 and store
    float *rpixelD;
    float *pixel_block;
    float *rpixel_block;
    float *h;
	float *w;
    int *pixelI;//store the original pixels value 0~255
    int picture_number; //the total number of pictures
    int nrow_pixel,ncol_pixel; //pictures is nrow_pixel*ncol_pixel
    int filter_row;
	int filter_col;
    int input_channel; //colorful picture,with red,green,blue
    int hidden_channel;
    int stepsize;
	int hidden_block_row;
	int hidden_block_col;
	int blocksNumber;
	int blocksNumberOfPerProcess;
    int process_id;
    int pSize;
    int minibatch;
};
#endif

