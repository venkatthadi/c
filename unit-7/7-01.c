#include <stdio.h>
#include <ctype.h>

#define DEFAULT 1

/* upper to lower and lower to upper - 1
 * to lower - 2
 * to upper - 3 */

int main (int argc, char **argv) {
	int c, op = 0;
	
	if (argc == 1)
		op = DEFAULT;
	else if(argc == 2)
		op = atoi(argv[1]);
	else
		printf("invalid parameters\n");

	while ((c = getchar()) != EOF) {
		if (op == 1) {
			if (islower(c))
				putchar(toupper(c));
			else
				putchar(tolower(c));
		} else if (op == 2) {
			putchar(tolower(c));
		} else if (op == 3) {
			putchar(toupper(c));
		} else {
			printf("invalid parameter\n");
			break;
		}
	}

	return 0;
}
