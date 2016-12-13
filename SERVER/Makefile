CC = gcc
PROGRAM = server
CFLAGS = -Wall -O
CFLAGS_SQL = -Wall -O -lsqlite3

OBJS = main.o vncpwmgr.o accessmgr.o

$(PROGRAM) : $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) -lsqlite3

main.o : main.c
	$(CC) -c $(CFLAGS) main.c

vncpwmgr.o : vncpwmgr.c
	$(CC) -c $(CFLAGS) vncpwmgr.c

accessmgr.o : accessmgr.c
	$(CC) -c $(CFLAGS) accessmgr.c

clean :
	rm $(OBJS)
