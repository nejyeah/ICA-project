#ifndef STL10_H
#define STL10_H

#include<iostream>
#include<vector>
using namespace std;

class dataset_stl10{
public:
    void free();
    void malloc();
    void loaddata(string filename);
    dataset_stl10();
    
    //the three channel images are stored in one vector ,order by R G B ,each image is col major
    //as is to say ,the first image pixels is R channel and col major
    double *pixelD;//change the pixels value to 0~1 and store
    int *pixelI;//store the original pixels value 0~255
    int picture_number; //the total number of pictures
    int nrow_pixel,ncol_pixel; //pictures is nrow_pixel*ncol_pixel
    int channel; //colorful picture,with red,green,blue 
};
#endif

