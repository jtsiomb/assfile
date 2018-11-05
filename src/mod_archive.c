#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assman_impl.h"
#include "tar.h"

static void *fop_open(const char *fname, void *udata);
static void fop_close(void *fp, void *udata);
static long fop_seek(void *fp, long offs, int whence, void *udata);
static long fop_read(void *fp, void *buf, long size, void *udata);


struct ass_fileops *ass_alloc_archive(const char *fname)
{
	struct ass_fileops *fop;
	struct tar *tar;

	if(!(tar = malloc(sizeof *tar))) {
		return 0;
	}
	if(load_tar(tar, fname) == -1) {
		free(tar);
		return 0;
	}

	if(!(fop = malloc(sizeof *fop))) {
		return 0;
	}
	fop->udata = tar;
	fop->open = fop_open;
	fop->close = fop_close;
	fop->seek = fop_seek;
	fop->read = fop_read;
	return fop;
}

void ass_free_archive(struct ass_fileops *fop)
{
}

static void *fop_open(const char *fname, void *udata)
{
	return 0;	/* TODO */
}

static void fop_close(void *fp, void *udata)
{
}

static long fop_seek(void *fp, long offs, int whence, void *udata)
{
	return 0;	/* TODO */
}

static long fop_read(void *fp, void *buf, long size, void *udata)
{
	return 0;	/* TODO */
}
