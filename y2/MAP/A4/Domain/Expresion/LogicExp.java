package Domain.Expresion;

import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIHeap;
import Domain.Exception.MyException;
import Domain.Type.BoolType;
import Domain.Value.BoolValue;
import Domain.Value.Value;

public class LogicExp implements Exp{
    private Exp e1;
    private Exp e2;
    private int op;
    public LogicExp(Exp exp1, Exp exp2, int opr){
        e1 = exp1;
        e2 = exp2;
        op = opr;
    }
    public Value eval(MyIDictionary<String,Value>tbl, MyIHeap<Integer, Value> heap) throws MyException{
        Value var1, var2;
        var1 = e1.eval(tbl, heap);
        if(var1.getType().equals(new BoolType())){
            var2 = e2.eval(tbl, heap);
            if(!var2.getType().equals(new BoolType()))
                throw new MyException("second operand is not bool");
            else{
                BoolValue v1 = (BoolValue)var1;
                BoolValue v2 = (BoolValue)var2;
                return op == 1 ? new BoolValue(v1.getVal() && v2.getVal()) : new BoolValue(v1.getVal() || v2.getVal());
            }
        }else
            throw new MyException("first operand is not bool");
    }
    public String toString(){
        String var;
        if(op == 1){
            var = e1.toString();
            return var + " AND " + e2.toString();
        }
        else{
            var = e1.toString();
            return var + " OR " + e2.toString();
        }
    }
    public Exp deepCopy(){
        return new LogicExp(e1.deepCopy(), e2.deepCopy(), op);
    }
}
