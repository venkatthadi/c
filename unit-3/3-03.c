#include <stdio.h>

#define max 1000

void expand(char s1[], char s2[]){
	int c;
	int i = 0;
	int j = 0;
	
	while((c = s1[i++]) != '\0'){
		if(s1[i] == '-' && s1[i+1] >= c){
			++i;
			while(c < s1[i]){
				s2[j++] = c++;
			}
		}
		else{
			s2[j++] = c;
		}
	}
	s2[j] = '\0';
}

int main(){
	int c, i = 0;
	char s[max], t[max];	
	
	while((c=getchar()) != EOF && i < max - 1){
		s[i++] = c;
	}
	s[i] = '\0';
	
	expand(s,t);
	
	printf("%s", t);
	
	return 0;
}
