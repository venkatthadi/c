#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 10

int getint(int *);
int getch(void);
void ungetch(int);

int main(){
	int i, j, arr[MAXSIZE], getint(int *);
	for(i = 0; i < MAXSIZE; i++){
		arr[i] = 99999;
	}
	for(i = 0; i < MAXSIZE; i++){
		if((j = getint(&arr[i])) == 1)
			getch();
		if(j == EOF)
			continue;
	}
	for(i = 0; i < MAXSIZE; i++)
		printf("%d\n", arr[i]);
	return 0;
}

int getint(int *ip){
	int c, d, sign;
	while(isspace(c = getch()));
	if(!isdigit(c) && c != EOF && c != '+' && c!= '-'){
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+') {
        	d = c;
        	while (!isdigit(c = getchar())) {
            		if (c !=EOF) {
                		ungetch(c);
            		}
            		ungetch(d);        
            		return d;
        	}
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
