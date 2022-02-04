#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

struct _Graph{
    int num_nodos, num_raices;
    Node* nodos[MAX_NODES];
    Bool adyacencia[MAX_NODES][MAX_NODES];
    int max_name;
    int aux;
};

Graph * graph_ini(){
    Graph *graph_new;
    int i,j;
    graph_new=(Graph*)malloc(sizeof(Graph));
    if(graph_new==NULL){
        return NULL;
    }
    for (i=0;i<MAX_NODES;i++) {
        graph_new->nodos[i]=NULL;
    }
    for (i=0;i<MAX_NODES;i++) {
        for(j=0;j<MAX_NODES;j++){
            graph_new->adyacencia[i][j]=FALSE;
        }
    }
    graph_new->num_nodos=0;
    graph_new->num_raices=0;
    graph_new->max_name=0;
    graph_new->aux=0;

    return graph_new;
}

void graph_setMax_name(Graph *g, int maxname){
    g->max_name = maxname;
}

void graph_destroy(Graph * g){

    int i;

    if(g == NULL){
        return;
    }

    for(i=0;i<(g->num_nodos);i++){
        if(g->nodos[i]!=NULL){
            node_destroy(g->nodos[i]);
        }
    }

    free(g);
}

int graph_getNnodes(const Graph * g){

    if (g==NULL){
        return -1;
    }
    return g->num_nodos;
}

int graph_getAux(Graph *g){
	return g->aux;
}

int graph_getNedges(const Graph * g){

    int i,j,conexiones=0;

    if(g==NULL){
        return -1;
    }

    for(i=0;i<g->num_nodos;i++){
        for(j=0;j<g->num_nodos;j++){
            if(g->adyacencia[i][j]==TRUE){
                conexiones++;
            }
        }
    }

    return conexiones;
}

Graph * graph_addNode(Graph * g, const Node* n){

    if((g == NULL) || (n == NULL)){
        return NULL;
    }

    g->nodos[g->num_nodos] = node_copy(n);
    g->num_nodos++;

    return g;
}

int find_node_index(Graph * g, char* nId1){

    int i;

    if(g==NULL){
        return -1;
    }

    for(i=0;i<g->num_nodos;i++){
        if(strcmp(nId1,node_getId(g->nodos[i]))==0){
            return i;
        }
    }
    return -1;
}

Graph * graph_addEdge(Graph * g, char* nId1, char* nId2){

    int id1_loc, id2_loc;

    if(g==NULL){
        return NULL;
    }

    id1_loc=find_node_index(g,nId1);
    if(find_node_index(g,nId1)==-1){
        return NULL;
    }
    id2_loc=find_node_index(g,nId2);
    if(find_node_index(g,nId2)==-1){
        return NULL;
    }

    g->adyacencia[id1_loc][id2_loc]=TRUE;

    return g;
}

Node * graph_getNode(const Graph * g, char* nId){

    int index;
    Node *new_node;

    if(g==NULL){
        return NULL;
    }

    index=find_node_index((Graph*) g, nId);
    if(find_node_index((Graph*) g, nId)==-1){
        return NULL;
    }

    new_node=g->nodos[index];

    return new_node;
}

Bool graph_areConnected(const Graph * g, char* nId1, char* nId2){

    int index1, index2;

    if(g==NULL){
        return FALSE;
    }

   index1=find_node_index((Graph*) g,nId1);
   if(find_node_index((Graph*) g,nId1)==-1){
        return FALSE;
    }

   index2=find_node_index((Graph*) g,nId2);
   if(find_node_index((Graph*) g,nId2)==-1){
        return FALSE;
    }

   if(g->adyacencia[index1][index2]==1 || g->adyacencia[index2][index1]==1){
       return TRUE;
   }
   else{
       return FALSE;
   }
}

int graph_getNumberOfConnectionsFrom(const Graph * g, char* ToId){

    int index,i,conexiones=0;

    if(g==NULL){
        return -1;
    }

    index=find_node_index((Graph*) g,ToId);
    if(find_node_index((Graph*) g,ToId)==-1){
        return -1;
    }

    for(i=0;i<g->num_nodos;i++){
        if(g->adyacencia[index][i]==TRUE){
            conexiones++;
        }
    }
    return conexiones;
}

char** graph_getConnectionsFrom(const Graph * g, char* ToId){

    int index,i,j=0;
    char **lista;

    int nTo = graph_getNumberOfConnectionsFrom(g,ToId);
    lista=(char**)malloc(nTo*sizeof(char*));
    if(lista==NULL){
        return NULL;
    }

    if(g==NULL){
        return NULL;
    }

    index=find_node_index((Graph*) g, ToId);
    if(find_node_index((Graph*) g,ToId)==-1){
        return NULL;
    }

    for(i=0;i<g->num_nodos;i++){
        if(g->adyacencia[index][i]==TRUE){
            lista[j]=node_getId(g->nodos[i]);
            j++;
        }
    }

    return lista;
}

int graph_getNumberOfConnectionsTo(const Graph * g, char* ToId){

    int index,i,conexiones=0;

    if(g==NULL){
        return -1;
    }

    index=find_node_index((Graph*) g,ToId);
    if(find_node_index((Graph*) g,ToId)==-1){
        return -1;
    }

    for(i=0;i<g->num_nodos;i++){
        if(g->adyacencia[i][index]==TRUE){
            conexiones++;
        }
    }
    return conexiones;
}

char** graph_getConnectionsTo(const Graph * g, char* ToId){

    int index,i,j=0;
    char **lista=NULL;

    int nTo = graph_getNumberOfConnectionsTo(g,ToId);
    lista=(char**)calloc(nTo,sizeof(char*));
    if(lista==NULL){
        return NULL;
    }

    if(g==NULL){
		free(lista);
        return NULL;
    }

    index=find_node_index((Graph*) g, ToId);
    if(find_node_index((Graph*) g,ToId)==-1){
		free(lista);
        return NULL;
    }

    for(i=0;i<g->num_nodos;i++){
        if(g->adyacencia[i][index]==TRUE){
            lista[j]=node_getId(g->nodos[i]);
            j++;
        }
    }

    return lista;
}

int graph_getNRaices(const Graph * g){
	if(!g) return -1;
	else return g->num_raices;
}

char** graph_getRoots(Graph * g){

	int i=0, k=0, num_candidatos=0;
	Node *raices[g->num_nodos];
	char **lista_raices;

	if(!g){
		return NULL;
	}

	for(i=0; i<g->num_nodos; i++){
		if(graph_getNumberOfConnectionsTo(g, node_getId(g->nodos[i])) == 0){
			for(k=0; k<num_candidatos; k++){
				if(node_equals(g->nodos[i], raices[k]) == TRUE){
					break;
				}
			}
      if(k==num_candidatos){
				raices[k] = g->nodos[i];
				num_candidatos++;
			}
		}
	}

	lista_raices = (char**)malloc(num_candidatos*sizeof(char*));
	if(!lista_raices) return NULL;
	for(i=0; i<num_candidatos; i++){
		lista_raices[i] = (char*)calloc(g->max_name,sizeof(char));
		if(!lista_raices[i]) return NULL;
	}

	for(i=0; i<num_candidatos; i++){
		strcpy( lista_raices[i], node_getId(raices[i]));
	}

	g->num_raices = num_candidatos;

	return lista_raices;
}

char** graph_linealizacion(Graph *g){
	char** raices;
	char** linealizacion;
	char** grafo_linealizado;
	char** aux;
	int *nodos_marcados;
	int i=0, j=0, last;

	if(!g) return NULL;

	grafo_linealizado = (char**)malloc(g->num_nodos*sizeof(char*));
	if(!grafo_linealizado) return NULL;
	for(i=0; i<g->num_nodos; i++){
		grafo_linealizado[i] = (char*)calloc(g->max_name,sizeof(char));
		if(!grafo_linealizado[i]) return NULL;
	}

	linealizacion = (char**)malloc(MAX_NODES*sizeof(char*));
	if(!linealizacion) return NULL;
	for(i=0; i<MAX_NODES; i++){
		linealizacion[i] = (char*)calloc(g->max_name,sizeof(char));
		if(!linealizacion[i]) return NULL;
	}

	raices = graph_getRoots(g);

	for(i=0; i<g->num_raices; i++){
		strcpy(linealizacion[i],raices[i]);
	}

	last = i;

	for(i=0; i<g->num_nodos; i++){
		aux = graph_getConnectionsFrom(g, linealizacion[i]);
		for(j=0; j<graph_getNumberOfConnectionsFrom(g,linealizacion[i]); j++){
			strcpy(linealizacion[last],aux[j]);
			last++;
		}
		free(aux);
	}

	nodos_marcados = (int*)malloc(last*sizeof(int));
	if(!nodos_marcados) return NULL;
	for(i=0; i<last; i++){
		nodos_marcados[i]=0;
	}

	for(i=0; i<last; i++){
		for(j=i+1; j<last; j++){
			if(strcmp(linealizacion[i],linealizacion[j]) == 0){
				nodos_marcados[j]=1;
				break;
			}
		}
	}

	for(i=0, j=0; i<last; i++){
		if(nodos_marcados[i] == 0){
			strcpy(grafo_linealizado[j],linealizacion[i]);
			j++;
		}
	}

	for(i=0; i<MAX_NODES; i++){
		free(linealizacion[i]);
	}
	free(linealizacion);
	for(i=0; i<graph_getNRaices(g); i++){
		free(raices[i]);
	}
	free(raices);
	free(nodos_marcados);

	return grafo_linealizado;
}

char** graph_getNodo_predecesores(Graph *g, char* id){

	char **candidatos=NULL, **predecesores=NULL, **aux_predecesores=NULL, **padres=NULL;
	int i=0, j=0, n_predecesores, last=0, n_padres=0;
	int *nodos_marcados=NULL;

	if(!g || !id) return NULL;

	candidatos = (char**)calloc(MAX_NODES,sizeof(char*));
	if(!candidatos) return NULL;
	for(i=0; i<MAX_NODES; i++){
		candidatos[i] = (char*)calloc(g->max_name,sizeof(char));
		if(!candidatos[i]){
			free(candidatos);
			return NULL;
		}
	}

	n_predecesores = graph_getNumberOfConnectionsTo(g,id);
	aux_predecesores = graph_getConnectionsTo(g,id);

	for(i=0; i<n_predecesores; i++){
		strcpy(candidatos[last],aux_predecesores[i]);
		last++;
	}

	free(aux_predecesores);

	for(i=0; i<MAX_NODES; i++){
		if(candidatos[i] != NULL){
			padres = graph_getConnectionsTo(g,candidatos[i]);
			n_padres = graph_getNumberOfConnectionsTo(g,candidatos[i]);

			if(n_padres > 0){
				for(j=0; j<n_padres; j++){
					strcpy(candidatos[last],padres[j]);
					last++;
				}
			}

			free(padres);
		}
	}

	nodos_marcados = (int*)calloc(last,sizeof(int));
	if(!nodos_marcados){
		free(candidatos);
		for(i=0; i<MAX_NODES; i++){
			free(candidatos[i]);
			}
		return NULL;
	}
	for(i=0; i<last; i++){
		nodos_marcados[i]=0;
	}

	for(i=0; i<last; i++){
		for(j=i+1; j<last; j++){
			if(strcmp(candidatos[i],candidatos[j]) == 0){
				nodos_marcados[j]=1;
				break;
			}
		}
	}

	predecesores = (char**)calloc(last,sizeof(char*));
	if(!predecesores) return NULL;
	for(i=0; i<last; i++){
		predecesores[i] = (char*)calloc(g->max_name,sizeof(char));
	}

	for(i=0, j=0; i<last; i++){
		if(nodos_marcados[i] == 0){
			strcpy(predecesores[j],candidatos[i]);
			j++;
		}
	}

	g->aux = last;

	for(i=0; i<MAX_NODES; i++){
		free(candidatos[i]);
	}
	free(candidatos);
	free(nodos_marcados);

	return predecesores;
}


int graph_print(FILE *pf, const Graph * g){

    int num_caract=0, i,j;

    if(pf==NULL || g==NULL){
        return -1;
    }

    num_caract=fprintf(pf,"N=%d, E=%d:\n", g->num_nodos, graph_getNedges(g));
    for(i=0;i<g->num_nodos;i++){
        num_caract+=node_print(pf, g->nodos[i]);
        num_caract+=fprintf(pf,"->");
        for(j=0;j<g->num_nodos;j++){
            num_caract+=fprintf(pf,"%d ", g->adyacencia[i][j]);
        }
        fprintf(pf,"\n");
    }

    return num_caract;
}
