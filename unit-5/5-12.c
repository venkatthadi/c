#include <stdio.h>
#include <stdlib.h>

#define TAB 8

void entab(int , int);
void detab(int, int);

int main(int argc, char *argv[]){
	int pos, tabinc;

	if(argc > 3){
		printf("too many arguments\n");
		return 0;
	}
	if(argc <= 1){
		detab(0, TAB);
	}
	else if(argc == 3 && argv[1] == '-' && argv[2] == '+'){
		pos = atoi(argv[1]);
		tabinc = atoi(argv[2]);
		detab(pos, tabinc);
		entab(pos, tabinc);
	}
	else{
		pos = atoi(argv[1]);
		detab(pos, TAB);
		entab(pos, TAB);
	}

	return 0;
}

void detab(int m, int n){
	int c, i, ntab = 0,  pos = 1;
	m = -m;

	while((c = getchar()) != EOF && c != '\n'){
		if(m-- > 0){
			putchar(c);
		}
		else
		if(c == '\t'){
			ntab = n - (pos - 1);
			for(i = 0; i < ntab; i++){
				putchar(' ');
			}
		}
		else{
			putchar(c);
			pos++;
			if(pos == n)
				pos = 0;	
		}
	}
}

void entab(int m, int n){
	int c;	
	int ntab = 0, nspace = 0, pos = 1;
	m = -m;

	while((c = getchar()) != EOF && c != '\n'){
		if(m-- > 0){
			putchar(c);
			continue;
		}
		pos++;
		if(c == ' '){
			if(pos % n == 0){
				ntab++;
				nspace = 0;
			}
			else{
				nspace++;
			}
		}
		else{
			while(ntab > 0){
				putchar('\t');
				ntab--;
			}
			if(c == '\t'){
				nspace = 0;
				putchar('\t');
				pos += n - (pos % n);
			}
			else{
				while(nspace > 0){
					putchar(' ');
					nspace--;
				}
				putchar(c);
				if(c == '\n'){
					pos = 0;
					ntab = 0;
					nspace = 0;
				}
			}
		}

	}
}
