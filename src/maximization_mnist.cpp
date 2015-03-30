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
    //输入相关
    const int l1_input_row=28;
    const int l1_input_col=28;
    const int l1_input_channel=1;
    const string l1_inputFileName="../data/MINIST/train-images.idx3-ubyte";
    const int picture_number=1;

    //模型相关，filter
    const int filter_row=10;
    const int filter_col=10;
    const int step_size=2;
    //hidden layer
    const int hidden_block_row=2;
    const int hidden_block_col=2;
    const int hidden_channel=3;
    const int l1_hidden_row=((l1_input_row-filter_row)/step_size+1)*hidden_block_row;
    const int l1_hidden_col=((l1_input_col-filter_col)/step_size+1)*hidden_block_col;

    //pooling layer
    const int pooling_row=3;
    const int pooling_col=3;

    HPC firstlayer(l1_input_row,l1_input_col,l1_input_channel,l1_inputFileName,picture_number,filter_row,filter_col,step_size,hidden_block_row,hidden_block_col,hidden_channel,pooling_row,pooling_col);

    //lcn layer
    const int lcn_channel=3;
    const int lcn_row=3;
    const int lcn_col=3;


    const int l2_input_row=l1_hidden_row;
    const int l2_input_col=l1_hidden_col;
    const int l2_input_channel=lcn_channel; 
    string l2_inputFileName="";
    const int l2_hidden_row=((l2_input_row-filter_row)/step_size+1)*hidden_block_row;
    const int l2_hidden_col=((l2_input_col-filter_col)/step_size+1)*hidden_block_col;


    HPC secondlayer(l2_input_row,l2_input_col,l2_input_channel,l2_inputFileName,picture_number,filter_row,filter_col,step_size,hidden_block_row,hidden_block_col,hidden_channel,pooling_row,pooling_col);

    const int l3_input_row=l2_hidden_row;
    const int l3_input_col=l2_hidden_col;
    const int l3_input_channel=l2_input_channel;
    string l3_inputFileName="";
    const int l3_hidden_row=((l3_input_row-filter_row)/step_size+1)*hidden_block_row;
    const int l3_hidden_col=((l3_input_col-filter_col)/step_size+1)*hidden_block_col;

    HPC thirdlayer(l3_input_row,l3_input_col,l3_input_channel,l3_inputFileName,picture_number,filter_row,filter_col,step_size,hidden_block_row,hidden_block_col,hidden_channel,pooling_row,pooling_col);
    //trainning parameters
    //when maximization,must set to 1
    const int minibatch=1;
    const int n_epochs=250;
    float l1_alpha=0.101395;
    float l2_alpha=0.0273903;
    float l3_alpha=0.224225;

    const float theata=0.0001;
    const float l1_c=0.011;
    const float l2_c=0.65;
    const float l3_c=1.45;
    const float learning_rate=0.12;
    const float u=0.005;

    string l1_w_filename="minist1_w_t1.dat";
    string l2_w_filename="minist2_w_t2_4.dat";
    string l3_w_filename="minist3_w_t2.dat";

    string output="l2_hx1_4.bin";
    string output1="l2_hx1_4.txt";
    //if(rank==0){
    cout<<"************************************************"<<endl;
    cout<<"----------activation mnist2--------"<<endl;
    cout<<"input:"<<l1_inputFileName<<endl;
    cout<<"l1_w_filename:"<<l1_w_filename<<endl;
    cout<<"l2_w_filename:"<<l2_w_filename<<endl;
    cout<<"l3_w_filename:"<<l3_w_filename<<endl;
    cout<<"n_epoch:"<<n_epochs<<endl;
    cout<<"l1_alpha:"<<l1_alpha<<endl;
    cout<<"l2_alpha:"<<l2_alpha<<endl;
    cout<<"l3_alpha:"<<l3_alpha<<endl;
    cout<<"l1_c:"<<l1_c<<endl;
    cout<<"l2_c:"<<l2_c<<endl;
    cout<<"l3_c:"<<l3_c<<endl;
    //cout<<"ela:"<<ela<<endl;
    cout<<"learning_rate:"<<learning_rate<<endl;
    cout<<"u:"<<u<<endl;
    cout<<"output_activation_x:"<<output<<endl;
    cout<<"output_activation:"<<output1<<endl;
    cout<<"************************************************"<<endl;
    //}


    firstlayer.set_minibatch(minibatch);
    firstlayer.set_alpha(l1_alpha);
    firstlayer.set_c(l1_c);
    firstlayer.set_theata(theata);
    firstlayer.set_learning_rate(learning_rate);
    firstlayer.set_lcn_channel(lcn_channel);
    firstlayer.set_lcn_row(lcn_row);
    firstlayer.set_lcn_col(lcn_col);


    secondlayer.set_minibatch(minibatch);
    secondlayer.set_alpha(l2_alpha);
    secondlayer.set_c(l2_c);
    secondlayer.set_theata(theata);
    secondlayer.set_learning_rate(learning_rate);
    secondlayer.set_lcn_channel(lcn_channel);
    secondlayer.set_lcn_row(lcn_row);
    secondlayer.set_lcn_col(lcn_col);

    thirdlayer.set_minibatch(minibatch);
    thirdlayer.set_alpha(l3_alpha);
    thirdlayer.set_c(l3_c);
    thirdlayer.set_theata(theata);
    thirdlayer.set_learning_rate(learning_rate);
    thirdlayer.set_lcn_channel(lcn_channel);
    thirdlayer.set_lcn_row(lcn_row);
    thirdlayer.set_lcn_col(lcn_col);

    srand(time(NULL));
    time_t time1=time(NULL);

    firstlayer.malloc_maximization();
    firstlayer.loaddata_w(l1_w_filename);
    firstlayer.copy_w_gather_to_w();
    firstlayer.initlize_lcn_GW();
    firstlayer.normalize_w();

    secondlayer.malloc_maximization();
    secondlayer.loaddata_w(l2_w_filename);
    secondlayer.copy_w_gather_to_w();
    secondlayer.initlize_lcn_GW();
    secondlayer.normalize_w();

    thirdlayer.malloc_maximization();
    thirdlayer.loaddata_w(l3_w_filename);
    thirdlayer.copy_w_gather_to_w();
    thirdlayer.initlize_lcn_GW();
    thirdlayer.normalize_w();

    firstlayer.compute_delta_hx();
    firstlayer.compute_delta_vp();
    secondlayer.compute_delta_hx();
    secondlayer.compute_delta_vp();
    thirdlayer.compute_delta_hx();
    thirdlayer.compute_delta_vp();

    int size_l1_input=l1_input_row*l1_input_col*l1_input_channel;
    int size_l1_hidden=l1_hidden_row*l1_hidden_col*hidden_channel;
    int size_l2_input=l2_input_row*l2_input_col*hidden_channel;
    int size_l2_hidden=l2_hidden_row*l2_hidden_col*hidden_channel;
    int size_l3_input=l3_input_row*l3_input_col*hidden_channel;
    int size_l3_hidden=l3_hidden_row*l3_hidden_col*hidden_channel;

    float *delta_x=new float[size_l1_input];
    float *l2_delta_x=new float[size_l2_hidden*size_l1_input];
    float *l3_delta_x=new float[size_l3_hidden*size_l1_input];

    ofstream fp(output.c_str(),ios::out|ios::binary);
    ofstream fp1(output1.c_str(),ios::out);

    for(int i=0;i<size_l2_hidden;i++){ 
        //output to the next layer
        //firstlayer.loaddata_minist(0);
        firstlayer.random_x();
        cout<<"-----------------------point:"<<i<<"---------------------------"<<endl;
        for(int epoch=0;epoch<n_epochs;epoch++){
            firstlayer.normalize_x();

            firstlayer.compute_h();
            firstlayer.copy_h_to_h_gather();
            firstlayer.sort_h_gather();
            firstlayer.pooling();
            firstlayer.Lcn();
            
            firstlayer.compute_delta_ph();
            firstlayer.compute_delta_px();
            firstlayer.compute_delta_vx();
            //firstlayer.compute_delta_lv();
            //firstlayer.compute_delta_lx();

            
            float* l1_lcn=firstlayer.get_lcn();
            secondlayer.copy_to_x(l1_lcn,size_l1_hidden);
            secondlayer.compute_h();
            secondlayer.copy_h_to_h_gather();
            secondlayer.sort_h_gather();
            //secondlayer.pooling();
            //secondlayer.Lcn();

            //secondlayer.compute_delta_ph();
            //secondlayer.compute_delta_px();
            //secondlayer.compute_delta_vx();
            
            //float* l2_lcn=secondlayer.get_lcn();
            //thirdlayer.copy_to_x(l2_lcn,size_l2_hidden);
            //thirdlayer.compute_h();
            //thirdlayer.copy_h_to_h_gather();
            //thirdlayer.sort_h_gather();
            //thirdlayer.pooling();
            
            //thirdlayer.compute_delta_ph();
            //thirdlayer.compute_delta_px();
            
            //compute the gradient of l2_lcn_layer with l1_input 
            float* l1_delta_x=firstlayer.get_delta_vx();
            float* l2_delta_2x=secondlayer.get_delta_hx();
            int M=size_l3_input;
            int K=size_l2_input;
            int N=size_l1_input;
            cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,M,N,K,1,l2_delta_2x,K,l1_delta_x,N,0,l2_delta_x,N);
            
            //compute the gradient of layer3 with l1_input
            
            //float* l3_delta_2x=thirdlayer.get_delta_hx();
            //M=size_l3_hidden;
            //K=size_l2_hidden;
            //N=size_l1_input;
            //cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,M,N,K,1,l3_delta_2x,K,l2_delta_x,N,0,l3_delta_x,N);
        
            //float* l_max=firstlayer.get_lcn();
            //float* l_delta_x=firstlayer.get_delta_lx();
            float* l_max=secondlayer.get_h_sort();
            float* l_delta_x=l2_delta_x;

            cout<<"-----point:"<<i<<"/"<<size_l2_hidden<<" \t"<<"epoch:"<<epoch<<"/"<<n_epochs<<endl;
            cout<<"maximization point value:"<<l_max[i]<<endl;
            
            //更新x
            //float* l1_nx=firstlayer.get_pixelD();
            float* l1_x=firstlayer.get_pixelD();
            //firstlayer.projected_gradient(&l_delta_x[i*size_l1_input],l1_x,l1_nx,size_l1_input);
            for(int j=0;j<50;j++){
                cout<<j<<"#"<<l1_x[j]<<":"<<learning_rate*l_delta_x[i*size_l1_input+j]<<" ";
            }
            cout<<endl;
            catlas_saxpby(size_l1_input,learning_rate,&l_delta_x[i*size_l1_input],1,1,l1_x,1);
            //catlas_saxpby(size_l1_input,-1,delta_x,1,1,l1_x,1);
            
            //store the outcome
            
            if(epoch==n_epochs-1){
                fp.write((char*)l1_x,sizeof(float)*size_l1_input);
                fp1<<l_max[i]<<endl;
            }
        }
    }
    time_t time2=time(NULL);
    cout<<"time cost_all:"<<time2-time1<<"\t every point time cost:"<<(time2-time1)/size_l2_hidden<<endl;
    delete[] delta_x;
    delete[] l2_delta_x;
    delete[] l3_delta_x;
    fp.close();
    fp1.close();
    secondlayer.free_maximization();
    firstlayer.free_maximization();
    thirdlayer.free_maximization();
    return 0;
}
