package Domain.ADT;

import java.util.Map;
import java.util.HashMap;
import java.util.Set;

public class MyDictionary<K,V> implements MyIDictionary<K,V>{
    private Map<K,V> map = new HashMap();
    public MyDictionary(){}
    public V lookup(K key){
        return map.get(key);
    }
    public void put(K key, V val){
        map.put(key,val);
    }
    public boolean isVarDef(K key){
        return map.containsKey(key);
    }
    public void update(K key, V val){
        map.put(key,val);
    }
    public String toString(){
        return map.toString();
    }
    public Set<K> getKeys(){
        return map.keySet();
    }
    public void delete(K key){map.remove(key);}
    public Map<K,V> getContent(){return this.map;}
    public MyIDictionary<K,V> cloneH(){
        MyIDictionary<K,V> clone = new MyDictionary<K,V>();
        for (K e : map.keySet())
            clone.put(e, lookup(e));
        return clone;
    }

}
