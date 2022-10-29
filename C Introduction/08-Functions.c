#include <stdio.h>

// Function Prototype
int add(int a,int b); 
void exchange(int *a, int *b);

int main(){
 
 int x = 10;
 int y = 20;
 printf("Addition of %i and %i is = %i\n",x,y,add(x,y));
 
 printf("Value for x:%d and y:%d before exchanging\n",x,y);
 exchange(&x, &y); // pass by reference
 printf("Value for x:%d and y:%d after exchanging (back to main)\n",x,y);
 
 return 0;

}

// A function to return the sum of a and b 
int add(int a,int b){
	return a + b;
}


// A function to exchange the value for the pointer a and b
void exchange(int *a, int *b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

