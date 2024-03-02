package Domain.IStmt;

import Domain.ADT.*;
import Domain.Exception.MyException;
import Domain.Type.Type;
import Domain.Value.StringValue;
import Domain.Value.Value;
import PrgState.PrgState;

import java.io.BufferedReader;

public class ForkStmt implements IStmt{
    IStmt stmt;
    public ForkStmt(IStmt var){stmt = var;}

    @Override
    public PrgState execute(PrgState state) throws MyException{
        MyIDictionary<String, Value> symTbl = state.getSymTable().cloneH();
        MyIStack<IStmt> stk = new MyStack<IStmt>();
        MyIList<Value> out = state.getOut();
        MyIDictionary<StringValue, BufferedReader> fileMap = state.getFileTable();
        MyIHeap<Integer, Value> heap = state.getHeap();
        PrgState prg = new PrgState(stk, symTbl, out, fileMap, heap, stmt, PrgState.getNumberThreads());
        return prg;
    }

    @Override
    public IStmt deepCopy(){return new ForkStmt(stmt.deepCopy());}
    public String toString(){return "fork(" + stmt.toString() + ")";}
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        stmt.typecheck(typeEnv.cloneH());
        return typeEnv;
    }
}
