#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<limits.h>
#include"operations.h"
#include"io.h"

void
add(struct context ctx)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	char id[11];
	sprintf(id, "%d%02d%02d%02d%02d", tm.tm_year + 1900 - 2000, tm.tm_mon + 1,
			tm.tm_mday, tm.tm_hour, tm.tm_min);

	char filepath[PATH_MAX];
	sprintf(filepath, "%s/%c%c/%s.md", ctx.zet_dir, id[0], id[1], id);

	char vim_cmds[255];
	sprintf(vim_cmds, "put='# %s TITLE ' | put='' | put='tags: #' | 1 ", id);

	execlp(ctx.editor, ctx.editor, "-c", vim_cmds, filepath, NULL);
}

void delete(struct context ctx, char *id)
{
	char filepath[PATH_MAX];
	sprintf(filepath, "%s/%c%c/%s.md", ctx.zet_dir, id[0], id[1], id);
	remove(filepath);
}

void edit(struct context ctx, char *id)
{
	char filepath[PATH_MAX];
	sprintf(filepath, "%s/%c%c/%s.md", ctx.zet_dir, id[0], id[1], id);

	execlp(ctx.editor, ctx.editor, filepath, NULL);
}

void
view(struct context ctx, char *id)
{
	char filepath[PATH_MAX];
	sprintf(filepath,
			"%s/%c%c/%s.md", ctx.zet_dir, id[0], id[1], id);
	file_to_stdout(filepath);
}

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

