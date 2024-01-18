#include <stdio.h>
#include <stdlib.h>

#define MAXOP	100
#define NUMBER	'0'

int getop (char []);
void push (double);
double pop (void);

int main() {
	int type; 
	double op2;
	char s[MAXOP];
	
	while ((type = getop(s)) != EOF) {
		switch(type) {
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
				if (op2 != 0.0) {
					push(pop() / op2);
				} else 
					printf("division by 0\n");
				break;
			case '\n':
				printf("%.8g\n", pop());
				break;
			default:
				printf("error: invalid command\n");
				break;
		}
	}

	return 0;
}

#define MAXVAL	100

int sp = 0;
double val[MAXVAL];

void push (double d) {
	if (sp >= MAXVAL) {
		printf("stack overflow\n");
	} else {
		val[sp++] = d;
	}
}

double pop (void) {
	if (sp <= 0) {
		printf("stack empty\n");
		return 0.0;
	} else {
		return val[--sp];
	}
}	

#include <ctype.h>

int getop(char s[])
{
    int i, c, rc;
    static char lastc[] = " ";
   
    c = lastc[0];
    lastc[0] = ' ';
    while((s[0] = c) == ' ' || c == '\t')
        if(scanf("%c", &c) == EOF)
            c = EOF;
    s[1] = '\0';
    if(!isdigit(c) && c != '.' && c != '-') // not a number
        return c;
    i = 0;
    if (c == '-')
    {
        scanf("%c", &c);
        rc = c;
        if(isdigit(c) || c == '.')
            s[++i] = c; //negative numbers
        else
            {
                if(rc != EOF)
                    lastc[0] = c;
                return '-';
            }
    }
    if(isdigit(c)) //collect integer part
        do
        {
            scanf("%c", &c);
            rc = c;
            if(!isdigit(s[++i] = c))
                break;
        } while(rc != EOF);
    if(c == '.') //collect fraction part
        do
        {
            scanf("%c", &c);
            rc = c;
            if(!isdigit(s[++i] = c))
                break;
        } while(rc != EOF);
    s[i] = '\0';
    if(rc != EOF)
        lastc[0] = c;
    return NUMBER;
}
