CXX = g++
CFLAGS = -Wall -Werror -std=c++11 -fPIC


INCLUDE = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LDLIBS = -lcurl


all: vk

vk: api.o attachment.o
	$(CXX) $(INCLUDE) $(CFLAGS) $(LDFLAGS) $(LDLIBS) api.o attachment.o -o ../vk.so -shared

api.o: api.h api.cpp json.hpp attachment.h
	$(CXX) $(INCLUDE) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c api.cpp

attachment.o: attachment.h attachment.cpp json.hpp
	$(CXX) $(INCLUDE) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c attachment.cpp

clean:
	rm -rf *.o hello
