package Domain.IStmt;

import Domain.ADT.MyHeap;
import Domain.ADT.MyIDictionary;
import Domain.Exception.MyException;
import Domain.Type.RefType;
import Domain.Type.Type;
import Domain.Value.RefValue;
import Domain.Value.Value;
import PrgState.PrgState;
import Domain.Expresion.Exp;

public class HeapAllocationStmt implements IStmt{
    private String name;
    private Exp exp;

    public HeapAllocationStmt(String n, Exp e){
        this.name = n;
        this.exp = e;
    }
    public PrgState execute(PrgState state) throws MyException{
        if(!state.getSymTable().isVarDef(this.name)){
            throw new MyException(this.name + " is not defined in SymTbl");
        }else{
            Value result = this.exp.eval(state.getSymTable(), state.getHeap());
            if(!(((Value)state.getSymTable().lookup(this.name)).getType() instanceof RefType)){
                throw new MyException(this.name + " is not of reference type");
            }else if(!((Value)state.getSymTable().lookup(this.name)).getType().equals(new RefType(result.getType()))){
                throw new MyException(this.name + " is not of reference type");
            }else if (!result.getType().equals(((RefType)((Value)state.getSymTable().lookup(this.name)).getType()).getInner())){
                throw new MyException(result.toString() + " has different type from " + ((Value)state.getSymTable().lookup(this.name)).toString());
            }else{
                int addr = MyHeap.getNewAddr();
                state.getHeap().put(addr,result);
                state.getSymTable().put(this.name, new RefValue(addr, ((RefType)((Value)state.getSymTable().lookup(this.name)).getType()).getInner()));
                return state;
            }
        }
    }
    public String toString(){
        return "new(" + this.name + ", " + this.exp.toString() + ")";
    }
    public IStmt deepCopy(){
        return new HeapAllocationStmt(new String(this.name), this.exp.deepCopy());
    }
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        Type typeVar = typeEnv.lookup(name);
        Type typeExpr = exp.typecheck(typeEnv);
        if(typeVar.equals(new RefType(typeExpr)))
            return typeEnv;
        else
            throw new MyException("NEW statement: right hand side and left hand side have different types");
    }

}
