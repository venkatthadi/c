#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 100

enum {NAME, PARENS, BRACKETS};
enum {NO, YES};

int gettoken(void);
int nexttoken(void);

int tokentype;
char token[MAXLEN];
char out[1000];

int main(void) {
    int type;
    char temp[MAXLEN];

    while (gettoken() != EOF) {
        strcpy(out, token);

        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                if ((type = nexttoken()) == PARENS || type == BRACKETS)
                    sprintf(temp, "(*%s)", out);
                else
                    sprintf(temp, "*%s", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, " %s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s \n", token);
        printf("%s\n", out);
    }
    return 0;
}

extern int tokentype;
extern char token[];
int prevtoken = NO;

int gettoken(void){
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	if (prevtoken == YES) {
		prevtoken = NO;
		return tokentype;
	}

	while ((c = getch()) == ' ' || c == '\t');

	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for(*p++ = c; (*p++ = getch()) != ']';);
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

int nexttoken(){
	int type;
	extern int prevtoken;

	type = gettoken();
	prevtoken = YES;
	return type;
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
