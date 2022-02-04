#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

struct _Node {
    char id[50];
    void* value;
};

Node * node_ini(){
    Node *n;
    n=(Node*)malloc(sizeof(Node));
    if(n==NULL){
        return NULL;
    }
    n->id[0]='\0';
    return n;
}

void node_destroy(Node * n){

    free(n);
}

void* node_getValue(const Node * n){
	if(n==NULL){
        return NULL;
    }
    return n->value;
}

void node_setValue(Node * n, void* value){
	n->value = value;
}

char* node_getId(const Node * n){
    if(n==NULL){
        return NULL;
    }
    return (char*)n->id;
}

Node * node_setId(Node * n, const char* name){
    if( !n || !name){
        return NULL;
    }
    strcpy(n->id,name);
    return n;
}

Bool node_equals(const Node * n1, const Node * n2){

    if(strcmp(n1->id,n2->id)==0){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

Node * node_copy(const Node * src){

    Node *copied_node;

    if(src==NULL){
        return NULL;
    }

    copied_node=node_ini();
    if(copied_node==NULL){
        return NULL;
    }

    strcpy(copied_node->id, src->id);

    return copied_node;
}

int node_print(FILE *pf, const Node * n){

    int num_caract;
    num_caract=fprintf(pf,"[%s]", node_getId(n));
    return num_caract;
}
