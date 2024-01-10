#include <stdio.h>

#define max 1000

int get_length(char line[]){
	int i, c;
	
	for(i = 0; i < max && (c=getchar()) != EOF && c != '\n'; ++i){
		line[i] = c;
	}
	if(c == '\n'){
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	
	return i;
}

void reverse(char line[], int len){
	int j, c;
	char revline[len+1];
	
	for(j = 0; j < len; ++j){
		revline[j] = line[len-j-1];
	}
	revline[j + 1] = '\0';
	
	printf("%s",revline); 
}

int main(){
	int len;
	char line[max];
	while((len = get_length(line)) > 0){
		reverse(line, len);
	}
	return 0;
}


