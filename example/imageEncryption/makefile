#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC=gcc
CFLAGS=-Wall -std=c99
GCBC_LIB_DIR=../../bin/
GCBC_LIB=lgcbc
GCBC_INCLUDE_DIR=../../include/

all: ./bin/prog.elf
	rm -rf ./bin/*.o

run: ./bin/prog.elf
	./bin/prog.elf

clean:
	rm -rf ./bin

./bin/prog.elf: ./bin/prog.o ./bin/utils.o
	mkdir -p bin/
	$(CC) $(CFLAGS) ./bin/prog.o ./bin/utils.o -I$(GCBC_INCLUDE_DIR) -L$(GCBC_LIB_DIR) -lgcbc -o $@

./bin/prog.o: ./src/prog.c
	mkdir -p bin/
	$(CC) $(CFLAGS) -c $? -I$(GCBC_INCLUDE_DIR) -L$(GCBC_LIB_DIR) -lgcbc -o $@

./bin/utils.o: ./src/utils/utils.c
	mkdir -p bin/
	$(CC) $(CFLAGS) -c $? -I$(GCBC_INCLUDE_DIR) -L$(GCBC_LIB_DIR) -lgcbc -o $@
