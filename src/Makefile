CC     = gcc
INC    = -Iinc
CCFLAG =

NVCC   = nvcc

CUDA_LIB = -lcudart -L/usr/local/cuda/lib64

HOST   = ./lib/host
KERNEL = ./lib/kernel
DEVICE = ./lib/device

H_LIB = init jobControl packer parser ranker
K_LIB = threadCtl
D_LIB = matching

OUT = ./gpu-grep
OBJ = ./

#$(OUT): $(H_OBJS) $(K_OBJS) $(D_OBJS)
#	echo 'Hello World!'

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
