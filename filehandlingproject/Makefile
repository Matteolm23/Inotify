all: main

clean: main main.o directory_functions.o inotify_functions.o
	rm -rf main main.o directory_functions.o

main: main.o directory_functions.o inotify_functions.o
	gcc -o main main.o directory_functions.o inotify_functions.o

main.o: main.c directory_functions.h inotify_functions.h
	gcc -c -o main.o main.c

directory_functions.o: directory_functions.c
	gcc -c -o directory_functions.o directory_functions.c

inotify_functions.o: inotify_functions.c
	gcc -c -o inotify_functions.o inotify_functions.c