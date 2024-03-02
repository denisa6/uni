package Domain.ADT;

import java.util.List;

public interface MyIList<T> {
    void add(T v);
    String toString();
    List getContent();
}
