package Domain.ADT;


import java.util.Map;
import java.util.Set;

public interface MyIHeap<K, V> {
    V lookup(K var1);

    void put(K var1, V var2);

    boolean isVarDef(K var1);

    void update(K var1, V var2);

    String toString();

    void delete(K var1);

    Set<K> getKeys();

    void setContent(Map<K, V> var1);

    Map<K, V> getContent();
}

