#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <pthread.h>
#include <iomanip>
#include "functions.hpp"

void* collatz(void *param);

pthread_mutex_t lock;
const int K = 1001;
int histogram[K] = {0};
int counter = 2;
bool noLock = false;

int main(int argc, char **argv){
	struct timespec time[2];
	clock_gettime(CLOCK_REALTIME,time);
	
	Functions function;
	int N = 0;
	int T = 0;
	function.CheckArgs(argc,argv);
	function.Init(argc,argv,N,T,noLock);
	
	//creates one thread
	int x = 3;
	int *n = &x;
	pthread_t tid;
	pthread_create(&tid,NULL,collatz,(void*)n);
	pthread_join(tid,NULL);
	
	clock_gettime(CLOCK_REALTIME,time+1);
	double diff = function.Clock(time);

	function.PrintHistogram(histogram,K,N,T,diff);
}

void* collatz(void *param){
	int *n = (int*)param;
	int stopTime = 0;
	
	while(*n != 1){
		if(*n % 2 == 0){
			*n /= 2;
			stopTime++;
		}
		else{
			*n = 3*(*n) + 1;
			stopTime++;
		}
	}
	
	if(!noLock){
		pthread_mutex_lock (&lock);
		std::cout << "locked\n";
	}
	else{
		std::cout << "not locked\n";
	}
	
	histogram[stopTime] += 1;
	counter++;
	
	if(!noLock){
		pthread_mutex_unlock(&lock);
		std::cout << "then unlocked \n";
	}
	
	pthread_exit(0);
}