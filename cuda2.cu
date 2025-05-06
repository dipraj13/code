#include <stdio.h>
#include <cuda.h>
#define N 16

__global__ void mul(int *a,int *b,int *c,int width){
	int rows = threadIdx.y + blockIdx.y * blockDim.y;
	int cols = threadIdx.x + blockIdx.x * blockDim.x;
	
	int sum = 0;

	if(rows < width && cols < width){
		for(int k = 0;k < width;k++)
			sum += a[rows * width + k] * b[k * width + cols];
		c[rows * width + cols] = sum;
	}	
}

int main(){
	int size = N * N *sizeof(int);
	int h1[N*N], h2[N*N], h3[N*N];
	
	for(int i = 0;i < N*N;i++){
		h1[i] = 1;
		h2[i] = 2;
	}
	
	int *d1,*d2,*d3;
	
	cudaMalloc((void**)&d1,size);
	cudaMalloc((void**)&d2,size);
	cudaMalloc((void**)&d3,size);
	
	cudaMemcpy(d1,h1,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d2,h2,size,cudaMemcpyHostToDevice);
	
	dim3 threadsPerBlock(16,16);
	dim3 blocksPerGrid((N+15)/16,(N+15)/16);
	
	mul<<<blocksPerGrid, threadsPerBlock>>>(d1,d2,d3,N);
	
	cudaMemcpy(h3,d3,size,cudaMemcpyDeviceToHost);
	
	printf("Output : %d",h2[12]);
	
	cudaFree(d1);
	cudaFree(d2);
	cudaFree(d3);
	
	return 0;
}
