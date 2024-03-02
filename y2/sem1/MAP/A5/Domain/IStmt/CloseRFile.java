package Domain.IStmt;

import Domain.Exception.MyException;
import Domain.Expresion.Exp;
import Domain.Type.StringType;
import Domain.Value.StringValue;
import Domain.Value.Value;
import PrgState.PrgState;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFile implements IStmt{
    Exp exp;
    public CloseRFile(Exp e){exp = e;}
    public PrgState execute(PrgState state) throws MyException{
        Value res = exp.eval(state.getSymTable(), state.getHeap());
        if(res.getType().equals(new StringType())){
            StringValue result = (StringValue) exp.eval(state.getSymTable(),state.getHeap());
            if(state.getFileTable().isVarDef(result)){
                try{
                    BufferedReader br = state.getFileTable().lookup(result);
                    br.close();
                    state.getFileTable().delete(result); // is result a key?
                }catch (IOException e) {
                    throw new MyException("error - " + e);
                }
            }else
                throw new MyException(result.toString() + "not defined in FileTable");
        }else
            throw new MyException("Expression is not a string type");
        return state;
    }
    public IStmt deepCopy(){return new CloseRFile(exp.deepCopy());}
    public String toString(){return "closeRFile(" + exp.toString() + ")";}
}
