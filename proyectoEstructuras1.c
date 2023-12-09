#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

//Nodo lista
struct structNodo{
    char simbolo;
    struct structNodo *siguiente;
};

//nodo arbol
typedef struct NODO_ARBOL{
    char cDato;
    struct NODO_ARBOL *pIzquierdo;
    struct NODO_ARBOL *pDerecho;
 }nodo_arbol;

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

//funciones para construir e imprimir arbol
nodo_arbol *FnArbolCreaNodo(char xDato);
int FnBoolArbolInsertarNodo(nodo_arbol **pRaiz,char xDatoInserta, char xDatoPadre, char cLado);
void mostrarArbol(nodo_arbol *arbol,int cont);

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

    //Menu para construir arbol

    nodo_arbol *pRaiz =NULL;
    int n,op,cont = 0;
    char insertar,padre,lado;
    do{
        printf("\n 1.Ingresar raiz");
        printf("\n 2.Ingresar nodo");
        printf("\n 3.Mostrar arbol");
        printf("\n 4.Salir\n");

        scanf("%d", &op);

        switch(op){
        case 1:
            printf("Introduzca el dato a insertar como raiz \n");
            scanf(" %c",&insertar);
            FnBoolArbolInsertarNodo(&pRaiz,insertar,' ',' ');

            break;

        case 2:
            printf("Introduzca el dato a insertar \n");
            scanf(" %c",&insertar);
            printf("Introduzca el  nodo padre del nodo a insertar\n");
            scanf(" %c",&padre);
            printf("Introduzca el lado del nodo a insertar : I = izquierdo y D = derecho\n\n");
            scanf(" %c",&lado);
            FnBoolArbolInsertarNodo(&pRaiz,insertar,padre,lado);
            break;

        case 3:
            printf("arbol binario\n");
            mostrarArbol(pRaiz,cont);
            printf("\n");

            break;

        case 4:

            break;
        }


    }while(op != 4);

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

//funciones para construir e imprimir arbol

nodo_arbol *FnArbolCreaNodo(char xDato){
    nodo_arbol *xNodo;

    xNodo = (nodo_arbol *)malloc(sizeof(nodo_arbol));
    if(xNodo == NULL)
        printf("error");
    else{
        xNodo->cDato=xDato;
        xNodo->pDerecho=NULL;
        xNodo->pIzquierdo=NULL;
    }
    return xNodo;
 }
int FnBoolArbolInsertarNodo(nodo_arbol **pRaiz,char xDatoInserta, char xDatoPadre, char cLado){
    nodo_arbol *pAuxiliar;
    if(*pRaiz==NULL){
        nodo_arbol *pNodoNuevo;
        pNodoNuevo=FnArbolCreaNodo(xDatoInserta);

        *pRaiz=pNodoNuevo;
        printf("se inserto : %c como raiz\n",xDatoInserta);

        return TRUE;
    }
    else{
        pAuxiliar = *pRaiz;
        if(pAuxiliar->cDato == xDatoPadre)
            if(cLado=='D'){
                if(pAuxiliar->pDerecho==NULL){
                    nodo_arbol *pNodoNuevo;
                    pNodoNuevo=FnArbolCreaNodo(xDatoInserta);
                    pAuxiliar->pDerecho=pNodoNuevo;
                    printf("inserto %c del lado der de %c \n",xDatoInserta,xDatoPadre);
                    return TRUE;
                }
            }
            else{
                if(pAuxiliar->pIzquierdo==NULL){
                    nodo_arbol *pNodoNuevo;
                    pNodoNuevo=FnArbolCreaNodo(xDatoInserta);
                    pAuxiliar->pIzquierdo=pNodoNuevo;
                    printf("inserto %c del lado izq de %c \n",xDatoInserta,xDatoPadre);
                    return TRUE;
                }
            }

        if(pAuxiliar->pIzquierdo!=NULL)
            if(!FnBoolArbolInsertarNodo(&(pAuxiliar->pIzquierdo),xDatoInserta,xDatoPadre,cLado))
                if(pAuxiliar->pDerecho!=NULL)
                    if(!FnBoolArbolInsertarNodo(&(pAuxiliar->pDerecho),xDatoInserta,xDatoPadre,cLado))
                        return FALSE;
                    else
                        return TRUE;
                else
                    return FALSE;
            else
                return TRUE;
        else
            return FALSE;



    }
}

void mostrarArbol(nodo_arbol *arbol,int cont){
    if(arbol == NULL){
        return;
    }
    else{
        mostrarArbol(arbol->pDerecho,cont+1);
        for(int i=0;i<cont;i++){
            printf("   ");
        }
        printf("%c",arbol->cDato);
        printf("\n");
        mostrarArbol(arbol->pIzquierdo,cont+1);
    }

}

