package GarbageCollector;

import Domain.Value.RefValue;
import Domain.Value.Value;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class GarbageCollector {
    public GarbageCollector(){}
    public static Map<Integer, Value> unsafeGarbageCollector(List<Integer> symTableAddr, Map<Integer,Value> heap){
        return (Map)heap.entrySet().stream().filter((e) -> {
            return symTableAddr.contains(e.getKey());
        }).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }
    public static List<Integer> getAddrFromSymTable(Collection<Value> SymTableValues, Collection<Value> heapTableValues){
        List<Integer> result = new ArrayList();
        result.addAll((Collection)SymTableValues.stream().filter((v) -> {
            return v instanceof RefValue;
        }).map((v) -> {
            RefValue v1 = (RefValue)v;
            return v1.getAddr();
        }).collect(Collectors.toList()));
        result.addAll((Collection)heapTableValues.stream().filter((v) -> {
            return v instanceof RefValue;
        }).map((v) -> {
            return ((RefValue)v).getAddr();
        }).collect(Collectors.toList()));
        return result;
    }
}
