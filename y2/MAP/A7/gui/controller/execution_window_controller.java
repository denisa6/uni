package gui.controller;

import Controller.Controller;
import Domain.ADT.MyIStack;
import Domain.Exception.MyException;
import Domain.IStmt.IStmt;
import Domain.Value.Value;
import PrgState.PrgState;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import java.net.URL;
import java.util.*;
import java.util.stream.Collectors;

public class execution_window_controller implements Initializable {
    @FXML
    private ListView<String> OutListView;
    @FXML
    private ListView<String> FileTableListView;
    @FXML
    private ListView<Integer> ProgramStateListView;
    @FXML
    private ListView<String> ExeStackListView;
    @FXML
    private TableView<Map.Entry<Integer, Value>> HeapTableView;
    @FXML
    private TableColumn<Map.Entry<Integer, Value>, Integer> heapAddrC;
    @FXML
    private TableColumn<Map.Entry<Integer, Value>, String> heapValueC;
    @FXML
    private TableView<Map.Entry<String, Value>> symTableView;
    @FXML
    private TableColumn<Map.Entry<String, Value>, String> symTnameC;
    @FXML
    private TableColumn<Map.Entry<String, Value>, String> symTvalueC;
    @FXML
    private TextField nrPrgStatesTextField;
    @FXML
    private Button RunStepButton;
    private Controller ctrl;

    public Controller getController() {
        return ctrl;
    }

    public void setController(Controller controller) {
        ctrl = controller;
        populateNrPrgStatesTextField();
        populateProgramStateListView();
        RunStepButton.setDisable(false);
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        ctrl = null;
        this.heapAddrC.setCellValueFactory((p) -> {
            return (new SimpleIntegerProperty((Integer)((Map.Entry)p.getValue()).getKey())).asObject();
        });
        this.heapValueC.setCellValueFactory((p) -> {
            return new SimpleStringProperty(String.valueOf(((Map.Entry)p.getValue()).getValue()) + " ");
        });
        this.symTnameC.setCellValueFactory((p) -> {
            return new SimpleStringProperty((String)((Map.Entry)p.getValue()).getKey() + " ");
        });
        this.symTvalueC.setCellValueFactory((p) -> {
            return new SimpleStringProperty(String.valueOf(((Map.Entry)p.getValue()).getValue()) + " ");
        });
        this.ProgramStateListView.setOnMouseClicked((mouseEvent) -> {
            this.changeProgramStateHandler(this.getSelectedProgramState());
        });
        this.RunStepButton.setDisable(true);
    }

    private void changeProgramStateHandler(PrgState currentPrg) {
        if (currentPrg == null)
            return;
        try {
            populateNrPrgStatesTextField();
            populateProgramStateListView();
            populateHeapTableView(currentPrg);
            populateOutputListView(currentPrg);
            populateFileTableListView(currentPrg);
            populateExeStackView(currentPrg);
            populateSymTableView(currentPrg);
        }catch (MyException e){
            Alert error = new Alert(Alert.AlertType.ERROR, e.getMessage());
            error.show();
        }
    }

    public void oneStepHandler(ActionEvent actionEvent) {
        if (ctrl == null) {
            Alert error = new Alert(Alert.AlertType.ERROR, "No program was selected.");
            error.show();
            RunStepButton.setDisable(true);
            return;
        }
        PrgState prg = getSelectedProgramState();
        if (prg != null && !prg.isNotCompleted()) {
            Alert error = new Alert(Alert.AlertType.ERROR, "Nothing left tot execute! ");
            error.show();
            return;
        }
        try {
            ctrl.oneStepAll();
            changeProgramStateHandler(prg);
            if (ctrl.getRepo().getPrgList().size() == 0)
                RunStepButton.setDisable(true);
        } catch (MyException e) {
            Alert error = new Alert(Alert.AlertType.ERROR, e.getMessage());
            error.show();
            RunStepButton.setDisable(true);
        }
    }

    private void populateNrPrgStatesTextField() {
        nrPrgStatesTextField.setText("nr prg states: " + ctrl.getRepo().getPrgList().size());
    }

    private void populateProgramStateListView() {
        ProgramStateListView.setItems(FXCollections.observableArrayList(ctrl.getRepo().getPrgList().stream().map(PrgState::getId).collect(Collectors.toList())));
        ProgramStateListView.refresh();
    }

    private void populateHeapTableView(PrgState givenPrg) {
        HeapTableView.setItems(FXCollections.observableList(new ArrayList<>(givenPrg.getHeap().getContent().entrySet())));
        HeapTableView.refresh();
    }

    private void populateOutputListView(PrgState givenPrg) throws MyException {
        OutListView.setItems(FXCollections.observableArrayList(givenPrg.getOut().getContent()));
    }

    private void populateFileTableListView(PrgState givenPrg) {
        FileTableListView.setItems(FXCollections.observableArrayList());
    }

    private void populateExeStackView(PrgState givenPrg) {
        MyIStack<IStmt> stack = givenPrg.getStk();
        List<String> stackOutput = new ArrayList<>();
        for (Object stm : stack.getValues()) {
            stackOutput.add(stm.toString());
        }
        Collections.reverse(stackOutput);
        ExeStackListView.setItems(FXCollections.observableArrayList(stackOutput));
    }

    private void populateSymTableView(PrgState givenPrg) {
        symTableView.setItems(FXCollections.observableList(new ArrayList<>(givenPrg.getSymTable().getContent().entrySet())));
        symTableView.refresh();
    }
    private PrgState getSelectedProgramState(){
        if(ProgramStateListView.getSelectionModel().getSelectedIndex() == -1)
            return null;
        int id = ProgramStateListView.getSelectionModel().getSelectedItem();
        return ctrl.getRepo().getProgramWithId(id);
    }
}
