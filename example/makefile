#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC=gcc
CFLAGS=-Wall -std=c99
ABN_LIB_DIR=../lib/abn/bin/
ABN_LIB_NAME=libabn.a
ABN_INCLUDE_DIR=../lib/abn/include

all: ./bin/prog.elf

run: ./bin/prog.elf
	./bin/example.elf

clean:
	rm -rf ./bin

./bin/prog.elf: ./src/prog.c
	mkdir -p bin/
	$(CC) $(CFLAGS) $? -I$(ABN_INCLUDE_DIR) -L$(ABN_LIB_DIR) -labn -o $@
