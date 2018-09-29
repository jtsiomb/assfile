#ifndef ASSMAN_IMPL_H_
#define ASSMAN_IMPL_H_

typedef struct ass_file ass_file;

#include "assman.h"

struct ass_file {
	void *file;
	struct ass_fileops *fop;
};

struct mount {
	char *prefix;
	struct ass_fileops *fop;
	int type;

	struct mount *next;
};

enum {
	MOD_PATH,
	MOD_ARCHIVE,
	MOD_URL,
	MOD_USER
};

/* implemented in mod_*.c files */
struct ass_fileops *ass_alloc_path(const char *path);
void ass_free_path(struct ass_fileops *fop);
struct ass_fileops *ass_alloc_archive(const char *fname);
void ass_free_archive(struct ass_fileops *fop);
struct ass_fileops *ass_alloc_url(const char *url);
void ass_free_url(struct ass_fileops *fop);

int ass_mod_url_max_threads;
char ass_mod_url_cachedir[512];

int ass_verbose;

#endif	/* ASSMAN_IMPL_H_ */
