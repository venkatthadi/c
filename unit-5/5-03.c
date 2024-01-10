#include <stdio.h>

#define MAXLEN 100

void _strcat(char *, char *);
int _getline(char []);

int main(){
	char s[MAXLEN], t[MAXLEN];
	_getline(s);
	_getline(t);
	_strcat(s, t);
	printf("%s\n", s);
	return 0;
}

int _getline(char s[]){
	int c, i = 0;
	while((c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void _strcat(char *s, char *t){
	while(*s != '\0'){
		s++;
	}
	while((*s = *t) != '\0'){
		s++;
		t++;
	}
}
