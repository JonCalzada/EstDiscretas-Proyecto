/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proyecto;

import java.util.ArrayList;
import java.util.List;

//clase que se encarga de los atributos del nodo asi como las operaciones internas de este
class NodoLogico {
    int valor;
    String valorStr;
    NodoLogico izq = null;
    NodoLogico der = null;
    NodoLogico padre=null;
    boolean soyIzquierdo;
    List<Integer> valoresDeVerdad=new ArrayList<Integer>();
    
    //constructores para diversos tipos de condiciones diferentes al iniciar
    //algunos no reciben hijos, otros ambos nodos hijos pero en orden distinto, y para diferentes tipos de datos
    public NodoLogico(){
        izq=der=null;
    }
    public NodoLogico(int data){
        this(data,null,null);
    }
    public NodoLogico(String data){
        this(data,null,null);
    }
    public NodoLogico(int data, NodoLogico lt, NodoLogico rt){
        valor=data;
        izq = lt;
        der = rt;
    }
     public NodoLogico(String data, NodoLogico lt, NodoLogico rt){
        valorStr=data;
        izq = lt;
        der = rt;
    }
     
    public NodoLogico(NodoLogico rt,NodoLogico lt,String data){ //constructor que primero pone el hijo derecho(para adaptar con las pilas
        valorStr=data;
        izq = lt;
        der = rt;
    }
     
    //operaciones con nodos
    public void setIzq(NodoLogico izq){
        this.izq = izq;
    }
    public void setDer(NodoLogico der){
        this.der = der;
    }
    public void setPadre(NodoLogico padre){
        this.padre = padre;
    }
    public void setSoyIzquierdo(boolean soyIzquierdo){
        this.soyIzquierdo = soyIzquierdo;
    }    
    public boolean getSoyIzquierdo(){
        return this.soyIzquierdo;
    }
    //metodo que genera la tabla de verdad del nodo, recibe parametros n y r
    //donde n es el numero de incognitas de la funcion y r es el numero que 
    //representa el ordinal de la incognita (si es la primera, segunda, etc..)
    public void generarTabla(int n, int r){
        for(int i=0;i<Math.pow(2,r-1);i++){
           for(int j=0;j<Math.pow(2,n-r);j++){
               valoresDeVerdad.add(1);
               
           } 
           for(int j=0;j<Math.pow(2,n-r);j++){
               valoresDeVerdad.add(0);
           }
        }        
    }
}
