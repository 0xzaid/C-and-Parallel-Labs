#include <stdlib.h>
#include <stdio.h>

int main(){
	
	int remainder;
	
	for(int i=1; i<=100; i++){
		
		remainder = i%2;
		
		switch(remainder){
			case 0:
				break;
			case 1:
				printf("Odd number: %d\n", i);
				break;
			default:
				printf("This is default\n");
				break;
		}
	}

	return 0;
}


