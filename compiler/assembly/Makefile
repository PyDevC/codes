.PHONY: build clean

build:
	nasm -f elf64 hello.asm -o build/hello.o
	ld build/hello.o -o build/hello
	build/hello

clean:
	rm build/*
