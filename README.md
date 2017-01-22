# C-Channels
Channels implemented in C as inspired by Go's channels.

There is a test.c program to sum over all the threadID(indexed beginning from 0). To run the program, simply
	'C-Channels$ make'

For pressure testing, you can uncomment the corresponding line in Makefile. There is no known memory leak found by using valgrind and address sanitizer.

Initial testing shows this implementation can scale up to 400 threads on a Dual Core CPU.



# Documents
http://stackoverflow.com/questions/19621149/how-are-go-channels-implemented
