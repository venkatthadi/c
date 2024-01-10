#include <stdio.h>
#include <string.h>

#define MAXLEN 100
#define MAXBUF 100

int bufp = 0;
int buf[MAXBUF];

void ungetch(int);
int getch(void);

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
	if(bufp >= MAXBUF){
		printf("too many characters\n");
	}
	else{
		buf[bufp++] = c;
	}
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}
