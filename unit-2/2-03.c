#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>

int htoi(){
	int n = 0, c;

	if((c = getchar()) == '0'){
		if((c=getchar()) == 'x' || c == 'X')
			c = getchar();
	}
	
	if(isdigit(c)){
		n = 16 * n + (c - '0');
	}
	else if(c >= 'a' && c <= 'f'){
		n = 16 * n + (c - 'a' + 10);
	}
	else if(c >= 'A' && c <= 'F'){
		n = 16 * n + (c - 'A' + 10);
	}
	
	while((c=getchar()) != EOF){
		if(isdigit(c)){
			n = 16 * n + (c - '0');
		}
		else if(c >= 'a' && c <= 'f'){
			n = 16 * n + (c - 'a' + 10);
		}
		else if(c >= 'A' && c <= 'F'){
			n = 16 * n + (c - 'A' + 10);
		}
	}
	return n;
}

int main(){
	printf("%d", htoi());
	return 0;
}
