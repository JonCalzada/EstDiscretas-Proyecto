#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define nodo_arbol  (struct nodo *) malloc (sizeof (struct nodo) )
#define MAXIMO 20

int auxX = 0 ;

//Nodo lista
struct structNodo{
    char simbolo;
    struct structNodo *siguiente;
};

//nodo arbol

 struct nodo {
	int info;
	struct nodo *izq;
	struct nodo *der;
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
void gotoxy(int x,int y);

//funciones para construir e imprimir arbol
//funcion crea arbol
struct nodo *crea_arbol(char *prefijo);
void mostrarArbol(struct nodo *arbol,int cont);

int main(){
    char expresion[50];
    nodo *postFija, *preFija;
    int opcion, auxY = 0;
    struct nodo *raiz;
    auxX = 0;

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
                char buffer[50];
                char expresionPre[50] = "";
                memset(&expresionPre,0,sizeof(expresionPre));
                nodo *nodoAuxiliar;
                nodoAuxiliar=preFija;
                while(nodoAuxiliar!=NULL){
                    sprintf(buffer,"%c",nodoAuxiliar->simbolo);
                    strcat(expresionPre,buffer);
                    nodoAuxiliar=nodoAuxiliar->siguiente;
                }
                printf(expresionPre);
                printf("\n");

                raiz = crea_arbol(expresionPre);
                printf ("El arbol esta construido en la memoria... Oprima una tecla\n");
                getch();
                mostrarArbol(raiz, auxY);


            }
            else
                printf(" Expresion no valida");

    //Menu para construir arbol
}

#define MAXIMO 20

struct LIFO {
	int t;
	struct nodo *a[MAXIMO];
};

void init_pila (struct LIFO *p)
{
	p->t = 0;
}

int pila_vacia (struct LIFO *p)
{
	return (!p->t);
}

void ins_pila (struct LIFO *p, struct nodo *s)
{
	if (p->t == MAXIMO)
		printf ("la pila no soporta mas elementos\n");
	else  {
			p->t++;
			p->a [p->t -1] = s;
	}
}

void retira_pila (struct LIFO *p,struct nodo **s)
{
	if (pila_vacia (p) )  {
		printf ("la pila esta vacia\n");
		*s = NULL;
	  }
	else  {
			*s = p->a [p->t -1];
			p->t--;
	}
}



int operando (char c)
{
	return (c != '+' &&
			 c != '-' &&
			 c != '*' &&
			 c != '/' &&
			 c != '^' &&
		    c != ')' &&
			 c != '('    );
}

struct nodo *crea_arbol(char *prefijo)
/* construye una expresion en un arbol binario */
{
	struct nodo *raiz;
	void conformar (struct nodo **raiz,char *prefijo);
	printf ("   De expresion en prefijo. <Se asume correcta>\n\n");
	conformar (&raiz,prefijo);
	return (raiz);
}

#define MAXIMO1 20

struct LIFO1 {
	int t;
	struct nodo *a[MAXIMO1];
};


void init1_pila (struct LIFO1 *p)
{
	p->t = 0;
}

int pila1_vacia (struct LIFO1 *p)
{
	return (!p->t);
}

void ins1_pila (struct LIFO1 *p, struct nodo *s)
{
	if (p->t == MAXIMO)
		printf ("la pila no soporta mas elementos\n");
	else  {
			p->t++;
			p->a [p->t -1] = s;
	}
}

void retira1_pila (struct LIFO1 *p,struct nodo **s)
{
	if (pila1_vacia (p) )  {
		printf ("la pila esta vacia\n");
		*s = NULL;
	  }
	else  {
			*s = p->a [p->t -1];
			p->t--;
	}
}


void conformar (struct nodo **raiz,char *prefijo)
{
	struct nodo *ultimo,*nuevo;
	struct LIFO1 pila;
	int senal,i,caracter;

	i=0;
	caracter = prefijo [i++];
	nuevo = nodo_arbol;
	nuevo->info = caracter;
	*raiz = nuevo;
	senal = 0;
	init1_pila (&pila);
	caracter = prefijo [i++];
	while (caracter) {
		ultimo = nuevo;
		nuevo = nodo_arbol;
		nuevo->info = caracter;
		if (senal) {
			retira1_pila (&pila,&ultimo);
			ultimo->der = nuevo;
		}
		else {
				ultimo->izq = nuevo;
				ins1_pila (&pila,ultimo);
			}
		if (!operando (caracter))
			senal = 0;
		else {
				nuevo->izq = NULL;
				nuevo->der = NULL;
				senal = 1;
			}
		caracter = prefijo [i++];
	}
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

void gotoxy(int x,int y)
{
printf("%c[%d;%df");
}




//funciones para construir e imprimir arbol
void mostrarArbol(struct nodo *arbol,int auxY){
    if(arbol == NULL){
        return;
    }
    else{
        auxX += 5;
        mostrarArbol(arbol->izq,auxY+2);
        gotoxy(10+auxX-auxY,15+auxY);
        printf("%c",arbol->info);
        printf("\n");
        printf("\n");
        mostrarArbol(arbol->der,auxY+2);
    }

}


