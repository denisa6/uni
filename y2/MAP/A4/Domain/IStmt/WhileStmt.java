package Domain.IStmt;

import Domain.Exception.MyException;
import Domain.Expresion.Exp;
import Domain.Type.BoolType;
import Domain.Value.BoolValue;
import Domain.Value.Value;
import PrgState.PrgState;

public class WhileStmt implements IStmt{
    private Exp exp;
    private IStmt stmt;

    public WhileStmt(Exp e, IStmt st){
        exp = e;
        stmt = st;
    }

    public PrgState execute(PrgState state) throws MyException{
        Value result = this.exp.eval(state.getSymTable(), state.getHeap());
        if(!result.getType().equals(new BoolType())){
            throw new MyException(this.exp.toString() + " cond exp is not bool");
        } else {
            if(((BoolValue)result).getVal()){
                state.getStk().push(new WhileStmt(this.exp.deepCopy(), this.stmt.deepCopy()));
                state.getStk().push(this.stmt);
            }
            return state;
        }
    }

    public String toString(){
        return "while (" + exp.toString() + "){" + stmt.toString() + "}";
    }

    public IStmt deepCopy(){
        return new WhileStmt(exp.deepCopy(), stmt.deepCopy());
    }
}
