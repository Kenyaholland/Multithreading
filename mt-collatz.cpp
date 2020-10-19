#include <iostream>

int main(int argc, char *argv[]){

	std::string command;
	
	//loops if string is empty
	do{
		std::cout << "\n$$$ ";
		std::getline(std::cin, command);
		
		//will not execute if there was no user input
		if(!command.empty()){
			//do something
			
			//if user entered "exit", program will terminate
			//CheckExit();
		}
	}while(command.empty());
	
	//checks for "-Debug" and if ture, will print parameter values
	std::string debug = "-nolock";
	std::string toCompare;
	
	for(int i = 0; i < argc; i++){
		toCompare = *(argv+i);	
		
		if(toCompare == debug){
			//do something
			break;
		}
	}
}