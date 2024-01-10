#include <stdio.h>

int tab = 4;

void main(){
	int count = 0, i;
	int c;
	while((c = getchar()) != EOF){
		if(c == ' ')
			++count;
		else{
			if(count > 0){
				for(i = 0; i < count/tab; ++i){
					putchar('\t');
				}
				for(i = 0; i < count%tab; ++i){
					putchar(' ');
				}
				count = 0;
			}
			putchar(c);
		}
	}
}
