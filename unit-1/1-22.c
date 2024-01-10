#include <stdio.h>

int lim = 10;
int tab_val = 4;

int last_blank(char line[], int len){
	int i, lb = -1;
	for(i = 0; i < len; ++i){
		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			lb = i;
	}
	return lb;
}

void main(){
	int i, j, c;
	int pos, col, lb;
	char line[lim + 1];
	pos = col = 0;
	while((c = getchar()) != EOF){
	
		line[pos++] = c;
		
		if(c == '\t')
			col += (tab_val - (col%tab_val));
		else
			col += 1;
		
		if(col >= lim || c == '\n'){
			line[pos] = '\0';
			if((lb = last_blank(line, pos)) == -1){
				for(i = 0; i < pos; ++i){
					putchar(line[i]);
				}
				col = pos = 0;
			}
			else{
				for(i = 0; i < lb; ++i){
					putchar(line[i]);
				}
				for(i = 0, j = lb + 1, col = 0; j < pos; ++i, ++j){
					line[i] = line[j];
					if(c == '\t')
						col += (tab_val - (col%tab_val));
					else
						col += 1;
				}
				pos = i;
			}
			putchar('\n');
		}
	}
}
