CC=g++

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lm
	CPPFLAGS=
else
	LDFLAGS=-L/opt/homebrew/opt/libomp/lib -lomp
	CPPFLAGS=-I/opt/homebrew/opt/libomp/include -Xpreprocessor
endif

threads ?= 1

main:
	$(CC)  -DNUMT=$(threads) -fopenmp $(CPPFLAGS) $(LDFLAGS) *.cpp -o main

clean:
	rm -rf main
	rm -rf *.o
