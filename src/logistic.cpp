#include"Logistic.h"
#include"math.h"
#include<fstream>
extern "C"{
#include"cblas.h"
#include<stdlib.h>
}

Logistic::Logistic(int iinput,int hhidden,int iinput_channel,int mminibatch,int iinput_number,string iinput_file_x,string iinput_file_y,int vvalidation_number,int ttest_number,string ttest_file_x,string ttest_file_y){
    input=iinput;
    hidden=hhidden;
    input_channel=iinput_channel;
    minibatch=mminibatch;
    train_number=iinput_number;
    input_file_x=iinput_file_x;
    input_file_y=iinput_file_y;
    validation_number=vvalidation_number;
    test_number=ttest_number;
    test_file_x=ttest_file_x;
    test_file_y=ttest_file_y;
}

float Logistic::train_model(int minibatch_index){
    loaddata_integer(minibatch_index,0);
    preprocess();
    //loaddata_minist(minibatch_index,0);
    //loaddata_float(minibatch_index,0);
    //normalize();
    float error=train(0);
    update_parameters(minibatch_index);
    return error;
}

float Logistic::validation_model(){
    int batch_number=validation_number/minibatch;
    float error=0;
    for(int i=0;i<batch_number;i++){
        loaddata_integer(i,1);
        preprocess();
        //loaddata_minist(i,1);
        //loaddata_float(i,1);
        //normalize();
        error+=train(1);
    }
    error=error/validation_number;
    return error;
}

float Logistic::test_model(){
    int batch_number=test_number/minibatch;
    float error=0;
    for(int i=0;i<batch_number;i++){
        loaddata_integer(i,2);
        preprocess();
        //loaddata_minist(i,2);
        //loaddata_float(i,2);
        //normalize();
        error+=train(1);
    }
    error=error/test_number;
    return error;
}

float Logistic::train(int flag){
    float error=0.0;
    float negative_log=0.0;

    int M=minibatch;
    int K=input;
    int N=hidden;
    zeros_output();
    /*
    float output0=0;
    for(int i=0;i<input;i++){
        if(x[i]!=0){
            cout<<x[i]<<":"<<w[i*hidden]<<" ";
            output0+=x[i]*w[i*hidden];
        }
    }
    cout<<endl;*/
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,M,N,K,1,x,K,w,N,0,output,N);
    for(int i=0;i<minibatch;i++){
        catlas_saxpby(hidden,1,bias,1,1,&output[i*hidden],1);
    }

    for(int i=0;i<minibatch;i++){
        int index=i*hidden;
        float sum=0;
        for(int j=0;j<hidden;j++){
            output[index+j]=exp(output[index+j]);
            if(output[index+j]==0) cout<<index+j<<" ";
            sum+=output[index+j];
        }

        int index_max=0;
        float max=0;
        for(int j=0;j<hidden;j++){
            output[index+j]=output[index+j]/sum;
            //cout<<output[index+j]<<" ";
            if(output[index+j]>max){
                max=output[index+j];
                index_max=j;
            }
        }

        char l=label[i];
        if(flag==0) negative_log-=log(output[index+l]);
        else {
            if(index_max!=l) error+=1.0;
        }


    }
    if(flag==0) return negative_log/minibatch;
    else return error;
}

void Logistic::update_parameters(int minibatch_index){
    for(int i=0;i<minibatch;i++){
        int index=i*hidden;
        for(int j=0;j<hidden;j++){
            //using label
            //if(output[index+j]==0) cout<<index+j<<":0"<<endl;
            if(j==label[i]) output[index+j]=output[index+j]-1;
            //cout<<output[index+j]<<" ";
        }
    }
    //cout<<endl;
    int M=input;
    int K=minibatch;
    int N=hidden;
    //w=w-learning_rate*X^T*output
   /* 
    float* delta_w=new float[input*hidden];
    cblas_sgemm(CblasRowMajor,CblasTrans,CblasNoTrans,M,N,K,learning_rate,x,M,output,N,0,delta_w,N);
    
    for(int i=0;i<100;i++){
        cout<<delta_w[i]<<":"<<w[i]<<"\t";
    }
    cout<<endl;
    delete[] delta_w;
    */

    cblas_sgemm(CblasRowMajor,CblasTrans,CblasNoTrans,M,N,K,-learning_rate/minibatch,x,M,output,N,1,w,N);
    M=1;
    float* a=new float[minibatch];
    for(int i=0;i<minibatch;i++){
        a[i]=1;
    }
    cblas_sgemm(CblasRowMajor,CblasTrans,CblasNoTrans,M,N,K,-learning_rate/minibatch,a,M,output,N,1,bias,N);
    delete[] a;
}

void Logistic::loaddata_integer(int minibatch_index,int flag){
    string filename_x=test_file_x;
    string filename_y=test_file_y;
    if(flag==0){
        filename_x=input_file_x;
        filename_y=input_file_y;
    }
    int size_x=input*minibatch;
    ifstream fp(filename_x.c_str(),ios::in|ios::binary);
    //fp.seekg(size_x*minibatch_index,ios::beg);
    fp.seekg(size_x*minibatch_index+16,ios::beg);
    if(flag==2) fp.seekg(input*validation_number,ios::cur);
    char* buffer=new char[size_x];
    fp.read(buffer,size_x);
    fp.close();
    for(int i=0;i<size_x;i++){
        unsigned char a=buffer[i];
        x[i]=a/255.0;
    }
    delete[] buffer;

    ifstream fp1(filename_y.c_str(),ios::in|ios::binary);
    fp1.seekg(minibatch*minibatch_index,ios::beg);
    if(flag==2) fp1.seekg(validation_number,ios::cur);
    fp1.read(label,minibatch);
    fp1.close();
}

void Logistic::loaddata_float(int minibatch_index,int flag){
    string filename_x=input_file_x;
    string filename_y=input_file_y;
    if(flag==2){
        filename_x=test_file_x;
        filename_y=test_file_y;
    }
    int size_x=input*minibatch;
    ifstream fp(filename_x.c_str(),ios::in|ios::binary);
    fp.seekg(size_x*sizeof(float)*minibatch_index,ios::beg);
    if(flag==1) fp.seekg(input*sizeof(float)*train_number,ios::cur);
    fp.read((char*)x,size_x*sizeof(float));
    fp.close();
   
    ifstream fp1(filename_y.c_str(),ios::in|ios::binary);
    fp1.seekg(minibatch*minibatch_index+8,ios::beg);
    if(flag==1) fp1.seekg(train_number,ios::cur);
    fp1.read(label,minibatch);
    fp1.close();
    
}

void Logistic::loaddata_minist(int minibatch_index,int flag){
    string filename_x=input_file_x;
    string filename_y=input_file_y;
    if(flag==2){
        filename_x=test_file_x;
        filename_y=test_file_y;
    }
    int size_x=input*minibatch;
    ifstream fp(filename_x.c_str(),ios::in|ios::binary);
    fp.seekg(size_x*minibatch_index+16,ios::beg);
    if(flag==1) fp.seekg(input*train_number,ios::cur);
    char* buffer=new char[size_x];
    fp.read(buffer,size_x);
    fp.close();
    for(int i=0;i<size_x;i++){
        unsigned char a=buffer[i];
        x[i]=a/255.0;
    }
    delete[] buffer;
   
    ifstream fp1(filename_y.c_str(),ios::in|ios::binary);
    fp1.seekg(minibatch*minibatch_index+8,ios::beg);
    if(flag==1) fp1.seekg(train_number,ios::cur);
    fp1.read(label,minibatch);
    fp1.close();
}

void Logistic::preprocess(){
    int size_picture=input/input_channel;
    for(int i=0;i<minibatch*input_channel;i++){
        int index=i*size_picture;
        float mean=0.0;
        for(int j=0;j<size_picture;j++){
            mean+=x[index+j];
        }
        mean=mean/(size_picture);
        for(int j=0;j<size_picture;j++){
            x[index+j]=x[index+j]-mean;
        }

        float sum=0.0;
        for(int j=0;j<size_picture;j++){
            sum+=x[index+j]*x[index+j];
        }
        sum=sqrt(sum);
        for(int j=0;j<size_picture;j++){
            x[index+j]=x[index+j]/sum;
        }
    }
}

void Logistic::normalize(){
    int size_picture=input/input_channel;
    for(int i=0;i<minibatch*input;i++){
        x[i]=x[i]*x[i];
    }
    for(int i=0;i<minibatch*input_channel;i++){
        int index=i*size_picture;
        float max=-1000;
        float min=1000;
        for(int j=0;j<size_picture;j++){
            if(x[index+j]>max) max=x[index+j];
            if(x[index+j]<min) min=x[index+j];
        }
        for(int j=0;j<size_picture;j++){
            x[index+j]=(x[index+j]-min)/(max-min);
        }
    }
}

void Logistic::malloc(){
    int size_x=input*minibatch;
    int size_w=input*hidden;
    int size_bias=hidden;
    int size_output=minibatch*hidden;

    x=new float[size_x];
    label=new char[minibatch];
    w=new float[size_w];
    bias=new float[size_bias];
    output=new float[size_output];
}

void Logistic::free(){
    delete[] x;
    delete[] label;
    delete[] w;
    delete[] bias;
    delete[] output;
}

void Logistic::initialize_w(){
    int size_w=input*hidden;
    float high=sqrt(6.0/(input+hidden));
    for(int i=0;i<size_w;i++){
        w[i]=(rand()%200-100)*high/100.0;
    }
}

void Logistic::initialize_bias(){
    int size_bias=hidden;
    for(int i=0;i<size_bias;i++){
        bias[i]=0;
    }
}

void Logistic::set_learning_rate(float llearning_rate){
    learning_rate=llearning_rate;
}

void Logistic::zeros_output(){
    int size_output=hidden*minibatch;
    for(int i=0;i<size_output;i++){
        output[i]=0.0;
    }
}
