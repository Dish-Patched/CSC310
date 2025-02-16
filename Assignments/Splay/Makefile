INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := customErrorClass.o splay.o mainsplay.o
DEPS 		 := customErrorClass.h splay.h

.PHONY: clean all

all: customErrorClass.o splay.o mainsplay.o output

clean:
	rm $(OBJS) output

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

splay.o: splay.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mainsplay.o: mainsplay.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

output: ${OBJS}
	$(CC) -o $@ $^ $(CFLAGS)