#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOP 1000
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
void ungetch(int);
void ungets(char []);
int getch(void);

int sp = 0;
double var[MAXOP];

int main(int argc, char *argv[]){
	char s[MAXOP];
	double op2;
	
	while(--argc > 0){
		ungets(" ");
		ungets(*++argv);

		switch(getop(s)){
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error\n");
				break;
			default:
				printf("invalid operator\n");
				argc = 1;
				break;
		}
	}
	printf("%6g\n", pop());
	return 0;
}

#define BUFSIZE 1000

int bufp = 0;
char buf[BUFSIZE];

int getop(char s[]){
	int i = 0, c;
	while((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if(!isdigit(c) && c != '.')
		return c;
	if(isdigit(c)){
		while(isdigit(s[++i] = c = getch()));
	}
	if(c == '.')
		while(isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungets(char s[]){
	int len = strlen(s);
	while(len > 0){
		ungetch(s[--len]);
	}
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("too many characters\n");
	else
		buf[bufp++] = c;
}

void push(double d){
	if(sp < MAXOP)
		var[sp++] = d;
	else
		printf("stack overflow\n");
}

double pop(void){
	if(sp <= 0){
		printf("stack empty\n");
		return 0.0;
	}
	else
		return var[--sp];
}
