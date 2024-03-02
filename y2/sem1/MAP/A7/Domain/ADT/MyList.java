package Domain.ADT;
import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements MyIList<T>{
    private List<T> out = new ArrayList<>();
    public MyList(){}
    public void add(T e){
        out.add(e);
    }
    public String toString(){
        return out.toString();
    }
    public List getContent(){return out;}
}
