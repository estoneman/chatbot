// Copyright Ethan Stoneman

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define FILE_SIZE_CAP	1024
#define LINE_LEN_CAP	100
#define LINE_CNT			35
#define STEP					300000

char line[LINE_LEN_CAP];
size_t line_sz, q_idx = 0, r_idx = 0;

char responselist[LINE_CNT][LINE_LEN_CAP];
char questionlist[LINE_CNT][LINE_LEN_CAP];

char* readfile(const char* restrict path, const char* restrict mode)
{
	assert(path != NULL);

	FILE* fp = fopen(path, mode);
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, fp);
	fclose(fp);

	string[fsize] = 0;

	return string;
}

void random_read(char* line, const char* contents, const char* fn, int line_no)
{

	line_sz = 0;

	memset(line, 0, LINE_LEN_CAP);

	size_t newlines = 0;

	while (newlines < line_no) {
		if (*contents++ == '\n') {
			newlines++;
		}
	}

	while (*contents != '\n')
		line[line_sz++] = *contents++;

}

int main()
{

	char* questions = (char*) malloc(FILE_SIZE_CAP + 1);
	char* responses = (char*) malloc(FILE_SIZE_CAP + 1);

	questions = readfile("./questions.txt", "r");
	responses = readfile("./responses.txt", "r");

	size_t numspaces, numchars;

	unsigned seed = time(0);
	srand(seed);
	int rand_num;

	printf("\e[?25l");

 	for (int i = 0; i < LINE_CNT; i++) {
		rand_num = rand() % LINE_CNT;
 		random_read(line, questions, "q", rand_num);

		numchars = strlen(line);
		numspaces = LINE_LEN_CAP - numchars;

		printf("%s", line);
		for (size_t j = 0; j < numspaces; j++)
			printf(" ");

		printf("\r");
		fflush(stdout);

		usleep(STEP);

		rand_num = rand() % LINE_CNT;
 		random_read(line, responses, "r", rand_num);

		printf("%s", line);
		for (size_t j = 0; j < numspaces; j++)
			printf(" ");

		printf("\r");
		fflush(stdout);

		usleep(STEP);

 	}

	printf("Goodbye, Let's chat again soon..\n");

	printf("\e[?25h");

	free(questions);
	free(responses);

	return 0;
}

