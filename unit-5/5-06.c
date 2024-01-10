#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100
#define NUMBER '0'

int var[SIZE];
int sp = 0;

int atoi(char *);
int _getline(char *);
int _getop(char *);
void push(int);
int pop(void);
void reverse(char *s);
int strindex(char *, char *);
char pattern[] = "orld";

int main(){
	char s[] = "hello world";
	printf("found at pos - %d\n", strindex(s, pattern));
	reverse(s);
	printf("%s\n", s);

	char line[SIZE];
	int type, op1, op2;

	while((type = _getop(line)) != EOF){
		switch(type){
			case NUMBER:
				push(atoi(line));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op1 = pop();
				push(pop() - op1);
				break;
			case '/':
				op1 = pop();
				op2 = pop();
				if(op1 != 0){
					push(op1 / op2);
				}
				else
					printf("error (division by 0)\n");
				break;
			case '\n':
				printf("%d\n", pop());
				break;
			default:
				printf("invalid operator\n");
				break;
		}
	}

	return 0;
}

int _getline(char *s){
	int c, i = 0;
	char *t = s;
	while((c=getchar()) != EOF && c == '\n')
		*s++ = c;
	if(*s == '\n')
		*s++ = '\n';
	*s = '\0';
	return s - t;
}

void reverse(char *s){
	int temp;
	char *t;
	for(t = s +  strlen(s) - 1; s < t; s++, t--){
		temp = *s;
		*s = *t;
		*t = temp;
	}
}

int atoi(char *s){
	int n, sign;
	for(; isspace(*s); s++);
	sign = (*s == '-') ? -1 : 1;
	if(*s == '+' || *s == '-')
		s++;
	for(n = 0; isdigit(*s); s++){
		n = n * 10 + (*s - '0');
	}
	return sign * n;
}

void push(int c){
	if(sp >= SIZE)
		printf("stack overload\n");
	else
		var[sp++] = c;
}

int pop(void){
	if(sp <= 0){
		printf("stack empty\n");
		return 0;
	}
	else
		return var[--sp];
}

#define BUFSIZE 100

int bufp = 0;
char buf[BUFSIZE];

void ungetch(int c){
	if(bufp < BUFSIZE){
		buf[bufp++] = c;
	}
	else
		printf("too many characters\n");
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

int _getop(char *s){
	int c;
	while ((*s = c = getch()) == ' ' || c == '\t');
	*(s + 1) = '\0';
	if(!isdigit(c) && c != '.')
		return c;
	if(isdigit(c))
		while(isdigit(*++s = c = getch()));
	if(c == '.')
		while(isdigit(*++s = c = getch()));
	*s = '\0';
	if(c != EOF)	
		ungetch(c);
	return NUMBER;	
}

int strindex(char *s, char *pattern){
	char *temp  = s;
	char *p, *r;
	for(; *s != '\0'; s++){
		for(p = s, r = pattern; *r != '\0' && (*p == *r); p++, r++);
		if(*r == '\0')
			return s - temp;
			
	}
	return -1;
}
