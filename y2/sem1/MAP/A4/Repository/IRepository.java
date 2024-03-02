package Repository;

import Domain.Exception.MyException;
import PrgState.PrgState;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public interface IRepository {
    PrgState getCrtPrg();
    void addPrgState(PrgState var);
    void logPrgStateExec() throws MyException, IOException;
    List<PrgState> getPrgList();
    void setPrgList(LinkedList<PrgState> var);
}
