#ifndef CIFAR_H
#define CIFAR_H

#include<iostream>
#include<vector>
using namespace std;

class dataset_CIFAR_10{
public:
    void free();
    void malloc(int pictureNumber);
    void loaddata(vector<string> filename);
    dataset_CIFAR_10();
    
    //the pictures including R G B three channels are install in one vector in orders R G B per image
    //as is to say ,the first image pixels is R channel image,and row major, the second image pixels are G channel image
    double *pixelD;//change the pixels value to 0~1 and store it
    int *pixelI;//store the original pixels value 0~255 and store it
    int *label;//stor the original pixels label 0~9
    int picture_number; //the total number of pictures
    int nrow_pixel,ncol_pixel; //pictures is nrow_pixel*ncol_pixel
    int channel; //colorful picture,with red,green,blue 
    int pictureNumberOfOneDataset;//one file contains the number of picture
};
#endif

