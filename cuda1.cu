#include <stdio.h>
#include <cuda.h>

__global__ void add(int *a, int* b, int* c,int n){
	int id = threadIdx.x + blockIdx.x * blockDim.x;
	if(id < n){
		c[id] = a[id] + b[id];
	}
}

int main(){
	int n = 1 << 20;
	int size = n * sizeof(int);
	
	int *h1 = (int*) malloc(size);
	int *h2 = (int*) malloc(size);
	int *h3 = (int*) malloc(size);
	
	for(int i =0;i<n;i++){
		h1[i] = i;
		h2[i] = 2* i;
	}
	int *d1,*d2,*d3;
	
	cudaMalloc((void**)&d1,size);
	cudaMalloc((void**)&d2,size);
	cudaMalloc((void**)&d3,size);
	
	cudaMemcpy(d1,h1,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d2,h2,size,cudaMemcpyHostToDevice);
	
	add<<<(n+255)/256,256>>>(d1,d2,d3,n);
	
	cudaMemcpy(h3,d3,size,cudaMemcpyDeviceToHost);
	
	printf("Samp Out : %d + %d = %d \n",h1[12],h2[12],h3[12]);
	
	cudaFree(d1);
	cudaFree(d2);
	cudaFree(d3);
	
	free(h1);
	free(h2);
	free(h3);
	
	return 0;
		
}
