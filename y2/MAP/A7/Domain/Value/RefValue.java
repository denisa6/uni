package Domain.Value;

import Domain.Type.RefType;
import Domain.Type.Type;

public class RefValue implements Value{
    private int addr;
    private Type type;

    public RefValue(int address, Type t){
        this.addr = address;
        this.type = t;
    }
    public int getAddr(){return this.addr;}
    public Type getType(){return new RefType(this.type);}
    public String toString(){
        return "(" + Integer.toString(this.addr) + "," + this.type.toString() + ")";
    }
    public Value deepCopy(){
        return new RefValue(this.addr, this.type.deepCopy());
    }
}
