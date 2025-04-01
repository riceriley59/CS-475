CC=g++

threads ?= 2
trials ?= 50000

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	CPPFLAGS=-fopenmp -lm
else
	CPPFLAGS=-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
endif

main:
	$(CC) -DNUMT=$(threads) -DNUMTRIALS=$(trials) $(CPPFLAGS) *.cpp -o main

clean:
	rm -rf main
	rm -rf *.o
