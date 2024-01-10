#include <stdio.h>
#include <string.h>

#define MAXLEN 100
#define MAXBUF 100

int bufp = 0;
int buf[MAXBUF];

void ungetch(int);
void ungets(char []);
int getch(void);
int mgetline(char [], int);

int main(){
	char line[MAXLEN];
	int c;
	
	mgetline(line, MAXLEN);
	ungets(line);
	
	while((c=getch()) != EOF){
		putchar(c);
	}
	
	return 0;
}

int mgetline(char s[], int lim){
	int c, i = 0;
	
	while((c=getchar()) != EOF && c != '\n'){
		s[i++] = c;
	}
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';
}

void ungets(char s[]){
	int i;
	i = strlen(s);
	
	while(i > 0){
		ungetch(s[--i]);
	}
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
