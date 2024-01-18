#include <stdio.h>
#include <stdlib.h>

int _isupper (int);

int main() {
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\n')
			continue;

		if (_isupper(c))
			printf("true\n");
		else
			printf("false\n");
	}

	return 0;
}

int _isupper(int c) {
	if (c >= 'A' && c <= 'Z') 
		return 1;
	else
		return 0;
}
