#include<iostream>
#include<fstream>
using namespace std;

int main(){
	string mnist="../data/MINIST/train-images.idx3-ubyte";
	string infile="top2_h2_4.bin";
	string outfile="top2_h2_4_pixel.bin";
	int point=12*12*3;
	ifstream fp(mnist.c_str(),ios::in|ios::binary);
	ifstream fp1(infile.c_str(),ios::in|ios::binary);
	ofstream fp2(outfile.c_str(),ios::out|ios::binary);
	
	int size_image=28*28;
	int top_size=200;
	int location=0;
	for(int i=0;i<point;i++){
		fp1.seekg(i*top_size*sizeof(int),ios::beg);
		fp1.read((char*)&location,sizeof(int));
		cout<<i+1<<":"<<location<<endl;
		fp.seekg(16+location*size_image,ios::beg);
		char a;
		float b=0;
		for(int j=0;j<size_image;j++){
			fp.read(&a,1);
			b=(unsigned char)a;
			b=b/255.0;
			fp2.write((char*)&b,sizeof(float));
		}
	}
	fp.close();
	fp1.close();
	fp2.close();

}
