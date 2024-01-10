#include <stdio.h>

int buf = 0;

int getch(void);
void ungetch(int);

int main(){
	int c;
	c = '*';
	
	ungetch(c);
	
	while((c=getch()) != EOF){
		putchar(c);
	}
	
	return 0;
}

void ungetch(int c){
	if(buf != 0){
		printf("too many characters\n");
	}
	else{
		buf = c;
	}
}

int getch(void){
	int c;
	if(buf != 0){
		c = buf;
	}
	else{
		c = getchar();
	}
	buf = 0;
	return c;
}
