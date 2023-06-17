CXX=g++
CFLAGS=-g -std=c++20

SRC=$(wildcard *.cpp)
TARGET=$(patsubst %.cpp,%.out,$(SRC))

all: $(TARGET)
	@echo done

%.out : %.cpp
	$(CXX) $(CFLAGS) -o $@ $<
	./$@

clean:
	rm -rf $(TARGET)
