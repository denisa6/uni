package Domain.Value;

import Domain.Type.Type;
import Domain.Type.IntType;

public class IntValue implements Value{
    private int val;
    public IntValue(int v){
        val = v;
    }
    public IntValue(){
        val = 0;
    }
    public int getVal(){
        return val;
    }
    public String toString(){
        return Integer.toString(val);
    }
    public Type getType(){
        return new IntType();
    }
    public Value deepCopy(){
        return new IntValue(val);
    }
}
