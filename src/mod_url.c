#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef BUILD_MOD_URL
#include <curl/curl.h>

static const char *get_temp_dir(void);

static char *tmpdir, *cachedir;

struct ass_fileops *ass_alloc_url(const char *url)
{
	static int done_init;
	struct ass_fileops *fop;

	if(!done_init) {
		curl_global_init(CURL_GLOBAL_ALL);
		atexit(curl_global_cleanup);
		done_init = 1;

		if(!*ass_mod_url_cachedir) {
			strcpy(ass_mod_url_cachedir, "assman_cache");
		}
		tmpdir = get_temp_dir();
		if(!(cachedir = malloc(strlen(ass_mod_url_cachedir) + strlen(tmpdir) + 2))) {
			fprintf(stderr, "assman: failed to allocate cachedir path buffer\n");
			return 0;
		}
		sprintf(cachedir, "%s/%s", tmpdir, ass_mod_url_cachedir);
	}

	if(!(fop = malloc(sizeof *fop))) {
		return 0;
	}

	fop->udata = 0;
	fop->open = fop_open;
	fop->close = fop_close;
	fop->seek = fop_seek;
	fop->read = fop_read;
	return fop;
}

void ass_free_url(struct ass_fileops *fop)
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
	return 0;
}

static long fop_read(void *fp, void *buf, long size, void *udata)
{
	return 0;
}

#else
int ass_mod_url_disabled;
#endif
