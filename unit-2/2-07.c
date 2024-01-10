#include <stdio.h>

unsigned invert(unsigned x, int p, int n){
	return x ^ (~(~0 << n) << (p - n + 1));
}

int main(){
	printf("%u\n", invert((unsigned) 12, 4, 3));
	return 0;
}
