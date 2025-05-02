CC=g++ --std=c++17
TARGET=project-4

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	CPPFLAGS=-fopenmp -lm
else
	CPPFLAGS=-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
endif

arraysize ?= 1000

PARAMETERS=-DARRAYSIZE=$(arraysize)

main:
	$(CC) $(CPPFLAGS) $(PARAMETERS) *.cpp -o $(TARGET)

clean-no-csv:
	rm -rf $(TARGET)
	rm -rf *.o

clean:
	rm -rf $(TARGET)
	rm -rf *.o
	rm -rf *.csv
