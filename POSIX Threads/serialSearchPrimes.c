// Header file for libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include <time.h>

/* Function Declaration */
// A function to check if the given number n is a prime or non-prime number
bool isPrime(int n); 

/* Main Function */
int main(){

	/* Variables */
	int pUpperLimit;
	FILE *fp;
	
	int *primeNumbers;
	int primeCounter = 0;
	
	struct timespec start, end, start_s, end_s;
	double time_taken; 
	
	// Part-1 Read Input (Serialized Portion)
	printf("Input an integer number:");
	scanf("%d", &pUpperLimit);
	
	// Get current clock time.
	clock_gettime(CLOCK_MONOTONIC, &start); 

	
		// Get current clock time.
		clock_gettime(CLOCK_MONOTONIC, &start_s); 
	
	
	primeNumbers = malloc(pUpperLimit *sizeof(int)); // dynamically allocate size to the pointer variable
	
		// Get the clock current time again
		// Subtract end from start to get the CPU time used.
		clock_gettime(CLOCK_MONOTONIC, &end_s); 
		time_taken = (end_s.tv_sec - start_s.tv_sec) * 1e9; 
	    	time_taken = (time_taken + (end_s.tv_nsec - start_s.tv_nsec)) * 1e-9; 
		printf("Processing time (non-parallelizable)(Read)(s): %lf\n", time_taken);
	
	

	// Part-2 Check prime from 2 to pUpperLimit
	for(int i=2; i<pUpperLimit; i++){
		if(isPrime(i)){
			primeNumbers[primeCounter] = i;
			primeCounter++;
		
		}
	}
	// Part-3 Output to text file (Serialized Portion)
		// Get current clock time.
		clock_gettime(CLOCK_MONOTONIC, &start_s); 
	
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

	return 0;
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


