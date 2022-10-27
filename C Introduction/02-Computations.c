/**
 * The following program, sine.c, computes a table of the sine function for angles between and 360 degrees.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Main function
int main(){

	// Variable definition
	int angle_degree = 75;
	double angle_radian, sine_value;
	
	printf("Calculating sine value...\n");
	printf("Angle Degree\tSine Value\n"); 
	// A while loop to calculate the since value based on the input 
	// angle (in radian)
	while(angle_degree <= 360){

		// Calculate the angle (in radian) because the sin() function
		// takes radian as input...
		angle_radian  = M_PI * angle_degree / 180;
		sine_value = sin(angle_radian);

		printf("%d\t%.4f\n", angle_degree, sine_value);
		// Increment of the angle (in degree)
		angle_degree ++;
	}
	return 0;
}
