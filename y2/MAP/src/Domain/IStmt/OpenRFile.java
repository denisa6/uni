package Domain.IStmt;

import Domain.ADT.MyIDictionary;
import Domain.Exception.MyException;
import Domain.Expresion.Exp;
import Domain.Type.StringType;
import Domain.Value.StringValue;
import Domain.Value.Value;
import PrgState.PrgState;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenRFile implements IStmt{
    Exp exp;
    public OpenRFile(Exp e){exp = e;}
    public PrgState execute(PrgState state) throws MyException{
        Value result = exp.eval(state.getSymTable());
        MyIDictionary<StringValue, BufferedReader> fileTbl = state.getFileTable();
        if(!result.getType().equals(new StringType()))
            throw new MyException(result.toString() + " does not have String type");
        if(fileTbl.isVarDef((StringValue) result))
            throw new MyException(result.toString() + "is already defined in FileTable");
        else{
            try{
                BufferedReader br = new BufferedReader(new FileReader(result.toString()));
                fileTbl.put((StringValue) result, br);
            }catch (IOException e) {
                throw new MyException("error " + e);
            }
        }
        return state;
    }
    public IStmt deepCopy(){return new OpenRFile(exp.deepCopy());}
    public String toString(){return "openRFile(" + exp.toString() + ")";}
}
