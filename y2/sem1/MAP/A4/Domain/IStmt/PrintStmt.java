package Domain.IStmt;
import Domain.ADT.MyIList;
import PrgState.PrgState;
import Domain.Expresion.Exp;
import Domain.Exception.MyException;
import Domain.Value.Value;

public class PrintStmt implements IStmt{
    private Exp exp;
    public PrintStmt(Exp expr){
        exp = expr;
    }
    public String toString(){
        return  "print(" +exp.toString()+")";
    }
    public PrgState execute(PrgState state) throws MyException{
        MyIList<Value> out = state.getOut();
        Value v = exp.eval(state.getSymTable(), state.getHeap());
        out.add(v);
        state.setOut(out);
        return state;
    }
    public IStmt deepCopy(){
        return new PrintStmt(exp.deepCopy());
    }
}
