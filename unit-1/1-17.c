#include <stdio.h>

#define MAX 1000
#define lim 80

int get_line(char line[], int max){
	int i, c;
	for(i = 0; i < max && (c=getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
		
	if(c == '\n'){
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

int main(){
	int len;
	char line[MAX];
	
	while((len = get_line(line, MAX)) > 0)
		if(len > lim)
			printf("%s", line);
			
	return 0;
}
