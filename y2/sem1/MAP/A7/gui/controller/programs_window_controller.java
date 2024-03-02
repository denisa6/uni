package gui.controller;

import Controller.Controller;
import Domain.ADT.*;
import Domain.Exception.MyException;
import Domain.Expresion.*;
import Domain.IStmt.*;
import Domain.Type.BoolType;
import Domain.Type.IntType;
import Domain.Type.RefType;
import Domain.Type.StringType;
import Domain.Value.BoolValue;
import Domain.Value.IntValue;
import Domain.Value.StringValue;
import PrgState.PrgState;
import Repository.IRepository;
import Repository.Repository;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.ListView;
import java.io.BufferedReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

public class programs_window_controller implements Initializable {
    private execution_window_controller executionCtrl;
    @FXML
    private ListView<IStmt> MyListView;
    public execution_window_controller getExecWindowCtrl(){return executionCtrl;}
    public void setExecWindowCtrl(execution_window_controller newExecCtrl){executionCtrl = newExecCtrl;}
    private List<IStmt> initExamples(){
        List<IStmt> sts = new ArrayList<>();
        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));
        //wrong types for typechecker
        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new StringType()), new CompStmt(new AssignStmt("a", new ArithExp(new ValueExp(new IntValue(2)), new ArithExp(new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5)), 3), 1)), new CompStmt(new AssignStmt("b", new ArithExp(new VarExp("a"), new ValueExp(new IntValue(1)), 1)), new PrintStmt(new VarExp("b"))))));
        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
        IStmt ex5 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new RelationalExp(new ValueExp(new IntValue(5)), new ValueExp(new IntValue(4)), "<"), new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
        IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()), new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))), new CompStmt(new OpenRFile(new VarExp("varf")), new CompStmt(new VarDeclStmt("varc", new IntType()), new CompStmt(new ReadFile(new VarExp("varf"), "varc"), new CompStmt(new PrintStmt(new VarExp("varc")), new CompStmt(new ReadFile(new VarExp("varf"), "varc"), new CompStmt(new PrintStmt(new VarExp("varc")), new CloseRFile(new VarExp("varf"))))))))));
        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))), new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"), new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp(new VarExp("v"), new ValueExp(new IntValue(1)), 2)))), new PrintStmt(new VarExp("v")))));
        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())), new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))), new CompStmt(new PrintStmt(new HeapReadingExp(new VarExp("v"))), new CompStmt(new HeapWritingStmt("v", new ValueExp(new IntValue(30))), new PrintStmt(new ArithExp(new HeapReadingExp(new VarExp("v")), new ValueExp(new IntValue(5)), 1))))));
        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())), new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))), new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))), new CompStmt(new HeapAllocationStmt("a", new VarExp("v")), new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(30))), new PrintStmt(new HeapReadingExp(new HeapReadingExp(new VarExp("a")))))))));
        IStmt ex9 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new VarDeclStmt("a", new RefType(new IntType())), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))), new CompStmt(new HeapAllocationStmt("a", new ValueExp(new IntValue(22))), new CompStmt(new ForkStmt(new CompStmt(new HeapWritingStmt("a", new ValueExp(new IntValue(30))), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))), new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new HeapReadingExp(new VarExp("a"))))))), new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new HeapReadingExp(new VarExp("a")))))))));

        sts.add(ex1);
        sts.add(ex2);
        sts.add(ex3);
        sts.add(ex4);
        sts.add(ex5);
        sts.add(ex6);
        sts.add(ex7);
        sts.add(ex8);
        sts.add(ex9);
        return sts;
    }
    public void add_programs(List<IStmt> states){
        MyListView.getItems().addAll(states);
    }
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        displayEx();
    }
    @FXML
    private IStmt selectEx(ActionEvent event){
        return MyListView.getItems().get(MyListView.getSelectionModel().getSelectedIndex());
    }
    private void displayEx(){
        List<IStmt> exs = initExamples();
        MyListView.setItems(FXCollections.observableArrayList(exs));
        MyListView.setOnMouseClicked(new EventHandler<Event>() {
            @Override
            public void handle(Event mouseEvent) {
                int index = MyListView.getSelectionModel().getSelectedIndex();
                IStmt selectedPrg = MyListView.getItems().get(index);
                index++;
                PrgState programState = new PrgState(selectedPrg);
                IRepository repo = new Repository(new StringValue("log" + index + ".txt"));
                repo.addPrgState(programState);
                Controller controller = new Controller(repo);
                try{
                    selectedPrg.typecheck(new MyDictionary<>());
                    executionCtrl.setController(controller);
                }catch (MyException e){
                    Alert alert = new Alert(Alert.AlertType.ERROR, e.getMessage());
                    alert.show();
                }
            }
        });
    }

}
