#include <stdio.h>

unsigned setbits(unsigned x, int n, int p, unsigned y){
	return x & ~(~(~0 << n) << (p + 1 - n)) | (y & (~(~0 << n)) << (p + 1 - n));
}

int main(){
	printf("%u\n", setbits((unsigned) 12, 3, 2, (unsigned) 55));
	return 0;
}
