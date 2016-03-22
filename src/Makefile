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

# flex compilation info
LEX = flex
LEX_LIB = -ll

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

$(OUT): main.c $(patsubst %, %.o, $(H_LIB) $(K_LIB) $(D_LIB)) fileParser.o
	$(CC) -o $@ $^ $(CUDA_LIB) $(LEX_LIB)
	rm -f *.o ./flex/fileParser.c

$(OBJ)/%.o: $(HOST)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

threadCtl.o: $(KERNEL)/threadCtl.c
	$(CC) -c -o $@ $< $(LEX_LIB)

matching.o: $(DEVICE)/matching.cu
	$(NVCC) -c -o $@ $< $(CFLAGS)

fileParser.o: ./flex/fileParser.l
	$(LEX) -o ./flex/fileParser.c $<
	$(CC) -c -o $@ ./flex/fileParser.c -ll

clean:
	rm -f gpu-grep *.o ./flex/fileParser.c

