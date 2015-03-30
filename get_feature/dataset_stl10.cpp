#include"../include/dataset_stl10.h"
#include<fstream>

dataset_stl10::dataset_stl10(){
    pixelD=NULL;
    pixelI=NULL;
    picture_number=5000;
    nrow_pixel=96;
    ncol_pixel=96;
    channel=3;

}

void dataset_stl10::malloc(){
    pixelD=new double[picture_number*channel*nrow_pixel*ncol_pixel];
    pixelI=new int[picture_number*channel*nrow_pixel*ncol_pixel];
}

void dataset_stl10::free(){
    delete[] pixelD;
    delete[] pixelI;
}

void dataset_stl10::loaddata(string filename){
    malloc();
    //unsigned char unsignedbuffer;
    //int pixel_flag=0;
    //col-major order
    ifstream fp(filename.c_str(),ios::in|ios::binary|ios::ate);
    /*
    for(int j=0;j<picture_number;j++){
        unsigned char a;
        for(int n=0;n<nrow_pixel*ncol_pixel*channel;n++){
            fp>>a;
            //cout<<(int)a<<endl;
            pixelI[pixel_flag]=a;
            pixelD[pixel_flag]=a/255.0;
            pixel_flag++;
        }
    }
    */
    long size;
    size=fp.tellg();
    cout<<"size:"<<size<<endl;
    fp.seekg(0,ios::beg);
    char* buffer;
    buffer=new char[size];
    fp.read(buffer,size);
    fp.close();

    for(int j=0;j<picture_number*nrow_pixel*ncol_pixel*channel;j++){
        unsigned char a=buffer[j];
        pixelI[j]=a;
        pixelD[j]=a/255.0;
    }
    delete[] buffer;
    cout<<filename<<" has loaded!"<<endl;
}

