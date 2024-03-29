#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#define MAXWORD	1000
#define DEFAULT	6

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct simroot {
	struct simword *firstword;
	struct simroot *nextroot;
};

struct simword {
	char *word;
	int count;
	struct simword *nextword;
};

struct tnode *addtree (struct tnode*, char *);
void treeprint (struct tnode *);
int _getword (char *, int);
struct simroot *addroot (struct simroot *, struct tnode *, int);
struct simroot *parse (struct tnode *, int);
void printlist (struct simroot *, int);
void printwords (struct simword *);

int main (int argc, char *argv[]){
	struct tnode *root;
	char word[MAXWORD];
	struct simroot *listroot;
	int len;

	root = NULL;
	while (_getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	
	if (argc == 1)
		len = DEFAULT;
	else if (argc == 2)
		len = atoi(argv[1]);
	else{
		printf("incorrect arguments\n");
		return 0;
	}

	listroot = NULL;
	listroot = parse(root, len);
	treeprint(root);
	printf("list : \n");
	printlist(listroot, len);

	return 0;
}

struct simroot *parse (struct tnode *node, int len){
	struct tnode *temp;
	int this_len;
	static struct simroot *root = NULL;

	if(node == NULL)
		return NULL;

	this_len = strlen(node->word);
	parse(node->left, len);

	temp = node->left;
	if(temp != NULL){
		while (temp->right != NULL)
			temp = temp->right;
		if(this_len >= len && strncmp(temp->word, node->word, len) == 0){
			root = addroot(root, temp, len);
			addroot(root, node, len);
		}
	}

	temp = node->right;
	if(temp != NULL){
		while (temp->left != NULL)
			temp = temp->left;
		if(this_len >= len && strncmp(temp->word, node->word, len) == 0){
                        root = addroot(root, temp, len);
                        addroot(root, node, len);
                }

	}

	parse(node->right, len);

	return root;
}

void printlist (struct simroot *p, int len){
	int i;
	if(p == NULL)
		return;
	for(i = 0; i < len; i++){
		putchar(p->firstword->word[i]);
	}
	putchar('\n');
	printwords(p->firstword);
	printlist(p->nextroot, len);
}

void printwords (struct simword *p){
	printf("%4d %s\n", p->count, p->word);
	if(p->nextword != NULL)
		printwords(p->nextword);
}

struct tnode *talloc (void);
char *_strdup (char *);
struct simword *walloc (struct simword *, struct tnode *);
void addword (struct simword *, struct tnode *);

struct simroot *addroot (struct simroot *p, struct tnode *n, int len) {
	if (p == NULL) {
		p = (struct simroot *) malloc(sizeof(struct simroot));
		p->nextroot = NULL;
		p->firstword = walloc(p->firstword, n);
	} else if (strncmp(p->firstword->word, n->word, len) == 0)
		addword(p->firstword, n);
	else
		p->nextroot = addroot(p->nextroot, n, len);

	return p;
}

void addword (struct simword *p, struct tnode *n) {
	if (strcmp(p->word, n->word) == 0)
		return;
	if (p->nextword == NULL)
		p->nextword = walloc(p->nextword, n);
	else
		addword(p->nextword, n);
}

struct simword *walloc(struct simword *p, struct tnode *n) {
    p = (struct simword *) malloc(sizeof(struct simword));
    if (p != NULL) {
        p->word = n->word;
        p->count = n->count;
        p->nextword = NULL;
    }
    return p;
}

#define IN 1
#define OUT 0

int _getword(char *word, int lim) {
    int c, d, getch(void), comment, string, directive;
    void ungetch(int);
    char *w = word;

    comment = string = directive = OUT;

    while (isspace(c = getch()));

    if (c == '/') {
        if ((d = getch()) == '*') {
            comment = IN;
        } else {
            comment = OUT;
            ungetch(d);
        }
    }

    if (c == '\"') {
        string = IN;
    }

    if (c == '#') {
        directive = IN;
    }

    if (c == '\\') {
        c = getch(); 
    }

    if (comment == OUT && string == OUT && directive == OUT) {

        if (c != EOF)
            *w++ = c;

        if (!isalnum(c) && c != '_') {
            *w = '\0';
            return c;
        }

        for (; --lim > 0; w++) {
            *w = getch();
            if (!isalnum(*w) && *w != '_') {
                ungetch(*w);
                break;
            }
        }
        *w = '\0';
        return word[0];
    } else if (comment == IN) {
        *w++ = c;
        *w++ = d;

        while ((*w++ = c = getch())) {
            if (c == '*') {
                if ((c = getch()) == '/') {
                    *w++ = c;
                    comment = OUT;
                    break;
                } else {
                    ungetch(c);
                }
            }
        }
        *w = '\0';

    } else if (string == IN) {
        *w++ = c;
        while ((*w++ = getch()) != '\"') {
            if (*w == '\\') 
                *w++ = getch();
        }
        string = OUT;
        *w = '\0';
    } else if (directive == IN) {
        *w++ = c;
        while ((*w++ = getch()) != '\n') {
            if (c == '\\') { 
                *w++ = getch();
            }
        }
        directive = OUT;
        *w = '\0';
    }

    return c;
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) { 
        p = talloc();
        p->word = _strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *_strdup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
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
