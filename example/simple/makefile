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

run: ./bin/prog.elf
	./bin/prog.elf

clean:
	rm -rf ./bin

./bin/prog.elf: ./src/prog.c
	mkdir -p bin/
	$(CC) $(CFLAGS) $? -I$(GCBC_INCLUDE_DIR) -L$(GCBC_LIB_DIR) -lgcbc -o $@
