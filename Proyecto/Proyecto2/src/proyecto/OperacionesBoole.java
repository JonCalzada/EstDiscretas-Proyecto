package proyecto;

import java.util.ArrayList;
import java.util.List;

//clase que contiene las operaciones de Boole en forma estatica para su uso en el programa
public class OperacionesBoole {
    //metodo que realiza la operacion OR de Boole, recibe dos listas de enteros y regresa una lista de enteros
    //generada a partir de la operacion con las listas recibidas
    public static List<Integer> suma(List<Integer> x, List<Integer> y){
        int n;
        List<Integer> r = new ArrayList<Integer>();
        n = x.size();
        for(int i = 0; i<n; i++){
            if(x.get(i)==0 && y.get(i)==0){
                r.add(0);
            }
            else{
                r.add(1);
            }
        }
        return r;
    }
    
    //metodo que realiza la operacion AND de Boole, recibe dos listas de enteros y regresa una lista de enteros
    //generada a partir de la operacion con las listas recibidas
    public static List<Integer> producto(List<Integer> x, List<Integer> y){
        int n;
        List<Integer> r = new ArrayList<Integer>();
        n = x.size();
        for(int i=0; i<n; i++){
            if(x.get(i)==1 && y.get(i)==1){
                r.add(1);
            }
            else{
                r.add(0);
            }
        }
        return r;
    }

    //metodo que realiza la negacion de Boole, recibe una lista de enteros y regresa una lista de enteros
    //generada a partir de la operacion con las lista recibida
    public static NodoLogico negacion(NodoLogico r,List<Integer> x){
        for(int i=0; i<x.size(); i++){
            if(x.get(i)==1){
                r.valoresDeVerdad.add(0);
            }
            else{                
                r.valoresDeVerdad.add(1);
            }
        }
        return r;
    }
}
