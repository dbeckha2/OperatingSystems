all: stat ls tail recursive
stat: stat.c
	gcc -o stat stat.c
ls: ls.c
	gcc -o ls ls.c
tail: tail.c
	gcc -o tail tail.c
recursive: recursive.c
	gcc -o recursive recursive.c
