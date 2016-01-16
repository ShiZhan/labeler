CC = g++

CXXFLAGS = --std=c++11 -O3

all:
	make labeler

labeler: labeler.cpp
	$(CC) labeler.cpp $(CXXFLAGS) -o labeler

test:
	make labeler
	echo "this is a test, test a string for this program." | ./labeler

clean:
	rm *.exe *.o labeler
