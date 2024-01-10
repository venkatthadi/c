#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){

	printf("signed char - %d to %d\n", CHAR_MIN, CHAR_MAX);
	printf("unsigned char - %d to %d\n", 0, UCHAR_MAX);
	printf("signed int - %d to %d\n", INT_MIN, INT_MAX);
	printf("unsigned int - %u to %u\n", 0, UINT_MAX);
	
	return 0;
}
