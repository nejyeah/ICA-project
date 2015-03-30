#ifndef IMAGE_H
#define IMAGE_H

class Image
{
public:
    Image();                           //constructor
    Image(int numRows, int numCols, int grayLevels);//constructor
    ~Image();//                            destructor
    Image(const Image& oldImage);//constructor
    void operator=(const Image&);//overloaded assignment operator
    void setImageInfo(int numRows, int numCols, int maxVal); 
    void getImageInfo(int &numRows, int &numCols, int &maxVal);
    int getPixelVal(int row, int col);
    void setPixelVal(int row, int col, int value);
    bool inBounds(int row, int col);//checks to see if a pixel is in bounds
    void getSubImage(int upperLeftRow, int upperLeftCol, 
    int lowerRightRow, int lowerRightCol, Image& oldImage);
    void enlargeImage(int value, Image& oldImage);
    void shrinkImage(int value, Image& oldImage);
    void reflectImage(bool flag, Image& oldImage);
    void translateImage(int value, Image& oldImage);
    void rotateImage(int theta, Image& oldImage);
    Image operator+(const Image &oldImage);//ove       rloaded + operator
    Image operator-(const Image& oldImage);//overl     oaded - operator
    void negateImage(Image& oldImage);
private:
    int N;                            // number of rows
    int M; // number of columns                           
    int Q;                            // number of gray levels
    int **pixelVal;                       //2D array
};
