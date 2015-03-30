#include<iostream>
#include<thread>
#include<vector>
#include"dataset_stl10.h"
#include<random>
#include"cblas.h"
//#include"cblas_f77.h"

using namespace std;

const int pictureSize=96*96;
const int step=4;
const int minibatch=20;
const int trainingNumber=5000;
const int minibatchNumber=trainingNumber/minibatch;
const int filterSize=20*20;
const int channel=3;
const int filterBlockSize=8*filterSize*channel;
const int filterBlockNumber=400;
const int inputBlockSize=filterSize*channel*minibatch;

void getBlockInput(int epoch,int n,double *input,const dataset_stl10 &train);

int main(){
    double **W;
    double **H;
    W=(double **)malloc(sizeof(double *)*filterBlockNumber);
    H=(double **)malloc(sizeof(double *)*filterBlockNumber);
    random_device rd;
    //init W 0~1
    for(int i=0;i<filterBlockNumber;i++){
        W[i]=(double*)malloc(sizeof(double)*filterBlockSize);
        H[i]=(double*)malloc(sizeof(double)*filterBlockSize);

        for(int j=0;j<filterBlockSize;j++){
            W[i][j]=rd()/(double)(rd.max());
            //cout<<H[i][j]<<endl;
        }
    }


    //read the data
    string dataFilename="../data/stl10/train_X.bin";
    dataset_stl10 stl_train;
    stl_train.loaddata(dataFilename);

    for(int epoch=0;epoch<minibatchNumber;epoch++){
        //vector<thread> forward_threads;
        cout<<"epoch:"<<epoch<<"/"<<minibatchNumber<<endl;
        for(int i=0;i<filterBlockNumber;i++){
            double *input=(double*)malloc(sizeof(double)*inputBlockSize);
            getBlockInput(epoch,i,input,stl_train);
            int m=8,n=minibatch,k=20*20*3;
            int lda=k,ldb=n,ldc=n;
            double alpha=1.0,beta=0.0;
            cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,m,n,k,alpha,W[i],lda,input,ldb,beta,H[i],ldc);
            free(input);
        }
        /*
        for(auto& thread:forward_threads){
            thread.join();
        }*/

    }

    for(int i =0;i<filterBlockNumber;i++){
        free(W[i]);
        free(H[i]);
    }
    free(W);
    free(H);
    return 0;
}


void getBlockInput(int epoch,int n,double *input,const dataset_stl10 &train){
    //block store based on row major
    int block_row=n/20;
    int block_col=n%20;
    int input_flag=0;
    for(int j=0;j<channel;j++){
        for(int m=0;m<filterSize;m++){
            for(int i=0;i<minibatch;i++){
                //store in vector input based on col major
                int col=m/20;
                int row=m%20;
                input[input_flag++]=train.pixelD[27648*(epoch*minibatch+i)+9216*j+96*(block_col+col)+block_row+row];
            }       
        }
    }

}
