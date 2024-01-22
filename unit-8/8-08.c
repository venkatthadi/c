#include <stdio.h>
#include <stdlib.h>

#define MAXBYTES (unsigned)1024

typedef long align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	align x;
};

typedef union header Header;

unsigned bfree (void *p, unsigned n) {
	Header *hp;

	if (n < sizeof(Header)) {
		return 0;
	} 

	hp = (Header *) p;
	hp->s.size = n / sizeof(Header);
	free((void *) (hp + 1));
	return hp->s.size;
}

int main() {
	int *p = NULL;
	int i;

	p = malloc(100 * sizeof(*p));
	if (p == NULL) {
		printf("returned NULL\n");
	} else {
		for (i = 0; i < 100; i++) {
			printf("%08X ", p[i]);
			if (i % 8 == 7) {
				printf("\n");
			}
		}
		printf("\n");
		bfree(p, sizeof(*p));
		// printf("%08X\n", p[0]);
	}

	return 0;
}
