# declaring compiler because i was having errors without
CC = gcc


CFLAGS = -g -O3

# object files
OBJ = tokenizer.o history.o uimain.o

#what we will call instead of uimain
EXEC = toke  


all: $(EXEC)

# confuses me
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm -f $(EXEC)


.PHONY: all clean
