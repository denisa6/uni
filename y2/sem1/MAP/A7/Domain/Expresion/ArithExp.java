package Domain.Expresion;

import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIHeap;
import Domain.Exception.MyException;
import Domain.Type.IntType;
import Domain.Type.Type;
import Domain.Value.IntValue;
import Domain.Value.Value;

public class ArithExp implements Exp{
    private Exp e1;
    private Exp e2;
    private int op; //1-plus, 2-minus, 3-star, 4-divide
    public ArithExp(Exp exp1, Exp exp2, int opr){
        e1 = exp1;
        e2 = exp2;
        op = opr;
    }
    public Value eval(MyIDictionary<String, Value>tbl, MyIHeap<Integer, Value> heap) throws MyException{
        Value v1,v2;
        v1 = e1.eval(tbl, heap);
        if(v1.getType().equals(new IntType())){
            v2 = e2.eval(tbl, heap);
            if(v2.getType().equals(new IntType())){
                IntValue i1 = (IntValue)v1;
                IntValue i2 = (IntValue)v2;
                int n1,n2;
                n1 = i1.getVal();
                n2 = i2.getVal();
                switch (op){
                    case 1:
                        return new IntValue(n1+n2);
                    case 2:
                        return new IntValue(n1-n2);
                    case 3:
                        return new IntValue(n1*n2);
                    case 4:
                        if(n2==0) throw new MyException("division by zero");
                        else
                            return new IntValue(n1/n2);
                    default:
                        throw new MyException("?");
                }
            }else
                throw new MyException("first operand is not an integer");
        }else
            throw new MyException("second operand is not an integer");
    }
    public String toString(){
        if(op == 1)
            return e1.toString() + " + " + e2.toString();
        else{
            if(op == 2)
                return e1.toString() + " - " + e2.toString();
            else{
                if(op == 3)
                    return e1.toString() + " * " + e2.toString();
                else{
                    return e1.toString() + " / " + e2.toString();
                }
            }
        }
    }
    public Exp deepCopy(){
        return new ArithExp(e1.deepCopy(), e2.deepCopy(), op);
    }
    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        Type typ1, typ2;
        typ1 = e1.typecheck(typeEnv);
        typ2 = e2.typecheck(typeEnv);
        if (typ1.equals(new IntType())){
            if (typ2.equals(new IntType())){
                return new IntType();
            }else
                throw new MyException("second op is not an integer");
        }else
            throw new MyException("first op is not an integer");
    }
}

