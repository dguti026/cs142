CC = g++
CFLAGS = -O2 -mcx16 -march=native -DCILK -fcilkplus -std=c++11

all:	reduce scan qsort

reduce:	reduce.cpp
	$(CC) $(CFLAGS) -DNDEBUG reduce.cpp -o reduce
	
scan:	scan.cpp scan.h
	$(CC) $(CFLAGS) -DNDEBUG scan.cpp -o scan

qsort:	quicksort.cpp qsort.h
	$(CC) $(CFLAGS) -DNDEBUG quicksort.cpp -o qsort

Ex_2.2: Ex_2.2.cpp
	$(CC) $(CFLAGS) -DNDEBUG Ex_2.2.cpp -o Ex_2.2

clean:
	rm -f reduce scan qsort Ex_2.2
