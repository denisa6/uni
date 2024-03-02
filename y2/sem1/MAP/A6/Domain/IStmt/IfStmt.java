package Domain.IStmt;

import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIStack;
import Domain.Exception.MyException;
import Domain.Type.BoolType;
import Domain.Type.Type;
import Domain.Value.BoolValue;
import PrgState.PrgState;
import Domain.Expresion.Exp;
import Domain.Value.Value;

public class IfStmt implements IStmt{
    private Exp exp;
    private IStmt thenS;
    private IStmt elseS;
    public IfStmt(Exp e, IStmt t, IStmt el){
        exp = e;
        thenS = t;
        elseS = el;
    }
    public String toString() {
        return "(IF("+exp.toString()+")THEN("+thenS.toString()+")ELSE("+elseS.toString()+"))";
    }
    public PrgState execute(PrgState state) throws MyException{
        Value var = exp.eval(state.getSymTable(), state.getHeap());
        MyIStack<IStmt> stack = state.getStk();
        if(var.getType().equals(new BoolType())){
            BoolValue v = (BoolValue)var;
            if(v.getVal()){
                stack.push(thenS);
            }else{
                stack.push(elseS);
            }
            return state;
        }else
            throw new MyException("expression is not bool");
    }
    public IStmt deepCopy(){
        return new IfStmt(exp.deepCopy(), thenS.deepCopy(), elseS.deepCopy());
    }
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException{
        Type typexp = exp.typecheck(typeEnv);
        if(typexp.equals(new BoolType())){
            thenS.typecheck(typeEnv.cloneH());
            elseS.typecheck(typeEnv.cloneH());
            return typeEnv;
        }else
            throw new MyException("The condition of IF doesn't have the type bool");
    }

}
