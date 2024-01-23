#include <stdio.h>
#include <string.h>

#define MAXLINE 100

void reverse(char []);
int _getline(char []);

int main(){
	char line[MAXLINE];
	
	_getline(line);
	reverse(line);

	printf("%s\n", line);

	return 0;
}

int _getline(char s[]){
	int c;
	int i = 0;
	while((c=getchar()) != EOF && c != '\n'){
		s[i++] = c;
	}
	s[i] = '\0';

	return i;
}

void reverse(char s[]){
	char ch;
	static int left = 0;
	static int len;

	if(left == 0)
		len = strlen(s);
	int right = len - (left + 1);
	
	if(left < right){
		ch = s[left];
		s[left] = s[right];
		s[right] = ch;
		left++;
		reverse(s);
	}
}
