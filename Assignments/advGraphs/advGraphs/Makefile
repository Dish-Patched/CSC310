INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS) -g

OBJS 		 := binaryHeap.o binomialHeap.o mst.o main.o
DEPS 		 := binaryHeap.h binomialHeap.h mst.h

.PHONY: clean all

all: binaryHeap.o binomialHeap.o mst.o main.o output

clean:
	rm $(OBJS) output

binaryHeap.o: binaryHeap.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

binomialHeap.o: binomialHeap.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mst.o: mst.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

output: ${OBJS}
	$(CC) -o $@ $^ $(CFLAGS)