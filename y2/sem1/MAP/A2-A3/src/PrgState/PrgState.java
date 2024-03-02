package PrgState;

import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIList;
import Domain.ADT.MyIStack;
import Domain.IStmt.IStmt;
import Domain.Value.StringValue;
import Domain.Value.Value;

import java.io.BufferedReader;

public class PrgState {
    private MyIStack<IStmt> exeStack;
    private MyIDictionary<String,Value> symTable;
    private MyIList<Value> out;
    private MyIDictionary<StringValue,BufferedReader> fileTable;
    private IStmt originalProgram;
    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot, MyIDictionary<StringValue,BufferedReader> ft, IStmt prg){
        exeStack = stk;
        symTable = symtbl;
        out = ot;
        fileTable = ft;
        originalProgram = prg.deepCopy();
        stk.push(prg);
    }
    public MyIDictionary<StringValue,BufferedReader> getFileTable(){return fileTable;}
    public MyIStack<IStmt> getStk(){
        return exeStack;
    }
    public void setExeStack(MyIStack<IStmt> ex){
        exeStack = ex;
    }
    public void setSymTable(MyIDictionary<String,Value> tbl){
        symTable = tbl;
    }
    public void setOut(MyIList<Value> ot){
        out = ot;
    }
    public void setFileTable(MyIDictionary<StringValue, BufferedReader> ft){fileTable = ft;}
    public void setOriginalProgram(IStmt op){
        originalProgram = op;
    }
    public IStmt getCrgPrg(){
        return originalProgram;
    }
    public MyIList<Value> getOut(){
        return out;
    }
    public MyIDictionary<String,Value> getSymTable(){
        return symTable;
    }
    public String toString(){
        StringBuilder str = new StringBuilder();
        for(StringValue s : fileTable.getKeys())
            str.append(" " + s + "\n");
        return "Exe Stack " + exeStack.toString() + "\nSym Table " + symTable.toString() + "\nOutput " +
                out.toString() + "\nFileTable " + str.toString() + "\n";
    }
}
