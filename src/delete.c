#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "defs.h"

void delete(struct context ctx, char *id)
{
	char filepath[PATH_MAX];
	sprintf(filepath, "%s/%c%c/%s.md", ctx.zet_dir, id[0], id[1], id);
	remove(filepath);
}
