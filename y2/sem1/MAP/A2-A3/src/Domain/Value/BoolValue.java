package Domain.Value;

import Domain.Type.BoolType;
import Domain.Type.Type;

public class BoolValue implements Value{
    private boolean val;
    public BoolValue(boolean v){
        val = v;
    }
    public BoolValue(){
        val = false;
    }
    public boolean getVal(){
        return val;
    }
    public String toString(){
        return val ? "true" : "false";
    }
    public Type getType(){
        return new BoolType();
    }
    public Value deepCopy(){
        return new BoolValue(val);
    }
}
