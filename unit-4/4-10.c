#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 100
#define NUMBER '0'

int mgetline(char []);
int getop(char []);
void push(double);
double pop(void);

int main(){
	int type;
	double op1;
	char line[MAXLEN];
	
	while((type = getop(line)) != EOF){
		switch(type){
			case NUMBER:
				push(atof(line));
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
				if(op1 != 0.0){
					push(pop() / op1);
				}
				else{
					printf("not divisible by 0...\n");
				}
				break;
			case '\n':
				printf("%g\n", pop());
				break;
			default:
				printf("invalid operation...\n");
		}
	}
	return 0;
}

int sp = 0;
double val[MAXLEN];

void push(double d){
	if(sp >= MAXLEN){
		printf("stack overload...\n");
	}
	else
		val[sp++] = d;
}

double pop(void){
	if(sp <= 0){
		printf("stack empty...\n");
		return 0.0;
	}
	else
		return val[--sp];
}

#include <ctype.h>

int li = 0;
char line[MAXLEN];

int getop(char s[]){
	int i, c;
	
	if(line[li] == '\0'){
		if(mgetline(line) == 0){
			return EOF;
		}
		else
			li = 0;
	}
	
	while((s[0] = c = line[li++]) == ' ' || c == '\t');
	s[1] = '\0';
	
	if(!isdigit(c) && c != '.')
		return c;
		
	i = 0;
	
	if(isdigit(c)){
		while(isdigit(s[++i] = c = line[li++]));
	}
	if(c == '.'){
		while(isdigit(s[++i] = c = line[li++]));
	}
	s[i] = '\0';
	li--;
	
	return NUMBER;
}

int mgetline(char line[]){
	int c, i = 0;
	
	while(i<MAXLEN-1 && (c=getchar()) != EOF && c != '\n'){
		line[i++] = c;
	}
	if(c == '\n')
		line[i++] = c;
	line[i] = '\0';
	
	return i;
}
