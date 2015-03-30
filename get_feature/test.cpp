#include<iostream>
#include<vector>
using namespace std;

void number(vector<string> filename);

int main(){
	int* a=new int[10];
	for(int i=0;i<10;i++){
		a[i]=i;
	}
	delete[] a;

	for(int i=0;i<10;i++){
		cout<<a[i]<<endl;
	}
	
	int* b=new int[10];

	for(int i=0;i<10;i++){
		cout<<b[i]<<endl;
	}
	/*
    vector<string> filename;
    filename.push_back("1");
    filename.push_back("2");
    filename.push_back("3");
    number(filename);*/
    return 0;
}

void number(vector<string> filename){
    int n=filename.size();
    cout<<n<<endl;
}
