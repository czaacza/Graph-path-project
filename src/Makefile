
program: main.o graph.o search.o generate.o arguments.o
	cc main.o graph.o search.o generate.o arguments.o -o program

main.o: main.c
	cc -c main.c

graph.o: graph.c
	cc -c graph.c

search.o: search.c
	cc -c search.c

generate.o: generate.c
	cc -c generate.c

arguments.o: arguments.c
	cc -c arguments.c

clean:
	rm *.o program