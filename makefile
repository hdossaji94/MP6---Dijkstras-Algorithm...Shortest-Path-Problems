# The makefile for MP6.
# Type:
#   make         -- to build program lab6
#
#
# Format for each entry
#    target : dependency list of targets or files
#    <tab> command 1
#    <tab> command 2
#    ...
#    <tab> last command
#    <blank line>   -- the list of commands must end with a blank line

lab6 : dijkstra.o lab6.o lab6.c dijkstra.c dijkstra.h
	gcc -Wall -g dijkstra.o lab6.o -o lab6 -lm

dijkstra.o : dijkstra.c lab6.c
	gcc -Wall -g -c dijkstra.c

lab6.o : lab6.c dijkstra.h 
	gcc -Wall -g -c lab6.c
