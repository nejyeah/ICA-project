#Filename:Makefile
CXX=g++
CX=mpicxx
CC=mpicc
FC=gfortran
DEBUG= -g
CFLAGS= -Wall -c $(DEBUG) 
LFLAGS= -Wall $(DEBUG)
LDFLAGS=-pthread
MODEL=-std=c++11
HPATH=../include
LIB1=../lib/libcblas.a
LIB2=../lib/libatlas.a

loaddata:
	$(CXX) $(CFLAGS) -I $(HPATH) dataset.cpp dataset_CIFAR_10.cpp dataset_stl10.cpp
	#$(CXX) loaddata.cpp -I$(HPATH) -o loaddata `pkg-config --cflags --libs opencv` dataset.o dataset_CIFAR_10.o dataset_stl10.o
	$(CXX) loaddata.cpp -I$(HPATH) -o loaddata dataset.o dataset_CIFAR_10.o dataset_stl10.o
	
hpc_first:
	$(CX) $(CFLAGS) -I $(HPATH) HPC.cpp train_hpc_firstlayer.cpp 
	$(CX) -o train_hpc_firstlayer HPC.o train_hpc_firstlayer.o $(LIB1) $(LIB2) -lm
	scp train_hpc_firstlayer root@gpu-server3:/home/common/nej/cpluscode/src1	
	mpirun_rsh -np 44 -hostfile hostfile MV2_CPU_BINDING_POLICY=scatter ./train_hpc_firstlayer

hpc_second:
	$(CX) $(CFLAGS) -I $(HPATH) HPC.cpp train_hpc_secondlayer.cpp 
	$(CX) -o train_hpc_secondlayer HPC.o train_hpc_secondlayer.o $(LIB1) $(LIB2) -lm
	scp train_hpc_secondlayer root@gpu-server3:/home/common/nej/cpluscode/src1	
	mpirun_rsh -np 40 -hostfile hostfile MV2_CPU_BINDING_POLICY=scatter ./train_hpc_secondlayer

hpc_third:
	$(CX) $(CFLAGS) -I $(HPATH) HPC.cpp train_hpc_thirdlayer.cpp 
	$(CX) -o train_hpc_thirdlayer HPC.o train_hpc_thirdlayer.o $(LIB1) $(LIB2) -lm
	scp train_hpc_thirdlayer root@gpu-server3:/home/common/nej/cpluscode/src1	
	mpirun_rsh -np 36 -hostfile hostfile MV2_CPU_BINDING_POLICY=scatter ./train_hpc_thirdlayer

minist_test1:
	$(CX) $(CFLAGS) -I $(HPATH) HPC.cpp test_minist1.cpp 
	$(CX) -o test_minist1 HPC.o test_minist1.o $(LIB1) $(LIB2) -lm
	scp test_minist1 root@gpu-server3:/home/common/nej/cpluscode/src
	mpirun_rsh -np 10 -hostfile hostfile MV2_CPU_BINDING_POLICY=scatter ./test_minist1

minist_test2:
	$(CX) $(CFLAGS) -I $(HPATH) HPC.cpp test_minist2.cpp 
	$(CX) -o test_minist2 HPC.o test_minist2.o $(LIB1) $(LIB2) -lm
	scp test_minist2 root@gpu-server3:/home/common/nej/cpluscode/src
	mpirun_rsh -np 12 -hostfile hostfile MV2_CPU_BINDING_POLICY=scatter ./test_minist2

minist_test3:
	$(CX) $(CFLAGS) -I $(HPATH) HPC.cpp test_minist3.cpp 
	$(CX) -o test_minist3 HPC.o test_minist3.o $(LIB1) $(LIB2) -lm
	scp test_minist3 root@gpu-server3:/home/common/nej/cpluscode/src
	mpirun_rsh -np 4 -hostfile hostfile MV2_CPU_BINDING_POLICY=scatter ./test_minist3

hpc_minist1:
	$(CX) $(CFLAGS) -I $(HPATH) HPC.cpp train_minist1.cpp 
	$(CX) -o train_minist1 HPC.o train_minist1.o $(LIB1) $(LIB2) -lm
	scp train_minist1 root@gpu-server2:/home/common/nej/cpluscode/src	
	mpirun_rsh -np 10 -hostfile hostfile MV2_CPU_BINDING_POLICY=scatter ./train_minist1
	
hpc_minist2:
	$(CX) $(CFLAGS) -I $(HPATH) HPC.cpp train_minist2.cpp 
	$(CX) -o train_minist2 HPC.o train_minist2.o $(LIB1) $(LIB2) -lm
	scp train_minist2 root@gpu-server2:/home/common/nej/cpluscode/src	
	mpirun_rsh -np 12 -hostfile hostfile MV2_CPU_BINDING_POLICY=scatter ./train_minist2

hpc_minist3:
	$(CX) $(CFLAGS) -I $(HPATH) HPC.cpp train_minist3.cpp 
	$(CX) -o train_minist3 HPC.o train_minist3.o $(LIB1) $(LIB2) -lm
	scp train_minist3 root@gpu-server2:/home/common/nej/cpluscode/src	
	mpirun_rsh -np 4 -hostfile hostfile MV2_CPU_BINDING_POLICY=scatter ./train_minist3

logistic:
	$(CXX) $(CFLAGS) -I $(HPATH) logistic.cpp train_logistic.cpp 
	$(CXX) -o train_logistic logistic.o train_logistic.o $(LIB1) $(LIB2) -lm
	./train_logistic

sfm:
	$(CXX) $(CFLAGS) -I $(HPATH) softmax.cpp train_softmax.cpp 
	$(CXX) -o train_softmax softmax.o train_softmax.o $(LIB1) $(LIB2) -lm
	./train_softmax

test:
	$(CXX) $(LFLAGS) test.cpp -o test
	./test


maximization:
	$(CXX) $(CFLAGS) -I $(HPATH) HPC.cpp maximization_mnist.cpp 
	$(CXX) -o maximization_mnist HPC.o maximization_mnist.o $(LIB1) $(LIB2) -lm
	#scp maximization_mnist root@gpu-server2:/home/common/nej/cpluscode/src
	./maximization_mnist

cleanall:
	rm -f *.o train_hpc_firstlayer train_hpc_secondlayer train_hpc_thirdlayer test_hpc1 test_hpc2 test_hpc3 test train_logistic train_softmax train_minist1 train_minist2 train_minist3 test_minist1 test_minist2 test_minist3 maximization_mnist
