#################################                                                                                                                                                 
#  Compiler, tools and options  #
#################################

CXX = g++ 
DEBUG = -g
CFLAGES = -Wall -c $(DEBUG)
LFLAGES = -Wall $(DEBUG)
LINK = g++ 
CXXFLAGES = -O3 -DADD_
MC = mpicc
MCXX=mpicxx
BLASPATH = /opt/atlas/
INCLUDE = $(BLASPATH)include
CBLIB = $(BLASPATH)lib/libcblas.a $(BLASPATH)lib/libatlas.a
####### Compile
LIB1=/home/nej/wf/deeplearning/blas/CBLAS/lib/cblas_LINUX.a
LIB2=/home/nej/wf/deeplearning/blas/BLAS/blas_LINUX.a


show:
	$(CXX) $(CFLAGES) show.cpp
	$(LINK) -o show show.o `pkg-config --libs opencv`
	./show

loaddata_w:
	$(CXX) $(CFLAGES) loaddata_w.cpp
	$(LINK) -o loaddata_w loaddata_w.o `pkg-config --libs opencv`

get_feature:
	$(CXX) $(CFLAGES) -I ../include get_feature.cpp
	$(LINK) -o get_feature get_feature.o `pkg-config --libs opencv` $(LIB1) $(LIB2) /usr/lib/gcc/i686-linux-gnu/4.6/libgfortran.so 
	./get_feature

process:
	$(CXX) $(CFLAGES) -I ../include process_image.cpp image.cpp
	$(LINK) -o process_image process_image.o image.o  `pkg-config --libs opencv` $(LIB1) $(LIB2) /usr/lib/gcc/i686-linux-gnu/4.6/libgfortran.so 
	./process_image

test:
	$(CXX) test.cpp -o test

gray:
	$(CXX) gray_picture.cpp -o gray_picture

read_w:
	$(CXX) read_w.cpp -o read_w

get_top:
	$(CXX) get_top.cpp -o get_top
	./get_top

get_max:
	$(CXX) get_max_mnist.cpp -o get_max_mnist
	./get_max_mnist

cleanall:
	rm -f *.o show loaddata_w get_feature test gray_picture read_w get_top get_max_mnist process_image
