#include <stdio.h>

#define MAXL 10

int getLine(char line[], int maxl){
	int i, c;
	for(i = 0; i < maxl-1 && (c = getchar()) != EOF && c != '\n'; ++i){
		line[i] = c;
	}
	if(c == '\n'){
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

void copy(char to[], char from[]){
	int i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
}

void main(){
	int len;
	int lenx;
	int max_len = 0;
	char curr[MAXL];
	char currx[MAXL];
	char longest[MAXL];
	
	while((len = getLine(curr, MAXL)) > 0){
		if(len == MAXL-1 && curr[MAXL-2] != '\n')
			while((lenx = getLine(currx, MAXL)) > 0 && (len = len + lenx) && currx[lenx-1] != '\n');
		if(len > max_len){
			max_len = len;
			copy(longest, curr);
		}
		len = 0;
	}
	if(max_len > 0){
		printf("%d", max_len-1);
	}
}
