BIN=btoc
SRC=btoc.c
BFCC=bfcc
CFLAGS=-Wall

all: $(BIN)

$(BIN): $(SRC)

install: $(BIN)
	install $(BIN) $(BFCC) /usr/bin

clean:
	rm -f $(BIN)
