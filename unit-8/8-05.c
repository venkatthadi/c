#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define NAME_MAX	14

typedef struct {
	long ino;
	char name[NAME_MAX + 1];
} Dirent;

typedef struct {
	int fd;
	Dirent d;
} MYDIR;

MYDIR *_opendir (char *dirname);
Dirent *_readdir (MYDIR *dfd);
void _close (MYDIR *dfd);
void fsize (char *);
void dirwalk (char *, void (*fcn)(char *));

void fsize (char *name) {
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "can't access %s\n", name);
		return;
	}

	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);

	printf("%8ld %s\n%8u %8ld\n", stbuf.st_size, name, stbuf.st_uid, stbuf.st_mtime);
}

#define MAX_PATH	1024

void dirwalk (char *dir, void (*fcn) (char *)) {
	char name[MAX_PATH];
	Dirent *dp;
	MYDIR *dfd;

	if ((dfd = _opendir(dir)) == NULL) {
		fprintf(stderr, "can't open %s\n", dir);
		return;
	}

	while ((dp = _readdir(dfd)) != NULL) {
		if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
			continue;
		if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
			fprintf(stderr, "name %s/%s too long\n",dir, dp->name);
		else {
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}

	_closedir(dfd);
}

#ifndef DIRSIZE
#define DIRSIZE	14
#endif

struct direct {
	ino_t d_ino;
	char d_name[DIRSIZE];
};

int fstat (int fd, struct stat *);

MYDIR *_opendir (char *dirname) {
	int fd;
	struct stat stbuf;
	MYDIR *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (MYDIR *) malloc(sizeof(MYDIR))) == NULL)
		return NULL;
	dp->fd = fd;

	return dp;
}

void _closedir (MYDIR *dp) {
	if (dp) {
		close(dp->fd);
		free(dp);
	}
}

#include <sys/dir.h>

Dirent *_readdir (MYDIR *dp) {
	struct dirent dirbuf;
	static Dirent d;

	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
		if (dirbuf.d_ino == 0)
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZE);
		d.name[DIRSIZE] = '\0';
		return &d;
	}

	return NULL;
}

int main (int argc, char **argv) {
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);

	return 0;
}
