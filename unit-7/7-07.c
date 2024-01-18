#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 1000

void fpat (FILE *, char *, char *);

int main(int argc, char **argv) {
	char pattern[MAXLINE];
	int c;
	FILE *fp;

	if (argc > 1)
		strcpy(pattern, *++argv);
	else {
		printf("usage: find [pattern] [file..]\n");
		exit(1);
	}
	argc--;

	if (argc == 1) {
		fpat(stdin, "", pattern);
	} else {
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				printf("can't open file %s\n", *argv);
				exit(1);
			} else {
				fpat(fp, *argv, pattern);
				fclose(fp);
			}
	}

	return 0;
}

void fpat (FILE *fp, char *name, char *pattern) {
	char line[MAXLINE];
	long lineno = 0;

	while (fgets(line, MAXLINE, fp) != NULL) {
		++lineno;
		if (strstr(line, pattern)) {
			if (*name) {
				printf("%s - ", name);
			}
			printf("%s\n", line);
		}
	}
}

