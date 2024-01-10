#include <stdio.h>
#include <string.h>

#define maxline 1000
#define abs(x) ((x) > 0 ? (x) : -(x))

void reverse(char arr[]){
	int i, j, c;
	for(i = 0, j = strlen(arr) - 1; i < j; i++, j--){
		c = arr[i];
		arr[i] = arr[j];
		arr[j] = c;
	}
}

void itoa(int n, char s[]){
	int sign = n;
	int i = 0;
	do{
		s[i++] = abs(n % 10) + '0';
		n /= 10;
	}while(n != 0);
	if(sign < 0){
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}

int main(){
	int num;
	char s[maxline];
	
	num = -2147483648;
	itoa(num, s);
	
	printf("%s\n", s);
	
	return 0;
}
