#include <stdio.h>

#define max 1000

int getlength(char line[]){
	int i, c;
	int len = 0, length = 0;
	for(i = 0; i < max && (c=getchar()) != EOF && c != '\n'; ++i){
		line[i] = c;
		++len;
	}
	if(c == '\n'){
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	for(i = 0; i < len; ++i){
		if(line[i] != ' ' && length < i){
			length = i;
		} 
	}
	return length;
}

int main(){
	int len, i;
	char line[max];
	
	while((len = getlength(line)) > 0){
		for(i = 0; i <= len; ++i)
			printf("%c", line[i]);
	}
	return 0;
}
