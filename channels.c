#include <pthread.h>
#include <stdlib.h>

typedef struct channel_t {
    pthread_mutex_t mutex;
    pthread_cond_t cond;

    void** buffer;
    unsigned int capacity;
    unsigned int head;
    unsigned int length;
} channel;

channel* chan_create(unsigned int capacity) {
    capacity += 1; // for the blocking send/rcv

    channel* chan = malloc(sizeof(channel));

    pthread_mutex_init(&chan->mutex, NULL);
    pthread_cond_init(&chan->cond, NULL);

    chan->buffer = malloc(sizeof(void*) * capacity);
    chan->capacity = capacity;
    chan->head = 0;
    chan->length = 0;

    return chan;
}

void chan_close(channel* chan) {
    pthread_mutex_lock(&chan->mutex);
    free(chan->buffer);
    chan->buffer = NULL;
    pthread_mutex_unlock(&chan->mutex);
}

void chan_destroy(channel* chan) {
    free(chan->buffer);
    pthread_mutex_destroy(&chan->mutex);
    pthread_cond_destroy(&chan->cond);
    free(chan);
}

int chan_send(channel* chan, void* data) {
    pthread_mutex_lock(&chan->mutex);

    if(chan->buffer == NULL) {
        pthread_mutex_unlock(&chan->mutex);
        return -1;
    }

    while(chan->length == chan->capacity) {
        pthread_cond_wait(&chan->cond, &chan->mutex);
    }

    unsigned int index = (chan->head + chan->length) % chan->capacity;
    chan->buffer[index] = data;
    chan->length++;

    pthread_cond_signal(&chan->cond);

    while(chan->length == chan->capacity) {
        pthread_cond_wait(&chan->cond, &chan->mutex);
    }

    pthread_mutex_unlock(&chan->mutex);
}

int chan_recv(channel* chan, void** data) {
    pthread_mutex_lock(&chan->mutex);

    if(chan->buffer == NULL) {
        pthread_mutex_unlock(&chan->mutex);
        return -1;
    }

    while(chan->length == 0) {
        pthread_cond_wait(&chan->cond, &chan->mutex);
    }

    *data = chan->buffer[chan->head];

    chan->head = (chan->head + 1) % chan->capacity;
    chan->length--;

    pthread_cond_signal(&chan->cond);

    pthread_mutex_unlock(&chan->mutex);
}