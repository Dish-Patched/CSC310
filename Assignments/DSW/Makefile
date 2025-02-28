INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := customErrorClass.o dsw.o main.o
DEPS 		 := customErrorClass.h dsw.h

.PHONY: clean all

all: customErrorClass.o dsw.o main.o output

clean:
	rm $(OBJS) output

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

dsw.o: dsw.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

output: ${OBJS}
	$(CC) -o $@ $^ $(CFLAGS)