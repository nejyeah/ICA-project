#include<iostream>
#include"mpi.h"
#include"../include/hpc_block.h"

using namespace std;
/*
void init(int argc,char **argv,hpc_block &block){
	const string filename="../data/stl10/train_X.bin";
    const int picture_number=5000;
    const int nrow_pixel=96;
    const int ncol_pixel=96;
    const int input_channel=3;
    const int hidden_channel=8;
    const int filter_row=10;
	const int filter_col=10;
    const int step_size=2;
    const int hidden_block_row=2;
	const int hidden_block_col=2;
    int rank;
    int nodesize;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nodesize);
    block=new hpc_block(picture_number,nrow_pixel,ncol_pixel,input_channel,hidden_channel,step_size,filter_row,filter_col,hidden_block_row,hidden_block_col,rank,nodesize);
	block.loaddata(filename);
}
*/
int main(int argc,char **argv){
	const string filename="../data/stl10/train_X.bin";
    const int picture_number=5000;
    const int nrow_pixel=96;
    const int ncol_pixel=96;
    const int input_channel=3;
    const int hidden_channel=8;
    const int filter_row=10;
	const int filter_col=10;
    const int step_size=2;
    const int hidden_block_row=2;
	const int hidden_block_col=2;
    const int minibatch=40;
    int rank;
    int nodesize;
    int minibatch_index=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nodesize);
    hpc_block block(picture_number,nrow_pixel,ncol_pixel,input_channel,hidden_channel,step_size,filter_row,filter_col,hidden_block_row,hidden_block_col,rank,nodesize,minibatch);
    cout<<rank<<endl;
    block.malloc();

	for(;minibatch<picture_number/minibacth;minibatch++){
    	block.loaddata(filename,minibatch_index);
		for()
	}
    block.free();
    MPI_Finalize();
	return 0;
}

