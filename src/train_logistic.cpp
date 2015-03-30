#include<iostream>
#include"Logistic.h"
extern "C"{
#include<stdlib.h>
}
using namespace std;

int main(){
    /*
    const int input=96*96*3;
    const int hidden=10;
    const int input_channel=3;
    const int minibatch=20;
    
    const int input_number=5000;
    string input_file_x="../data/stl10/train_X.bin";
    string input_file_y="../data/stl10/train_y.bin";

    const int validation_number=3000;
    const int test_number=5000;
    string test_file_x="../data/stl10/test_X.bin";
    string test_file_y="../data/stl10/test_y.bin";
    */

    
    const int input=28*28;
    const int hidden=10;
    const int input_channel=1;
    const int minibatch=100;

    const int input_number=50000;
    string input_file_x="/home/nej/data/mnist_binary/train-images.idx3-ubyte";
    string input_file_y="/home/nej/data/mnist_binary/train-labels.idx1-ubyte";
    const int validation_number=10000;
    const int test_number=10000;
    string test_file_x="/home/nej/data/mnist_binary/t10k-images.idx3-ubyte";
    string test_file_y="/home/nej/data/mnist_binary/t10k-labels.idx1-ubyte";
    
    
    //after ICA process ,mnist data 
	/*
    const int input=12*12*3;
    const int hidden=10;
    const int input_channel=1;
    const int minibatch=100;

    const int input_number=50000;
    string input_file_x="minist2_h_t1.dat";
    string input_file_y="../data/MINIST/train-labels.idx1-ubyte";
    const int validation_number=10000;
    const int test_number=10000;
    string test_file_x="minist2_h_t2.dat";
    string test_file_y="../data/MINIST/t10k-labels.idx1-ubyte";
*/
    const int n_epochs=1000;
    const float learning_rate=0.13;

    Logistic logistic(input,hidden,input_channel,minibatch,input_number,input_file_x,input_file_y,validation_number,test_number,test_file_x,test_file_y);
    logistic.set_learning_rate(learning_rate); 
    
    int n_train_batches=input_number/minibatch;
    int patience=10000;
    const int patience_increase=2;
    const float improvement_threshold=0.995;
    int validation_frequency=(n_train_batches<patience/2)?n_train_batches:(patience/2);

    float best_validation_loss=1000;
    float validation_loss=0;
    float test_loss=0.0;
    bool done_looping=false;
    int epoch=0;
    
    cout<<"---------------train_logistic----------------------"<<endl;
    cout<<"input_file_x:"<<input_file_x<<endl;
    cout<<"input_file_y:"<<input_file_y<<endl;
    cout<<"input_number:"<<input_number<<endl;
    cout<<"validation_number:"<<validation_number<<endl;
    cout<<"test_number:"<<test_number<<endl;
    cout<<"test_file_x:"<<test_file_x<<endl;
    cout<<"test_file_y:"<<test_file_y<<endl;
    cout<<"input:"<<input<<endl;
    cout<<"hidden:"<<hidden<<endl;
    cout<<"minibatch:"<<minibatch<<endl;
    cout<<"n_epochs:"<<n_epochs<<endl;
    cout<<"learning_rate:"<<learning_rate<<endl;
    cout<<"patience:"<<patience<<endl;
    cout<<"patience_increase:"<<patience_increase<<endl;
    cout<<"improvement_threshold:"<<improvement_threshold<<endl;
    cout<<"---------------------------------------------------"<<endl;

    srand(time(NULL));
    logistic.malloc();
    logistic.initialize_w();
    logistic.initialize_bias();

    time_t time1=time(NULL);
    while(epoch<n_epochs&&!done_looping){
        epoch++;
        for(int minibatch_index=0;minibatch_index<n_train_batches;minibatch_index++){
            float minibatch_avg_cost=logistic.train_model(minibatch_index);
            int iter=(epoch-1)*n_train_batches+minibatch_index;
            if((iter+1)%validation_frequency==0){
                validation_loss=logistic.validation_model();
                cout<<"epoch:"<<epoch<<"\t"<<"minibatch_avg_cost:"<<minibatch_avg_cost<<endl;
                cout<<"\tvalidation_loss:"<<validation_loss<<endl;
                if(validation_loss<best_validation_loss){
                    if(validation_loss<best_validation_loss*improvement_threshold) patience=patience>iter*patience_increase?patience:iter*patience_increase;
                    best_validation_loss=validation_loss;
                    
                    test_loss=logistic.test_model();
                    cout<<"\tepoch:"<<epoch<<"\t"<<minibatch_index<<"/"<<n_train_batches<<endl;
                    cout<<"\t\ttest_loss:"<<test_loss<<endl;
                }
            }
            if(patience<=iter){
                done_looping=true;
                break;
            }
        }
    }
    time_t time2=time(NULL);
    cout<<"Optimization complete with best validation score of "<<best_validation_loss<<",\nwith test performance "<<test_loss<<endl;
    cout<<"the code run for "<<1.0*(time2-time1)/epoch<<" sec/epoch"<<endl;
    logistic.free(); 
    return 0;
}
