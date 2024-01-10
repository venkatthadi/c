#include <stdio.h>

#define max 100

void squeeze(char s1[], char s2[]){
	int i, j, k = 0;
	int flag;
	for(i = 0; i < max; i++){
		flag = 0;
		for(j = 0; j < max; j++){
			if(s1[i] == s2[j])
				flag = 1;
		}
		if(!flag){
			s1[k++] = s1[i];
		}
	}
	s1[k] = '\0';
	printf("%s", s1);
}

int main(){
	char s1[max], s2[max];
	int i = 0, c;
	while((c=getchar()) != '\n' && c != EOF){
		s1[i++] = c;
	}
	i = 0;
	while((c=getchar()) != '\n' && c != EOF){
		s2[i++] = c;
	}
	squeeze(s1, s2);
	return 0;
}
