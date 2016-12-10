#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "channels.h"

void* thread1(void* arg) {
	channel* chan = arg;

	printf("[thread1] Spawned, waiting for value...\n");
	fflush(stdout);

	sleep(5);

	int* value;
	chan_recv(chan, (void**)&value);
	printf("[thread1] Received %d\n", *value);

	printf("[thread1] Exiting\n");
	fflush(stdout);

	return NULL;
}

int main() {
	channel* chan = chan_create(0);

	pthread_t t1;
	pthread_create(&t1, NULL, thread1, (void*)chan);

	printf("[main] Sending to channel\n");
	fflush(stdout);

	int* hello = malloc(sizeof(int));
	*hello = 42;

	chan_send(chan, hello);

	printf("[main] Value sent to channel\n");
	fflush(stdout);

	pthread_join(t1, NULL);
}
