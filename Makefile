all:
	gcc -std=c99 -Wall -o zte_extract zte_extract.c

clean:
	rm -f zte_extract
