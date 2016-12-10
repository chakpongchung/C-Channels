#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "channels.h"

typedef struct {
	channel* chan;
	int start;
} thread_data;

void* thread(void* arg) {
	thread_data* data = arg;

	printf("[thread%d] Spawned\n", data->start);
	fflush(stdout);

	int* value = malloc(sizeof(int));
	*value = data->start;
	printf("[thread%d] Sending %d\n", data->start, *value);
	chan_send(data->chan, value);

	printf("[thread%d] Exiting\n", data->start);
	fflush(stdout);

	return NULL;
}

int main() {
	channel* chan = chan_create(0);

	pthread_t threads[100];
	for(int i = 0; i < sizeof(threads)/sizeof(threads[0]); i++) {
		thread_data* data = malloc(sizeof(thread_data));
		data->chan = chan;
		data->start = i;

		pthread_create(&threads[i], NULL, thread, (void*)data);
	}

	printf("[main] Receiving from threads...\n");
	fflush(stdout);

	int sum = 0;
	for(int i = 0; i < sizeof(threads)/sizeof(threads[0]); i++) {
		void* data;
		chan_recv(chan, &data);

		int value = *(int*)data;
		printf("[main] Received %d\n", value);
		sum += value;

		free(data);
	}

	printf("[main] Total sum received: %d\n", sum);
	fflush(stdout);

	for(int i = 0; i < sizeof(threads)/sizeof(threads[0]); i++) {
		pthread_join(threads[i], NULL);
	}
}
