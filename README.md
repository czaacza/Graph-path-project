# Graph-path-project
Sample runs of the program

./program -h
writes help

./program -gen -nc 100 -nr 100 -minw 1 -maxw 100 -s 0 -file data/graph
generates graph of size 100x100 with weights in range of <1; 100>, every vertex is connected with its neighbours and graph is saved in data/graph

./program -search -start 34 -end 1999 -in data/graph -out data/results
checks if graph stored in data/graph is connected and finds the shortest path between given vertices, results are saved in data/results

./program -split -splits 12 -splite 9995 -in data/graph -splitout data/graph1
splits graph stored in data/graph, index of the starting vertex = 12, index of the final vertex = 9995, splitted graph is saved in data/graph1

./program -search -start 199 -end 1999 -in data/graph1 -out data/results
graph is not connected but there is a connection between given vertices

./program -search -start 34 -end 9900 -in data/graph1 -out data/results
graph is not connected and there is no connection between given vertices

./program -gen -nc 50 -nr 50 -minw 1 -maxw 50 -s 0 -split -splits 12 -splite 2496 -search -start 34 -end 1232
all 3 modes simultaneously: graph is generated to the default file (data/graf_dane), graph from the default file is splitted, splitted graph is saved in the default file,
then program checks if graph is connected and finds the shortest path between given vertices, results are written to stdout