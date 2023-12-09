/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proyecto;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;
import java.util.StringTokenizer;
/**
 *Clase encargada de las operaciones sobre arboles Aritmeticos, puede crear el arbol a partir de una expresion aritmetica, resolver el arbol
 * e imprimir en BFS, PreOrden, InOrden y PostOrden
 */
public class ArbolAritmeticoLogico {
    NodoLogico root;
    Stack<String> pilaOperadores;
    Stack<NodoLogico> pilaOperandos;
    Stack<NodoLogico> operandosOrden;
    List<NodoLogico> operandosSinRepetir;
    int numeroDeIncognitas;
    
    /*Metodo encargado de crear el arbol a partir de la expresion aritmetica recibida en forma de cadena, esta expresion debe ir sin espacios
    //No regresa nada, modifica los atributos de la clase
    */
    public void crearArbol(String exAritmetica){
        String dato;
        StringTokenizer sc = new StringTokenizer(exAritmetica,"(*+~)",true);//el true para que tambien regrese los tokens
        String operadores=("(*+~)");
        
        while(sc.hasMoreElements()){
            dato=sc.nextToken();
            
            if(!operadores.contains(dato)) {
                //sera un operando
                NodoLogico nodoOperando = new NodoLogico(dato);
                pilaOperandos.push(nodoOperando);
                operandosOrden.push(nodoOperando);
            }else if(dato.equals(")")){
                while (!pilaOperadores.empty()&& !pilaOperadores.peek().equals("(")) {
                    if(pilaOperadores.peek().contentEquals("~")){
                        pilaOperandos.push(new NodoLogico(pilaOperandos.pop(),null,pilaOperadores.pop())); //crea un subarbol con el operador como nodo raiz y sus operandos como hijos
                    }else{
                        pilaOperandos.push(new NodoLogico(pilaOperandos.pop(),pilaOperandos.pop(),pilaOperadores.pop())); //crea un subarbol con el operador como nodo raiz y sus operandos como hijos
                    }
                    
                }
                pilaOperadores.pop();
            }else{//es operador
                if (!dato.equals("(") && !pilaOperadores.empty()) {
                    String jerarquia=")+*~(";
                    String unOperador = pilaOperadores.peek();
                    while (!unOperador.equals("(") && !pilaOperadores.empty()&& jerarquia.indexOf(unOperador) >= jerarquia.indexOf(dato)) {
                        if(unOperador.contentEquals("~")){
                            pilaOperandos.push(new NodoLogico(pilaOperandos.pop(),null,pilaOperadores.pop()));
                        }else{
                            pilaOperandos.push(new NodoLogico(pilaOperandos.pop(),pilaOperandos.pop(),pilaOperadores.pop()));
                            
                        }
                        if (!pilaOperadores.empty())
                            unOperador = pilaOperadores.peek();
                    }
                }
                pilaOperadores.push(dato);
            }
            
        }
        //para los operadores que quedan en la pila
        while (!pilaOperadores.empty()) {
            if (!pilaOperadores.peek().equals("(")) {
                if (pilaOperadores.peek().equals("~")){
                    pilaOperandos.push(new NodoLogico(pilaOperandos.pop(),null,pilaOperadores.pop()));
                }else{
                    pilaOperandos.push(new NodoLogico(pilaOperandos.pop(),pilaOperandos.pop(),pilaOperadores.pop()));
                }
                
            } else {
                pilaOperadores.pop();
            }
        }
        root = pilaOperandos.peek();
    }
    
    //constructor crea una instancia de las pilas
    public ArbolAritmeticoLogico(){
        pilaOperadores= new Stack();
        pilaOperandos= new Stack();
        operandosOrden= new Stack();
    }
    
    //metodo que toma la expresion aritmetica y regresa una cadena de esta en el formato necesario para el encabezado de la tabla final
    public String obtenerFuncionEnFormato(String exAritmetica){
        String cadena = new String();
        
        for(NodoLogico aux:operandosSinRepetir){
            cadena=cadena+aux.valorStr+"\t";
        }
        cadena=cadena+"|"+"\t";
        StringTokenizer sc = new StringTokenizer(exAritmetica,"*+~",true);//el true para que tambien regrese los tokens
        
        
        while(sc.hasMoreElements()){
            String token=sc.nextToken();
            if(token.charAt(token.length()-1)=='('){
                cadena=cadena+token;
            }else{
                cadena=cadena+token+"\t";
            }
        }
        return cadena;
    }
   
    //Metodo para poder imprimir los valores de los nodos de la pila de Operandos conforme el orden dado
    public String pilaOperandosOrdenToString(){
        String aux="";
        for(int i=0;i<operandosOrden.size();i++){
            aux=aux+operandosOrden.get(i).valorStr+" ";
        }
        return aux;
    }
    /*Metodo que apartir de los operandos  genera las tablas de verdad en funcion del numero de incognitas (2^n)
    al encontrar una incognita repetida no la cuenta para el numero de incognitas, y al momento de generar la tabla
    usa la tabla de la primer ocurrencia de dicha incognita. Este metodo no devuelve nada
    */
     public void calcularTablasOperandos(){
        List<NodoLogico> operandosSinRepetirLocal = new ArrayList<NodoLogico>();
        NodoLogico nodoAux;
        int n=0;
        for(int r=0; r<operandosOrden.size();r++){
            nodoAux = operandosOrden.get(r);
            n++;
            int repetido=0;
            for(int i=0; i<r;i++){
                if(nodoAux.valorStr.contentEquals(operandosOrden.get(i).valorStr)){
                    nodoAux.valoresDeVerdad=operandosOrden.get(i).valoresDeVerdad;
                    i=r;
                    repetido=1;
                    n--;
                }
            }
            if(repetido==0){
                operandosSinRepetirLocal.add(nodoAux); 
            }
            
        }
        int r=0;
        for(NodoLogico aux:operandosSinRepetirLocal){
            r++;
            aux.generarTabla(n, r);
        }
        this.numeroDeIncognitas=n;
        operandosSinRepetir=operandosSinRepetirLocal;
    }
    
    
    
    //Metodo encargado de a partir del arbol aritmetico genera las tablas de los operadores, utilizando la notacion polaca inversa y una pila
    //no recibe nada y no regresa ningun valor
    public void resolver(){
        String operadores="*+~ ";
        List<NodoLogico> nodosPostOrden =postOrdenNodosUtil(root);
        Stack<NodoLogico> operandos=new Stack<NodoLogico>();
        
        for(NodoLogico aux:nodosPostOrden){
            if(!operadores.contains(aux.valorStr)){
                operandos.push(aux);
            }else{
                if(aux.valorStr.contentEquals("~")){
                    NodoLogico operando1 = operandos.pop();
                    operandos.push(OperacionesBoole.negacion(aux,operando1.valoresDeVerdad));
                }else{
                    NodoLogico operando2 = operandos.pop();
                    NodoLogico operando1 = operandos.pop();
                    operandos.push(hacerOperacion(aux,operando1,operando2));
                }
                
            }
        }
    }
    
    //metodo auxiliar para el metodo resolver, regresa el valor dependiendo de la operacion solicitada, lo regresa en forma de Nodo para poder ser insertado en la pila
    //recibe el tipo de operacion como Nodo y los 2 operando como Nodos
    public NodoLogico hacerOperacion(NodoLogico dato,NodoLogico operando1,NodoLogico operando2){
        if(dato.valorStr.contentEquals("*")){
            dato.valoresDeVerdad=OperacionesBoole.producto(operando1.valoresDeVerdad,operando2.valoresDeVerdad);
        }else if(dato.valorStr.contentEquals("+")){
            dato.valoresDeVerdad=OperacionesBoole.suma(operando1.valoresDeVerdad,operando2.valoresDeVerdad);
        }else{
            System.out.print("Algo salio mal");
        }
        return dato;
    }

    //imprime el valor del nodo
    //recibe el nodo y no regresa nada
    protected void visit(NodoLogico n){
        System.out.print(n.valorStr+" ");
    }
    
    //Metodo que realiza el recorrdio BFS del arbolAritmeticoLogico
    //no recibe nada, regresa como cadena el recorrido BFS
    public String breadthFrist(){
        String cadena=new String();
        NodoLogico r = root;
        Queue<NodoLogico> queue = new LinkedList();
        if(r!=null){
            queue.add(r);
           
            while(!queue.isEmpty()){
                r = (NodoLogico)queue.poll();
                cadena=cadena+r.valorStr+" ";
                
                if(r.izq!=null){
                    queue.add(r.izq);
                }
                if(r.der!=null){
                    queue.add(r.der);
                }
            }
        }
        return cadena;
    }

    //Metodo para obtener el recorrido en preOrden(Prefijo), es mas bien unos valores iniciales para un metodo recursivo
    //no recibe nada, regresa el recorrido prefijo como cadena
    public String preOrden(){
        String cadena=new String();
        NodoLogico r = root;
        cadena=cadena+preOrdenUtil(r);
        return cadena;
    }
    
    //metodo recursivo auxiliar del preOrden(prefija), visita el nodo antes de recorrer sus nodos hijos
    //recibe el nodo que sera visitado, regresa la cadena del valor del nodo visitado seguido por el de sus hijos recursivamente
    public String preOrdenUtil(NodoLogico r){
        String cadena=new String();
        if(r!=null){
            cadena=cadena+r.valorStr+" ";
            if(r.izq!=null){
                cadena=cadena+preOrdenUtil(r.izq);
            }
            if(r.der!=null){
                cadena=cadena+preOrdenUtil(r.der);
            }
        }
        return cadena;
    }
    //Metodo para obtener el recorrido en inOrden, es mas bien unos valores iniciales para un metodo recursivo
    //Es utilizado para generar la tabla de resultados de verdad de la funcion, en el formato diseniado
    public String inOrden(){
        String cadena=new String();
        NodoLogico r = root;
        List<NodoLogico> nodosInOrden = inOrdenUtil(r);
        
        cadena=cadena+"\n";
        for(int i=0;i<Math.pow(2, numeroDeIncognitas);i++){
            
            String linea=new String();
            
            for(NodoLogico aux:operandosSinRepetir){
                linea=linea+aux.valoresDeVerdad.get(i)+"\t";
            }
            linea=linea+"|"+"\t";
            for(NodoLogico aux:nodosInOrden){
                    linea=linea+aux.valoresDeVerdad.get(i)+"\t";
            }
            cadena=cadena+linea+"\n";
        }
        
        return cadena;
    }
    //metodo recursivo auxiliar del inOrden, visita el nodo despues de visitar el hijo izquierdo
    //recibe el nodo que sera visitado, regresa la lista de nodos ya ordenados a partir del nodo recibido
    public List<NodoLogico> inOrdenUtil(NodoLogico r){
        List<NodoLogico> nodosInOrden = new ArrayList<NodoLogico>();
        if(r!=null){
            
            if(r.izq!=null){
                nodosInOrden.addAll(inOrdenUtil(r.izq));
                
            }
            nodosInOrden.add(r);
            if(r.der!=null){
                nodosInOrden.addAll(inOrdenUtil(r.der));
            }
        }
        return nodosInOrden;
    }
    
    //Metodo para generar una lista de NodosLogicos ordenada en PostOrden a partir del arbol, visita el nodo despues de visitar el hijo izquierdo
    //recibe el nodo que sera visitado, regresa la lista de nodos ordenada en PostOrden
    public List<NodoLogico> postOrdenNodosUtil(NodoLogico r){
        List<NodoLogico> nodosPostOrden = new ArrayList<NodoLogico>();
        if(r!=null){
            
            if(r.izq!=null){
                nodosPostOrden.addAll(postOrdenNodosUtil(r.izq));
            }
            
            if(r.der!=null){
                nodosPostOrden.addAll(postOrdenNodosUtil(r.der));
            }
            nodosPostOrden.add(r);
        }
        return nodosPostOrden;
    }
    //Metodo para obtener el recorrido en postOrden, es mas bien unos valores iniciales para un metodo recursivo
    //No recibe nada pero regresa el recorrido en postOrden en forma de String. Es necesario que sea de esta manera para facilitar la resolucion del arbol
    public String postOrden(){
        NodoLogico r = root;
        return postOrdenUtil(r);
    }
    //metodo recursivo auxiliar del postOrdenUtil, visita el nodo despues de visitar ambos hijos
    //recibe el nodo que va a visitar y regresa la cadena de PostOrden que se ha calculado al momento
    public String postOrdenUtil(NodoLogico r){
        String postOrden="";
        if(r!=null){
            if(r.izq!=null){
                postOrden= postOrden+postOrdenUtil(r.izq)+" ";
            }
            if(r.der!=null){
                postOrden= postOrden+postOrdenUtil(r.der)+" ";
            }
            return postOrden+r.valorStr;
        }
        return "";
    }
    
}
