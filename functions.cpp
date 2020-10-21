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
	else{
		if(atoi(argv[2]) > 30 || atoi(argv[2]) < 1){
			std::cout << "T must be 1 - 30\n";
			exit(0);
		}
	}
}

void Functions::Init(int argc, char** argv, int &N, int &T, bool &noLock){
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

void Functions::PrintHistogram(int *histogram,int K, int N, int T, double diff){
	for(int i = 1; i < K; i++){
		if(histogram[i] > 0) //delete this line when done
		std::cout << "K = " << i << ", " << histogram[i] << std::endl;
	}
	std::cout << N << "," << T << "," << diff << std::endl;
}