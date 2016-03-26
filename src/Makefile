# author      : p2p
# date        : 2016/03/16
# description : a makefile

# GNU compilation info
CC     = gcc
INC    = -Iinc
CCFLAGS =

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

$(OUT): main.c $(patsubst %, %.o, $(H_LIB) $(K_LIB) $(D_LIB))
	$(CC) -g -o $@ $^ $(CUDA_LIB) $(LEX_LIB)

$(OBJ)/%.o: $(HOST)/%.c
	$(CC) -g -c -o $@ $< $(CFLAGS)

threadCtl.o: $(KERNEL)/threadCtl.c
	$(CC) -g -c -o $@ $< $(LEX_LIB)

matching.o: $(DEVICE)/matching.cu
	$(NVCC) -g -c -o $@ $< $(CFLAGS)

clean:
	rm -f gpu-grep *.o

