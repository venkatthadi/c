#include <stdio.h>

int main(){
	unsigned x;
	int count;
	
	x = (unsigned) 12;
	
	for(count = 0; x > 0; x &= x - 1)
		count++;
	
	printf("%d\n", count);
	return 0;
}
