#include"image.h"

Image::Image(int numRows, int numCols, int grayLevels){
    /* Creates an Image of numRows x numCols and creates the arrays for it*/

    N = numRows;
    M = numCols;
    Q = grayLevels;

    pixelVal = new int *[N];
    for(int i = 0; i < N; i++)
    {
        pixelVal[i] = new int [M];
        for(int j = 0; j < M; j++)
            pixelVal[i][j] = 0;
    }
} 


