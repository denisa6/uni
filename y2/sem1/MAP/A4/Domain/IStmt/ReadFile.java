package Domain.IStmt;

import Domain.ADT.MyIDictionary;
import Domain.Exception.MyException;
import Domain.Expresion.Exp;
import Domain.Type.IntType;
import Domain.Type.StringType;
import Domain.Value.IntValue;
import Domain.Value.StringValue;
import Domain.Value.Value;
import PrgState.PrgState;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements IStmt{
    Exp exp;
    String name;
    public ReadFile(Exp e, String n){
        exp = e;
        name = n;
    }
    public PrgState execute(PrgState state) throws MyException{
        MyIDictionary<String, Value> symtbl = state.getSymTable();
        if(!symtbl.isVarDef(name))
            throw new MyException(name + "var is not in the SymTable");
        Value result = symtbl.lookup(name);
        if(!result.getType().equals(new IntType()))
            throw new MyException(name + " doesn't have an int type");
        Value res = exp.eval(symtbl,state.getHeap());
        if(res.getType().equals(new StringType())){
            MyIDictionary<StringValue, BufferedReader> filetbl = state.getFileTable();
            if(filetbl.isVarDef((StringValue)res)){
                BufferedReader br = filetbl.lookup((StringValue) res);
                try{
                    String content = br.readLine();
                    symtbl.update(name, new IntValue(Integer.parseInt(content)));
                }catch (NumberFormatException nfe){
                    symtbl.update(name, new IntValue(0));
                }catch (IOException ioe){
                    throw new MyException("error " + ioe);
                }
            }else
                throw new MyException(result.toString() + "is not open");
        }else
            throw new MyException(res.toString() + "file name is not string");
    return state;
    }
    public IStmt deepCopy(){return new ReadFile(exp.deepCopy(), name);}
    public String toString(){return "ReadFile(" + exp.toString() + "," + name + ")";}
}
