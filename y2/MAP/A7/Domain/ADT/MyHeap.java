package Domain.ADT;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class MyHeap<K, V> implements MyIHeap<K, V> {
    Map<K, V> map = new HashMap();
    static int a = 0;

    public MyHeap() {
    }

    public V lookup(K key) {
        return this.map.get(key);
    }

    public void put(K k, V v) {
        this.map.put(k, v);
    }

    public boolean isVarDef(K key) {
        return this.map.containsKey(key);
    }

    public void update(K key, V value) {
        this.map.put(key, value);
    }

    public void delete(K key) {
        this.map.remove(key);
    }

    public Set<K> getKeys() {
        return this.map.keySet();
    }

    public static int getNewAddr() {
        ++a;
        return a;
    }

    public static void clearAddr() {
        a = 0;
    }

    public String toString() {
        StringBuilder stream = new StringBuilder();
        Iterator var2 = this.getKeys().iterator();

        while(var2.hasNext()) {
            K i = (K)var2.next();
            String var10001 = i.toString();
            stream.append("    " + var10001 + "-->" + this.lookup(i).toString() + "\n");
        }

        return stream.toString();
    }

    public void setContent(Map<K, V> m) {
        this.map = m;
    }

    public Map<K, V> getContent() {
        return this.map;
    }
}
