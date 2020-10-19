CXX = g++
CXXFLAGS = -std=c++11 -Wall

#OBJECTS = 

mt-collatz: mt-collatz.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) *.o *.txt myshell