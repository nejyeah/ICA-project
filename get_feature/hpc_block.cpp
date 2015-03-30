#include"../include/hpc_block.h"
#include<fstream>

hpc_block::hpc_block(int picture_Number,int nrow_pixel,int ncol_pixel,int Input_channel,int hidden_channel,int stepSize,int filter_row,int filter_col,int hidden_block_row,int hidden_block_col,int process_id,int pSize,int minibatch){
    picture_number=picture_Number;
    nrow_pixel=nrow_pixel;
    ncol_pixel=ncol_pixel;
    input_channel=Input_channel;
    hidden_channel=hidden_channel;
    stepsize=stepSize;
    filter_row=filter_row;
	filter_col=filter_col;
    hidden_block_row=hidden_block_row;
	hidden_block_col=hidden_block_col;
	process_id=process_id;
	pSize=pSize;
	blocksNumber=((nrow_pixel-filter_row)/stepSize+1)*((ncol_pixel-filter_col)/stepSize+1);
	blocksNumberOfPerProcess=blocksNumber/pSize;
    minibatch=minibatch;
}

void hpc_block::malloc(){
    pixel_block=new float[minibatch*input_channel*filter_row*filter_col];
    rpixel_block=new float[minibatch*input_channel*filter_row*filter_col];
    //pixelI=new int[picture_number*input_channel*nrow_pixel*ncol_pixel];
    pixelI=NULL;
    pixelD=NULL;
    rpixelD=NULL;
	w=new float[blocksNumberOfPerProcess*filter_row*filter_col*input_channel*hidden_block_row*hidden_block_col*hidden_channel];
	h=new float[blocksNumberOfPerProcess*hidden_block_row*hidden_block_col*hidden_channel];
	
}

void hpc_block::free(){
    delete[] pixelD;
    delete[] pixelI;
    delete[] rpixelD;
    delete[] w;
    delete[] h;
    delete[] pixel_block;
    delete[] rpixel_block;
}

void hpc_block::loaddata(string filename,int minibatch_index){
    pixelD=new float[minibatch*input_channel*nrow_pixel*ncol_pixel];
    
    ifstream fp(filename.c_str(),ios::in|ios::binary);
    long size=minibatch*nrow_pixel*ncol_pixel*input_channel;
    char* buffer;
    buffer=new char[size];
    fp.seekg(minibatch_index*size,ios::beg);
    fp.read(buffer,size);
    fp.close();

    for(int j=0;j<size;j++){
        unsigned char a=buffer[j];
        //pixelI[j]=a;
        pixelD[j]=a/255.0;
    }
    delete[] buffer;
    //cout<<"process "<<process_id<<":"<<filename<<" has loaded!"<<endl;
}

