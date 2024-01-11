#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT 10
#define MAXLEN 1000
#define MAXLINES 100

int _getline(char *, int);

int main(int argc, char **argv){
	char *p;
	char *buf;
	char *bufmax;

	char line[MAXLEN];
	char *lineptr[MAXLINES];
	
	int first, i, last, len, n, nlines;

	if(argc == 1)
		n = DEFAULT;
	else if(argc == 2 && (*++argv)[0] == '-'){
		n = atoi(argv[0] + 1);
	}

	if(n < 1 || n > MAXLINES)
		n = MAXLINES;

	for(i = 0; i < MAXLINES; i++){
		lineptr[i] = NULL;
	}

	if((p = buf = malloc(MAXLINES * MAXLEN)) == NULL){
		printf("memory not allocated\n");
	}
	bufmax = buf + MAXLINES + MAXLEN;

	last = 0;
	nlines = 0;

	while((len = _getline(line, MAXLEN)) > 0){
		if(p + len + 1 >= bufmax)
			p = buf;
		lineptr[last] = p;
		strcpy(lineptr[last], line);
		if(++last >= MAXLINES)
			last = 0;
		p += len + 1;
		nlines++;
	}

	if(n > nlines)
		n = nlines;

	first = last - n;
	if(first < 0)
		first += MAXLINES;

	for(i = first; n-- > 0; i = (i + 1) % MAXLINES){
		printf("%s",lineptr[i]);
	}
	return 0;
		
}

int _getline(char *s, int max){
	int c;
	char *p = s;
	while((c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if(c == '\n')
		*s++ = c;
	*s = '\0';
	return s - p;
}

