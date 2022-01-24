CC=gcc
OBJS=gpio_pps.c
LIBS=-lpthread -lpigpio
PROGRAM=gpio_pps.elf

all: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM)
