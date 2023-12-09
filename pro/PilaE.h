#include "pila1.cpp"
#define MAX 20

int Proced(TipoDato cima,TipoDato simb);
int main ()
{
    TipoDato simb,Cad[MAX]={' '};
    Pila Pil;
    int a=0,i,flag=0;
    CrearPila(&Pil);
    puts("introduce una operacion en notacion interfija");
    while((simb=getchar())!='n'){
          if(simb!=('/') && simb!=('*') && simb!=('-') && simb!=('+') && simb!=('^') && simb!=('(') &&simb!=(')')){
             Cad[a]=simb;
             a=a+1;
             }
             else{
                if(simb=='('){
                  Cad[a]=simb;
                  a=a+1;
                  flag=1;}
                   else if(simb==')'){
                       while(!PilaVacia(Pil)){
                        Cad[a]=Quitar(&Pil);
                        a=a+1; 
                        }
                        Cad[a]=simb;
                        a=a+1;
                        flag=0;
                        }
                     else if(!PilaVacia(Pil) && Proced(Cima(Pil),simb)){
                        while(!PilaVacia(Pil) && Proced(Cima(Pil),simb)){
                            Cad[a]=Quitar(&Pil); 
                            a=a+1;                   
                     }}
                  if(simb!=')' && simb!='(')
                  Ingresar(&Pil,simb);
                  }
             }

    while(!PilaVacia(Pil)){
    Cad[a]=Quitar(&Pil);
    a=a+1; 
}
puts(Cad);
system("pause");
}

int Proced(TipoDato cima,TipoDato simb)
{
if(cima=='^')
   {
    return 1;  
             }
    else if((cima=='*' || cima=='/') && (simb=='-' || simb=='+'))
           {
           return 1;
                       }
         else{
              return 0;}
}