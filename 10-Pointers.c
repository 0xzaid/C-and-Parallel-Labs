#include<stdio.h>

int main(){

	// Devlare an actual variable
	int AValue = 0;
	
	// Declare a pointer variable
	int *BValue = NULL;
	
	// Default value of integer is 0 or other value...
	printf("AValue=%d \n", AValue);
	
	// Assigne a value to AValue
	AValue = 101;
	
	
	// Display the memory address where AValue is stored and the value of AValue
	// %p is the format specifier to display data of type (void*). 
	// In other word, we use it to display memory address
	// Every memory has a memory location and the address of the memory location 
	// can be accessed by using the ampersand (&) operator...
	printf("Address of AValue = %p; AValue = %d\n", &AValue, AValue); 
	
	
	// Store address of AValue in the pointer BValue
	// By doing so, we will 
	BValue = &AValue;
	
	// BValue is a pointer value that store the address of variable AValue.
	// To access to the actual value of the variable, we will use *  operator
	// to perform derefferencing process
	printf("Address of BValue = %p; BValue = %d\n", BValue, *BValue); 
		
	return 0;	
}
