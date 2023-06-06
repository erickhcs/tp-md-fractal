all: one two three

one: one.o
	gcc -o one.o one.c

two: two.o
	gcc -o two.o two.c

three: three.o
	gcc -o three.o three.c

clean:
	rm -f one.o two.o three.o

drawer: drawer.o
	g++ -o drawer.o drawer.c `sdl2-config --cflags --libs`

clean-drawer:
	rm -f drawer.o
