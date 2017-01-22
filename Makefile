OUTPUT=channels
INPUTS=channels.c test.c
NUM_THREADS:= $(shell nproc --all) 
	
all: run

build:
	gcc -Wall --std=gnu99 -g3 -Wno-format-security -fno-omit-frame-pointer -pthread  $(INPUTS) -o $(OUTPUT)

clean:
	rm $(OUTPUT)

run: build
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(OUTPUT) -t $(NUM_THREADS) 
	bash -x format.sh