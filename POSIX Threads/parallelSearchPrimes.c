#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>
#include<pthread.h>
#define NUMTHREAD 4 // Number of thread

/* Global Variables */
int *primeNumbers;
int primeCounter; 
int pUpperLimit;

/* Function Declaration */
bool isPrime(int n);
void *searchPrimeFunction(void *arg);

pthread_mutex_t g_Mutex;

int main(){

	struct timespec start, end, start_s, end_s;
	double time_taken; 

	pthread_t hThread[NUMTHREAD];
	int threadNum[NUMTHREAD];
	
	pthread_mutex_init(&g_Mutex, NULL);
	
	FILE *fp;	
	
	// Part-1 Read Input
	printf("Input an integer number:");
	scanf("%d", &pUpperLimit);
	
	// Get current clock time.
	clock_gettime(CLOCK_MONOTONIC, &start); 

	
		// Get current clock time.
		clock_gettime(CLOCK_MONOTONIC, &start_s); 
		
	primeNumbers = malloc(pUpperLimit *sizeof(int)); // dynamically allocate size to the pointer variable
	primeCounter = 0;
	
		// Get the clock current time again
		// Subtract end from start to get the CPU time used.
		clock_gettime(CLOCK_MONOTONIC, &end_s); 
		time_taken = (end_s.tv_sec - start_s.tv_sec) * 1e9; 
	    	time_taken = (time_taken + (end_s.tv_nsec - start_s.tv_nsec)) * 1e-9; 
		printf("Processing time (non-parallelizable)(Read)(s): %lf\n", time_taken);
	
	
	// Part-2A Create Thread to do parallel task
	for(int i=0;i<NUMTHREAD;i++){
		threadNum[i] = i;
		pthread_create(&hThread[i], NULL, searchPrimeFunction, &threadNum[i]);
	}	
	
	
	// Part-2B Join Thread
	for(int i=0;i<NUMTHREAD;i++){
		pthread_join(hThread[i], NULL);
	}	
	
		// Get current clock time.
		clock_gettime(CLOCK_MONOTONIC, &start_s); 
		
	// Part-3 Output to text file
	fp = fopen("primes.txt","w");
	for(int i=0;i<primeCounter;i++){
		fprintf(fp, "%d\n", primeNumbers[i]);
	
	}
	fclose(fp);

		// Get the clock current time again
		// Subtract end from start to get the CPU time used.
		clock_gettime(CLOCK_MONOTONIC, &end_s); 
		time_taken = (end_s.tv_sec - start_s.tv_sec) * 1e9; 
	    	time_taken = (time_taken + (end_s.tv_nsec - start_s.tv_nsec)) * 1e-9; 
		printf("Processing time (non-parallelizable)(Write)(s): %lf\n", time_taken);


	// Get the clock current time again
	// Subtract end from start to get the CPU time used.
	clock_gettime(CLOCK_MONOTONIC, &end); 
	time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 
	printf("Overall time (Including read, search and write)(s): %lf\n", time_taken); // ts

	/* Clean environment */
	pthread_mutex_destroy(&g_Mutex);
	free(primeNumbers);


	return 0;
}

/* Function Definition */
void *searchPrimeFunction(void *arg){

	struct timespec start_p, end_p;
	double time_taken; 

	// Get current clock time.
	clock_gettime(CLOCK_MONOTONIC, &start_p); 

	// Get the thread id the (int*) is to type cast the arg from (void*) to (int*)
	int pid = *(int*) arg;
	
	// Perform range partition so that the thread search for prime number within specific range.
	int start = pid * pUpperLimit/NUMTHREAD + 1;
	int end = (pid+1) * pUpperLimit/NUMTHREAD;
	if(pid == NUMTHREAD-1){
		 end = end-1;
	}
	
	// Prime number searching
	for(int i=start; i<=end; i++){
		if(isPrime(i)){
			// Add the prime number into the global array, mutex is implemented to prevent race condition
			pthread_mutex_lock(&g_Mutex);
			primeNumbers[primeCounter] = i;
			primeCounter++;
			pthread_mutex_unlock(&g_Mutex);	
		}
	}
	
	// Get the clock current time again
	// Subtract end from start to get the CPU time used.
	clock_gettime(CLOCK_MONOTONIC, &end_p); 
	time_taken = (end_p.tv_sec - start_p.tv_sec) * 1e9; 
    	time_taken = (time_taken + (end_p.tv_nsec - start_p.tv_nsec)) * 1e-9; 

	printf("[Thread %d] Processing time(s): %lf\n", pid, time_taken);
}


/* Function Definition */
bool isPrime(int n){

	// Exclude the case when n <= 1
	if(n<=1){
		return false;
	}
	
	// Exclude the case for n is even number and larger than 2
	if(n!=2 && n%2==0){
		return false;
	}
	
	// If a factor can be found between 3 - sqrt(n), the given number n is a non-prime number
	for(int i=3; i<=sqrt(n); i++){
		if(n%i==0){
			return false;
		}
	}
	
	return true;
}


