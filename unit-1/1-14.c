#include <stdio.h>

void main(){
	int c, i, j;
	int letters[26] = {0};
	while((c=getchar())!=EOF){
		if(c >= 'a' && c <= 'z'){
			++letters[c - 'a'];
		}
	}
	for(i=0; i<26; ++i){
		printf("%c - ",'a'+i);
		for(j=0; j<letters[i]; ++j){
			printf("*");
		}
		printf("\n");
	}
}
