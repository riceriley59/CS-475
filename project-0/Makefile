CC=g++

threads ?= 1
UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	CPPFLAGS=-fopenmp -lm
else
	CPPFLAGS=-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
endif

main:
	$(CC) -DNUMT=$(threads) $(CPPFLAGS) *.cpp -o main

clean:
	rm -rf main
	rm -rf *.o
