.PHONY: all, clean

# Disable implicit rules
.SUFFIXES:

# Keep intermediate files
#.PRECIOUS: %.o

CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS =

# Note: -lnsl does not seem to work on Mac OS but will
# probably be necessary on Solaris for linking network-related functions 
#LIBS += -lsocket -lnsl -lrt
LIBS += -lpthread


all: myshell	


bg_fg.o: bg_fg.c myshell.h
	$(CC) $(CFLAGS) -c -o $@ $<

job.o: job.c myshell.h
	$(CC) $(CFLAGS) -c -o $@ $<

csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c -o $@ $<	

parseline.o: parseline.c myshell.h
	$(CC) $(CFLAGS) -c -o $@ $<

eval.o: eval.c myshell.h
	$(CC) $(CFLAGS) -c -o $@ $<

signal.o: signal.c myshell.h
	$(CC) $(CFLAGS) -c -o $@ $<

myshell.o: myshell.c myshell.h
	$(CC) $(CFLAGS) -c -o $@ $<	

myshell: myshell.o eval.o bg_fg.o parseline.o csapp.o job.o signal.o
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	rm -f myshell *.o
