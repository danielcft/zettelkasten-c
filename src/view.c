#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"io.h"
#include"defs.h"

void
view(struct context ctx, char *id)
{
	char filepath[PATH_MAX];
	sprintf(filepath,
			"%s/%c%c/%s.md", ctx.zet_dir, id[0], id[1], id);
	file_to_stdout(filepath);
}

