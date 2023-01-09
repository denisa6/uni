package PrgState;

import Domain.ADT.MyIDictionary;
import Domain.ADT.MyIHeap;
import Domain.ADT.MyIList;
import Domain.ADT.MyIStack;
import Domain.Exception.MyException;
import Domain.IStmt.IStmt;
import Domain.Value.StringValue;
import Domain.Value.Value;

import java.io.BufferedReader;

public class PrgState {
    private MyIStack<IStmt> exeStack;
    private MyIDictionary<String,Value> symTable;
    private MyIList<Value> out;
    private MyIDictionary<StringValue,BufferedReader> fileTable;
    private MyIHeap<Integer, Value> heap;
    private int id = 0;
    public static int numberThreads = 0;
    private IStmt originalProgram;
    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot, MyIDictionary<StringValue,BufferedReader> ft, MyIHeap<Integer,Value> h, IStmt prg, int i){
        exeStack = stk;
        symTable = symtbl;
        out = ot;
        fileTable = ft;
        heap = h;
        originalProgram = prg.deepCopy();
        stk.push(prg);
        id = i;
    }
    public int getId(){return id;}
    static public int getNumberThreads(){return ++numberThreads;}
    public MyIHeap<Integer,Value> getHeap(){return this.heap;}
    public void setHeap(MyIHeap<Integer,Value> h){heap = h;}
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
        return id + "\n" + "Exe Stack " + exeStack.toString() + "\nSym Table " + symTable.toString() + "\nOutput " +
                out.toString() + "\nFileTable " + str.toString() + "\nHeap " + heap.toString() + "\n";
    }
    public boolean isNotCompleted(){
        return !this.exeStack.isEmpty();
    }

    public PrgState oneStep() throws MyException{
        if(exeStack.isEmpty())
            throw new MyException("prgState is empty");
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }
}
