#include<thread>
#include<iostream>

using namespace std;

void hello(){
    cout<<"Hello from thread"<<endl;
}

int main(){
    std::thread t1(hello);
    t1.join();
    cout<<"Main Thread"<<endl;
    return 0;
}
