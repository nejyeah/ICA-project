//Filename:dataset.h
#ifndef CAT_H
#define CAT_H
#include<string>
#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

class dataset{
    public:
        void free() ;
        void malloc(int symbol);
        void loaddata(string filename);
        dataset();

        int number,nrow_pixel,ncol_pixel;
        unsigned char *label;
        double **pixel;
};

#endif
