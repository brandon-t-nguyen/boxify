EXEC=3box5me
STR=THICC

all:
	gcc -std=c99 -g 3box5me.c -o $(EXEC)

test:
	./$(EXEC) $(STR)

debug:
	gdb --args $(EXEC) $(STR)
