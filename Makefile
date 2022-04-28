all: main

main: main.o
	g++ main.cpp -std=c++11 -o deadlock-detect

clean:
	rm main.o deadlock-detect