#include <iostream>
#include <thread>

using namespace std;
int j = 0;
mutex mtx;
void function_1P(){
	//int j = 0;
	for(int i=0;i<0xFFFFFFF;i++){
		if(i%0xFFFFF==0){
			mtx.lock();
			cout<<"Thread 1 - "<<j++<<endl;
			mtx.unlock();
		}
	}
}
void function_2P(){
	//int j = 0;
    for(int i=0;i<0xFFFFFFF;i++){
		if(i%0xFFFFF==0){
			mtx.lock();
			cout<<"Thread 2 - "<<j++<<endl;
			mtx.unlock();
		}
	}
}

int main(int argc, char* argv[]){
    cout<<"Hello World!\n";
    thread t1(function_1P);
    thread t2(function_2P);
    t1.join();
    t2.join();
	return 0;
}
