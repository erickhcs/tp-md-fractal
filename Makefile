all: one two three

one: one.o
	gcc -o one.o one.c

two: two.o
	gcc -o two.o two.c

three: three.o
	gcc -o three.o three.c
 
clean:
	rm -f one two three
