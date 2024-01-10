#include <stdio.h>
void main(){
	int c;
	while((c=getchar()) != EOF){
		if(c == ' '){
			putchar(c);
			while(((c=getchar())==' ') && (c=getchar())!=EOF);
			putchar(c);
		}
		else
			putchar(c);
	}
}
