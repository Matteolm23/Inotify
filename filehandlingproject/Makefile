all: main

clean: main main.o dir_file_functions.o inotify_functions.o
	rm -rf main main.o dir_file_functions.o inotify_functions.o

main: main.o dir_file_functions.o inotify_functions.o
	gcc -o main main.o dir_file_functions.o inotify_functions.o

main.o: main.c dir_file_functions.h inotify_functions.h
	gcc -c -o main.o main.c

dir_file_functions.o: dir_file_functions.c
	gcc -c -o dir_file_functions.o dir_file_functions.c

inotify_functions.o: inotify_functions.c
	gcc -c -o inotify_functions.o inotify_functions.c