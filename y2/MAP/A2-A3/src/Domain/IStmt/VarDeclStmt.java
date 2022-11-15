package Domain.IStmt;
import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIStack;
import Domain.Exception.MyException;
import Domain.Type.Type;
import Domain.Value.Value;
import PrgState.PrgState;

public class VarDeclStmt implements IStmt{
    private String name;
    private Type typ;
    public VarDeclStmt(String n, Type t){
        name = n;
        typ = t;
    }
    public PrgState execute(PrgState state) throws MyException{
        MyIStack<IStmt> stk = state.getStk();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        if(symTable.isVarDef(name))
            throw new MyException("variable name is already used");
        else{
            symTable.put(name, typ.getDefaultValue());
            return state;
        }
    }
    public String toString(){
        return typ.toString() + " " + name + " = " + typ.getDefaultValue().toString();
    }
    public IStmt deepCopy(){
        return new VarDeclStmt(new String(name), typ.deepCopy());
    }
}