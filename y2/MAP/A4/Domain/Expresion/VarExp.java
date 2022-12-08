package Domain.Expresion;

import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIHeap;
import Domain.Exception.MyException;
import Domain.Value.Value;

public class VarExp implements Exp{
    private String id;
    public VarExp(String var){
        id = var;
    }
    public Value eval(MyIDictionary<String,Value>tbl, MyIHeap<Integer, Value> heap) throws MyException{
        return (Value)tbl.lookup(id);
    }
    public String toString(){
        return id;
    }
    public Exp deepCopy(){
        return new VarExp(new String(id));
    }
}
