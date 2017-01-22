#ifndef __CHANNELS_H__
#define __CHANNELS_H__

// #define NUM_THREADS 2
struct channel_t;
typedef struct channel_t channel;

channel* chan_create(unsigned int capacity);

void chan_close(channel* chan);

void chan_destroy(channel* chan);

int chan_send(channel* chan, void* data);

int chan_recv(channel* chan, void** data);

#endif
