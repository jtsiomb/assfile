#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assman_impl.h"

struct ass_fileops *ass_alloc_archive(const char *fname)
{
	fprintf(stderr, "assman: archive asset handler not implemented yet\n");
	return 0;	/* TODO */
}

void ass_free_archive(struct ass_fileops *fop)
{
}
