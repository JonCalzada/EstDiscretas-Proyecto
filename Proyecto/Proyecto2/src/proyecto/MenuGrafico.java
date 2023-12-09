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
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.text.Text;

//clase que se encarga de hacer los llamados necesarios para generar la informacion de los resultados
//obtenidos de tablas de verdad asi como algunos datos relevantes sobre el arbol aritmetico
public class MenuGrafico extends Stage {

    private Label agregarLbl;
    private TextField agregarTxt;


    private Button regresarBtn;

    private ArbolAritmeticoLogico arbolAritmetico;

    public MenuGrafico(String funcion){    
        
        //llamado a los metodos para generar los resultados a partir de la funcion recibida
        arbolAritmetico=new ArbolAritmeticoLogico();
        try{
            arbolAritmetico.crearArbol(funcion);
        }catch(Exception e){
            new Informador("La funcion no esta escrita con la notacion requerida.\nAsegurese de haber leido las instrucciones.");
            return;
        }
        arbolAritmetico.calcularTablasOperandos();
        arbolAritmetico.resolver();
        
        //creacion del grid con sus parametros para su posicion
        GridPane  grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setGridLinesVisible(false);

        //encabezado del formulario
        Text encabezado = new Text("Algebra de Boole\n\nFuncion: "+funcion);
        encabezado.setFont(Font.font("Tahoma", FontWeight.NORMAL,16));
        

        //datos del formulario
        this.agregarLbl = new Label("Funcion:");
        this.agregarLbl.setAlignment(Pos.CENTER_RIGHT);
        this.agregarTxt = new TextField();

        //Informacion acerca de la funcion
        Text encabezado2 = new Text("BFS: "+arbolAritmetico.breadthFrist()+"\nNotacion PreFija: "+arbolAritmetico.preOrden()+" \nNotacion PostFija(Polaca inversa): " + arbolAritmetico.postOrden()+"\nTabla de Verdad: \n"+arbolAritmetico.obtenerFuncionEnFormato(funcion)+arbolAritmetico.inOrden());
	encabezado2.setFont(Font.font("Tahoma", FontWeight.NORMAL,15));
        
        //boton para regresar a la ventana principal
        this.regresarBtn = new Button("Regresar");
        this.regresarBtn.setOnAction(new EventHandler<ActionEvent>() {

            @Override
            public void handle(ActionEvent event) {
                    close();
            }
        });
        
        //creacion de una caja para facilitar la configuracion de la posicion del boton
        HBox botones = crearCajaH(this.regresarBtn, Pos.CENTER_RIGHT, 5);
        
        //Scroll para poder visualizar el contenido de la ventana si este es demasiado grande
        ScrollPane scrollPane = new ScrollPane(grid);
        scrollPane.setFitToHeight(true);
        scrollPane.setFitToWidth(true);
        
        //grid para contener los elementos del formulario
        Scene sceneGrid = new Scene(scrollPane,700,900);
        
        //se agregan los parametros de la escena y se manda a dibujar
        this.setTitle("Proyecto Algebra de Boole");
        this.setScene(sceneGrid);

        this.initModality(Modality.APPLICATION_MODAL);
        this.show();  

        //adicion de los elementos en el grid		
        grid.add(crearCajaH(encabezado, Pos.TOP_CENTER, 10),0,0,2,1);
        grid.add(crearCajaH(encabezado2, Pos.TOP_CENTER, 10),0,1,2,1);
        grid.add(crearCajaH(botones, Pos.BOTTOM_RIGHT,10),0,2,2,1);
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

