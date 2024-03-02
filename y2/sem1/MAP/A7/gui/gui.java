package gui;

import Domain.IStmt.IStmt;
import gui.controller.execution_window_controller;
import gui.controller.programs_window_controller;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.util.*;


public class gui extends Application {

    static List<IStmt> statements = new ArrayList<>();
    public static void main_gui(String[] args, List <IStmt> sts){
        statements = sts;
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception {
        try{
            FXMLLoader exec_fxml = new FXMLLoader();
            exec_fxml.setLocation(getClass().getResource("resources/execution_window.fxml"));
            Parent execWindow = exec_fxml.load();
            execution_window_controller execWindowCtrl = exec_fxml.getController();
            Image exec_icon = new Image("img_1.png");
            stage.getIcons().add(exec_icon);
            stage.setTitle("Execution Window");
            stage.setScene(new Scene(execWindow));
            stage.setX(100);
            stage.setY(100);
            stage.show();

            FXMLLoader prg_fxml = new FXMLLoader();
            prg_fxml.setLocation(getClass().getResource("resources/programs_window.fxml"));
            Parent prgWindow = prg_fxml.load();
            programs_window_controller prgWindowCtrl = prg_fxml.getController();
            prgWindowCtrl.setExecWindowCtrl(execWindowCtrl);
            prgWindowCtrl.add_programs(statements);
            Image prg_icon = new Image("img.png");
            Stage stage2 = new Stage();
            stage2.getIcons().add(prg_icon);
            stage2.setTitle("Programs Window");
            stage2.setScene(new Scene(prgWindow));
            stage2.setX(800);
            stage2.setY(200);
            stage2.show();
        }
        catch (Exception e){
            throw new Exception("exception gui");
        }
    }
}
