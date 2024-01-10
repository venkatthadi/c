#include <stdio.h>
#define max 100

int getl(char s[], int len){
	int c, i;
	i = 0;
	
	while(--len && (c=getchar()) != EOF && c != '\n'){
		s[i++] = c;
	}
	if(c == '\n'){
		s[i++] = c;
	}
	s[i] = '\0';
	
	return i;
}

int strindex(char s[], char t[]){
	int ind = -1, i, j, k;
	
	for(i = 0; s[i] != '\0'; i++){
		for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
		if(k > 0 && t[k] == '\0')
			ind = i;
	}
	
	return ind;
}

int main(){
	char line[max];
	char pattern[] = "abc";
	int ind = 0, len;
	
	while((getl(line,max)) > 0){
		len = strindex(line, pattern);
		if(len > ind){
			ind = len;
		}
	}
	printf("%d\n", ind);
	
	return 0;
}
