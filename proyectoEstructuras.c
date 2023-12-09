#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct structNodo{
    char simbolo;
    struct structNodo *siguiente;
};

typedef struct structNodo nodo;

nodo *crearLista(nodo *lista);
nodo *push(char simbolo, nodo *pila);
nodo *insertNodoFinal(char simbolo, nodo *lista);
nodo *pop(char *valor, nodo *pila);
void imprimirExpresion(nodo *lista);

int expresionBalanceada(char expresion[]);
int esOperador(char simbolo);
int prioridad(char operador);
nodo *infijaPostfija(char expresion[]);
int main(){
    char expresion[50];
    nodo *postFija;
    int opcion;

    do{

        printf("      MENU      \n\n");
        printf("[1] Convertir expresion infija a postFija\n");
        printf("[4] Salir\n");
        scanf("%d",&opcion);

        switch(opcion){
        case 1:
            printf("Expresion infija: ");
            scanf(" %[^\n]",expresion);

            if(expresionBalanceada(expresion)){
                postFija=infijaPostfija(expresion);
                imprimirExpresion(postFija);
            }
            else
                printf("no valida");
            break;
        case 4:
            printf("adios");


        }
        getch();
    }while(opcion!=4);

    return 0;
}

nodo *crearLista(nodo *lista){
    return lista = NULL;
}

nodo *push(char simbolo, nodo *pila){
    nodo *nodoNuevo;

    nodoNuevo = (nodo *) malloc(sizeof(nodo));

    if(nodoNuevo != NULL){
        nodoNuevo->simbolo=simbolo;
        nodoNuevo->siguiente=pila;

        pila=nodoNuevo;
    }
    return pila;
}

nodo *insertNodoFinal(char simbolo, nodo *lista){
    nodo *nodoNuevo,*nodoAuxiliar;

    nodoNuevo = (nodo *) malloc(sizeof(nodo));

    if (nodoNuevo != NULL){
        nodoNuevo->simbolo=simbolo;
        nodoNuevo->siguiente=NULL;
        if (lista == NULL)
            lista = nodoNuevo;
        else{
            nodoAuxiliar=lista;

            while(nodoAuxiliar->siguiente!=NULL)
                nodoAuxiliar=nodoAuxiliar->siguiente;
            nodoAuxiliar->siguiente=nodoNuevo;
        }
    }
    return lista;
}

nodo *pop(char *valor, nodo *pila){
    nodo *nodoAuxiliar;
    char dato;

    if(pila==NULL)
        printf("pila Vacia");
    else{
        nodoAuxiliar=pila;
        dato=nodoAuxiliar->simbolo;
        pila=nodoAuxiliar->siguiente;

        *valor=dato;
        free(nodoAuxiliar);
    }

    return pila;
}

void imprimirExpresion(nodo*lista){
    nodo *nodoAuxiliar;
    nodoAuxiliar=lista;
    printf("POSTFIJA: ");

    while(nodoAuxiliar!=NULL){
        printf("%c ",nodoAuxiliar->simbolo);
        nodoAuxiliar=nodoAuxiliar->siguiente;
    }
}

int expresionBalanceada(char expresion[]){
    nodo *pilaAuxiliar;
    int longitudExpresion,i;
    char valor;

    pilaAuxiliar=crearLista(pilaAuxiliar);

    longitudExpresion = strlen(expresion);

    for(i=0;i<longitudExpresion;i++){
        if(expresion[i]=='(')
            pilaAuxiliar=push(expresion[i],pilaAuxiliar);

        if (expresion[i] == ')')
            pilaAuxiliar=pop(&valor,pilaAuxiliar);
    }

    if (pilaAuxiliar==NULL)
        return 1;

    return 0;
}

int esOperador(char simbolo){
    if((simbolo=='+') || (simbolo=='-') ||  (simbolo=='*') || (simbolo == '/') || (simbolo=='^'))
        return 1;

    return 0;
}
int prioridad(char operador){
    if (operador=='^')
        return 3;

    if((operador == '*') || (operador == '/'))
        return 2;

    if((operador == '+') || (operador == '-'))
        return 1;

    if(operador == '(')
        return 0;

}

nodo *infijaPostfija(char expresion[]){
    nodo *pila, *postFija;
    int longitudExpresion,i;
    char valor;

    pila=crearLista(pila);
    postFija=crearLista(postFija);

    longitudExpresion=strlen(expresion);

    for(i=0;i<longitudExpresion;i++){
        if (((expresion[i]>=48) && (expresion[i]<=57)) || ((expresion[i]>=65) && (expresion[i]<=90)) || ((expresion[i]>=97) && (expresion[i]<=122)))
            postFija=insertNodoFinal(expresion[i],postFija);
        else{
            if(expresion[i]=='(')
                pila=push(expresion[i],pila);
            else{
                if(esOperador(expresion[i])){
                    if (pila==NULL)
                        pila=push(expresion[i],pila);
                    else{
                        while(pila!=NULL){
                            if ((prioridad(pila->simbolo)>=prioridad(expresion[i]))){
                                pila=pop(&valor,pila);
                                postFija=insertNodoFinal(valor,postFija);
                            }
                            else
                                break;
                        }
                        pila=push(expresion[i],pila);
                    }
                }
            }
        }
        if(expresion[i]==')'){
            while((pila->simbolo!='(') && (pila!=NULL)){
                    pila=pop(&valor,pila);
                    postFija=insertNodoFinal(valor,postFija);
            }
            pila=pop(&valor,pila);
        }

    }

    while(pila!=NULL){
        pila=pop(&valor,pila);
        postFija=insertNodoFinal(valor,postFija);
    }
    return postFija;
}
