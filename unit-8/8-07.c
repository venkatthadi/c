#include <stdio.h>
#include <stdlib.h>

#define MAXBYTES	(unsigned)10240
#define NALLOC		1024

typedef long align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	align x;
};

typedef union header Header;

//static unsigned maxalloc;
static Header base;
static Header *freep = NULL;

static Header *morecore (unsigned nu) {
	char *cp, *sbrk (int);
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;

	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)
		return NULL;

	up = (Header *) cp;
	up->s.size = nu;
	free((void *) (up + 1));
	return freep;
}

void *_malloc (unsigned nbytes) {
	Header *p, *prevp;
	Header *morecore (unsigned);
	unsigned nunits;

	if (nbytes > MAXBYTES) {
		fprintf(stderr, "can't allocate more than %u bytes\n", MAXBYTES);
		return NULL;
	}
	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *) (p + 1);
		}
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

void free (void *ap) {
	Header *bp, *p;

	bp = (Header *) ap - 1;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;
	}

	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else {
		bp->s.ptr = p->s.ptr;
	}

	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;

	freep = p;
}

int main() {
	int *p = NULL;
	int i;

	p = _malloc(1000);
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
		free(p);
	}

	return 0;
}
