#include <stdio.h>

int n = 8;

void main(){
	int c, space;
	int count = 0;
	while((c = getchar()) != EOF){
		if(c == '\t'){
			space = n - (count % n);
			while(space > 0){
				--space;
				++count;
				putchar(' ');
			}
		}
		else{
			putchar(c);
			++count;
		}
		
		if(c == '\n')
			count = 0;
	}	
}
