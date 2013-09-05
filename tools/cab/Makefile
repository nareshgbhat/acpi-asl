CFLAGS	:= -g -Wall -I../common/include

HEADERS = $(wildcard *.h) $(wildcard ../common/include/*.h)

SOURCES = $(wildcard *.c) $(wildcard ../common/*.c)

$(PROG) : $(patsubst %.c,%.o, $(SOURCES)) $(HEADERS)
	$(CC) $(CFLAGS) $(patsubst %.c,%.o, $(SOURCES)) -o $@

clean :
	-rm -f $(patsubst %.c,%.o, $(wildcard *.c)) $(PROG)
