#include <iostream>
#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include "ThreadPool.h"

using namespace std;
class Mytask : public  lz::Task {
public:
	Mytask() {}
	virtual int run() {
		printf("thread[%lu] : %s\n", pthread_self(), (char*)this->arg_);
		Sleep(1000);
		return 0;
	}
};


int main()
{
	cout << "begin" << endl;
	char szTmp[] = "hello world";
	Mytask taskobj;
	taskobj.setArg((void*)szTmp);

	lz::ThreadPool threadPool(10);
	threadPool.start();

	for (int i = 0; i < 200; i++) {
		threadPool.addTask(&taskobj);
	}

	while (1) {
		printf("there are still %d tasks need to process\n", threadPool.size());
		if (threadPool.size() == 0) {
			threadPool.stop();
			printf("now i will exit from main\n");
			exit(0);
		}
		Sleep(5000);
	}
	cout << "end" << endl;
	return 0;
}