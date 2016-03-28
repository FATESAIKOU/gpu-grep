# author      : p2p
# date        : 2016/03/16
# description : a makefile

# GNU compilation info
CC     = gcc
INC    = -lm
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
	$(CC) -O3 -g -o $@ $^ $(CUDA_LIB) $(INC)
	rm -f *.o

$(OBJ)/%.o: $(HOST)/%.c
	$(CC) -O3 -g -c -o $@ $< $(CFLAGS)

threadCtl.o: $(KERNEL)/threadCtl.cu
	$(NVCC) -O3 -g -c -o $@ $<

matching.o: $(DEVICE)/matching.cu
	$(NVCC) -O3 -g -c -o $@ $< $(CFLAGS)

clean:
	rm -f gpu-grep *.o

