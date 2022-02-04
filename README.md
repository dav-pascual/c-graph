# C graph library

This repository contains a library to implement a **[bidirected graph](https://en.wikipedia.org/wiki/Bidirected_graph)**. 

E.g.

![Graph example](https://i.stack.imgur.com/LHP8l.png)

It supports several operations such as getting the number of nodes, getting number of edges, add new nodes and edges, checking if two nodes are connected, amongst others.

## Built with

- C

## Source directory structure

- *graph.c*: Graph implementation.
- *graph.h*: Header file for graph.
- *node.c*: Implementation for node elements in the graph.
- *node.h*: Header file for node.
- *types.h*: Generic header. 
- *main.c*: Program which perform a series of tests and outputs results.
- *makefile*: Rule for 'make' to compile and execute main.

## Usage
To execute main program, in '/src' run:
> $ make

> $ ./main


