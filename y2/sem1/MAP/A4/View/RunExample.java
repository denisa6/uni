package View;

import Controller.Controller;
import Domain.ADT.*;
import Domain.Exception.MyException;
import Domain.IStmt.IStmt;
import Domain.Value.StringValue;
import PrgState.PrgState;
import Repository.IRepository;
import Repository.Repository;

import java.io.IOException;
import java.io.PrintWriter;

public class RunExample extends Command{
    private IStmt orgPrg;
    String fileName;
    public RunExample(String key, String desc, IStmt orgprg, String file){
        super(key,desc);
        orgPrg = orgprg;
        fileName = file;
    }
    @Override
    public void execute() throws MyException{
        try{
            MyIDictionary map = new MyDictionary();
            MyIStack stk = new MyStack();
            MyIList out = new MyList();
            MyIDictionary fileMap = new MyDictionary();
            MyIHeap heap = new MyHeap();
            PrgState prg = new PrgState(stk, map, out, fileMap, heap, orgPrg);
            IRepository repo = new Repository(new StringValue(fileName));
            repo.addPrgState(prg);
            Controller ctrl = new Controller(repo);

            try{
                PrintWriter writer = new PrintWriter(fileName);
                writer.print("");
                writer.close();
            }catch (IOException v){

            }

            MyHeap.clearAddr();
            ctrl.allStep();
        }catch (MyException v2){
            System.out.println(v2);
        }
    }
}
