#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#define STDIN	0
#define STDOUT	1
#define STDERR	2

void filecopy (int ifd, int ofd) {
	int n;
	char buf[BUFSIZ];

	while ((n = read(ifd, buf, BUFSIZ)) > 0) {
		if (write(ofd, buf, n) != n) {
			error("cat: write error\n");
		}
	}
}

int main(int argc, char *argv[]) {
	int fd;

	if (argc == 1) {
		filecopy(STDIN, STDOUT);
	} else {
		while (--argc > 0) {
			if ((fd = open(*++argv, O_RDONLY)) == -1) {
				error("cat: can't open %s\n", *argv);
			} else {
				filecopy(fd, STDOUT);
				close(fd);
			}
		}
	}

	return 0;
}
