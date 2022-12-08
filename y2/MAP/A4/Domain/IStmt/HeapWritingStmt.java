package Domain.IStmt;

import Domain.Exception.MyException;
import Domain.Expresion.Exp;
import Domain.Type.RefType;
import Domain.Value.RefValue;
import Domain.Value.Value;
import PrgState.PrgState;

public class HeapWritingStmt implements IStmt{
    private String name;
    private Exp exp;

    public HeapWritingStmt(String n, Exp e){
        this.name = n;
        this.exp = e;
    }

    public PrgState execute(PrgState state) throws MyException{
        if(!state.getSymTable().isVarDef(this.name)){
            throw new MyException(this.name + " is not declared");
        }else if(!(((Value)state.getSymTable().lookup(this.name)).getType() instanceof RefType)){
            throw new MyException(this.name + " doesn't have ref type");
        }else if(!state.getHeap().isVarDef(((RefValue)state.getSymTable().lookup(this.name)).getAddr())){
            RefValue var = (RefValue)state.getSymTable().lookup(this.name);
            throw new MyException(var.getAddr() + " addr is not used");
        }else{
            Value result = this.exp.eval(state.getSymTable(),state.getHeap());
            if(!result.getType().equals(((Value)state.getHeap().lookup(((RefValue)state.getSymTable().lookup(this.name)).getAddr())).getType())){
                throw new MyException(result.toString() + " doesn't have " + ((Value)state.getSymTable().lookup(this.name)).getType().toString());
            }else{
                state.getHeap().put(((RefValue)state.getSymTable().lookup(this.name)).getAddr(), result);
                return state;
            }
        }
    }
    public String toString(){
        return "wH(" + this.name + ", " + this.exp.toString() + ")";
    }
    public IStmt deepCopy(){return null;}
}
