#include<iostream>
#include<fstream>
using namespace std;

int main(){
	ofstream outfile("float.dat");
	const int size=211300;
	float *a=new float[size];
	for(int i=0;i<size;i++){
		a[i]=5.3842-i;
	}
	outfile.write((char *)a,sizeof(float)*size);
	outfile.close();

	ifstream fp("float.dat",ios::in|ios::binary);
	float *a1=new float[size];
	fp.read((char *)a1,sizeof(float)*size);
	fp.close();
	for(int i=0;i<100;i++){
		cout<<a1[i]<<endl;
	}

	for(int i=211100;i<size;i++){
		//fp.read((char *)&a,sizeof(float));
		cout<<a1[i]<<endl;
	}
	return 0;
}
