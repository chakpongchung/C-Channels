OUTPUT=channels
INPUTS=channels.c test.c
NUM_THREADS:= $(shell nproc --all) 
	
all: run

build:
	gcc -std=c99 -pthread $(INPUTS) -o $(OUTPUT)

clean:
	rm $(OUTPUT)

run: build
	./$(OUTPUT) -t $(NUM_THREADS)
