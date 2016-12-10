#ifndef __CHANNELS_H__
#define __CHANNELS_H__

struct channel_t;
typedef struct channel_t channel;

channel* chan_create(unsigned int capacity);

int chan_send(channel* chan, void* data);

int chan_recv(channel* chan, void** data);

#endif
