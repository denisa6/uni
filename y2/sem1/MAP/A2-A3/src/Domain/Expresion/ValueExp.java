package Domain.Expresion;

import Domain.ADT.MyIDictionary;
import Domain.Exception.MyException;
import Domain.Value.Value;

public class ValueExp implements Exp{
    private Value e;
    public ValueExp(Value val){
        e = val;
    }
    public Value eval(MyIDictionary<String,Value>tbl) throws MyException{
        return e;
    }
    public String toString(){
        return e.toString();
    }
    public Exp deepCopy(){
        return new ValueExp(e.deepCopy());
    }
}
