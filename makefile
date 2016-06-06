all: closestPair randData

closestPair: main.cpp
	g++ -std=c++11 main.cpp -o closestPair

randData: randData.cpp
	g++ -std=c++11 randData.cpp -o randData
