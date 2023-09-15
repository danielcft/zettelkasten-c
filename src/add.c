#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<limits.h>
#include"defs.h"

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

