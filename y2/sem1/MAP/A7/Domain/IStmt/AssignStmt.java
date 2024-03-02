package Domain.IStmt;

import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIStack;
import Domain.Exception.MyException;
import Domain.Expresion.Exp;
import Domain.Type.Type;
import Domain.Value.Value;
import PrgState.PrgState;

public class AssignStmt implements IStmt{
    private String id;
    private Exp exp;
    public AssignStmt(String var, Exp expr){
        id = var;
        exp = expr;
    }
    public String toString(){
        return id + " = " + exp.toString();
    }
    public PrgState execute(PrgState state) throws MyException{
        MyIStack<IStmt> stk = state.getStk();
        MyIDictionary<String,Value> symTbl = state.getSymTable();
        if (symTbl.isVarDef(id)){
            Value val = exp.eval(symTbl, state.getHeap());
            Type typId = ((Value)symTbl.lookup(id)).getType();
            if(val.getType().equals(typId)){
                symTbl.update(id, val);
                return state;
            }else
                throw new MyException("declared type of variable" + id + "and type of the assigned expression do not match");
        }
        else
            throw new MyException("the used variable" + id + "was not declared before");
    }
    public IStmt deepCopy(){
        return new AssignStmt(new String(id), exp.deepCopy());
    }
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException{
        Type typevar = typeEnv.lookup(id);
        Type typexp = exp.typecheck(typeEnv);
        if(typevar.equals(typexp))
            return typeEnv;
        else
            throw new MyException("Assignment: right hand side and left hand side have different types");
    }

}
