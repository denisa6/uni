package Domain.ADT;

import Domain.Exception.MyException;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class MyStack<T> implements MyIStack<T>{
    private Stack<T> stack = new Stack();
    public MyStack(){}
    public T pop() throws MyException{
        if(stack.isEmpty()){
            throw new MyException("empty stack");
        }else{
            return stack.pop();
        }
    }
    public void push(T v){
        stack.push(v);
    }
    public boolean isEmpty(){
        return stack.isEmpty();
    }
    public List<T> getReverse(){
        List<T> lst = Arrays.asList((T[])stack.toArray());
        Collections.reverse(lst);
        return lst;
    }
    public String toString(){
        return stack.toString();
    }
}
