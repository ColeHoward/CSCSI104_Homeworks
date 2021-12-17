all: stringparser

stringparser: stringparser.cpp ulliststr.o stackstring.o
	g++ -g -Wall stringparser.cpp ulliststr.o stackstring.o -o stringparser

stackstring.o: stackstring.h stackstring.cpp ulliststr.o
	g++ -g -Wall -c stackstring.cpp ulliststr.o -o stackstring.o

ulliststr.o: ulliststr.h ulliststr.cpp
	g++ -g -Wall -c ulliststr.cpp -o ulliststr.o