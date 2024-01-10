#include <stdio.h>
#include <string.h>

#define maxlen 100

int mgetline(char s[]){
	int c;
	int i = 0;
	while((c=getchar()) != EOF && c != '\n'){
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}

int balparen(char s[]){
	int b1, b2, b3;
	int i = 0;
	b1 = 0;
	b2 = 0;
	b3 = 0;
	int len = strlen(s);
	printf("%d\n",len);
	if(len == 0)
		return 0;
	while(len--){
		if(s[i] == '(')
			b1++;
		else if(s[i] == '{')
			b2++;
		else if(s[i] == '[')
			b3++;
		else if(s[i] == ')')
			b1--;
		else if(s[i] == '}')
			b2--;
		else if(s[i] == ']')
			b3--;
		if(b1 < 0 || b2 < 0 || b3 < 0)
			return 0;
		i++;
	}
	if(b1 == 0 && b2 == 0 && b3 == 0)
		return 1;
	return 0;
}

int main(){
	int line[maxlen];
	while(mgetline(line) > 0){
		printf("%d\n", balparen(line));
	}
	return 0;
}
