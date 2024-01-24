#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 1000
#define DEFAULT 8

struct tnode {
	char *word;
	int count;
	struct linenumber *linenumbers;
	struct tnode *left;
	struct tnode *right;
};

struct linenumber {
	int *number;
	struct linenumber *nextnumber;
};

struct simroot {
	struct simword *firstword;
	struct simroot *nextroot;
};

struct simword {
	char *word;
	int count;
	int linenumber;
	struct simword *nextword;
};

struct tnode *addtree (struct tnode *, char *, int);
void treeprint (const struct tnode *);
int mgetword (char *, int, int *);
struct linenumber *lnumberalloc (void);
struct linenumber *addlinenumber (struct linenumber *, int);

int main (int argc, char *argv[]){
	struct tnode *root;
	char word[MAXWORD];
	int len, lineno = 0;

	root = NULL;
	while(mgetword(word, MAXWORD, &lineno) != EOF){
		if (isalpha(word[0]))
			root = addtree(root, word, lineno);
	}

	if(argc == 1)
		len = DEFAULT;
	else if(argc == 2)
		len = atoi(argv[1]);
	else
		printf("invalid parameters \n");

	treeprint(root);

	return 0;
}

struct tnode *talloc (void);
char *mstrdup (char *);

int mgetword (char *word, int lim, int *lineno_addr) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	int t;

	while(isspace(c = getch())){
		if (c == '\n')
			*lineno_addr += 1;
	}
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

struct tnode *addtree (struct tnode *p, char *w, int linenumber) {
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = mstrdup(w);
		p->count = 1;
		p->linenumbers = NULL;
		p->linenumbers = addlinenumber(p->linenumbers, linenumber);
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++;
		p->linenumbers = addlinenumber(p->linenumbers, linenumber);
	} else if (cond < 0) {
		p->left = addtree(p->left, w, linenumber);
	} else
		p->right = addtree(p->right, w, linenumber);

	return p;
}

struct linenumber *addlinenumber (struct linenumber *p, int linenumber) {
	if (p == NULL) {
		p = lnumberalloc();
		p->number = linenumber;
		p->nextnumber = NULL;
	} else {
		p->nextnumber  = addlinenumber(p->nextnumber, linenumber);
	}

	return p;
}

struct linenumber *lnumberalloc (void) {
	return (struct linenumber *) malloc(sizeof(struct linenumber));
}

void printnumbers (struct linenumber *p) {
	if (p != NULL) {
		printf("%d, ", p->number);
		printnumbers(p->nextnumber);
	}
}

void treeprint (const struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("\n%s :", p->word);
		printnumbers(p->linenumbers);
		treeprint(p->right);
	}
}

struct tnode *talloc (void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *mstrdup (char *s)	{
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch() */
int bufp = 0;      /* next free position in buf */

int getch(void) { /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
    return;
}

