CFLAGS = -g -Wall
LDFLAGS = -lsqlite3

all: select input

select: select.c
	gcc $(CFLAGS) -o $@ $< $(LDFLAGS)

input: input.c
	gcc ${CFLAGS} -o $@ $<
