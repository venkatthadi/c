#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};
enum {NO, YES};

void dcl(void);
void directdcl(void);
int gettoken(void);
void error(char *);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char out[MAXTOKEN];
char datatype[MAXTOKEN];
int prevtoken;

int main(){
	while(gettoken() != EOF){
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if(tokentype != '\n')
			printf("syntax error\n");
		printf("%s : %s %s \n", name, out, datatype);
	}
	return 0;
}

void error(char *s){
	printf("%s\n", s);
	prevtoken = YES;
}

void dcl(void){
	int ns = 0;
	
	while(gettoken() == '*')
		ns++;
	
	directdcl();
	
	while(ns-- > 0){
		strcat(out, " pointer to");
	}
}

void directdcl(void){
	int type;
	
	if(tokentype == '('){
		dcl();
		if(tokentype != ')')
			error("missing ')'\n");
	} else if(tokentype == NAME){
		strcpy(name, token);
	} else{
		error("expected name or (dcl)\n");
	}

	while((type = gettoken()) == PARENS || type == BRACKETS){
		if(type == PARENS)
			strcat(out, " function returning");
		else{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

int tokentype = 0;
char token[MAXTOKEN];
int prevtoken = NO;

int gettoken(void){
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	if(prevtoken == YES){
		prevtoken = NO;
		return tokentype;
	}

	while((c = getch()) == ' ' || c == '\t');

	if(c == '('){
		if((c = getch()) == ')'){
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '['){
		for(*p++ = c; (*p = getch()) != ']';);
		*p++ = ']';
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for(*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else {
		return tokentype = c;
	}
}

#define BUFSIZE 100

int bufp = 0;
char buf[BUFSIZE];

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		error("too many characters..\n");
	else
		buf[bufp++] = c;
}
