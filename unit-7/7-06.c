#include <stdio.h>
#include <string.h>

int main (int argc, char **argv) {
	FILE *fp1, *fp2;
	void filecmp (FILE *, FILE *);

	if (argc == 1 || argc == 2) {
		printf("insufficient files\n");
		return 1;
	} else {
		if ((fp1 = fopen(argv[1], "r")) == NULL) {
			printf("can't open %s\n", *argv);
			return 1;
		}

		if ((fp2 = fopen(argv[2], "r")) == NULL) {
			printf("can't open %s\n", *argv);
			return 1;
		}

		filecmp(fp1, fp2);
	}

	return 0;
}

#define MAXLINE	100

void filecmp (FILE *fp1, FILE *fp2) {
	char str1[MAXLINE], str2[MAXLINE];
	
	while (!feof(fp1) && !feof(fp2)) {
		fgets(str1, MAXLINE - 1, fp1);
		fgets(str2, MAXLINE - 1, fp2);
		if (strcmp(str1, str2) != 0) {
			printf("%s%s", str1, str2);
			break;
		}
	}

	fclose(fp1);
	fclose(fp2);
}
