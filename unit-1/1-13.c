#include <stdio.h>

#define MAXLEN 10
#define IN 1
#define OUT 0

void main(){

	int c, i, j;
	int hist[MAXLEN+1] = {0};
	int state = OUT;
	int len = 0;

	while((c=getchar())!=EOF){
		if(c == ' ' || c == '\t' || c == '\n'){
			if(state == IN && len > 0){
				if(len<=MAXLEN){
					++hist[len-1];
				}
				else{
					++hist[MAXLEN];
				}
			}
			state = OUT;
			len = 0;
		}
		else{
			++len;
			if(state == OUT)
				state = IN;
		}
	}
	
	/* for(i=0; i<=MAXLEN; ++i)
		printf("%d",hist[i]); */
		
	// histogram
	
	for(i=0; i<MAXLEN; ++i){
		printf("%3d - ",i+1);
		for(j=0; j<hist[i]; ++j){
			printf("*");
		}
		printf("\n");
	}
	printf(">%2d - ",MAXLEN);
	for(i=0; i<hist[MAXLEN]; ++i){
		printf("*");
	}
	printf("\n");
		
}
