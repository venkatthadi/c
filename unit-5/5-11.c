#include <stdio.h>
#include <stdlib.h>

void entab(int argc, char **);
void detab(int, char **);

int main(int argc, char *argv[]){
	entab(argc, argv);
	detab(argc, argv);
	return 0;
}

void detab(int argc, char *argv[]){
	if(argc != 2 || atoi(argv[1]) <= 0){
		printf("not sufficient parameters\n");
		return;
	}

	int c, i;
	int ntab = 0,  pos = 1;

	while((c = getchar()) != EOF && c != '\n'){
		if(c == '\t'){
			ntab = atoi(argv[1]) - (pos - 1);
			for(i = 0; i < ntab; i++){
				putchar(' ');
			}
			pos = 0;
		}
		else{
			putchar(c);
			pos++;
			if(pos == atoi(argv[1]))
				pos = 0;	
		}
	}
}

void entab(int argc, char *argv[]){
	if(argc != 2){
		printf("not sufficient parameters\n");
		return;
	}

	int c;	
	int ntab = 0, nspace = 0, pos = 1;

	while((c = getchar()) != EOF && c != '\n'){
		pos++;

		if(c == ' '){
			if(pos % atoi(*(argv + 1)) == 0){
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
				pos += atoi(*(argv + 1)) - (pos % atoi(*(argv + 1)));
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
