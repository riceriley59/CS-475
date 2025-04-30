CC=g++ --std=c++17
TARGET=project-3

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	CPPFLAGS=-fopenmp -lm
else
	CPPFLAGS=-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
endif

threads ?= 1
capitals ?= 5
csv ?= false

main:
	$(CC) $(CPPFLAGS) -DNUMT=$(threads) -DNUMCAPITALS=$(capitals) $(if $(filter true, $(csv)), -DCSV) *.cpp -o $(TARGET)

clean-no-csv:
	rm -rf $(TARGET)
	rm -rf *.o

clean:
	rm -rf $(TARGET)
	rm -rf *.o
	rm -rf *.csv
