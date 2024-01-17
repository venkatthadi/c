#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 1000

int mgetword (char *, int, int *);

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;	
};

#define HASHSIZE 101

struct nlist *hashtab[HASHSIZE];

unsigned hash (char *s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}
	
	return hashval % HASHSIZE;
}

struct nlist *lookup (char *name) {
	struct nlist *np;

	for (np = hashtab[hash(name)]; np != NULL; np = np->next)
		if (strcmp(name, np->name) == 0)
			return np;

	return NULL;
}

struct nlist *install (char *name, char *defn) {
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));

		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;

		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else {
		free((void *) np->defn);
	}

	if ((np->defn = strdup(defn)) == NULL)
		return NULL;

	return np;

}

int main() {
	int lineno = 0;
	char word[MAXWORD];
	char key[MAXWORD], value[MAXWORD];

	struct nlist *result;

	while (mgetword(word, MAXWORD, &lineno) != EOF) {
		if (strcmp(word, "#define ") == 0) {
			mgetword(key, MAXWORD, &lineno);
			mgetword(value, MAXWORD, &lineno);
			install(key, value);
			result = lookup(key);
			printf("%s - %s\n", result->name, result->defn);
		}
	}

	return 0;
}

#define IN 1
#define OUT 0

int mgetword(char *word, int lim, int *lineno_addr) {
    int c, d, getch(void), comment, string, directive;
    void ungetch(int);
    char *w = word;

    comment = string = directive = OUT;

    while (isspace(c = getch())) {
        if (c == '\n') {

            *lineno_addr = *lineno_addr + 1;
        }
    }

    /* Check if inside a comment */

    if (c == '/') {
        if ((d = getch()) == '*') {
            comment = IN;
        } else {
            comment = OUT;
            ungetch(d);
        }
    }

    /* Check if inside a quote */

    if (c == '\"') {
        string = IN;
    }

    /* Check if inside a directive */

    if (c == '#') {
        directive = IN;
    }

    if (c == '\\') {
        c = getch(); /* ignore the \\ character */
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
            if (*w == '\\') /* Take care of escaped quotes */
                *w++ = getch();
        }
        string = OUT;
        *w = '\0';
    } else if (directive == IN) {
        *w++ = c;
        while ((*w++ = getch()) != ' ') {
            if (c == '\\') { /* Take care of continuation line escape */
                *w++ = getch();
            }
        }

        directive = OUT;
        *w = '\0';
    }

    return c;
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
