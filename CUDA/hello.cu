// indicates a function that runs on the device, 
// and is called from the host code
// compile: nvcc hello.cu
// execute: ./a.out

__global__ void mykernel(void) {
}
int main(void) {
		// a call from host code to device code (kernel launch)
		mykernel<<<1,1>>>();
		printf("Hello World!\n");
		return 0;
}