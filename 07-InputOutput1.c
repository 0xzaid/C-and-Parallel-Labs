#include <stdio.h>
int main(){

 int c, nc = 0, nl = 0, nw = 0;
 
 while ( (c = getchar()) != EOF ){
	 nc++;
	 if (c == '\n') nl++;
	 if (c == ' ' || c == '\n' ) nw++; // if statement to check number of words
 }
 
 	printf("\nNumber of characters = %d, number of words = %d, number of lines = %d\n", nc, nw+1, nl);
 	return(0);
 }
