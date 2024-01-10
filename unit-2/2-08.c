#include <stdio.h>

unsigned rightrot(unsigned x, int n){
	unsigned lb;
	while(n--){
		lb = x & 1;
		x = (x >> 1);
		if(lb){
			x = x | ~(~0u >> 1);
		}
	}
	return x;
}

int main(){
	printf("%u\n", rightrot((unsigned) 12, 2));
	return 0;
}
