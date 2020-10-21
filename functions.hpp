#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <cstdlib>
#include <iomanip>

class Functions{
public:
	void CheckArgs(int,char**);
	void Init(int,char**,int&,int&,bool&);
	double Clock(struct timespec*);
	void PrintHistogram(int*,int,int,int,double);
};

#endif
/*

void * threadFunction(void *param);
int collatz(int);
int count = 2;

int main{
	N = 100;
	T = 2;
	int *n = &N;
	
	pthread_t tid[T];
	
	//for loop
		pthread_create(tid+i,NULL,threadFunction,(void*)n);
	
	//for loop
	pthread_join(tid[i],NULL);

}

void * threadFunction(void *param){
	int *num = (int*)param;
	//if count < *num && !isLocked
		//lock count
	//while(count < *num){
		//call collatz(count)
		//lock histogram
		//update histogram
		//unlock histogram
	//}

	
	//end thread
}

int collatz(int n){
	//count++
	//if !isLocked
		//unlock count
	//calculate collatz
	//return the number
}
*/