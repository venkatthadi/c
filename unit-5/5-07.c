#include <stdio.h>
#include <string.h>

#define MAXLINES 1000

char *lineptr[MAXLINES];
char linestor[MAXLINES];

int readlines(char *lineptr[], char *linestor, int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *v[], int left, int right);

int main(){
	int nlines;

	if((nlines = readlines(lineptr, linestor, MAXLINES))){
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else{
		printf("error\n");
		return 0;
	}
}

#define MAXLEN 1000
#define MAXSTOR 5000

int _getline(char *, int);

int readlines(char *lineptr[], char *linestor, int maxlines){
	int len, nlines;
	char line[MAXLEN];
	char *p = linestor;
	char *linestop = linestor + MAXSTOR;

	nlines = 0;

	while((len = _getline(line, MAXLEN)) > 0)
		if(nlines >= maxlines || p + len > linestop)
			return -1;
		else{
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines){
	int i;
	for(i = 0; i < nlines; i++){
		printf("%s\n", lineptr[i]);
	}
}

void qsort(char *v[], int left, int right){
	int i, last;
	void swap(char *v[], int i, int j);

	if(left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for(i = left + 1; i <= right; i++){
		if(strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, left);
}

void swap(char *v[], int i, int j){
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;

}

int _getline(char *s, int maxlen){
	char *temp = s;
	int c;
	while((c=getchar()) != EOF && c != '\n')
		*s++ = c;
	if(c == '\n')
		*s++ = c;
	*s = '\0';
	return s - temp;
}
