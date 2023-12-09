#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define nodo_arbol (struc nodo *) maloc(sizeof(struct nodo))
#define MAXIMO 20

/* 	nodo Lista */
struct structNodo{
	char simbolo;
	struct structNodo *siguiente;
};

//nodo arbol 

struct nodo{
	int info;
	struct nodo *izq;
	struct nodo *der;
};

typedef struct 
{
	
};