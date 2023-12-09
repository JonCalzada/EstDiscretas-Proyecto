/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proyecto;


import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.text.Text;

//clase que se encarga de la ventana donde se especifican las instrucciones del programa
public class Instrucciones extends Stage {

    private Button regresarBtn;


    public Instrucciones(){
        
        
        GridPane  grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setGridLinesVisible(false);

        //encabezado del formulario
        Text encabezado = new Text("Instrucciones: ");
        encabezado.setFont(Font.font("Tahoma", FontWeight.NORMAL,16));
        

        //Texto de instrucciones, se le asigna una fuente y tamanio de letra a cada uno
        Text notacion1 = new Text("En la pantalla principal se debe introducir la funcion de la cual se desea obtener la \ntabla de verdad utilizando la notacion siguiente:");
        notacion1.setFont(Font.font("Tahoma", FontWeight.NORMAL,13));
        Text notaciones = new Text("Operador\t\tNotacion necesaria\t\tEjemplo\nAND(^)\t\t\t\t*\t\t\t  X*Y\nOR(v)\t\t\t\t+\t\t\t  X+Y\nNegacion\t\t\t\t~\t\t\t  (~X)");
        notaciones.setFont(Font.font("Tahoma", FontWeight.NORMAL,13));
        Text parentesis = new Text("\nEs necesario un buen uso de los parentesis al introducir la funcion, con especial cuidado en el "
                + "\nmomento de utilizar el operador negacion(~), este debera estar inmediatamente a la \nizquierda de su operando y"
                + " juntos dentro de parentesis.\n\nA continuacion se muestran algunos ejemplos de usos correctos de parentesis.\nEjemplos:");
        parentesis.setFont(Font.font("Tahoma", FontWeight.NORMAL,13));
        Text parentesisEjemplos = new Text("(~X)\n\nX+(~Y)\n\n(X*(~Z))+Y\n\n(P*Q)+(~(P*Q))\n\n(X+Y)*(~(X+(~Y))+X\n\n(B*(A+(~C))*((~A)+B+(~C))\n");
        parentesisEjemplos.setFont(Font.font("Tahoma", FontWeight.NORMAL,12));
        
        //creacion de un boton para regresar a la pantalla principal
        this.regresarBtn = new Button("Regresar");
        this.regresarBtn.setOnAction(new EventHandler<ActionEvent>() {

            @Override
            public void handle(ActionEvent event) {
                    close();
            }
        });
        
        HBox botones = crearCajaH(this.regresarBtn, Pos.CENTER_RIGHT, 5);
        
        
        //agregar un scroll a la ventana por si la resolucion no permite ver el contenido por completo
        ScrollPane scrollPane = new ScrollPane(grid);
        scrollPane.setFitToHeight(true);
        scrollPane.setFitToWidth(true);
        //grid para contener los elementos del formulario
        Scene sceneGrid = new Scene(scrollPane,600,500);
        
        //seleccion de la escena
        this.setTitle("Proyecto Algebra de Boole");
        this.setScene(sceneGrid);

        this.initModality(Modality.APPLICATION_MODAL);
        this.show();  

        //adicion de los elementos en el grid		
        grid.add(crearCajaH(encabezado, Pos.TOP_LEFT, 10),0,0,2,1);
        grid.add(crearCajaH(notacion1, Pos.CENTER_LEFT, 10),0,1,2,1);
        grid.add(crearCajaH(notaciones, Pos.TOP_CENTER, 10),0,2,2,1);
        grid.add(crearCajaH(parentesis, Pos.CENTER_LEFT, 10),0,3,2,1);
        grid.add(crearCajaH(parentesisEjemplos, Pos.CENTER_LEFT, 10),0,4,2,1);

        grid.add(crearCajaH(botones, Pos.BOTTOM_RIGHT,10),0,5,2,1);
    }
    
    //metodo para crear una caja a partir de los nodos de interfaz(gridPane,ScrollPane) para facilitar 
    //la posicion de los objetos dentro de los grids
    private HBox crearCajaH(Node nodo, Pos posicion, double espacio){
        HBox hbox = null;
        if(nodo !=null && posicion !=null){
            hbox=new HBox(espacio);
            hbox.setAlignment(posicion);
            hbox.getChildren().add(nodo);
        }

        return hbox;
    }
	
}

