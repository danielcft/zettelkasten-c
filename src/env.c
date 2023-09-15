#include<stdio.h>
#include<stdlib.h>

char* getenv_with_error(char* env_key)
{
	char* env_value = getenv(env_key);
	if(env_value == NULL) {
		fprintf(stderr, "Please set environment variable $%s.\n", env_key);
		exit(1);
	}

	return env_value;
}

