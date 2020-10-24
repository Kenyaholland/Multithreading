CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall

OBJECTS = functions.o

mt-collatz: mt-collatz.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) *.o mt-collatz