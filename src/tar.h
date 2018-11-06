#ifndef TAR_H_
#define TAR_H_

#include <stdio.h>

struct tar_entry {
	char *path;
	unsigned long offset;
	unsigned long size;
};

struct tar {
	FILE *fp;
	struct tar_entry *files;
	int num_files;
};

int load_tar(struct tar *tar, const char *fname);
void close_tar(struct tar *tar);

#endif	/* TAR_H_ */
