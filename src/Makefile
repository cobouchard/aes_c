CFLAGS = -std=c11 -Wall -Wextra -g -O3
CPPFLAGS = -I../include -DDEBUG
LDFLAGS = -lm

all: aes

aes: main.o cypher.o multiplication.o modes.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

cypher.o: cypher.c ../include/cypher.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c cypher.c

multiplication.o: multiplication.c ../include/multiplication.h

modes.o: modes.c ../include/modes.h

clean: 
	@rm -f *.o aes

help:
	@echo "Usage: "
	@echo "make [all]\t Build the software"
	@echo "make clean\t Remove all files generated by make"
	@echo "make help\t display this help"


.PHONY: all clean help 
