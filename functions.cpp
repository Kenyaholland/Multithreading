/** @file functions.cpp
 *  @brief This class has a sole purpose of seperating code from main to make it easier to read.
 *
 *	This class reads in arguments for error checking, assigns N and T variables and checks for "-nolock",
 *	contains functionality for the timer of this program, and prints out the results (histogram and total time). 
 *
 *  @author Thati Vang (tv20)
 *  @author Kenya Holland (kmh99)
 */

#include "functions.hpp"

void Functions::CheckArgs(int argc, char** argv){
	if(argc < 3){
		std::cout << "Please enter values for N and T.\n";
		exit(0);
	}
	
	if(atoi(argv[1]) == 0 || atoi(argv[2]) == 0){
		std::cout << "Both N and T must be a number.\n";
		exit(0);
	}
	else if(atoi(argv[2]) > 30 || atoi(argv[2]) < 1){
		std::cout << "T must be 1 - 30\n";
		exit(0);
	}
}

void Functions::Init(int argc, char** argv, unsigned int &N, int &T, bool &noLock){
	N = atoi(argv[1]);
	T = atoi(argv[2]);
	
	std::string toLock = "-nolock";
	std::string toCompare;
	
	for(int i = 0; i < argc; i++){
		toCompare = *(argv+i);
		
		if(toCompare == toLock){
			noLock = true;
			break;
		}
	}
}

double Functions::Clock(struct timespec *time){
	double nano = 1000000000;
	double nanoSec = static_cast<double>((time[1].tv_nsec - time[0].tv_nsec)) / nano;
	double diff = static_cast<double>((time[1].tv_sec - time[0].tv_sec)) + nanoSec;
	return diff;
}

void Functions::PrintHistogram(int *histogram,int K, unsigned int N, int T, double diff){
	//display histogram
	for(int i = 1; i < K; i++){
		std::cout << i << "," << histogram[i] << std::endl;
	}
	
	//display range, number of threads, and time it took.
	std::cerr << N << "," << T << "," << diff << std::endl;
}