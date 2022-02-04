#ifndef GRAPH_H
#define GRAPH_H
#include "types.h"
#include "node.h"

#define MAX_NODES 4096

typedef struct _Graph Graph;

/* Inicializa un grafo, reservando memoria y devolviendo el grafo inicializado si lo ha hecho correctamente, o NULL
si no */
Graph * graph_ini();

/* Libera la memoria dinámica reservada para un grafo */
void graph_destroy(Graph * g);

/* Devuelve el número de nodos de un grafo, o -1 si se produce algún error */
int graph_getNnodes(const Graph * g);

/* Devuelve el número de conexiones que se almacenan en un grafo, o -1 si se produce algún error */
int graph_getNedges(const Graph * g);

/* Se añade un nodo al grafo reservando memoria nueva para dicho nodo, actualizando los atributos internos del
grafo que sean necesarios. Se devuelve el grafo actualizado si todo ha ido bien, o NULL en otro caso */
Graph * graph_addNode(Graph * g, const Node* n);

/* Se añade una conexión (entre el nodo con id nId1 y el nodo con id nId2) al grafo, actualizando los atributos
internos del grafo que sean necesarios. Se devuelve el grafo actualizado si todo ha ido bien, o NULL en otro caso
*/
Graph * graph_addEdge(Graph * g, char* nId1, char* nId2);

/*
Función privada recomendada: permite encontrar el índice (del array) en el que se almacena un nodo en el grafo
con un id dado. Devuelve ese índice si lo encuentra o -1 si no o si ha habido algún otro error
*/
int find_node_index(Graph * g, char* nId1);

/* Devuelve un puntero a la estructura Node almacenada en el grafo tal que dicho nodo tiene como id nId. Si no se
encuentra o hay algún error, se devuelve NULL */
Node * graph_getNode(const Graph * g, char* nId);

/* Devuelve TRUE o FALSE según si los nodos correspondientes a los ids pasados como argumento están
conectados en el grafo o no (existe una conexión entre nId1 y nId2, en ese sentido). Si hay algún error se devuelve
FALSE */
Bool graph_areConnected(const Graph * g, char* nId1, char* nId2);

/* Devuelve el número de conexiones que se conocen en el grafo desde un nodo, si hay algún error devuelve -1 */
int graph_getNumberOfConnectionsFrom(const Graph * g, char* fromId);

/* Devuelve una lista con los ids de los nodos conectados desde un nodo dado, si hay algún error devuelve NULL*/
char** graph_getConnectionsFrom(const Graph * g, char* ToId);

/* Devuelve el número de conexiones que se conocen en el grafo hacia un nodo, si hay algún error devuelve -1 */
int graph_getNumberOfConnectionsTo(const Graph * g, char* toId);

/* Devuelve una lista con los ids de los nodos conectados desde un nodo dado, si hay algún error devuelve NULL*/
char** graph_getConnectionsTo(const Graph * g, char* toId);

/* Devuelve el numero de raices del grafo */
int graph_getNRaices(const Graph * g);

/* Devuelve las raices del grafo */
char** graph_getRoots(Graph * g);

/* Devuelve una lista del grafo linealizado */
char** graph_linealizacion(Graph *g);

/* Devuelve los predecesores de un nodo */
char** graph_getNodo_predecesores(Graph *g, char* id);

int graph_getAux(Graph *g);

void graph_setMax_name(Graph *g, int maxname);

int graph_print(FILE *pf, const Graph * g);

#endif /* GRAPH_H */
