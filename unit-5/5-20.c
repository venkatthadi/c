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
void paramdcl(void);
void errmsg(char *);

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
	void parmdcl(void);

	if(tokentype == '('){
		dcl();
		if(tokentype != ')')
			errmsg("missing ')'\n");
	} else if(tokentype == NAME){
		if (name[0] == '\0')
			strcpy(name, token);
	} else{
		prevtoken = YES;
	}

	while((type = gettoken()) == PARENS || type == BRACKETS || type == '('){
		if(type == PARENS)
			strcat(out, " function returning");
		else if(type == '('){
			strcat(out, " function expecting");
			paramdcl();
			strcat(out," and returning");
		}
		else{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

void errmsg(char *msg)
{
    printf("%s", msg);
    prevtoken = YES;
}

void declspec(void); 
int typespec(void);    
int typedesc(void);

void paramdcl(void)
{
    do
    {
        declspec(); //specification declaration
    } while(tokentype == ',');
    if(tokentype != ')')
        errmsg("missing ) in declarator of parameters\n");
}

void declspec(void)
{
    char temp[MAXTOKEN];
    
    temp[0] = '\0';
    gettoken();
    do
    {
        if(tokentype != NAME)
        {
            dcl();
        }
        else if(typespec() == YES) // type specifier
        {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else if(typedesc() == YES) //descriptor type
        {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else
            errmsg("error: unknown type in the parameter list\n");
    } while(tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if(tokentype == ',')
        strcat(out, ",");
}

int typespec(void)
{
    static char *types[] = {"char", "int", "void"};
    char *ptypes = token;
    int result, i;
   
    result = NO;
    for(i = 0; i < 3; i++)
        if(strcmp(ptypes, *(types + i)) == 0)
            return result = YES;
        else
            result = NO;
    return result;
        
}

int typedesc(void)
{
    static char *typed[] = {"const", "volatile"};
    char *ptd = token;
    int result, i;
    
    result = NO;
    for(i = 0; i < 2; i++)
        if(strcmp(ptd, *(typed + i)))
            return result = YES;
        else
            result = NO;
    return result;
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
		errmsg("too many characters..\n");
	else
		buf[bufp++] = c;
}
