//Filename:rbm.cpp

#include"dataset.h"
#include"dataset_CIFAR_10.h"
#include"dataset_stl10.h"
#include<iostream>
#include<fstream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void loaddata_minist();
void show_minist(const dataset &train);
void loaddata_CIFAR_10(dataset_CIFAR_10 &train);
void show_cifar10(const dataset_CIFAR_10 &train);
void loaddata_stl10(dataset_stl10 &train);
void show_stl10(const dataset_stl10 &train);

int main(){
    //loaddata_minist();
    
    /*
    dataset_CIFAR_10 train;
    loaddata_CIFAR_10(train);
    show_cifar10(train);
    */
	   
    
    dataset_stl10 train;
    loaddata_stl10(train);
    show_stl10(train);
    
    //train.free();
    return 0;
}

void loaddata_minist(){
    dataset train;
    dataset test;
    string filename[]={"../data/MINIST/train-images.idx3-ubyte","../data/MINIST/train-labels.idx1-ubyte","../data/MINIST/t10k-images.idx3-ubyte","../data/MINIST/t10k-labels.idx1-ubyte"};
    train.loaddata(filename[0]);
    train.loaddata(filename[1]);
    test.loaddata(filename[2]);
    test.loaddata(filename[3]);
    show_minist(train);
    test.free();
    train.free();

}

void show_minist(const dataset &train){
    for(int picNum=0;picNum<30;picNum++){
        //Mat image(32,32,CV_8UC3,Scalar(0,0,255));
        Mat image(28,28,CV_8UC1,Scalar(0));
        cout<<"init mat now"<<endl;
        for(int i=0;i<image.rows;i++){
            for(int j=0;j<image.cols;j++){
                //cout<<i<<":"<<j<<": "<<train.pixel[i*32+j]<<endl;

                //just show one channel
                image.at<unsigned char>(i,j)=(int)(train.pixel[picNum][i*image.rows+j]*255);
            }
        }
        cout<<"show image now!"<<endl;
        //cout<<"image="<<endl<<""<<image<<endl<<endl;
        namedWindow("picture_minist",WINDOW_AUTOSIZE);
        imshow("picture_minist",image);
        waitKey();
    }
    

}


void loaddata_CIFAR_10(dataset_CIFAR_10 &train){
    vector<string> filename;
    filename.push_back("../data/cifar-10/data_batch_1.bin");
    //filename.push_back("../data/cifar-10/data_batch_2.bin");
    //filename.push_back("../data/cifar-10/data_batch_3.bin");
    //filename.push_back("../data/cifar-10/data_batch_4.bin");
    //filename.push_back("../data/cifar-10/data_batch_5.bin");
    train.loaddata(filename);
    /*
       ofstream fp("red_image[0]_pixel.txt");
       for(int i=0;i<1024;i++){
       cout<<train.pixel[i]<<endl;
       fp<<train.pixel[i]<<"\n";
       }
       */
}

void show_cifar10(const dataset_CIFAR_10 &train){
    for(int picNum=0;picNum<30;picNum++){
        Mat image(32,32,CV_8UC3,Scalar(0,0,255));
        //Mat image(32,32,CV_8UC1,Scalar(0));
        cout<<"init mat now"<<endl;
        for(int i=0;i<image.rows;i++){
            for(int j=0;j<image.cols;j++){
                //cout<<i<<":"<<j<<": "<<train.pixel[i*32+j]<<endl;
                //show a colorful picture using R G B three channel
                
                Vec3b &rgb = image.at<Vec3b>(i,j);
                rgb[0]=train.pixelI[(i*image.rows+j+2048)+picNum*3072];
                rgb[1]=train.pixelI[(i*image.rows+j+1024)+picNum*3072];
                rgb[2]=train.pixelI[(i*image.rows+j)+picNum*3072];
                

                //just show one channel
                //image.at<unsigned char>(i,j)=train.pixelI[(i*image.rows+j+1024)+picNum*3072];
            }
        }
        cout<<"show image now!"<<endl;
        //cout<<"image="<<endl<<""<<image<<endl<<endl;
        namedWindow("picture_cifar10",WINDOW_AUTOSIZE);
        imshow("picture_cifar10",image);
        waitKey();
        /*
           cout<<"store image now!"<<endl;
           vector<int> compression_params ;
           compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
           compression_params.push_back(0);
           string pngName=picNum+".png";
           cout<<pngName<<endl;
           imwrite(pngName,image,compression_params);*/
    }
}

void loaddata_stl10(dataset_stl10 &train){
    //string filename="../data/stl10/unlabeled_X.bin";
    //string filename="../data/stl10/test_X.bin";
    string filename="../data/stl10/train_X.bin";
    cout<<"start loaddata!"<<endl;
    train.loaddata(filename);
}

void show_stl10(const dataset_stl10 &train){
    for(int picNum=0;picNum<30;picNum++){
        Mat grayImage;
        //显示用
        Mat display;
        int w=96;
        int h=96;
        display.create(h*2,w*2,CV_8UC3);
        //黑色
        Mat bk;
        bk.create(h,w,CV_8UC1);
        bk=Scalar(0);
        //显示框
        Mat m(display,Rect(0,0,w,h));
        Mat m1(display,Rect(0,h,w,h));
        Mat m2(display,Rect(w,0,w,h));
        Mat m3(display,Rect(w,h,w,h));

        //通道合成
        vector<Mat> mbgr(3);
        
        Mat imageR(96,96,CV_8UC1,Scalar(0));
        Mat imageG(96,96,CV_8UC1,Scalar(0));
        Mat imageB(96,96,CV_8UC1,Scalar(0));
        Mat image(96,96,CV_8UC3,Scalar(0,0,0));
        
        cout<<"init mat now"<<endl;
        for(int j=0;j<image.cols;j++){
            for(int i=0;i<image.rows;i++){
                //cout<<i<<":"<<j<<": "<<train.pixelI[i*32+j]<<endl;
            
                Vec3b &rgb = image.at<Vec3b>(i,j);
                //rgb[0]=UCHAR_MAX;
                rgb[2]=train.pixelI[(j*image.cols+i)+picNum*27648];
                rgb[1]=train.pixelI[(j*image.cols+i)+9216+picNum*27648];
                rgb[0]=train.pixelI[(j*image.cols+i)+18432+picNum*27648];
            
                imageB.at<unsigned char>(i,j)=train.pixelI[(j*image.cols+i+18432)+picNum*27648];
                imageG.at<unsigned char>(i,j)=train.pixelI[(j*image.cols+i+9216)+picNum*27648];
                imageR.at<unsigned char>(i,j)=train.pixelI[(j*image.cols+i)+picNum*27648];
            }
        }
        //合成到显示-B
        mbgr[0]=imageB;
        mbgr[1]=bk;
        mbgr[2]=bk;
        merge(mbgr,m);
        //合成到显示-G
        mbgr[0]=bk;
        mbgr[1]=imageG;
        mbgr[2]=bk;
        merge(mbgr,m1);
        //合成到显示-R
        mbgr[0]=bk;
        mbgr[1]=bk;
        mbgr[2]=imageR;
        merge(mbgr,m2);
        //原图显示
        image.copyTo(m3);

        cout<<"show image now!"<<endl;
        //放在同一个window上面显示
        namedWindow("stl10",CV_WINDOW_NORMAL);
        resizeWindow("stl10",w*2,h*2);
        imshow("stl10",display);
        waitKey(0);
        //cout<<"image="<<endl<<""<<image<<endl<<endl;
        //WINDOW_AUTOSIZE or WINDOW_NORMAL
        /*4个windows显示4张图片
        namedWindow("R",WINDOW_AUTOSIZE);
        namedWindow("G",WINDOW_AUTOSIZE);
        namedWindow("B",WINDOW_AUTOSIZE);
        namedWindow("A",WINDOW_AUTOSIZE);
        imshow("R",imageR);
        imshow("G",imageG);
        imshow("B",imageB);
        imshow("A",image);
        waitKey();
        */
        //store image
        /*
        if(picNum==0){
           cout<<"store image now!"<<endl;
           vector<int> compression_params ;
           compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
           compression_params.push_back(0);
           string pngName="1.png";
           cout<<pngName<<endl;
           imwrite(pngName,image,compression_params);

        }*/
    }    
}

    
    
