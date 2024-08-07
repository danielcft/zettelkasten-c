#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<limits.h>
#include<string.h>
#include<ftw.h>
#include<sys/wait.h>

#include"operations.h"
#include"io.h"


static char *results[PATH_MAX];
static size_t results_idx=0;
static struct environment env;
static char *getenv_with_error(const char * env_key);

static char* 
getenv_with_error(const char *env_key)
{
	char* env_value = getenv(env_key);
	if(env_value == NULL) {
		fprintf(stderr, "Please set environment variable $%s.\n", env_key);
		exit(1);
	}

	return env_value;
}

void 
init_env(){
	env.zet_dir=getenv_with_error("ZET_DIR");
	env.editor= getenv_with_error("EDITOR");
}

void
add()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	char id[11];
	sprintf(id, "%d%02d%02d%02d%02d", tm.tm_year + 1900 - 2000, tm.tm_mon + 1,
			tm.tm_mday, tm.tm_hour, tm.tm_min);

	char filepath[PATH_MAX];
	sprintf(filepath, "%s/%c%c/%s.md", env.zet_dir, id[0], id[1], id);

	char vim_cmds[255];
	sprintf(vim_cmds, "put='# %s TITLE ' | put='' | put='tags: #' | 1 ", id);

	execlp(env.editor, env.editor, "-c", vim_cmds, filepath, (char *) NULL);
}

void
delete(const char *id)
{
	char filepath[PATH_MAX];
	sprintf(filepath, "%s/%c%c/%s.md", env.zet_dir, id[0], id[1], id);
	remove(filepath);
}

void
edit(const char *id)
{
	char filepath[PATH_MAX];
	sprintf(filepath, "%s/%c%c/%s.md", env.zet_dir, id[0], id[1], id);

	execlp(env.editor, env.editor, filepath, (char *) NULL);
}

void
view(const char *id)
{
	char filepath[PATH_MAX];
	sprintf(filepath, "%s/%c%c/%s.md", env.zet_dir, id[0], id[1], id);
	file_to_stdout(filepath);
}

int
sort_function(const void *a,const void *b) {
	/* The actual arguments to this function are "pointers to
	   pointers to char", but strcmp(3) arguments are "pointers
	   to char", hence the following cast plus dereference */

	return strcmp(* (char * const *) a , * (char * const *) b);
}

static int
display_info(const char *fpath, const struct stat *sb, 
		int tflag, struct FTW *ftwbuf)
{
	if(tflag != FTW_F){
		/* We only care about regular files. Filter out directories, 
		 * symlinks, blocks, sockets, etc  */
		return 0;
	}
	results[results_idx] = calloc(PATH_MAX, sizeof(char));
	strcpy(results[results_idx], fpath);
	results_idx++;

	return 0;  /* tell nftw() to continue */
}

void 
ls() {
	nftw(env.zet_dir, display_info, 16, 0);

	qsort(results, results_idx, sizeof(char*), sort_function);

	for(size_t i=0; i<results_idx; i++){
		first_line_in_file_to_stdout(results[i]) ;
		free(results[i]);
	}
}

void 
grep(const char *regexp) {
	nftw(env.zet_dir, display_info, 16, 0);

	qsort(results, results_idx, sizeof(char*), sort_function);


	int statval, pid;
	for(size_t i=0; i<results_idx; i++){
		/*
		 * run grep on a child process
		 * wait for grep to finish
		 * print file if grep found a match, ie statuscode != 0
		 */
		pid = fork();
		if(pid == 0) {
			execlp("grep", "grep",  "-Eq", regexp, results[i], 
					(char *) NULL);
		}
		else {
			waitpid( pid, &statval, 0);
			if(WIFEXITED(statval) && !WEXITSTATUS(statval)){
				ruler();
				file_to_stdout(results[i]);
				free(results[i]);
			}
		}
	}
}

