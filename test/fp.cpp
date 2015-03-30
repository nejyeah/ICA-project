#include<iostream>
using namespace std;
int main(){
    while(true){
        unsigned char a;
        cin>>a;
        if(a=='q') break;
        cout<<"out:"<<(int)a<<endl;
    }
    return 0;
}
