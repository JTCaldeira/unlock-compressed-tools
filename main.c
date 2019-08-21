#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "lib/queue.h"


#define	NUM_CORES	get_nprocs_conf()
#define	BUFSIZE		1024
#define QUEUE_CAPACITY	10000000	// 10 million


queue_t * passwords;
char * filename;


void
read_passwords()
{
	FILE * fp = fopen(filename, "r");
	char buffer[BUFSIZE];

	while (fgets(buffer, BUFSIZE, fp)) {
		char * new_password = calloc(strlen(buffer) + 1, sizeof(char));
		strcpy(new_password, buffer);
		queue_push(password, new_password);
	}

	fclose(fp);
}


void *
do_work(void * data)
{
	char * password;

	// while there's passwords to try
	while (queue_trypop(passwords, (void**)&password)) {
		// TODO try to open compressed file
	}
}


void
create_workers()
{
	pthread_t threads[NUM_CORES];
	int i;

	for (i = 0; i < NUM_CORES; i++)
		pthread_create(&threads[i], NULL, do_work, NULL);

	for (i = 0; i < NUM_CORES; i++)
		pthread_join(threads[i], NULL);
}


int
main(int argc, char * argv[])
{
	queue_create(&passwords, QUEUE_CAPACITY);

	// read a file with passwords and store them in a linked list
	read_passwords();

	create_workers();

	queue_destroy(passwords);

	return EXIT_SUCCESS;
}