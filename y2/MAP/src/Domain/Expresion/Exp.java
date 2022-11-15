package Domain.Expresion;

import Domain.ADT.MyIDictionary;
import Domain.Exception.MyException;
import Domain.Value.Value;

public interface Exp {
    Value eval(MyIDictionary<String,Value>tbl) throws MyException;
    String toString();
    Exp deepCopy();
}
