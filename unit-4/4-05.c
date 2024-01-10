#include <stdio.h>
#include <stdlib.h>

#define	MAXOP	100
#define	NUMBER	'0'
#define	NAME	'n'

int getop(char []);
void push(double);
double pop(void);
void clearsp(void);
void mathfnc(char []);

int main(){
	int type;
	double op1, op2;
	char s[MAXOP];
	
	while((type = getop(s)) != EOF){
		switch(type){
			case NUMBER:
				push(atof(s));
				break;
			case NAME:
				mathfnc(s);
				break;
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op1 = pop();
				push(pop() - op1);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				op1 = pop();
				if(op1 != 0.0){
					push(pop() / op1);
				}
				else
					printf("not divisible by 0...\n");
				break;
			case '%':
				op1 = pop();
				op2 = pop();
				if(op1 != 0.0){
					push(op2 - op1 * (int) (op2 / op1));
				}
				else
					printf("not divisible by 0..\n");
				break;
			case '?':
				op2 = pop();
				printf("%g\n", op2);
				push(op2);
				break;
			case '$':
				op1 = pop();
				op2 = pop();
				push(op1);
				push(op2);
				break;
			case '#':
				clearsp();
				break;
			case '!':
				op1 = pop();
				push(op1);
				push(op1);
				break;
			case '\n':
				printf("%g", pop());
				break;
			default:
				printf("invalid command\n");
				break;
		}
	}
	
	return 0;
}

int sp = 0;
double val[MAXOP];

void push(double d){
	if(sp < MAXOP){
		val[sp++] = d;
	}
	else
		printf("stack full\n");
}

double pop(void){
	if(sp > 0){
		return val[--sp];
	}
	else
		printf("stack empty\n");
}

#include <ctype.h>
#include <string.h>

int getch(void);
void ungetch(int);

int getop(char s[]){
	int c, i;
	
	while((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	
	i = 0;
	if(islower(c)){
		while(islower(s[++i] = c = getchar()));
		s[i] = '\0';
		if(c != EOF)
			ungetch(c);
		if(strlen(s) > 1)
			return NAME;
		else 
			return s[0];
	}
	
	if(!isdigit(c) && c != '.' && c != '-')
		return c;
	if(c == '-'){
		if(isdigit(c = getch()) || c == '.'){
			s[++i] = c;
		}
		else{
			if(c != EOF){
				ungetch(c);
			}
			return '-';
		}
	}
	if(isdigit(c))
		while(isdigit(s[++i] = c = getchar()));
	if(c == '.')
		while(isdigit(s[++i] = c = getchar()));
	s[i] = '\0';
	
	if(c != EOF)
		ungetch(c);
		
	return NUMBER;
}

void clearsp(){ sp = 0; }

#define BUFSIZE 100

int bufp = 0;
char buf[BUFSIZE];

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp > BUFSIZE)
		printf("too many characters\n");
	else{
		buf[bufp++] = c;
	}
}

#include <math.h>

void mathfnc(char s[]){
	double op2;
	
	if(strcmp(s, "sin") == 0){
		push(sin(pop()));
	}
	else if(strcmp(s, "cos") == 0){
		push(cos(pop()));
	}
	else if(strcmp(s, "exp") == 0){
		push(exp(pop()));
	}
	else if(strcmp(s, "pow") == 0){
		op2 = pop();
		push(pow(pop(), op2));
	}
	else{
		printf("string not supported");
	}
}
