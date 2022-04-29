# Graph-path-project
C program using Dijkstra and BFS Algorithms, generating, splitting and searching a given graphs.

Program made as a part of Applied Informatics programming course at Warsaw University of Technology.

## Program structure

**The program consists of three operating modes:**
- **Generate mode**: Generates a graph of given properties and saves it into an output file.
- **Search mode:** Searches the graph and returns both the shortest path and the information wheather the graph is connected.
- **Split mode:** Splits the graph into two parts based on given properties and returns the splitted graph into output file.

</br>

**It is seperated into following modules:**

**main.c** - main program module initializing graph, parsing call parameters, calling gen/search/split module functions

**arguments.c**- arguments error handling, 

**generate.c** -  generates graph based on given weight range and graph size

**graph.c** - graph structure, initializes and creates the graph

**bfs.c** - uses **BFS** algorithm to say whether the graph is connected (there is always a path between two random vertices) or not

**search.c**- uses **Dijkstra's** algorithm to find the shortest path between two given vertices

**split.c** - uses **Dijkstra's** algorithm to split the graph into two parts between edges of the graph.

**inout.c** - loads and saves the graph into files



## Usage

The program can be called using following parameters:

#### `-gen` - Generator mode, program will generate the graph based on following flags:


`-nc`  - Integer number of columns. Must be greater than 0 

`-nr`  - Integer number of rows. Must be greater than 0 

`-minw`  - Decimal number of minimal weight of the edge. Must be greater than 0

`-maxw`  - Decimal number of maximal weight of the edge. Must be greater than k 

`-s`  - Integer number represanting % chance of NO existence of an edge between two vertices. Must be a value between 0 and 100

`-file`  - Name of the file the graph will be generated to. 

</br>

#### `-search` : Search mode, program will find the shortest path between two given vertices:

`-start` - Integer number of starting vertex. Must fit in the number of graph's vertices.

`-end` - Integer number of ending vertex. Must fit in the number of graph's vertices.

`-in`  inFile - Name of the file the graph will be collected from

`-out`   outFile - Name of the file the shortest path and length will be inserted to.

</br>

#### `-split`  Split mode, program will split graph (given after the option -in) along the shortest path between two given vertices

`-splits`    - Integer number of starting vertex. Starting vertex must be in the first row of the graph

`-splite`    - Integer number of ending vertex. Ending vertex must be in the last row of the graph

`-splitout`   - Name of the file the splited graph will be generated to

`-h` - Prints out help menu.



## Sample program calls

`./program`

writes help

`./program -gen -nc 100 -nr 100 -minw 1 -maxw 100 -s 0 -file data/graph`

generates graph of size 100x100 with weights in range of <1; 100>, every vertex is connected with its neighbours and graph is saved in data/graph

`./program -search -start 34 -end 1999 -in data/graph -out data/results`

checks if graph stored in data/graph is connected and finds the shortest path between given vertices, results are saved in data/results

`./program -split -splits 12 -splite 9995 -in data/graph -splitout data/graph1`

splits graph stored in data/graph, index of the starting vertex = 12, index of the final vertex = 9995, splitted graph is saved in data/graph1

`./program -search -start 199 -end 1999 -in data/graph1 -out data/results`

graph is not connected but there is a connection between given vertices

`./program -search -start 34 -end 9900 -in data/graph1 -out data/results`

graph is not connected and there is no connection between given vertices

`./program -gen -nc 50 -nr 50 -minw 1 -maxw 50 -s 0 -split -splits 12 -splite 2496 -search -start 34 -end 1232`

all 3 modes simultaneously: graph is generated to the default file (data/graf_dane), graph from the default file is splitted, splitted graph is saved in the default file,
then program checks if graph is connected and finds the shortest path between given vertices, results are written to stdout
