out.bin: out.o
	ld out.o -o out.bin

out.o: out.asm
	nasm -felf64 out.asm

out.asm:
	./build/glisp

clean:
	rm out.o out.asm out.bin
