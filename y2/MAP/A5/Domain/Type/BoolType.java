package Domain.Type;

import com.sun.jdi.BooleanValue;
import Domain.Value.Value;
import Domain.Value.BoolValue;

public class BoolType implements Type{
    public BoolType(){}
    public boolean equals(Object another){
        if(another instanceof BoolType)
            return true;
        else
            return false;
    }
    public String toString(){
        return "bool";
    }
    public Value getDefaultValue(){
        return new BoolValue();
    }
    public Type deepCopy(){
        return new BoolType();
    }
}
