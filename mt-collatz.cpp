#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <pthread.h>
#include <iomanip>
#include <atomic>
#include "functions.hpp"

int collatz(int n);
void* threadFunction(void* param);

pthread_mutex_t lock;
const int K = 501;
int histogram[K] = {0};
std::atomic<int> counter (2);
bool isLocked = false;

int main(int argc, char **argv){
	struct timespec time[2];
	clock_gettime(CLOCK_REALTIME,time);
	
	Functions function;
	int N = 0;
	int T = 0;
	function.CheckArgs(argc,argv);
	function.Init(argc,argv,N,T,isLocked);
	
	int x = 3;
	int *n = &x;
	pthread_t tid;
	for(int i = 0; i < T; i++){
		std::cout << "Making thread " << i << std::endl;
		pthread_create(&tid+i,NULL,threadFunction,(void*)n);
		pthread_join(tid+i,NULL);
	}
	
	clock_gettime(CLOCK_REALTIME,time+1);
	double diff = function.Clock(time);

	function.PrintHistogram(histogram,K,N,T,diff);
}

void* threadFunction(void* param){
	int* num = (int*)param;
	int stopTime = 0;
	int n = 0;
	
	while(counter < *num){
		pthread_mutex_lock (&lock);
		n = counter;
		stopTime = collatz(n);
		histogram[stopTime] += 1;
		std::cout << "Value at " << stopTime << ": " << histogram[stopTime] << std::endl;
		counter++;
		pthread_mutex_unlock (&lock);
	}
	pthread_exit(0);
}

int collatz(int n){
	int stopTime = 1;
	
	if(n == 1){
		return stopTime;
	}
	else if(n % 2 == 0){
		n = n / 2;
		stopTime++;
		collatz(n);
	}
	else{
		n = 3*(n) + 1;
		stopTime++;
		collatz(n);
	}
	return 0;
}
