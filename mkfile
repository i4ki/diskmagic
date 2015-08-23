CC=gcc

build: gpt mbr
	echo "build success"

gpt: src/gpt.c
	$CC -o gpt src/gpt.c

mbr: src/mbr.c
	$CC -o mbr src/mbr.c
