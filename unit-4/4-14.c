#include <stdio.h>

#define swap(t, x, y) {t _x; _x = x; x = y; y = _x;}

int main(){
	char x = 'a';
	char y = 'b';
	swap(char, x, y);
	printf("x - %c, y - %c\n", x, y);
	return 0;
}
