#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "operations.h"

int
main(int argc, char **argv)
{
	init_env();
	if (argc <= 1) {
		error_msg(
				"usage: zettelkasten operation\n\n"
				"operation = {"
				" add, view, edit, delete, grep, list "
				"}\n");
	}

	if(!strcmp(argv[1], "add") || !strcmp(argv[1],"a")){
		add();
	}
	else if(!strcmp(argv[1], "grep") || !strcmp(argv[1],"g")) {
		if(argv[2]==NULL){
			error_msg("fatal: regexp required\n");
		}
		grep(argv[2]);
	}
	else if(!strcmp(argv[1], "ls")) {
		ls();
	}
	else if(!strcmp(argv[1], "view") || !strcmp(argv[1], "v")) {
		if(argv[2]==NULL){
			error_msg("fatal: ID required\n");
		}
		view(argv[2]);
	}
	else if(!strcmp(argv[1], "edit") || !strcmp(argv[1], "e")) {
		if(argv[2]==NULL){
			error_msg("fatal: ID required\n");
		}
		edit(argv[2]);
	}

	else if(!strcmp(argv[1], "delete") || !strcmp(argv[1], "d")) {
		if(argv[2]==NULL){
			error_msg("fatal: ID required\n");
		}
		delete(argv[2]);
	}
}

static void
error_msg(const char* msg)
{
	fprintf(stderr, "%s", msg);
	exit(1);
}

