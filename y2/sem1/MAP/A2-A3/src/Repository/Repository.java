package Repository;

import Domain.Exception.MyException;
import PrgState.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;

public class Repository implements IRepository{
    private LinkedList<PrgState> repo = new LinkedList();
    private String logfilePath = "";
    public Repository(){}
    public PrgState getCrtPrg(){
        return (PrgState)repo.get(repo.size()-1);
    }
    public void addPrgState(PrgState state){
        repo.add(state);
    }
    public void addFileName(String name){logfilePath = name;}
    public void logPrgStateExec() throws MyException{
        try{
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logfilePath,true)));
            PrgState prgState = repo.get(repo.size()-1);
            logFile.write(prgState.toString());
            logFile.flush();
        }catch(IOException ioe){
            throw new MyException("error " + ioe);
        }
    }
}
