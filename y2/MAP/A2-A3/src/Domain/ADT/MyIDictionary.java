package Domain.ADT;
import java.util.Set;

public interface MyIDictionary<K,V> {
    V lookup(K k);
    void put(K k, V v);
    boolean isVarDef(K k);
    void update(K k, V v);
    String toString();
    Set<K> getKeys();
    void delete(K k);
}
