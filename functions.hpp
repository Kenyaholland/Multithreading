/** @file functions.hpp
 *  @brief This class has a sole purpose of seperating code from main to make it easier to read.
 *
 *	This class reads in arguments for error checking, assigns N and T variables and checks for "-nolock",
 *	contains functionality for the timer of this program, and prints out the results (histogram and total time). 
 *
 *  @author Thati Vang (tv20)
 *  @author Kenya Holland (kmh99)
 */

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

//includes
#include <iostream>
#include <cstdlib>
#include <iomanip>

class Functions{
	public:
		/** @brief Does error checking for the command line input
		 *  
		 *	Ensures that a value is entered for N and T after ./mt-collatz.
		 *	Ensured that N and T are numbers and that T is between values 1 and 30.
		 *
		 *  @param int argc from command line input
		 *	@param char** argv[] from command line input
		 */
		void CheckArgs(int, char**);
		
		/** @brief Assigns N and T to appropriate values given from command line input and checks for nolock
		 *
		 *  @param int argc from command line input
		 *	@param char** argv[] from command line input
		 *	@param unsigned int N range of numbers collatz will run
		 *	@param int T number of threads to create
		 *	@param bool noLock checks if program will do locking mechanism
		 */
		void Init(int, char**, unsigned int&, int&, bool&);
		
		/** @brief Calculates time program took to run
		 *  
		 *	Function calculates the time program took to complete in nanoseconds
		 *
		 *  @param struct timespec* time time in nanoseconds
		 */
		double Clock(struct timespec*);
		
		/** @brief Displays histogram and conluding results
		 *  
		 *	This function loops through each position in histogram and displays it's contents
		 *	Then an stderr displays the values that were tested(N), the number of threads created,
		 *	and how long the program took to complete.
		 *
		 *  @param int* histogram sequence of numbers from 1 - 500
		 *	@param int K position in histogram array
		 *	@param unsigned int N range of numbers collatz will run
		 *	@param int T number of threads to create
		 *	@param double diff time program took to run
		 *	@return double the amount of time it took to run program in nanoseconds
		 */
		void PrintHistogram(int*, int, unsigned int, int, double);
};

#endif