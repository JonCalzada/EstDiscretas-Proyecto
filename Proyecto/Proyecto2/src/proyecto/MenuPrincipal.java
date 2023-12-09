/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proyecto;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.TextAlignment;
import javafx.scene.text.Text;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;

//clase que se encarga de la interfaz grafica de la ventana principal del programa
//en esta ventana se introduce la funcion y se muestra el titulo del programa asi como
//el nombre de los integrantes del equipo
// contiene botones para continuar con el programa asi como para ver las instrucciones
public class MenuPrincipal extends Stage {
	private Button arbolMathBtn;
        private Button instruccionesBtn;
        private Label agregarLbl;
        private TextField agregarTxt;
	
	public MenuPrincipal(){    
		GridPane  grid = new GridPane();
		grid.setAlignment(Pos.CENTER);
		grid.setHgap(10);
		grid.setVgap(10);
		
		Text encabezado1 = new Text("Estructuras Discretas Grupo 4\nProyecto: Algebra de Boole");
		encabezado1.setFont(Font.font("Tahoma", FontWeight.SEMI_BOLD,20));
		encabezado1.setTextAlignment(TextAlignment.CENTER);
		
		Text encabezado2 = new Text("Presentado por:\nGonzalez Ochoa Jose Antonio\nPeralta Correa Jose Roberto");
		encabezado2.setFont(Font.font("Courier New", FontWeight.NORMAL,14));
		//encabezado2.setTextAlignment(TextAlignment.CENTER);
		
		
		//datos del formulario
                this.agregarLbl = new Label("Funcion:");
                this.agregarLbl.setAlignment(Pos.CENTER_RIGHT);
                this.agregarTxt = new TextField();

                //botones para instrucciones y siguiente, el boton siguiente toma el texto introducido
                //y lo manda a la clase MenuGrafico para la impresion de resultados
                this.instruccionesBtn= new Button("Instrucciones");
		this.instruccionesBtn.setOnAction(new EventHandler<ActionEvent>() {   
                    @Override
                    public void handle(ActionEvent event) {
                        new Instrucciones();
                    }
                });
                
		this.arbolMathBtn= new Button("Siguiente");
		this.arbolMathBtn.setOnAction(new EventHandler<ActionEvent>() {   
                    @Override
                    public void handle(ActionEvent event) {
                        if(agregarTxt.getText().equals("")){
                            new Informador("Necesita ingresar una funcion");
                        }else{
                            new MenuGrafico(agregarTxt.getText());
                        }
                    }
                });
                this.arbolMathBtn.setAlignment(Pos.CENTER_RIGHT);
		
                //se aniaden los elementos creados al grid
		grid.add(encabezado1, 0,0,2,1);
		grid.add(encabezado2, 0,1,2,1);
                grid.add(this.agregarLbl,0,3);
                grid.add(this.agregarTxt,1,3);
                grid.add(this.instruccionesBtn,0,4);
		grid.add(this.arbolMathBtn,1,4);
                
                //para que el boton se alinie a la derecha
                GridPane.setHalignment(this.arbolMathBtn, HPos.RIGHT);
		
		//creacion de la escena
		Scene sceneGrid = new Scene(grid, 600, 500);
		
		this.setTitle("Proyecto Algebra de Boole");
		this.setScene(sceneGrid);
		this.initModality(Modality.NONE);
		this.show();  
			

	}
}
