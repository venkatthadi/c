#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode {
	char *word;
	int match;
	struct tnode *left;
	struct tnode *right;
};

#define MAXWORD	100

enum {NO, YES};

struct tnode *addtree (struct tnode *, char *, int, int *);
void treeprint (struct tnode *);
int getword (char *, int);

int main (int argc, char *argv[]) {
	struct tnode *root;
	char word[MAXWORD];
	int found = NO;
	int num;

	num = (--argc && (*++argv)[0] == '-') ? atoi(argv[0] + 1) : 6;
	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]) && strlen(word) >= num)
			root = addtree(root, word, num, &found);
		found = NO;
	}
	treeprint(root);

	return 0;
}
int compare (char *, struct tnode *, int, int *);

struct tnode *addtree (struct tnode *p, char *w, int num, int *found) {
	int cond;

	if (p == NULL) {
		p = (struct tnode *) malloc(sizeof(struct tnode));
		p->word = strdup(w);
		p->match = *found;
		p->left = p->right = NULL;
	} else if ((cond = compare(w, p, num, found)) < 0) {
		p->left = addtree(p->left, w, num, found);
	} else if (cond > 0) {
		p->right = addtree(p->right, w, num, found);
	}

	return p;
}

int compare (char *s, struct tnode *p, int num, int *found) {
	int i;
	char *t = p->word;

	for (i = 0; *s == *t; i++, s++, t++) {
		if (*s == '\0')
			return 0;
	}
	if (i >= num) {
		*found = YES;
		p->match = YES;
	}

	return *s - *t;
}

void treeprint (struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		if (p->match) 
			printf("%s\n", p->word);
		treeprint(p->right);
	}
}

#define BUFSIZE	100

char buf[BUFSIZE];
int bufp = 0;

int getword (char *word, int lim) {
	int c, d, getch(void), in_comment(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()));
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '#' || c == '_') {
		for (; --lim > 0; w++) {
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
		}
	} else if (c == '\'' || c == '"') {
		for(; --lim > 0; w++) {
			if ((*w = getch()) == '\\')
				*++w = getch();
			else if (*w == c) {
				w++;
				break;
			}
			else if (*w == EOF)
				break;
		}
	} else if (c == '/') {
		if (((d = getch()) == '*'))
			c = in_comment();
		else
			ungetch(d);
	}
	*w = '\0';

	return c;
}

int getch (void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (int c) {
	if (bufp >= BUFSIZE) 
		printf("too many characters\n");
	else
		buf[bufp++] = c;
}

int in_comment (void) {
	int c;

	while ((c = getch()) != EOF) {
		if (c == '*') {
			if ((c == getch()) == '/')
				break;
			else
				ungetch(c);
		}	
	}

	return c;
}
