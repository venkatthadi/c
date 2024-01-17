#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 1000

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct words {
	char *words;
	int counts;
};

struct tnode *addtree (struct tnode *, char *);
int mgetword (char *, int);
void sort (struct words *);

int countword = 0;
int i = 0;

int main() {
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (mgetword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			root = addtree(root, word);
		}
	}

	struct words sortword[countword];
	void fillarray(struct tnode *, struct words *);
	fillarray(root, sortword);
	sort(sortword);

	int j;
	for (j = 0; j < countword; j++) {
		printf("%s -> %d\n", sortword[j].words, sortword[j].counts);
	}

	return 0;
}

void fillarray (struct tnode *p, struct words sortword[]) {
	if (p != NULL) {
		fillarray(p->left, sortword);
		sortword[i++] = (struct words) {p->word, p->count};
		fillarray(p->right, sortword);
	}
}

void sort (struct words sortword[]){
	struct words temp;
	int i, j;
	
	for(i = 1; i < countword; i++){
		temp = sortword[i];
		for(j = i - 1; j >= 0 && sortword[j].counts > temp.counts; j--){
			sortword[j + 1] = sortword[j];
			sortword[j] = temp;
		}
	}
}

struct tnode *talloc (void);
char *s_dup (char *);

struct tnode *addtree (struct tnode *p, char *w){
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = s_dup(w);
		countword++;
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count ++;
	else if (cond < 0) {
		p->left = addtree(p->left, w);
	} else {
		p->right = addtree(p->right, w);
	}

	return p;
}

struct tnode *talloc (void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *s_dup (char *s) {
	char *p;

	p = (char *) malloc(strlen(s) + 1);
	if(p != NULL)
		strcpy(p, s);
	
	return p;
}

int mgetword (char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	int t;
	
	while(isspace(c = getch()));
	
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		if (c == '\"'){
			while((c = getch()) != '\"');
		} else if (c == '#') {
			while((c = getch()) != '\n');
		} else if (c == '/') {
			if ((c = getch()) == '/')
				while((c = getch()) != '\n');
			else if (c == '*') {
				for (c = getch(), t = getch(); c != '*' && t != '/';)
					ungetch(t);
			} else
				ungetch(c);
		} else
			for (; !isspace(c) && c != EOF; c = getch());
		if (c != '\"' && c != '\n' && c != '/')
			ungetch(c);
		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			if(!isspace(*w)) {
				ungetch(*w);
				return (*w);
			} else {
				ungetch(*w);
				break;
			}
		}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0; 

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
    return;
}
