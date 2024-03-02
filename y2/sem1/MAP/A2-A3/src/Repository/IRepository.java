package Repository;

import Domain.Exception.MyException;
import PrgState.PrgState;

public interface IRepository {
    PrgState getCrtPrg();
    void addPrgState(PrgState var);
    void addFileName(String name);
    void logPrgStateExec() throws MyException;
}
