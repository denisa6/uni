package View;

import Controller.Controller;
import Domain.Exception.MyException;
import PrgState.PrgState;

public class View {
    private Controller ctrl;
    public View(Controller c){
        ctrl = c;
    }
    public void inputPrg(PrgState prg){

    }
    public void executePrg() throws MyException{
        ctrl.allStep();
    }
}
