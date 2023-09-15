#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<limits.h>
#include"io.h"
#include"defs.h"

void edit(struct context ctx, char *id)
{
	char filepath[PATH_MAX];
	sprintf(filepath, "%s/%c%c/%s.md", ctx.zet_dir, id[0], id[1], id);

	execlp(ctx.editor, ctx.editor, filepath, NULL);
}
