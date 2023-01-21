import Domain.Exception.MyException;
import Domain.Expresion.*;
import Domain.IStmt.*;
import Domain.Type.BoolType;
import Domain.Type.IntType;
import Domain.Type.RefType;
import Domain.Type.StringType;
import Domain.Value.BoolValue;
import Domain.Value.IntValue;
import Domain.Value.StringValue;
import View.ExitCommand;
import View.RunExample;
import View.TextMenu;
import gui.gui;

import java.util.*;


public class Interpreter {
    public Interpreter(){}
    public static void main(String[] args){
        try {
            IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));
            //wrong types for typechecker
            IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new StringType()), new CompStmt(new AssignStmt("a", new ArithExp(new ValueExp(new IntValue(2)), new ArithExp(new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5)), 3), 1)), new CompStmt(new AssignStmt("b", new ArithExp(new VarExp("a"), new ValueExp(new IntValue(1)), 1)), new PrintStmt(new VarExp("b"))))));
            IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
            IStmt ex5 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new RelationalExp(new ValueExp(new IntValue(5)), new ValueExp(new IntValue(4)), "<"), new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
            //wrong types for typechecker
            IStmt ex52 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new RelationalExp(new ValueExp(new IntValue(5)), new ValueExp(new StringValue("x")), "<"), new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
            IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()), new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))), new CompStmt(new OpenRFile(new VarExp("varf")), new CompStmt(new VarDeclStmt("varc", new IntType()), new CompStmt(new ReadFile(new VarExp("varf"), "varc"), new CompStmt(new PrintStmt(new VarExp("varc")), new CompStmt(new ReadFile(new VarExp("varf"), "varc"), new CompStmt(new PrintStmt(new VarExp("varc")), new CloseRFile(new VarExp("varf"))))))))));
            IStmt ex6 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))), new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"), new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp(new VarExp("v"), new ValueExp(new IntValue(1)), 2)))), new PrintStmt(new VarExp("v")))));
            IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())), new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))), new CompStmt(new PrintStmt(new HeapReadingExp(new VarExp("v"))), new CompStmt(new HeapWritingStmt("v", new ValueExp(new IntValue(30))), new PrintStmt(new ArithExp(new HeapReadingExp(new VarExp("v")), new ValueExp(new IntValue(5)), 1))))));
            IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())), new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))), new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))), new CompStmt(new HeapAllocationStmt("a", new VarExp("v")), new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(30))), new PrintStmt(new HeapReadingExp(new HeapReadingExp(new VarExp("a")))))))));
            IStmt ex9 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new VarDeclStmt("a", new RefType(new IntType())), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))), new CompStmt(new HeapAllocationStmt("a", new ValueExp(new IntValue(22))), new CompStmt(new ForkStmt(new CompStmt(new HeapWritingStmt("a", new ValueExp(new IntValue(30))), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))), new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new HeapReadingExp(new VarExp("a"))))))), new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new HeapReadingExp(new VarExp("a")))))))));




            TextMenu menu = new TextMenu();
            menu.addCommand(new ExitCommand("0", "exit"));
            menu.addCommand(new RunExample("1", ex1.toString(), ex1, "log1.out"));
            menu.addCommand(new RunExample("2", ex2.toString(), ex2, "log2.out"));
            menu.addCommand(new RunExample("3", ex3.toString(), ex3, "log3.out"));
            menu.addCommand(new RunExample("4", ex4.toString(), ex4, "log4.out"));
            menu.addCommand(new RunExample("5", ex52.toString(), ex52, "log5.out"));
            menu.addCommand(new RunExample("6", ex6.toString(), ex6, "log6.out"));
            menu.addCommand(new RunExample("7", ex7.toString(), ex7, "log7.out"));
            menu.addCommand(new RunExample("8", ex8.toString(), ex8, "log8.out"));
            menu.addCommand(new RunExample("9", ex9.toString(), ex9, "log9.out"));
            //menu.show();
            List<IStmt> st = new ArrayList<IStmt>();
            st.add(ex1);
            st.add(ex2);
            st.add(ex3);
            st.add(ex4);
            st.add(ex5);
            st.add(ex6);
            st.add(ex7);
            st.add(ex8);
            st.add(ex9);
            gui.main_gui(args, st);
        }catch(Exception e){
            System.err.println(e);
        }
    }
}
