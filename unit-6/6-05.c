#include <stdio.h>
#include <stdlib.h>

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned hash (char *s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++) 
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

struct nlist *lookup (char *s) {
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	
	return NULL;
}

char *strdup (char *s);

struct nlist *install (char *name, char *defn) {
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(struct nlist));
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

struct nlist *undef (char *s){
	struct nlist *found;
	found = lookup(s);
	
	if(found == NULL)
		return NULL;
	else {
		if (found->next != NULL) {
			found->next = found->next->next;
			found = found->next;
		} else {
			hashtab[hash(s)] = NULL;
			free((void *) found);
		}
	}
	
	return found;
}

int main() {
	struct nlist *table[4] = {
		(install("key1", "value1")), (install("key2", "value2")),
		(install("key3", "value3")), (install("key4", "value4")) };
	int i;

	undef("key2");

	struct nlist *result;
	char *keys[4] = {"key1", "key2", "key3", "key4"};

	for (i = 0; i < 4; i++) {
		if ((result = lookup(keys[i])) == NULL) {
			printf("key not found\n");
		} else {
			printf("%s -> %s \n", result->name, result->defn);
		}
	}

	return 0;
}
