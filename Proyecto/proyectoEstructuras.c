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
nodo *infijaPrefija(char expresion[]);

//funciones para imprimir arbol


int main(){
    char expresion[50];
    nodo *postFija, *preFija;
    int opcion;

    printf("Expresion infija: ");
            scanf(" %[^\n]",expresion);

            if(expresionBalanceada(expresion)){
                postFija=infijaPostfija(expresion);
                preFija=infijaPrefija(expresion);
                printf("\n\n");
                printf("Postfija:  ");
                imprimirExpresion(postFija);
                printf("\n\n");
                printf("Prefija:  ");
                imprimirExpresion(preFija);
                printf("\n\n");
            }
            else
                printf(" Expresion no valida");

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

    if((operador == '(') || (operador == ')'))
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

// infija a prefija

nodo *infijaPrefija(char expresion[]){
    nodo *pila, *preFija;
    int longitudExpresion,i;
    char valor;

    pila=crearLista(pila);
    preFija=crearLista(preFija);

    longitudExpresion=strlen(expresion);

    for(i=longitudExpresion-1;i>=0;i--){
        if (((expresion[i]>=48) && (expresion[i]<=57)) || ((expresion[i]>=65) && (expresion[i]<=90)) || ((expresion[i]>=97) && (expresion[i]<=122)))
            preFija=push(expresion[i],preFija);
        else{
            if(expresion[i]==')')
                pila=push(expresion[i],pila);
            else{
                if(esOperador(expresion[i])){
                    if (pila==NULL)
                        pila=push(expresion[i],pila);
                    else{
                        while(pila!=NULL){
                            if ((prioridad(pila->simbolo)>=prioridad(expresion[i]))){
                                pila=pop(&valor,pila);
                                preFija=push(valor,preFija);
                            }
                            else
                                break;
                        }
                        pila=push(expresion[i],pila);
                    }
                }
            }
        }
        if(expresion[i]=='('){
            while((pila->simbolo!=')') && (pila!=NULL)){
                    pila=pop(&valor,pila);
                    preFija=push(valor,preFija);
            }
            pila=pop(&valor,pila);
        }

    }

    while(pila!=NULL){
        pila=pop(&valor,pila);
        preFija=push(valor,preFija);
    }
    return preFija;
}
