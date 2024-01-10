#include <stdio.h>

int paren, brack, brace;

void incomment(){
	int c, d;
	
	c = getchar();
	d = getchar();
	
	while(c!='*' || d!= '/'){
		c = d;
		d = getchar();
	}
}

void inquote(int c){
	int d;
	
	while((d=getchar()) != c){
		if(d == '\\')
			getchar();
	}
}

void search(int c){
	extern int paren, brack, brace;
	
	if(c == '{') --brace;
	else if(c == '}' && brace < 0) ++brace;
	else if(c == '[') --brack;
	else if(c == ']' && brack < 0) ++brack;
	else if(c == '(') --paren;
	else if(c == ')' && paren < 0) ++paren;
}

void main(){
	extern int paren, brack, brace;
	int c;
	
	while((c=getchar()) != EOF){
		if(c == '/'){
			if((c==getchar()) == '*')
				incomment();
			else
				search(c);
		}
		else if(c == '\'' || c == '\"'){
			inquote(c);
		}
		else
			search(c);
	}
	
	if(brace != 0){
		printf("unmatched braces\n");
		brace = 0;
	}
	else if(brack != 0){
		printf("unmatched brackets\n");
		brack = 0;
	}
	else if(paren != 0){
		printf("unmatched parentheses\n");
		paren = 0;
	}
}
