#include<iostream>
#include<fstream>
#include<memory.h>

using namespace std;
void top(float newdata,float* data,int* label,int* location,int topsize,int pointsize,int index,char index_label);

int main(){
	string filename="minist2_h_t2_4.dat";
	string labelfile="../data/MINIST/train-labels.idx1-ubyte";
	string outfile="top2_h2_4.txt";
	string outfile1="top2_h2_4.bin";
	int pointsize=12*12*3;

	int topsize=200;
	int number=50000;
	ifstream fp(filename.c_str(),ios::in|ios::binary);
	ifstream fp1(labelfile.c_str(),ios::in|ios::binary);

	float* data=new float[pointsize*topsize];
	int* label=new int[pointsize*topsize];
	int* location=new int[pointsize*topsize];
    float* h=new float[pointsize*topsize];
	
	memset(data,0,sizeof(float)*pointsize*topsize);

	fp1.seekg(8,ios::beg);
	int sum=0;
	for(int i=0;i<number;i++){
		char a;
		fp.read((char*)h,sizeof(float)*pointsize);
		fp1.read(&a,1);
		if(i<10) cout<<(int)a<<endl;
		for(int j=0;j<pointsize;j++){
			if(j==0&&h[j]>=0) sum++; 
			if(j==44&&h[j]>=0) sum++; 
			top(h[j],&data[j*topsize],&label[j*topsize],&location[j*topsize],topsize,pointsize,i,a);
		}
	}

	cout<<"44th and 47th over 0 number:"<<sum<<endl;
	ofstream fp2(outfile.c_str(),ios::out);
	for(int i=0;i<pointsize;i++){
		fp2<<"max:"<<data[i*topsize]<<"\tindex:"<<location[i*topsize]<<"\tlabel:";
		for(int j=0;j<topsize;j++){
			fp2<<label[i*topsize+j]<<",";
		}
		fp2<<endl;
	}

	ofstream fp3(outfile1.c_str(),ios::out|ios::binary);
	fp3.write((char*)location,sizeof(int)*pointsize*topsize);

	fp.close();
	fp1.close();
	fp2.close();
	fp3.close();
	delete[] data;
	delete[] label;
	delete[] location;
	delete[] h;
	return 0;
}

void top(float newdata,float* data,int* label,int* location,int topsize,int pointsize,int index,char index_label){
	for(int i=topsize-1;i>=0;i--){
		if(newdata>data[i]){
			if(i==0){
				data[i]=newdata;
				label[i]=index_label;
				location[i]=index;
			}
			else{
				data[i]=data[i-1];
				label[i]=label[i-1];
				location[i]=location[i-1];
			}
		}
		else{
			if(i<topsize-1){
				data[i+1]=newdata;
				label[i+1]=index_label;
				location[i+1]=index;
			}
			break;
		}
	}
}
