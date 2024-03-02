package Domain.Expresion;

import Domain.ADT.MyIDictionary;
import Domain.Exception.MyException;
import Domain.Type.IntType;
import Domain.Value.BoolValue;
import Domain.Value.IntValue;
import Domain.Value.Value;

public class RelationalExp implements Exp{
    private Exp e1;
    private Exp e2;
    private int op; //1- <, 2- <=, 3- ==, 4- !=, 5- >, 6- >=
    public RelationalExp(Exp exp1, Exp exp2, int opr){
        e1 = exp1;
        e2 = exp2;
        op = opr;
    }
    public Value eval(MyIDictionary<String, Value> tbl) throws MyException {
        Value v1,v2;
        v1 = e1.eval(tbl);
        if(v1.getType().equals(new IntType())){
            v2 = e2.eval(tbl);
            if(v2.getType().equals(new IntType())){
                IntValue i1 = (IntValue)v1;
                IntValue i2 = (IntValue)v2;
                int n1,n2;
                n1 = i1.getVal();
                n2 = i2.getVal();
                switch (op){
                    case 1:
                        if (n1 < n2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    case 2:
                        if (n1 <= n2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    case 3:
                        if (n1 == n2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    case 4:
                        if (n1 != n2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    case 5:
                        if (n1 > n2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    case 6:
                        if (n1 >= n2)
                            return new BoolValue(true);
                        else
                            return new BoolValue(false);
                    default:
                        throw new MyException("relational expression invalid");
                }
            }else
                throw new MyException("first operand is not an integer");
        }else
            throw new MyException("second operand is not an integer");
    }
    public String toString(){
        if(op == 1)
            return e1.toString() + " < " + e2.toString();
        else{
            if(op == 2)
                return e1.toString() + " <= " + e2.toString();
            else{
                if(op == 3)
                    return e1.toString() + " == " + e2.toString();
                else{
                    if(op == 4)
                        return e1.toString() + " != " + e2.toString();
                    else{
                        if(op == 5)
                            return e1.toString() + " > " + e2.toString();
                        else{
                            return e1.toString() + " >= " + e2.toString();
                        }
                    }
                }
            }
        }
    }
    public Exp deepCopy(){
        return new RelationalExp(e1.deepCopy(), e2.deepCopy(), op);
    }
}
