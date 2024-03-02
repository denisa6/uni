package Domain.Expresion;

import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIHeap;
import Domain.Exception.MyException;
import Domain.Value.Value;

public interface Exp {
    Value eval(MyIDictionary<String,Value>tbl, MyIHeap<Integer, Value> heap) throws MyException;
    String toString();
    Exp deepCopy();
}
