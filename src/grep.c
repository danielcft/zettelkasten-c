#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "defs.h"

void
grep(struct context ctx, char *regexp)
{
	char argument_list[1024];
	/*  -E extended regexp
	 *  -R recursive
	 *  -l only filenames */
	snprintf(argument_list, sizeof(argument_list), "%s %s %s", "grep -ERl",
			regexp, ctx.zet_dir );

	FILE *grep_results = popen(argument_list, "r");
	char *line = NULL;
	size_t ln = 0;
	size_t n =0;
	while ((n = getline(&line, &ln, grep_results)) != -1) {
		line[n-1]='\0';
		file_to_stdout(line);
		ruler();
	}
	free(line);
	fclose(grep_results);
}

/* TODO: ls performs fairly well, yet it is not ordered.
 * Use fts(3) to transverse filesystem.  */
void
ls(struct context ctx)
{
	/* -E extended regexp
	 * -R recursive
	 * -l only filenames */
	char argument_list[1024];
	snprintf(argument_list, sizeof(argument_list), "%s %s", "grep -ERl .",
			ctx.zet_dir );


	FILE *grep_results = popen(argument_list, "r");
	char *grep_result_line = NULL;
	size_t ln = 0;
	ssize_t n;
	while ((n = getline(&grep_result_line, &ln, grep_results)) != -1) {
		grep_result_line[n-1]='\0';
		first_line_in_file_to_stdout(grep_result_line);
	}
	free(grep_result_line);
	fclose(grep_results);
}














