
program: main.o graph.o search.o bfs.o generate.o inout.o arguments.o
	cc main.o graph.o search.o bfs.o generate.o inout.o arguments.o -g -o program

main.o: main.c
	cc -c main.c

graph.o: graph.c
	cc -c -g graph.c

search.o: search.c
	cc -c -g search.c

bfs.o: bfs.c
	cc -c -g bfs.c

generate.o: generate.c
	cc -c -g generate.c

inout.o: inout.c
	cc -c -g inout.c


arguments.o: arguments.c
	cc -c -g arguments.c

clean:
	rm *.o program
