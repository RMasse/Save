CC = gcc
CCFLAGS = -Wall -lm

all: Buff NonBuff

Buff: Buff.o
	@echo "Building $@"
	$(CC) $(CCFLAGS) -o $@ $<

NonBuff: NonBuff.o
	@echo "Building $@"
	$(CC) $(CCFLAGS) -o $@ $<

%.o: %.c
	@echo "Building $@"
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	@rm -f *.o Buff NonBuff
