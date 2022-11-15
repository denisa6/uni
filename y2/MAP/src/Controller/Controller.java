package Controller;

import Domain.ADT.MyIStack;
import Domain.Exception.MyException;
import Domain.IStmt.IStmt;
import PrgState.PrgState;
import Repository.IRepository;

import java.io.IOException;

public class Controller {
    private IRepository repo;
    public Controller(IRepository r){
        repo = r;
    }
    public PrgState oneStep(PrgState state) throws MyException{
        MyIStack<IStmt> stk = state.getStk();
        if(stk.isEmpty())
            throw new MyException("stack is empty");
        IStmt crtStmt = (IStmt)stk.pop();
        return crtStmt.execute(state);
    }
    public void allStep() throws MyException{
        PrgState prg = repo.getCrtPrg();
        try {
            repo.logPrgStateExec();
            while (!prg.getStk().isEmpty()) {
                oneStep(prg);
                repo.logPrgStateExec();
            }
        }catch(MyException ioe){
            throw new MyException("error" + ioe);
        }
    }
    public void displayCurrentProgramState(PrgState state){
        System.out.println(state);
    }
}
