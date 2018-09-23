#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#ifdef __MSVCRT__
#include <malloc.h>
#else
#include <alloca.h>
#endif

#include "assman_impl.h"


static void *fop_open(const char *fname, void *udata);
static void fop_close(void *fp, void *udata);
static long fop_seek(void *fp, long offs, int whence, void *udata);
static long fop_read(void *fp, void *buf, long size, void *udata);


struct ass_fileops *ass_alloc_path(const char *path)
{
	char *p;
	struct ass_fileops *fop;

	if(!(fop = malloc(sizeof *fop))) {
		return 0;
	}
	if(!(p = malloc(strlen(path) + 1))) {
		free(fop);
		return 0;
	}
	fop->udata = p;

	while(*path) {
		*p++ = *path++;
	}
	while(p > (char*)fop->udata && (p[-1] == '/' || isspace(p[-1]))) p--;
	*p = 0;

	fop->open = fop_open;
	fop->close = fop_close;
	fop->seek = fop_seek;
	fop->read = fop_read;
	return fop;
}

void ass_free_path(struct ass_fileops *fop)
{
	free(fop->udata);
}

static void *fop_open(const char *fname, void *udata)
{
	const char *asspath = (char*)udata;
	char *path;
	FILE *fp;

	path = alloca(strlen(asspath) + strlen(fname) + 2);
	sprintf(path, "%s/%s", asspath, fname);

	if(!(fp = fopen(path, "rb"))) {
		ass_errno = errno;
		return 0;
	}
	return fp;
}

static void fop_close(void *fp, void *udata)
{
	fclose(fp);
}

static long fop_seek(void *fp, long offs, int whence, void *udata)
{
	fseek(fp, offs, whence);
	return ftell(fp);
}

static long fop_read(void *fp, void *buf, long size, void *udata)
{
	return fread(buf, 1, size, fp);
}
