#ifndef ASSMAN_H_
#define ASSMAN_H_

#include <stdlib.h>

#ifndef ASSMAN_IMPL_H_
typedef void ass_file;
#endif

struct ass_fileops {
	void *udata;
	void *(*open)(const char *fname, void *udata);
	void (*close)(void *fp, void *udata);
	long (*seek)(void *fp, long offs, int whence, void *udata);
	long (*read)(void *fp, void *buf, long size, void *udata);
};

/* options (ass_set_option/ass_get_option) */
enum {
	ASS_OPEN_FALLTHROUGH	/* try all matching handlers if the first fails to open the file */
};

#ifdef __cplusplus
extern "C" {
#endif

extern int ass_errno;

void ass_set_option(int opt, int val);
int ass_get_option(int opt);

/* add a handler for a specific path prefixes. 0 matches every path */
int ass_add_path(const char *prefix, const char *path);
int ass_add_archive(const char *prefix, const char *arfile);
int ass_add_url(const char *prefix, const char *url);
int ass_add_user(const char *prefix, struct ass_fileops *cb);
void ass_clear(void);

ass_file *ass_fopen(const char *fname, const char *mode);
void ass_fclose(ass_file *fp);
long ass_fseek(ass_file *fp, long offs, int whence);
long ass_ftell(ass_file *fp);

size_t ass_fread(void *buf, size_t size, size_t count, ass_file *fp);

/* convenience functions, derived from the above */
int ass_fgetc(ass_file *fp);
char *ass_fgets(char *s, int size, ass_file *fp);

#ifdef __cplusplus
}
#endif


#endif	/* ASSMAN_H_ */
