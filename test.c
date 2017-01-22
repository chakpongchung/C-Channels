#include <errno.h>
#include <getopt.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "channels.h"

#define USAGE                \
  "usage:\n"                 \
  "  C-Channels [options]\n" \
  "options:\n"               \
  "-t [NUM_THREADS]       Number of threads (Default 1)\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"NUM_THREADS", required_argument, NULL, 't'}, {NULL, 0, NULL, 0}};

static void Usage() { fprintf(stdout, "%s", USAGE); }

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
  free(arg);
  return NULL;
}

int main(int argc, char** argv) {
  channel* chan = chan_create(0);

  int NUM_THREADS = 1;
  int option_char = 0;
  // Parse and set command line arguments
  while ((option_char = getopt_long(argc, argv, "t:h", gLongOptions, NULL)) !=
         -1) {
    switch (option_char) {
      case 't':  // NUM_THREADS
        NUM_THREADS = atoi(optarg);
        break;
      case 'h':  // help
        Usage();
        exit(0);
        break;
      default:
        Usage();
        exit(1);
    }
  }
  pthread_t threads[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++) {
    thread_data* data = malloc(sizeof(thread_data));
    data->chan = chan;
    data->start = i;

    pthread_create(&threads[i], NULL, thread, (void*)data);
  }

  printf("[main] Receiving from threads...\n");
  fflush(stdout);

  int sum = 0;
  for (int i = 0; i < NUM_THREADS; i++) {
    void* data;
    chan_recv(chan, &data);

    int value = *(int*)data;
    printf("[main] Received %d\n", value);
    sum += value;

    free(data);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("[main] Total sum received: %d\n", sum);
  fflush(stdout);

  chan_destroy(chan);
}
