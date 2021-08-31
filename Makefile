cc:=g++

TARGET:=libnoicpputils.so

SRCS=$(wildcard src/*.cpp)
SRCS_NO_PATH=$(notdir $(SRCS))
OBJS=$(patsubst %.cpp, %.o, $(SRCS_NO_PATH))

$(TARGET):$(OBJS)
	$(cc) -shared -fPIC $^ -Iinclude -o $@

%.o:src/%.cpp
	@echo $^
	$(cc) -Iinclude -c $^ -o $@

.PHONY:clean
.PHONY:test
clean:
	rm -rf $(TARGET) *.o

test:
	$(cc) -L. -Iinclude test.cpp -lnoicpputils -o test
	./test
