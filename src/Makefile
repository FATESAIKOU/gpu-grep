# author      : p2p
# date        : 2016/03/16
# description : a makefile

# GNU compilation info
CC     = gcc
INC    = -Iinc
CCFLAG =

# Nvidia compilation info
NVCC   = nvcc
CUDA_LIB = -lcudart -L/usr/local/cuda/lib64

# defination of each lib path
HOST   = ./lib/host
KERNEL = ./lib/kernel
DEVICE = ./lib/device

# defination of each library
H_LIB = init jobControl packer parser ranker
K_LIB = threadCtl
D_LIB = matching

# output path
OUT = ./gpu-grep
OBJ = ./

$(OBJ)/%.o: $(HOST)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.o: $(KERNEL)/%.cu
	$(NVCC) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.o: $(DEVICE)/%.cu
	$(NVCC) -c -o $@ $< $(CFLAGS)

$(OUT): main.c $(patsubst %, %.o, $(H_LIB) $(K_LIB) $(D_LIB))
	$(CC) -o $@ $^ $(CUDA_LIB)
	rm -f $(shell ls *.o)

clean:
	rm -f gpu-grep *.o
