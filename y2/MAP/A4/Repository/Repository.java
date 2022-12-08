package Repository;

import Domain.Exception.MyException;
import Domain.Value.StringValue;
import PrgState.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;

public class Repository implements IRepository{
    private LinkedList<PrgState> repo = new LinkedList();
    private StringValue logfilePath;
    public Repository(StringValue FilePath){this.logfilePath = FilePath;}
    public PrgState getCrtPrg(){
        return (PrgState)repo.get(repo.size()-1);
    }
    public void addPrgState(PrgState state){
        repo.add(state);
    }
    public void logPrgStateExec() throws MyException{
        try{
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(String.valueOf(this.logfilePath),true)));
            PrgState prgState = repo.get(repo.size()-1);
            logFile.write(prgState.toString());
            logFile.flush();
        }catch(IOException ioe){
            throw new MyException("error " + ioe);
        }
    }
    public List<PrgState> getPrgList(){return this.repo;}
    public void setPrgList(LinkedList<PrgState> list){this.repo = list;}
}
