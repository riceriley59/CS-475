CC=g++

LDFLAGS="-L/opt/homebrew/opt/libomp/lib"
CPPFLAGS="-I/opt/homebrew/opt/libomp/include"

main:
	$(CC)  -Xpreprocessor  -fopenmp   $(CPPFLAGS)  $(LDFLAGS)  -lomp   *.cpp  -o  main
