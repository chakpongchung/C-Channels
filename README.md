# C-Channels
Channels implemented in C as inspired by Go's channels.

There is a test.c program to sum over all the threadID(indexed beginning from 0). To run the program, simply

	C-Channels$ make

For pressure testing, you can uncomment the corresponding line in Makefile. There is no known memory leak found by using Valgrind and address sanitizer.

Initial testing shows this implementation can scale up to 400 threads on a Dual Core CPU.
	
	time ./channels -t 400
	[main] Total sum received: 79800

	real	0m0.105s
	user	0m0.016s
	sys	0m0.124s



# Documents
https://github.com/golang/go/blob/4fc9565ffce91c4299903f7c17a275f0786734a1/src/runtime/chan.go#L17-L29

https://docs.google.com/document/d/1yIAYmbvL3JxOKOjuCyon7JhW4cSv1wy5hC0ApeGMV9s/pub

http://stackoverflow.com/questions/19621149/how-are-go-channels-implemented
