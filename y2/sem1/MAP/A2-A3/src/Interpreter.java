import Controller.Controller;
import Domain.ADT.*;
import Domain.Exception.MyException;
import Domain.Expresion.ArithExp;
import Domain.Expresion.RelationalExp;
import Domain.Expresion.ValueExp;
import Domain.Expresion.VarExp;
import Domain.IStmt.*;
import Domain.Type.BoolType;
import Domain.Type.IntType;
import Domain.Type.StringType;
import Domain.Value.BoolValue;
import Domain.Value.IntValue;
import Domain.Value.StringValue;
import Repository.IRepository;
import PrgState.PrgState;
import Repository.Repository;
import View.*;


public class Interpreter {
    public Interpreter(){}
    public static void main(String[] args){
        try {
            IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));
            MyIDictionary map1 = new MyDictionary();
            MyIStack stk1 = new MyStack();
            MyIList out1 = new MyList();
            MyIDictionary ft1 = new MyDictionary();
            PrgState prg1 = new PrgState(stk1, map1, out1, ft1, ex1);
            IRepository repo1 = new Repository();
            repo1.addPrgState(prg1);
            repo1.addFileName("log1.txt");
            Controller ctr1 = new Controller(repo1);

            IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new IntType()), new CompStmt(new AssignStmt("a", new ArithExp(new ValueExp(new IntValue(2)), new ArithExp(new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5)), 3), 1)), new CompStmt(new AssignStmt("b", new ArithExp(new VarExp("a"), new ValueExp(new IntValue(1)), 1)), new PrintStmt(new VarExp("b"))))));
            MyIDictionary map2 = new MyDictionary();
            MyIStack stk2 = new MyStack();
            MyIList out2 = new MyList();
            MyIDictionary ft2 = new MyDictionary();
            PrgState prg2 = new PrgState(stk2,map2,out2,ft2,ex2);
            IRepository repo2 = new Repository();
            repo2.addPrgState(prg2);
            repo2.addFileName("log2.txt");
            Controller ctr2 = new Controller(repo2);

            IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
            MyIDictionary map3 = new MyDictionary();
            MyIStack stk3 = new MyStack();
            MyIList out3 = new MyList();
            MyIDictionary ft3 = new MyDictionary();
            PrgState prg3 = new PrgState(stk3,map3,out3,ft3,ex3);
            IRepository repo3 = new Repository();
            repo3.addPrgState(prg3);
            repo3.addFileName("log3.txt");
            Controller ctr3 = new Controller(repo3);

            IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()), new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                    new CompStmt(new OpenRFile(new VarExp("varf")), new CompStmt(new VarDeclStmt("varc", new IntType()), new CompStmt(
                            new ReadFile(new VarExp("varf"), "varc"), new CompStmt(new PrintStmt(new VarExp("varc")), new CompStmt(
                            new ReadFile(new VarExp("varf"), "varc"), new CompStmt(new PrintStmt(new VarExp("varc")), new CloseRFile(
                            new VarExp("varf"))))))))));
            MyIDictionary map4 = new MyDictionary();
            MyIStack stk4 = new MyStack();
            MyIList out4 = new MyList();
            MyIDictionary ft4 = new MyDictionary();
            PrgState prg4 = new PrgState(stk4,map4,out4,ft4,ex4);
            IRepository repo4 = new Repository();
            repo4.addPrgState(prg4);
            repo4.addFileName("log4.txt");
            Controller ctr4 = new Controller(repo4);


            IStmt ex5 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new IntType()),
                    new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("a",
             new ValueExp(new IntValue(5))), new CompStmt( new AssignStmt("b",new ValueExp(new IntValue(6))),new CompStmt(new IfStmt(new RelationalExp(new VarExp("a"),new VarExp("b"),2),
             new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))),
              new PrintStmt(new VarExp("v"))))))));
            MyIDictionary map5 = new MyDictionary();
            MyIStack stk5 = new MyStack();
            MyIList out5 = new MyList();
            MyIDictionary ft5 = new MyDictionary();
            PrgState prg5 = new PrgState(stk5,map5,out5,ft5,ex5);
            IRepository repo5 = new Repository();
            repo5.addPrgState(prg5);
            repo5.addFileName("log5.txt");
            Controller ctr5 = new Controller(repo5);

            TextMenu menu = new TextMenu();
            menu.addCommand(new ExitCommand("0", "exit"));
            menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
            menu.addCommand(new RunExample("2",ex2.toString(), ctr2));
            menu.addCommand(new RunExample("3",ex3.toString(), ctr3));
            menu.addCommand(new RunExample("4",ex4.toString(), ctr4));
            menu.addCommand(new RunExample("5",ex5.toString(), ctr5));
            menu.show();
        }catch(MyException e){
            System.err.println(e);
        }
    }
}
