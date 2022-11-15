package Domain.Type;

import Domain.Value.StringValue;
import Domain.Value.Value;

public class StringType implements Type{
    public StringType(){}
    public boolean equals(Object another){
        if(another instanceof StringType)
            return true;
        else
            return false;
    }
    public String toString(){return "string";}
    public Value getDefaultValue(){return new StringValue();}
    public Type deepCopy(){return new StringType();}
}
