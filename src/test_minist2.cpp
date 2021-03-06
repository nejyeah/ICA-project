#include<iostream>
#include<fstream>
#include"mpi.h"
extern "C"{
#include"cblas.h"
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
}
#include"HPC.h"

using namespace std;

int main(int argc,char **argv){
    int rank;
    int process_number;
    int namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&process_number);
    MPI_Get_processor_name(processor_name,&namelen);

    //输入相关
    const int input_row=20;
    const int input_col=20;
    const int input_channel=3;
    const string inputFileName="minist1_outcome_t4_test.dat";
    const int picture_number=10000;

    //模型相关，filter
    const int filter_row=10;
    const int filter_col=10;
    const int step_size=2;
    //hidden layer
    const int hidden_block_row=2;
    const int hidden_block_col=2;
    const int hidden_channel=3;
    const int hidden_row=((input_row-filter_row)/step_size+1)*hidden_block_row;
    const int hidden_col=((input_col-filter_col)/step_size+1)*hidden_block_col;

    //pooling layer
    const int pooling_row=3;
    const int pooling_col=3;


    HPC firstlayer(rank,process_number,processor_name,input_row,input_col,input_channel,inputFileName,picture_number,filter_row,filter_col,step_size,hidden_block_row,hidden_block_col,hidden_channel,hidden_row,hidden_col,pooling_row,pooling_col);

    //trainning parameters
    const int minibatch=40;
    const int n_epochs=500;
    //alpha*W*X=h
    //ela 0.01 alpha 0.12  learning_rate 20 alpha_learning_rate=0.001 u 0.005
    float alpha=0.931181;
    const float theata=0.0001;
    //E=E1+ela*E2
    const float ela=0.01;
    //w=w+learning_rate*delta_W+u*delta_W_mconst float learning_rate=12;
    const float learning_rate=1.2;
    const float alpha_learning_rate=0.0001;
    const float u=0.5;
    if(rank==0){
        cout<<"************************************************"<<endl;
        cout<<"-----------train_minist2--------"<<endl;
        cout<<"input:"<<inputFileName<<endl;
        cout<<"n_epoch:"<<n_epochs<<endl;
        cout<<"alpha:"<<alpha<<endl;
        cout<<"ela:"<<ela<<endl;
        cout<<"learning_rate:"<<learning_rate<<endl;
        cout<<"u:"<<u<<endl;
        cout<<"alpha_learning_rate:"<<alpha_learning_rate<<endl;
        cout<<"************************************************"<<endl;
    }
    const string outfilename="minist2_w_t4.dat";
    const string h_filename="minist2_h_t4_test.dat";
    const string p_filename="minist2_p_t4_test.dat";
    const string lcn_filename="minist2_outcome_t4_test.dat";
    //const string R_0_file="minist2_R0_t3.dat";
    //const string R_n_file="minist2_Rn_t3.dat";

    //lcn layer
    const int lcn_channel=3;
    const int lcn_row=3;
    const int lcn_col=3;

    firstlayer.set_minibatch(minibatch);
    firstlayer.set_alpha(alpha);
    firstlayer.set_theata(theata);
    firstlayer.set_ela(ela);
    firstlayer.set_learning_rate(learning_rate);
    firstlayer.set_lcn_channel(lcn_channel);
    firstlayer.set_lcn_row(lcn_row);
    firstlayer.set_lcn_col(lcn_col);
    firstlayer.set_h_filename(h_filename);
    firstlayer.set_p_filename(p_filename);
    firstlayer.set_lcn_filename(lcn_filename);


    int numberOfminibatch=picture_number/minibatch;
    int hiddenBlocksNumberOfPerProcess=(hidden_row/hidden_block_row)*(hidden_col/hidden_block_col)/process_number;
    int size_pixelD=input_row*input_col*input_channel*minibatch;
    int size_w_block=hidden_block_row*hidden_block_col*hidden_channel*filter_row*filter_col*input_channel;
    int size_w=hiddenBlocksNumberOfPerProcess*size_w_block;
    int size_h_block=minibatch*hidden_block_row*hidden_block_col*hidden_channel;
    int size_h=size_h_block*hiddenBlocksNumberOfPerProcess;
    int size_h_gather=minibatch*hidden_row*hidden_col*hidden_channel;

    srand(time(NULL));
    firstlayer.malloc();
    //firstlayer.initlize_w();
    if(rank==0) firstlayer.loaddata_w(outfilename);
    float *w=firstlayer.get_w();
    float *w_gather=firstlayer.get_w_gather();
    MPI_Scatter(w_gather,size_w,MPI_FLOAT,w,size_w,MPI_FLOAT,0,MPI_COMM_WORLD);

    firstlayer.initlize_lcn_GW();
    firstlayer.zeros_delta_w();

    time_t time1=time(NULL);


    for(int minibatch_index=0;minibatch_index<numberOfminibatch;minibatch_index++){
        if(rank==0){
            firstlayer.loaddata_Float(minibatch_index);
            //need whitening
            //firstlayer.preprocess();
        }
        //0号进程将预处理后的输入图片数据广播给其他进程，同样存在pixelD中
        float *pixelD=firstlayer.get_pixelD();
        float *w=firstlayer.get_w();
        float *delta_w=firstlayer.get_delta_w();
        //float *pixelD_block=firstlayer.get_pixelD_block();
        float *h=firstlayer.get_h();
        float *h_gather=firstlayer.get_h_gather();
        //float *rpixelD_block=firstlayer.get_rpixelD_block();

        MPI_Bcast(pixelD,size_pixelD,MPI_FLOAT,0,MPI_COMM_WORLD);
        firstlayer.normalize_w();
        firstlayer.zeros_rpixelD();
        firstlayer.zeros_rpixelD_gather();
        //每个进程循环训练所分配的blocks
        firstlayer.compute_rpixelD();
        float* rpixelD=firstlayer.get_rpixelD();
        float* rpixelD_gather=firstlayer.get_rpixelD_gather();
        MPI_Allreduce(rpixelD,rpixelD_gather,size_pixelD,MPI_FLOAT,MPI_SUM,MPI_COMM_WORLD);
        firstlayer.copy_rpixelD();

        catlas_saxpby(size_pixelD,-1,pixelD,1,1,rpixelD_gather,1);
        MPI_Allgather(h,size_h,MPI_FLOAT,h_gather,size_h,MPI_FLOAT,MPI_COMM_WORLD);

        //pooling
        if(rank==0){
            firstlayer.sort_h_gather();
            firstlayer.pooling();
            firstlayer.Lcn();
            firstlayer.write_h();
            firstlayer.write_p();
            firstlayer.write_lcn();
            float* lcn=firstlayer.get_lcn();
            float* p=firstlayer.get_p();
            float* h_sort=firstlayer.get_h_sort();
            float R_cost=0;
            for(int i=0;i<size_pixelD;i++){
                R_cost+=rpixelD_gather[i]*rpixelD_gather[i];
            }
            float P_cost=0;
            for(int i=0;i<size_h_gather;i++){
                P_cost+=p[i];
            }
            P_cost=ela*P_cost;
            cout<<"-------------------cost---------------------------"<<endl;
            cout<<"minibatch_index:"<<minibatch_index<<"/"<<numberOfminibatch<<endl;
            cout<<"\tR_cost:"<<R_cost<<"\tP_cost:"<<P_cost<<"\tall_cost:"<<R_cost+P_cost<<endl;


            cout<<"--------------------h_sort--------------------"<<endl;
            for(int i=0;i<200;i++){
                cout<<h_sort[i]<<" ";
            }
            cout<<endl;

            cout<<"--------------------p--------------------"<<endl;
            for(int i=0;i<200;i++){
                cout<<p[i]<<" ";
            }
            cout<<endl;
            cout<<"-----------------lcn---------------------"<<endl;
            for(int i=0;i<200;i++){
                cout<<lcn[i]<<" ";
            }
            cout<<endl;
        }
    }
    firstlayer.free();
    MPI_Finalize();
    return 0;
}
