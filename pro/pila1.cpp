typedef char TipoDato;
#include "PilaE.h"

int PilaLlena(Pila P)
{
    return(P.cima == TAM -1)?1:0;
}
int PilaVacia(Pila P)
{
    return (P.cima == -1)?1:0;
}
void Ingresar(Pila *P, TipoDato x)
{
     if(PilaLlena(*P))
     {
                      puts("Error, Pila llena");
                      return;
                      //exit(-1);
     }
     P->lista[++P->cima] = x;
}

TipoDato Quitar(Pila *P)
{
     if(PilaVacia(*P))
     {
                      puts("Error, pila vacia");
                      TipoDato xx;
                      return xx;
                      //exit(-1);
     }
     TipoDato aux = P->lista[P->cima];
     P->cima--;
     return aux;
}
TipoDato Cima(Pila P)
{
         if(PilaVacia(P))
         {
                         puts("Error");
                         TipoDato xx;
                         return xx;
                         //exit(-1);
         }
         return (P.lista[P.cima]);
}
void CrearPila(Pila *P)
{
     P->cima = -1;
}

