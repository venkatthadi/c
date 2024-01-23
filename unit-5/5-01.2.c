#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 10

int getint(int *);
int getch(void);
void ungetch(int);

int main(){
	int i, j, arr[MAXSIZE] = {0}, getint(int *);
	for(i = 0; i < MAXSIZE; i++){
		if((j = getint(&arr[i])) == 1)
			getch();
		if(j == EOF)
			break;
	}
	for(int k = 0; k < i; k++)
		printf("%d\n", arr[k]);
	return 0;
}

int getint(int *ip){
	int c, d, sign;
	while(isspace(c = getch()));
	if(!isdigit(c) && c != EOF && c != '+' && c!= '-'){
		ungetch(c);
		return -1;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+') {
        	c = getch();
	}
	if(!isdigit(c)) {
		return 0;
	}	
	for(*ip = 0; isdigit(c); c = getch())
		*ip = 10 * *ip + (c - '0');
	*ip *= sign;
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
