CC=g++

LDFLAGS="-L/opt/homebrew/opt/libomp/lib"
CPPFLAGS="-I/opt/homebrew/opt/libomp/include"

threads ?= 1

main:
	$(CC)  -DNUMT=$(threads) -Xpreprocessor  -fopenmp   $(CPPFLAGS)  $(LDFLAGS)  -lomp   *.cpp  -o  main

clean:
	rm -rf main
	rm -rf *.o
