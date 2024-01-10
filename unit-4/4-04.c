#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'


int getop(char []);
void push(double);
double pop(void);
double head(void);
void duplicate(void);
void swap(void);
void clear(void);


/* reverse Polish calculator */
main()
{
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            printf("operand: %s\n", s);
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
        case '%':
            op2 = pop();
            op1 = pop();
            if (op2 != 0.0)
                push(op1 - op2 * (int) (op1 / op2));
            else
                printf("zero division error\n");
            break;
        case '?':
            printf("top of the stack: %f\n", head());
            break;
        case '$':
            printf("duplicate top of the stack\n");
            duplicate();
            break;
        case '!':
            printf("swap the top two elements of stack\n");
            swap();
            break;
        case '#':
            printf("clear stack\n");
            clear();
            break;
        case '\n':
            printf("\t%.2f\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
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

double head(void)
{
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void duplicate(void)
{
    push(head());
}

void swap(void)
{
    double swap;
    int i;

    if (sp < 2)
        printf("error: can not swap, not enough elements\n");
    else {
        i = sp - 1;  /* head index */
        swap = val[i - 1];
        val[i - 1] = val[i];
        val[i] = swap;
    }
}

void clear(void)
{
    while (--sp >= 0)
        val[sp] = 0.0;
    sp = 0;
}


#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;
    if (c == '-' && !isdigit(s[++i] = c = getch())) {
        ungetch(c);
        c = s[0];
    }

    if (!isdigit(c) && c != '.')
        return c;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
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
