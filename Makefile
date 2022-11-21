all:
	gcc ls.c -o ls
	gcc rm.c -o rm
	gcc mkdir.c -o mkdir
	gcc date.c -o date
	gcc cat.c -o cat
	gcc pthread_system.c
	./a.out
