#include <stdio.h>
#include <string.h>

#define maxlen 1000

void reverse(char s[]){
	int i, j, c;
	for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
		c = s[i];
		s[i] = s[j] ;
		s[j] = c;
	}
}

void itob(int n, char s[], int b){
	int i, j, sign;
	n = (sign = n) < 0 ? -n : n;
	i = 0;
	do{
		j = n % b;
		s[i++] = (j<=9) ? j + '0' : j + 'a' - 10;
	}while((n /= b) > 0);
	
	if(sign < 0){
		s[i++] = '-';
	}
	s[i] = '\0';
	
	reverse(s);
}

int main(){
	int num, b;
	char s[maxlen];
	
	num = 42425;
	b = 16;
	
	itob(num, s, b);
	
	printf("%s\n", s);
	
	return 0;
}
