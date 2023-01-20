package Repository;

import Domain.Exception.MyException;
import PrgState.PrgState;

import java.util.List;

public interface IRepository {
    PrgState getCrtPrg();
    void addPrgState(PrgState var);
    void logPrgStateExec(PrgState prg) throws MyException;
    List<PrgState> getPrgList();
    void setPrgList(List<PrgState> var);
    PrgState getProgramWithId(int id);
}
