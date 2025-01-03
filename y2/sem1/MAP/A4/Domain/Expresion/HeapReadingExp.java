package Domain.Expresion;

import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIHeap;
import Domain.Exception.MyException;
import Domain.Value.RefValue;
import Domain.Value.Value;

public class HeapReadingExp implements Exp{
    private Exp expression;
    public HeapReadingExp(Exp exp){expression = exp;}
    public Value eval(MyIDictionary<String,Value> table, MyIHeap<Integer,Value> heap) throws MyException{
        Value result = this.expression.eval(table,heap);
        if(!(result instanceof RefValue)){
            throw new MyException(result.toString() + " is not a reference value");
        }else if (!heap.isVarDef(((RefValue)result).getAddr())){
            throw new MyException(((RefValue)result).getAddr() + "addr is not in heap table");
        }else{
            Value val = (Value)heap.lookup(((RefValue)result).getAddr());
            return val;
        }
    }
    public String toString(){return "rH(" + this.expression.toString() + ")";}
    public Exp deepCopy(){return new HeapReadingExp(this.expression.deepCopy());}
}
