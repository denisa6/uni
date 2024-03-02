package View;

import Controller.Controller;
import Domain.Exception.MyException;

import java.io.IOException;

public class RunExample extends Command{
    private Controller ctr;
    public RunExample(String key, String desc, Controller ctr){
        super(key,desc);
        this.ctr = ctr;
    }
    @Override
    public void execute() throws MyException{
        try{
            ctr.allStep();
        }catch (MyException e){
            throw new MyException("error"+e);
        }
    }
}
