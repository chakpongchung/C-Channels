OUTPUT="channels"
NUM_THREADS="$(nproc --all)"
echo ${OUTPUT}
echo ${NUM_THREADS}
((NUM_THREADS=NUM_THREADS*10))
./${OUTPUT} -t ${NUM_THREADS}
# valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(OUTPUT) -t $(NUM_THREADS)