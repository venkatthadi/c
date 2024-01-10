#include <stdio.h>
#include <string.h>

#define SIZE 1000

int _getline(char[]);
int strend(char *, char *);

int main(){
	char s[SIZE], t[SIZE];
	_getline(s);
	_getline(t);
	printf("%d\n", strend(s, t));
	return 0;
}

int _getline(char s[]){
	int c, i = 0;
	while((c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int strend(char *s, char *t){
	int len = strlen(t);
	int i = 0, j = 0;
	while(*s)
		s++;
	s--;
	while(*t)
		t++;
	t--;
	while(len > 0){
		if(*s == *t){
			s--;
			t--;
			len--;
		}
		else{
			return 0;
		}
	}
	if(len == 0)
		return 1;
	return 0;
}
