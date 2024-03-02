package Statement;

import ADT.MyIDictionary;
import ADT.MyIStack;
import ADT.PrgState;
import Expression.*;
import Type.*;
import Exception.MyException;

public class RepeatUntil implements Statement{
    private Statement stmt;
    private Expression exp;
    public RepeatUntil(Statement s, Expression e){
        this.stmt = s;
        this.exp = e;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<Statement> exeStack = state.getExeStack();
        Statement converted = new CompStmt(stmt, new WhileStmt(new NotExp(exp), stmt));
        exeStack.push(converted);
        state.setExeStack(exeStack);
        return null;    }

    @Override
    public Statement deepCopy() {
        return new RepeatUntil(stmt.deepCopy(), exp.deepCopy());
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type type = exp.typecheck(typeEnv);
        if (type.equals(new BoolType())) {
            stmt.typecheck(typeEnv.cloneH());
            return typeEnv;
        } else {
            throw new MyException("Expression in the repeat statement must be of Bool type!");
        }
    }
    public String toString(){
        return String.format("repeat(%s) until (%s)", stmt, exp);
    }
}
