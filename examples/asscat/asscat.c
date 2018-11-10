#include <stdio.h>
#include <string.h>
#include "assfile.h"

void print_usage(const char *argv0);

int main(int argc, char **argv)
{
	int i, rdsz;
	const char *prefix = 0;
	ass_file *fp;
	static char buf[1024];

	for(i=1; i<argc; i++) {
		if(argv[i][0] == '-') {
			if(strcmp(argv[i], "-prefix") == 0) {
				prefix = argv[++i];

			} else if(strcmp(argv[i], "-path") == 0) {
				ass_add_path(prefix, argv[++i]);

			} else if(strcmp(argv[i], "-archive") == 0) {
				ass_add_archive(prefix, argv[++i]);

			} else if(strcmp(argv[i], "-url") == 0) {
				ass_add_url(prefix, argv[++i]);

			} else if(strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "-h") == 0) {
				print_usage(argv[0]);
				return 0;

			} else {
				fprintf(stderr, "invalid option: %s\n", argv[i]);
				return 1;
			}

		} else {
			if(!(fp = ass_fopen(argv[i], "rb"))) {
				fprintf(stderr, "failed to open asset: %s: %s\n", argv[i], strerror(ass_errno));
				return 1;
			}
			while((rdsz = ass_fread(buf, 1, sizeof buf, fp)) > 0) {
				fwrite(buf, 1, rdsz, stdout);
			}
			fflush(stdout);
			ass_fclose(fp);
		}
	}

	return 0;
}

void print_usage(const char *argv0)
{
	printf("Usage: %s [options] <file 1> <file 2> ... <file n>\n", argv0);
	printf("Options:\n");
	printf(" -prefix <prefix>   sets the path prefix to match for subsequent asset sources\n");
	printf(" -path <path>       filesystem asset source\n");
	printf(" -archive <archive> archive asset source\n");
	printf(" -url <url>         url asset source\n");
	printf(" -h,-help           print usage and exit\n");
	printf("\nExamples:\n");
	printf("\n Print the contents of sdr.glsl installed under /usr/share/foo/shaders:\n");
	printf("  %s -prefix shaders -path /usr/share/foo shaders/sdr.glsl\n", argv0);
	printf("\n Display the image img/foo.jpg from within a tar file:\n");
	printf("  %s -prefix data -archive data.tar data/img/foo.jpg | display -\n", argv0);
	printf("\n Print the contents of lgpl.txt from http://www.gnu.org/licenses/\n");
	printf("  %s -prefix gnu -url http://www.gnu.org/licenses/ gnu/lgpl.txt\n", argv0);
}
