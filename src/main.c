#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "view.h"
#include "add.h"
#include "delete.h"
#include "grep.h"
#include "env.h"

	static void
error_msg(char* msg)
{
	fprintf(stderr, "%s", msg);
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc <= 1) {
		error_msg(
			"usage: zettelkasten operation\n\n"
			"operation = {"
			" add, view, edit, delete, grep, list "
			"}\n");
	}

	struct context ctx;
	ctx.zet_dir = getenv_with_error("ZET_DIR");
	ctx.editor = getenv_with_error("EDITOR");

	if(!strcmp(argv[1], "add") || !strcmp(argv[1],"a")){
		add(ctx);
	}
	else if(!strcmp(argv[1], "grep") || !strcmp(argv[1],"g")) {
		if(argv[2]==NULL){
			error_msg("fatal: regexp required\n");
		}
		grep(ctx, argv[2]);
	}
	else if(!strcmp(argv[1], "ls")) {
		ls(ctx);
	}
	else if(!strcmp(argv[1], "view") || !strcmp(argv[1], "v")) {
		if(argv[2]==NULL){
			error_msg("fatal: ID required\n");
		}
		view(ctx, argv[2]);
	}
	else if(!strcmp(argv[1], "edit") || !strcmp(argv[1], "e")) {
		if(argv[2]==NULL){
			error_msg("fatal: ID required\n");
		}
		edit(ctx, argv[2]);
	}

	else if(!strcmp(argv[1], "delete") || !strcmp(argv[1], "d")) {
		if(argv[2]==NULL){
			error_msg("fatal: ID required\n");
		}
		delete(ctx,argv[2]);
	}
}
