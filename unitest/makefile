CXX=g++
CFLAGS=-std=c++11

SRC=$(wildcard *.hpp)
TARGET=$(patsubst %.cpp,%,$(SRC))

all: $(SRC) main.cpp
	g++ -g $(CFLAGS) -o test main.cpp -I../
	./test

clean:
	rm -rf $(TARGET)
