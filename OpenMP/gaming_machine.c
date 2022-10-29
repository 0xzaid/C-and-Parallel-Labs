#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MIN 1
#define MAX 9

int totalWin = 0;

int main(){
	clock_t t1;
	int size, i, num_thread, chunk_size;

	FILE *fp;	
	unsigned int seed;

	
	printf("Enter the size of display: ");
	scanf("%d", &size);

	printf("Enter the number of threads: ");
	scanf("%d", &num_thread);
	omp_set_num_threads(num_thread);

	printf("Enter the chunk size: ");
	scanf("%d", &chunk_size);


	// calloc allocates in heap memory
	int* ptr = (int*)calloc(size, sizeof(int));

	// this array stores the number of wins for each thread
	int* ptr2 = (int*)calloc( (MIN+MAX+1), sizeof(int));

	// open file for displaying results
	fp = fopen("display.txt", "w");

	// current time
	t1 = clock();


	#pragma omp parallel shared (ptr) private (seed) 
	{
		// create a random seed
		srand(time(NULL));	
		#pragma omp for schedule (dynamic, chunk_size) private (i) 
		
		for(i=0; i<size; i++){
			seed = rand();
			// printf("%d\n", seed);
			ptr[i] = (rand_r(&seed) % (MAX - MIN + 1)) + MIN;
			printf("Thread %d created %d\n", omp_get_thread_num(), ptr[i]);
			}
	}
	
	// end timer
	t1 = clock() - t1;


	//printf("\n[ ");
	// outputting to display.txt
	for(i=0; i<size; i++){
		ptr2 [ptr[i]-1 ]++;
		fprintf(fp, "%d", ptr[i]);
	}
	fprintf(fp, "\n");
	fclose(fp);

	// destroying heap array
	free(ptr);
	free(ptr2);
	//count wins

	FILE *myFile;
    myFile = fopen("display.txt", "r");

    //read file into array
    int* ptr3 = (int*)calloc(size, sizeof(int));
    int* count_arr = (int*)calloc((MAX+MIN-1), sizeof(int));

    if (myFile == NULL) {
        printf("Error Reading File\n");
        exit (0);
    }

	for (i = 0; i < size; i++) {
	     int c = fgetc(myFile);
	     if(c == EOF)
	        break;
	     ptr3[i] = c - '0';
	 }


    fclose(myFile);

    // count matches and wins
    clock_t t2;
    t2 = clock();

    
	#pragma omp parallel shared (ptr3, totalWin, count_arr) private (i)
		

    	#pragma omp for schedule (static, chunk_size) reduction(+:count_arr[:(MAX+MIN-1)])
		for(i= 0; i<size; i++){
			count_arr[ptr3[i]-1]++;
			printf("Thread %d found a %d\n",omp_get_thread_num(), ptr3[i]);
		}
		
		#pragma omp for schedule (static, chunk_size) reduction(+:totalWin) private (i)
		for(i= 0; i<(MAX+MIN-1); i++){
			if(count_arr[i]>1){
				printf("[Thread %d] found win\n",omp_get_thread_num());
				totalWin++;
			}
		}


    t2 = clock() -t2;

	// results
		
	for(i=0; i<(MAX+MIN-1); i++){
		if(count_arr[i]>1){
			printf("Number: %d, Number of occurances:: %d\n",i+1, count_arr[i]);
		}
	}
	printf("\nTotal wins: %d\n", totalWin);
	
	free(ptr3);
	free(count_arr);
	double time_taken_1 = ((double)t1)/CLOCKS_PER_SEC;
	double time_taken_2 =  ((double)t2)/CLOCKS_PER_SEC;
	printf("\n\nTime taken for generating random numbers and adding into array:  %f\n", time_taken_1);
	printf("Time taken for matching entries: %f\n", time_taken_2);


	return 0;
}