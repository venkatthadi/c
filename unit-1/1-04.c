#include <stdio.h>

void main(){
	float fahr, celsius;
	float lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;

	celsius = lower;
	printf("Celsius\t  Fahr\n");
	while(celsius <= upper){
		fahr = ((9.0)/(5.0)*celsius)+32.0;
		printf("%3.1f \t %6.1f \n", celsius, fahr);
		celsius += step;
	}
}
