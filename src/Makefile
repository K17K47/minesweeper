.PHONY: all, clean

CFLAGS := -I./ -std=c99

SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:%.c=%.o)

all : minesweeper

minesweeper : $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(OUTPUT_OPTION) $<

clean:
	@echo "Clean."
	-rm -f $(OBJECTS) minesweeper
