#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINELENGTH	80
#define LINESPERPAGE	10

void printpages (FILE *, FILE *);

int main(int argc, char *argv[]) {
	FILE *fp;
	char *prog = argv[0];
	int linecount = 0;

	if (argc == 1) {
		fprintf(stderr, "no file");
		printpages(stdin, stdout);
	} else {
		while (--argc > 0) {
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "can't open %s\n", *argv);
				exit(1);
			} else {
				fprintf(stdout, "\n\tFile: %s\n", *argv);
				printpages(fp, stdout);
				fclose(fp);
			}
		}
	}

	if (ferror(stdout)) {
		printf(stderr, "error writing stdout\n", prog);
		exit(2);
	}

	return 0;
}

void printpages (FILE *ifp, FILE *ofp) {
	int c, line = 0, pg = 1;

	while ((c = getc(ifp)) != EOF) {
		putc(c, ofp);
		if (c == '\n') {
			line += 1;
			if (line == LINESPERPAGE) {
				fprintf(stdout, "page %d end\n", pg);
				pg += 1;
				line = 0;
			}
		}
	}
}
