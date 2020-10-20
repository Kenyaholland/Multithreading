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