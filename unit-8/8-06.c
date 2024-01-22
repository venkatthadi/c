#include <stdio.h>
#include <stdlib.h>

void *_calloc (unsigned, unsigned);

int main (int argc, char **argv) {
	int *p;
	int i;
	
	p = _calloc(100, sizeof(*p));
	if (p == NULL) {
		printf("_calloc returned NULL\n");
		return 1;
	} else {
		for (i = 0; i < 100; i++) {
			printf("%08X ", p[i]);
			if (i % 8 == 7) {
				printf("\n");
			}
		}
		printf("\n");
	        free(p);
	}
	
	return 0;
}

void *_calloc (unsigned n, unsigned size) {
	unsigned i, nb;
	char *p, *q;

	nb = n * size;

	if ((p = q = malloc(nb)) != NULL)
		for (i = 0; i < nb; i++)
			*p++ = 0;

	return q;
}
