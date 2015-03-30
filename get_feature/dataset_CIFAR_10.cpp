#include"../include/dataset_CIFAR_10.h"
#include<fstream>

dataset_CIFAR_10::dataset_CIFAR_10(){
    pixelD=NULL;
    pixelI=NULL;
    picture_number=0;
    nrow_pixel=32;
    ncol_pixel=32;
    channel=3;
    pictureNumberOfOneDataset=10000;
}

void dataset_CIFAR_10::malloc(int dataFileNumber){
    pixelD=new double[picture_number*channel*nrow_pixel*ncol_pixel];
    pixelI=new int[picture_number*channel*nrow_pixel*ncol_pixel];
    label=new int[picture_number];
}

void dataset_CIFAR_10::free(){
    delete[] pixelD;
    delete[] pixelI;
    delete[] label;
}

void dataset_CIFAR_10::loaddata(vector<string> filename){
    picture_number=filename.size()*pictureNumberOfOneDataset;
    malloc(filename.size());
    //unsigned char unsignedbuffer;
    int pixel_flag=0;
    int label_flag=0;
    //row-major order
    for(unsigned int i=0;i<filename.size();i++){
        ifstream fp(filename[i].c_str(),ios::in|ios::binary);
        for(int j=0;j<10000;j++){
            char b;
			unsigned char a;
            for(int n=0;n<3073;n++){
                fp.read(&b,1);
				a=b;
                if(n==0) label[label_flag++]=a;
                else{
                    pixelD[pixel_flag]=a/255.0;
                    pixelI[pixel_flag]=a;
                    pixel_flag++;
                }
            }
        }
        cout<<filename[i]<<" has loaded!"<<endl;
    }
}

