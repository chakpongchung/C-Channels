OUTPUT=channels
INPUTS=channels.c test.c

all: run

build:
	gcc -std=c99 -pthread $(INPUTS) -o $(OUTPUT)

clean:
	rm $(OUTPUT)

run: build
	./$(OUTPUT)
