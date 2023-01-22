package gui;

import Statement.Statement;
import gui.controller.Execution_Controller;
import gui.controller.Select_Window_Controller;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import java.util.ArrayList;
import java.util.List;

public class Gui extends Application {
    static List<Statement> st = new ArrayList<Statement>();

    public static void main_gui(String[] args, List<Statement> sti) {
        st = sti;
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception {

        FXMLLoader mainLoader = new FXMLLoader();
        mainLoader.setLocation(getClass().getResource("resources/execution.fxml"));
        Parent mainWindow = mainLoader.load();
        Execution_Controller mainWindowController = mainLoader.getController();
        Image icon = new Image("img_1.png");
        stage.getIcons().add(icon);
        stage.setTitle("Execution Window");
        stage.setScene(new Scene(mainWindow));
        stage.setX(50);
        stage.setY(100);
        stage.show();


        FXMLLoader secondaryLoader = new FXMLLoader();
        secondaryLoader.setLocation(getClass().getResource("resources/select_window.fxml"));
        Parent secondaryWindow = secondaryLoader.load();
        Select_Window_Controller selectWindowController = secondaryLoader.getController();
        selectWindowController.setExecController(mainWindowController);
        selectWindowController.add_programs(st);
        Stage secondaryStage = new Stage();
        Image icon2 = new Image("img.png");
        secondaryStage.getIcons().add(icon2);
        secondaryStage.setTitle("Select Window");
        secondaryStage.setScene(new Scene(secondaryWindow));
        secondaryStage.setX(900);
        secondaryStage.setY(200);
        secondaryStage.show();

    }
}
