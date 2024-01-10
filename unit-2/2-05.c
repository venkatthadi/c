#include <stdio.h>

#define max 100

int squeeze(char s1[], char s2[]){
	int i, j;
	int pos = -1;
	for(i = 0; i < max; i++){
		for(j = 0; j < max; j++){
			if(s1[i] == s2[j]){
				pos = i;
				break;
			}
		}
		if(pos != -1)
			break;
	}
	return pos;
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
	printf("%d\n", squeeze(s1, s2));
	return 0;
}
