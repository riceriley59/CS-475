CC=g++ --std=c++17
TARGET=project-3

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	CPPFLAGS=-fopenmp -lm
else
	CPPFLAGS=-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
endif

threads ?= 2
capitals ?= 5

main:
	$(CC) $(CPPFLAGS) -DNUMT=$(threads) -DNUMCAPITALS=$(capitals) *.cpp -o $(TARGET)

clean:
	rm -rf main
	rm -rf *.o
