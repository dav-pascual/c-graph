#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "graph.h"

#define NODOS_MAX 10

void lista_imprimir(char** lista, int tam);
void lista_destruir(char** lista, int tam);

int main() {

	Graph * g = NULL;
	Node *n[NODOS_MAX];
	char c[1]= "";
	char **raices, **linealizacion, **predecesores_E, **predecesores_F;
	int i=0, ascii=65, counterE=0, counterF=0;

	g = graph_ini();
	graph_setMax_name(g,50);

	for(i=0, c[0]=ascii; i<NODOS_MAX; i++, c[0]++){
	    n[i] = node_ini();
	    node_setId(n[i],c);
	    graph_addNode(g,n[i]);
	    node_destroy(n[i]);
  	}

  	graph_addEdge(g, "A", "B");
  	graph_addEdge(g, "A", "C");
  	graph_addEdge(g, "A", "E");
  	graph_addEdge(g, "B", "D");
  	graph_addEdge(g, "C", "D");
  	graph_addEdge(g, "A", "B");
  	graph_addEdge(g, "D", "F");
  	graph_addEdge(g, "E", "F");
  	graph_addEdge(g, "G", "H");
  	graph_addEdge(g, "G", "I");
  	graph_addEdge(g, "H", "D");
  	graph_addEdge(g, "H", "J");
  	graph_addEdge(g, "I", "J");
  	graph_addEdge(g, "J", "F");

	graph_print(stdout,g);

	raices = graph_getRoots(g);
	printf("\nRaices del grafo: ");
	lista_imprimir(raices, graph_getNRaices(g));

	predecesores_E = graph_getNodo_predecesores(g,"E");
	counterE = graph_getAux(g);
	printf("\nPredecesores del nodo E: ");
	if(predecesores_E != NULL){
		lista_imprimir(predecesores_E, counterE);
	}

	predecesores_F = graph_getNodo_predecesores(g,"F");
	counterF = graph_getAux(g);
	printf("\nPredecesores del nodo F: ");
	if(predecesores_F != NULL){
		lista_imprimir(predecesores_F, counterF);
	}

	linealizacion = graph_linealizacion(g);
	printf("\nGrafo linealizado: ");
	lista_imprimir(linealizacion, graph_getNnodes(g));

	lista_destruir(raices, graph_getNRaices(g));
	lista_destruir(linealizacion, graph_getNnodes(g));
	lista_destruir(predecesores_F, counterF);
	lista_destruir(predecesores_E, counterE);
	graph_destroy(g);

	return 0;
}

void lista_imprimir(char** lista, int tam){
	int i=0;

	for(i=0; i<tam; i++){
		printf("%s ", lista[i]);
	}

	printf("\n");
}

void lista_destruir(char** lista, int tam){
	int i=0;

	for(i=0; i<tam; i++){
		free(lista[i]);
	}
	free(lista);
}
