#ifndef MLP_H
#define MLP_H
#include<iostream>
using namespace std;
class Logistic{

    public:
        Logistic(int,int,int,int,int,string,string,int,int,string,string);
        float train_model(int );
        float validation_model();
        float test_model();
        void loaddata_integer(int,int);
        void loaddata_float(int,int);
        void loaddata_minist(int,int);
        void malloc();
        void free();
        void initialize_w();
        void initialize_bias();
        void preprocess();
        void normalize();
        float train(int);
        void update_parameters(int);
        void set_learning_rate(float);
        void zeros_output();

    private:
        int input;
        int hidden;
        int input_channel;
        int minibatch;
        int train_number;
        string input_file_x;
        string input_file_y;
        int validation_number;
        int test_number;
        string test_file_x;
        string test_file_y;
        
        float learning_rate;

        float* x;
        char* label;
        float* w;
        float* output;
        float* bias;
        
};
#endif
