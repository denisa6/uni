package Domain.Type;

import Domain.Value.RefValue;
import Domain.Value.Value;

public class RefType implements Type{
    private Type inner;
    public RefType(Type i){this.inner = i;}
    public Type getInner(){return this.inner;}
    public boolean equals(Object another){
        return another instanceof RefType ? this.inner.equals(((RefType)another).getInner()):false;
    }
    public String toString(){return "Ref" + this.inner.toString();}
    public Value getDefaultValue(){return new RefValue(0,this.inner);}
    public Type deepCopy(){return new RefType(this.inner.deepCopy());}
}
