/** @file mt-collatz.cpp
 *  @brief This class contains the main of the program. 
 *
 *  @author Thati Vang (tv20)
 *  @author Kenya Holland (kmh99)
 */

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

/** @brief returns stop times, which are used to update histogram
 *
 *	returns stop time of n. n is determined by whatever global variable counter is.
 *	
 *  @param unsigned int n value passed in depending on counter
 *	@return int stop time for a given value
 */
int collatz(unsigned int n);

/** @brief calls collatz, uses locks, updates counter and updates histogram with stop times
 *	
 *	This is the function that is called when each thread is created.
 *	
 *  @param void* param set equal to N, the range of numbers collatz will run
 */
void* threadFunction(void* param); //calls collatz, uses locks, updates counter and updates histogram with stop times

std::mutex lock; //to prevent race conditions
const int K = 501; //size of histogram array
int histogram[K] = {0}; //keeps track of stop times
std::atomic<unsigned int> counter (2); //global counter for threads to allocate
bool noLock = false; //will determine if locks are used

int main(int argc, char **argv){
	
	//start time
	struct timespec time[2];
	clock_gettime(CLOCK_REALTIME,time);
	
	//gather information and assign variables
	Functions function;
	unsigned int N = 0;
	int T = 0;
	function.CheckArgs(argc,argv);
	function.Init(argc,argv,N,T,noLock);
	
	//begin multithreading
	unsigned int *n = &N;
	std::vector<std::thread> threads;
	for(int i = 0; i < T; i++){
		
		threads.push_back(std::thread(threadFunction,(void*)n));
	}
	
	//join all threads
	for(int j = 0; j < T; j++){
		threads.at(j).join();
	}
	
	//calculate time it took to run program
	clock_gettime(CLOCK_REALTIME,time+1);
	double diff = function.Clock(time);

	//display results
	function.PrintHistogram(histogram,K,N,T,diff);
}

void* threadFunction(void* param){
	unsigned int* num = (unsigned int*)param;
	int stopTime = 0;
	
	//calculate stoptimes for 1 - N and update counter and histogram per collatz call
	while(counter < *num){
		if(!noLock){
			lock.lock();
		}
		counter++;
		histogram[stopTime] += 1;
		if(!noLock){
			lock.unlock();
		}
	}
	
	pthread_exit(0);
}

int collatz(unsigned int n){
	
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
