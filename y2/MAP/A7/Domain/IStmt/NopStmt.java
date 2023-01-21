package Domain.IStmt;

import Domain.ADT.MyIDictionary;
import Domain.Exception.MyException;
import Domain.Type.Type;
import PrgState.PrgState;

public class NopStmt implements IStmt{
    public NopStmt(){}
    public PrgState execute(PrgState state) throws MyException{
        return null;
    }
    public IStmt deepCopy(){
        return new NopStmt();
    }
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        return typeEnv;
    }

}
