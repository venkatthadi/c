#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 10

int getfloat(float *);
int getch(void);
void ungetch(int);

int main(){
        int n;
    	float array[MAXSIZE] = {0};

    	for (n = 0; n < MAXSIZE && getfloat(&array[n]) != EOF; n++);
    	for(n = 0; n < MAXSIZE; n++)
    		printf("%g\n",array[n]);

        return 0;
}

int getfloat(float *ip){
        int c, sign;
        while(isspace(c = getch()));
        if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.'){
                ungetch(c);
                return 0;
        }
        sign = (c == '-') ? -1 : 1;
        if (c == '-' || c == '+'){
		c = getch();
		if(!isdigit(c) && c != '.'){
			if(c == EOF)
				return EOF;
			else{
				ungetch(c);
				return 0;
			}
		}
	}
        for(*ip = 0.0; isdigit(c); c = getch())
                *ip = 10.0 * *ip + (c - '0');
	float pow = 1.0;
	if(c == '.'){
		c = getch();
		while(isdigit(c)){
			*ip = 10.0 * *ip + (c - '0');
			pow *= 10.0;
			c = getch();
		}
	}
        *ip *= sign;
        *ip /= pow;
        if(c != EOF)
                ungetch(c);
        return c;
}

#define BUFSIZE 100

int bufp = 0;
char buf[MAXSIZE];

int getch(void){
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
        if(bufp >= MAXSIZE)
                printf("too many characters\n");
        else
                buf[bufp++] = c;
}

