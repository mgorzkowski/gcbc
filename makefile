#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC=gcc
AR=ar
CFLAGS=-c -Wall -std=c99
BINDIR=./bin
OBJS= \
$(BINDIR)/gcbc.o

all: create-bindir $(BINDIR)/libgcbc.a
	rm ./bin/*.o

clean:
	rm -rf $(BINDIR)

clean-all: clean-examples
	rm -rf $(BINDIR)
	rm include/*.h.gch

$(BINDIR)/libgcbc.a: $(OBJS)
	cd ./bin/ && $(AR) -x ../lib/abn/bin/libabn.a
	$(AR) rcsv $@ ./bin/*.o

$(BINDIR)/gcbc.o: ./src/gcbc.c
	$(CC) $(CFLAGS) $? -o $@

create-bindir:
	mkdir -p $(BINDIR)

clean-examples:
	rm -rf examples/*/bin
