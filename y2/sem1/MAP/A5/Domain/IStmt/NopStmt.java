package Domain.IStmt;

import Domain.Exception.MyException;
import PrgState.PrgState;

public class NopStmt implements IStmt{
    public NopStmt(){}
    public PrgState execute(PrgState state) throws MyException{
        return null;
    }
    public IStmt deepCopy(){
        return new NopStmt();
    }
}
