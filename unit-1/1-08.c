#include <stdio.h>
void main(){
	int c, blank=0, tab=0, nl=0;
	while((c=getchar()) != EOF){
		if(c == ' ')
			++blank;
		else if(c == '\t')
			++tab;
		else if(c == '\n')
			++nl;
	}
	printf("blanks-%d, tabs-%d, newlines-%d \n", blank, tab, nl);
}
