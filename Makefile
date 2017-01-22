OUTPUT=channels
INPUTS=channels.c test.c
NUM_THREADS:= $(shell nproc --all)
# uncomment for pressure testing
# ((NUM_THREADS=NUM_THREADS*10))

all: run

build:
	gcc -Wall -Werror --std=gnu99 -g3 -Wno-format-security -fno-omit-frame-pointer  -pthread  $(INPUTS) -o $(OUTPUT)
 # -fsanitize=address
clean:
	rm $(OUTPUT)

run: build
	time ./$(OUTPUT) -t $(NUM_THREADS) 
	# valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(OUTPUT) -t $(NUM_THREADS) 
	# bash -x format.sh
	# make clean