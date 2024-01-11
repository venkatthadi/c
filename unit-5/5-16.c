#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM 		1
#define REV 		2
#define FOLD		4
#define DIRE		8
#define MAXLINE 	1000

int numcmp(char *, char *);
int charcmp(char *, char *);
int readlines(char *lineptr[], int maxlines);
void _qsort(char *v[], int left, int right, int (*comp) (void *, void *));
void writelines(char *lineptr[], int nlines, int decr);

static char option = 0;

int main(int argc, char *argv[]){
	char *lineptr[MAXLINE];
	int nlines, c, rc = 0;

	while((--argc > 0) && (*++argv)[0] == '-')
		while(c = *++argv[0]){
			switch(c){
				case 'd':
					option |= DIRE;
					break;
				case 'f':
					option |= FOLD;
					break;
				case 'n':
					option |= NUM;
					break;
				case 'r':
					option |= REV;
					break;
				default:
					printf("invalid command\n");
					argc = 1;
					rc = -1;
					break;
			}
		}

	if(argc)
		printf("-nr : \n");
	else{
		if((nlines = readlines(lineptr, MAXLINE)) > 0){
			if(option & NUM)
				_qsort(lineptr, 0, nlines - 1, (int (*) (void *, void *)) numcmp);
			else
				_qsort(lineptr, 0, nlines - 1, (int (*) (void *, void *)) charcmp);
			writelines(lineptr, nlines, option & REV);
		}
		else{
			printf("input too long\n");
			rc = -1;
		}
	}
	return rc;
}

void writelines(char *lineptr[], int nlines, int decr){
	int i;
	if(decr){
		for(i = nlines - 1; i >= 0; --i)
			printf("%s\n", lineptr[i]);
	}
	else{
		for(i = 0; i < nlines; i++)
			printf("%s\n", lineptr[i]);
	}
}

int numcmp(char *s1, char *s2){
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	
	if(v1 > v2)
		return 1;
	else if(v1 < v2)
		return -1;
	else
		return 0;
}

int charcmp(char *s, char *t) {
    char a, b;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & DIRE) ? 1 : 0;

    do {
        if (dir) {
            while (!isalnum(*s) && *s != ' ' && *s != '\0')
                s++;
            while (!isalnum(*t) && *t != ' ' && *t != '\0')
                t++;
        }
        a = fold ? tolower(*s) : *s;
        s++;
        b = fold ? tolower(*t) : *t;
        t++;

        if (a == b && a == '\0')
            return 0;
    } while (a == b);

    return a - b;
}


#define MAXLEN 1000

int _getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines){
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;

	while((len = _getline(line, MAXLEN)) > 0){
		if(nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else{
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}

	return nlines;
}

int _getline(char *line, int max){
	int i = 0, c;

	while((c = getchar()) != EOF && c !='\n')
		line[i++] = c;
	if(c == '\n')
		line[i++] = c;
	line[i] = '\0';
	
	return i;
}

#define	ALLOCSIZE	1000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n){
	if(allocbuf + ALLOCSIZE - allocp >= n){
		allocp += n;
		return (allocp - n);
	}
	else{
		return 0;
	}
}

void afree(char *p){
	if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

/* qsort function */

void swap(char *v[], int i, int j){
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void _qsort(char *v[], int left, int right, int (*comp) (void *, void *)){
	int i, last;
	if(left >= right)
		return;
	last = left;
	swap(v, left, (left + right) / 2);
	for(i = left + 1; i <= right; i++){
		if((*comp) (v[i], v[left]) < 0){
			swap(v, i, left);
		}
	}
	swap(v, left, last);
	_qsort(v, left, last - 1, comp);
	_qsort(v, last + 1, right, comp);
}
