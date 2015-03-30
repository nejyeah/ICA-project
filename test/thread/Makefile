#Filename:Makefile
CXX=g++
DEBUG= -g
CFLAGS= -Wall -c $(DEBUG)
LFLAGS= -Wall $(DEBUG)
LIB=../lib/cs106lib.a
MODEL=-std=c++11
HPATH=../include
PROG=project
OBJS=$(PROG).o
LDFLAGS=-pthread

hello:
	$(CXX) $(CFLAGS) thread_hello.cpp $(MODEL)
	$(CXX) $(LDFLAGS) -o hello thread_hello.o $(MODEL)

hello1:
	$(CXX) $(CFLAGS) thread_hello1.cpp $(MODEL)
	$(CXX) $(LDFLAGS) -o hello1 thread_hello1.o $(MODEL)


cleanall:
	rm -f *.o hello
