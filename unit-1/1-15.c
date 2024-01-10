#include <stdio.h>

float celsius(int fahr){
	float cel = (5.0/9.0) * (fahr-32);
	return cel;
}

void main(){
	int i;
	for (i = 0; i <= 300; i += 20)
		printf("%3d %.2f\n", i, celsius(i));
}

