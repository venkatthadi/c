#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

int main()
{
    int type, var = 0;
    double op1, op2, v;
    char s[MAXOP];
    double variable[26];

    while ((type = getop(s)) != EOF) {
        switch (type) {
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
            		if (op2 != 0.0)
                		push(pop() / op2);
            		else
                		printf("zero division error\n");
            		break;
        	case '=':
        		pop();
        		if(var >= 'A' && var <= 'Z')
        			variable[var - 'A'] = pop();
        		else
        			printf("not a variable name\n");
        		break;
        	case '\n':
        		v = pop();
            		printf("\t%.2f\n", v);
            		break;
        	default:
        		if(type >= 'A' && type <= 'Z')
        			push(variable[type - 'A']);
        		else if(type == 'v')
        			push(v);
        		else
        			printf("unknown command %s\n", s);
            		break;
        }
        var = type;
    }
    return 0;
}


#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can not push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}


#include <ctype.h>


int getch(void);
void ungetch(int);


/* getop: get next operator or numeric operand */
int getop(char s[]){
	int i, c;
	
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));
	if (c == '.')
		while (isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
		
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;


int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void ungetch(int c)
{
    if (bufp > BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
