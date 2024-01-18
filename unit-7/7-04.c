#include <stdio.h>
#include <stdarg.h>

void minscanf (char *fmt, ...);

int main() {
	int i;
	minscanf("%d", &i);
	printf("input : %d\n", i);

	char *a;
        minscanf("%s", a);
        printf("input : %s\n", a);

	float f;
        minscanf("%f", &f);
        printf("input : %f\n", f);

	int o;
        minscanf("%o", &o);
        printf("input : %o\n", o);

	int x;
        minscanf("%x", &x);
        printf("input : %x\n", x);

	return 0;
}

void minscanf (char *fmt, ...) {
	va_list ap;
	char *p, *sval;
	int *ival;
	float *dval;

	va_start(ap, fmt);

	for (p = fmt; *p; p++) {
		if (*p != '%')
			continue;

		switch (*++p) {
			case 'd':
				ival = va_arg(ap, int *);
				char *d = "10";
				sscanf(d, "%d", ival);
				break;
			case 'f':
                                dval = va_arg(ap, float *);
                                char *f = "3.14";
                                sscanf(f, "%f", dval);
                                break;
			case 's':
                                sval = va_arg(ap, char *);
                                sscanf("test", "%s", sval);
                                break;
			case 'o':
                                ival = va_arg(ap, int *);
                                char *o = "011";
                                sscanf(o, "%o", ival);
                                break;
			case 'x':
                                ival = va_arg(ap, int *);
                                char *x = "1a";
                                sscanf(x, "%x", ival);
                                break;
			default:
				putchar(*p);
				break;
		}
	}

	va_end(ap);
}
