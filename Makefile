all: renju

renju: renju.c
	gcc -o renju renju.c

clean:
	rm renju
