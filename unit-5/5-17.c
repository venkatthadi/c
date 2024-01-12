#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

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
void readargs(int argc, char *argv[]);

int option = 0;
int pos1 = 0;
int pos2 = 0;

int main(int argc, char *argv[]){
	char *lineptr[MAXLINE];
	int nlines, c, rc = 0;

	readargs(argc, argv);

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
	return rc;
}

void readargs(int argc, char *argv[]){
	int c;

    while (--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+') {
        if (c == '-' && !isdigit(*(argv[0] + 1)))
            while (c = *++argv[0])
                switch (c) {
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
                        printf("sort: illegal option %c \n", c);
                        break;
                }
        else if (c == '-')
            pos2 = atoi(argv[0] + 1);
        else if ((pos1 = atoi(argv[0] + 1)) < 0)
            printf("Usage: sort -dfnr [+pos1][-pos2]\n");
    }

    if (argc || pos1 > pos2)
        printf("Usage: sort -dfnr [+pos1] [-pos2]\n");
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

void substr(char *, char*);

int numcmp(char *s1, char *s2){
	double v1, v2;
	char str[MAXLINE];

	substr(s1, str);
	v1 = atof(str);

	substr(s2, str);
	v2 = atof(str);
	
	if(v1 > v2)
		return 1;
	else if(v1 < v2)
		return -1;
	else
		return 0;
}

void substr(char *s, char *str) {
    int i, j, len;
    extern int pos1, pos2;

    len = strlen(s);

    if (pos2 > 0 && len > pos2)
        len = pos2;
    else if (pos2 > 0 && len < pos2)
        printf("substr: string too short\n");
    for (j = 0, i = pos1; i < len; i++, j++)
        str[j] = str[i];
    str[j] = '\0';
}

int charcmp(char *s, char *t) {
    char a, b;
    int i, j, endpos;

    extern int option, pos1, pos2;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & DIRE) ? 1 : 0;

    i = j = pos1;

    if (pos2 > 0)
        endpos = pos2;
    else if ((endpos = strlen(s)) > strlen(t))
        endpos = strlen(t);

    do {
        if (dir) {
            while (i < endpos && !isalnum(s[i]) && s[i] != ' ' && s[i] != '\0')
                s[i] != ' ' && s[i] != '\0';
            i++;
            while (j < endpos && !isalnum(t[j]) && t[j] != ' ' && t[j] != '\0')
                t[j] != ' ' && t[j] != '\0';
            j++;
        }
        if (i < endpos && j < endpos) {
            a = fold ? tolower(s[i]) : s[i];
            i++;
            b = fold ? tolower(t[j]) : t[j];
            j++;

            if (a == b && a == '\0')
                return 0;
        }
    } while (a == b && i < endpos && j < endpos);

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
