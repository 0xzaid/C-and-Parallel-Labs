#include <stdio.h>

int main(){

	char text_1[100], text_2[100];
	char *ta, *tb;
	int i;
	
	
	char message[] = "Hello, My name is Zaid";
	printf("Original message %s\n", message);
	
	
	i = 0;
	while ( (text_1[i] = message[i]) != '\0'){
		i ++;
	}
	printf("Text_1: %s\n", text_1);
	ta = message;
	tb = text_2;
	
	while ( (*tb++ = *ta++) != '\0'){
		;
	}
	printf("Text_2: %s\n", text_2);

	return 0;
}
