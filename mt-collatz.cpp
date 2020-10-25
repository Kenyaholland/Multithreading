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
void threadFunction(unsigned int param); //calls collatz, uses locks, updates counter and updates histogram with stop times
void toLock();
void toUnlock();

std::mutex lock; //to prevent race conditions
const int K = 1001; //size of histogram array
int histogram[K] = {0}; //keeps track of stop times
std::atomic<unsigned int> counter (2); //global counter for threads to allocate
bool noLock = false; //will determine if locks are used

int testNum = 0;

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
	std::vector<std::thread> threads;
	for(int i = 0; i < T; i++){
		threads.push_back(std::thread(threadFunction,N));
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

void threadFunction(unsigned int param){
	int stopTime = 0;
	unsigned int num;
	
	toLock();
	num = counter++;
	toUnlock();
	
	//calculate stoptimes for 1 - N and update counter and histogram per collatz call
	while(num < param){
		stopTime = collatz(num);
		
		toLock();
		histogram[stopTime] += 1;
		num = counter++;
		toUnlock();
	}
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

void toLock(){
	//locks by default
	//will not execute when user input -nolock
	if(!noLock){
		lock.lock();
	}
}

void toUnlock(){
	//unlocks by default
	//will not execute when user input -nolock
	if(!noLock){
		lock.unlock();
	}
}