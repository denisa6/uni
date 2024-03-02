package Expression;

import ADT.MyIDictionary;
import ADT.MyIHeap;
import Type.*;
import Value.*;
import Exception.MyException;

public class NotExp implements Expression{
    private Expression exp;
    public NotExp(Expression e){
        this.exp = e;
    }
    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap heap) throws MyException {
        BoolValue val = (BoolValue) exp.eval(tbl, heap);
        if(!val.getVal())
            return new BoolValue(true);
        else
            return new BoolValue(false);
    }

    @Override
    public Expression deepCopy() {
        return new NotExp(exp.deepCopy());
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return exp.typecheck(typeEnv);
    }
    public String toString() {
        return String.format("!(%s)", exp);
    }
}
