#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <mutex>
#include <pthread.h>
#include <thread>
#include <iomanip>
#include <atomic>
#include "functions.hpp"
#include <vector>

int collatz(int n);
void* threadFunction(void* param);

std::mutex lock;
const int K = 501;
int histogram[K] = {0};
std::atomic<int> counter (2);
bool noLock = false;

int main(int argc, char **argv){
	struct timespec time[2];
	clock_gettime(CLOCK_REALTIME,time);
	
	Functions function;
	int N = 0;
	int T = 0;
	function.CheckArgs(argc,argv);
	function.Init(argc,argv,N,T,noLock);
	
	int *n = &N;
	std::vector<std::thread> threads;
	for(int i = 0; i < T; i++){
		
		threads.push_back(std::thread(threadFunction,(void*)n));
	}
	for(int j = 0; j < T; j++){
		threads.at(j).join();
	}
	
	clock_gettime(CLOCK_REALTIME,time+1);
	double diff = function.Clock(time);

	function.PrintHistogram(histogram,K,N,T,diff);
}

void* threadFunction(void* param){
	int* num = (int*)param;
	int stopTime = 0;
	
	while(counter < *num){
		if(!noLock){
			lock.lock();
		}
		stopTime = collatz(counter);
		std::cout << counter << std::endl;
		counter++;
		histogram[stopTime] += 1;
		if(!noLock){
			lock.unlock();
		}
	}
	pthread_exit(0);
}

int collatz(int n){
	
	int stopTime = 0;
	
	while(n != 1){
		if(n % 2 == 0){
			n /= 2;
			stopTime++;
		}
		else{
			n = 3*n + 1;
			stopTime++;
		}
	}

	return stopTime;
}
