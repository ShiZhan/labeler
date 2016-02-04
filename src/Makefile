CC = g++

CXXFLAGS = --std=c++11 -O3

TEST_TEXT = "jingle bells, jingle bells, jingle all the way."

all:
	make labeler n-gram

labeler: labeler.cpp
	$(CC) labeler.cpp $(CXXFLAGS) -o labeler

n-gram: n-gram.cpp
	$(CC) n-gram.cpp $(CXXFLAGS) -o n-gram

test:
	make labeler
	echo $(TEST_TEXT) | ./text-alignment | ./labeler
	make n-gram
	echo $(TEST_TEXT) | ./text-alignment | ./n-gram | sort | uniq -c

clean:
	rm *.exe *.o labeler n-gram
