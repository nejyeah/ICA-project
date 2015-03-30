#include <thread>
#include <iostream>
#include <vector>

using namespace std;

int main()

{
    vector<thread> threads;
    for(int i = 0; i < 5; ++i){
         threads.push_back(
             std::thread([](){
                 cout << "Hello from lamda thread " <<this_thread::get_id() << endl;
                 }));
    }
    for(auto& thread : threads){
       thread.join();
    }
    cout<<"Main Thread"<<"\t"<<this_thread::get_id()<<endl;

    return 0;

}
