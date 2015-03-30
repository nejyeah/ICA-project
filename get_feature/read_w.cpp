#include<iostream>
#include<fstream>

using namespace std;

int main(){
	int size=4*4*3*10*10*3;
	float* w=new float[size];
	ifstream fp("minist3_w_t3.dat",ios::in|ios::binary);
	fp.read((char*)w,size*sizeof(float));
	for(int i=0;i<3;i++){
		cout<<"map "<<i<<endl;
		for(int j=0;j<10;j++){
			cout<<"col:"<<j<<"\t";
			for(int k=0;k<10;k++){
				cout<<w[i*10*10+j*10+k]<<" ";
			}
			cout<<endl;
		}
	}
	delete[] w;
	return 0;
}
