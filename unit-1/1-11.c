#include <stdio.h>
void main(){
	int wc = 0, c;
	int state = 0;
	while((c=getchar())!=EOF){
		if(c == ' ' || c == '\t' || c == '\n'){
			state = 0;
		}
		else if(c == '-'){
			state = 0;
		}
		else if(state == 0){
			state = 1;
			++wc;
		}
	}
	printf("%d",wc);
}
