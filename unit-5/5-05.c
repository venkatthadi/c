#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

int _strncmp(char *, char *, int n);
void _strncpy(char *, char *, int n);
void _strncat(char *, char *, char *, int n);
int _getline(char []);

int main(){
	char s[SIZE], t[SIZE];
	int n = 5;
	char *d;
	d = (char *) malloc(sizeof(char) * (strlen(s)+5+1)); 
	_getline(s);
	_getline(t);
	//printf("%s %s - %d\n", s, t, _strncmp(s, t, n));
	_strncat(s, t, d, n);
	printf("%s\n", d);
	_strncpy(s, t, n);
	printf("%s %s\n", s, t);

	return 0;
}

int _getline(char s[]){
	int c, i = 0;
	while((c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int _strncmp(char *s, char *t, int n){
	while(*s == *t){
		s++;
		t++;
		if(*s == '\0' || --n <= 0){
			return 0;
		}
	}
	return *s - *t;
}

void _strncpy(char *s, char *t, int n){
	while(*t && --n >= 0){
		*s++ = *t++;
	}
	int extra = strlen(s) - n;
	while(extra-- > 0){
		*s++;
	}
	*s = '\0';
}

void _strncat(char *s, char *t, char *d, int n){
	while(*s)
		*d++ = *s++;

	while(n-- > 0){
		*d++ = *t++;
	}
	*d = '\0';
}
