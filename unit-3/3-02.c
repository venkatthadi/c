#include <stdio.h>

#define max 100

void escape(char s[], char t[]){
	int i,j = 0;
	
	for(i = 0; i < max && s[i] != '\0'; i++){
		if(s[i] == '\n'){
			t[j++] = '\\';
			t[j++] = 'n';
		}
		else if(s[i] == '\t'){
			t[j++] = '\\';
			t[j++] = 't';
		}
		else{
			t[j++] = s[i];
		}
	}
	t[j] = '\0';
	
	printf("%s\n", t);
}

void inverse(char s[], char t[]){
	int i = 0, j = 0;
	
	while(s[i] != '\0'){
		if(s[i] == '\\'){
			if (s[i+1] == 'n'){
				t[j++] = '\n';
				i += 2;
			}
			else if(s[i+1] == 't'){
				t[j++] = '\t';
				i += 2;
			}
		}
		t[j++] = s[i++];
	}
	t[j] = '\0';
	
	printf("%s\n", t);
}

int main(){
	int c;
	char s[max], t[max];
	int i=0;
	
	while((c=getchar()) != EOF){
		s[i++] = c;
	}
	s[i] = '\0';
	escape(s,t);
	inverse(s,t);
	return 0;
}
