#include<stdio.h>
#include<stdlib.h>

#define RULER_SIZE 80

static FILE*
open_file(const char *filepath)
{
	FILE *fptr;

	fptr = fopen(filepath, "r");

	if (fptr == NULL)
	{
		printf("File '%s' not found.\n", filepath);
		exit(1);
	}

	return fptr;
}

static void
close_file(FILE *fptr)
{
	fclose(fptr);
}


void
file_to_stdout(const char *filepath)
{
	FILE *fptr = open_file(filepath);

	char c = fgetc(fptr);
	while (c != EOF)
	{
		printf ("%c", c);
		c = fgetc(fptr);
	}

	close_file(fptr);
}

void
first_line_in_file_to_stdout(const char *filepath)
{
	FILE *fptr = open_file(filepath);

	char c = fgetc(fptr);
	while (c != EOF && c!='\n')
	{
		printf ("%c", c);
		c = fgetc(fptr);
	}
	putchar('\n');

	close_file(fptr);
}

void 
ruler()
{
	for (size_t i=0; i<RULER_SIZE; i++){
		putchar('=');
	}
	putchar('\n');
}

