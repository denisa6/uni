package View;

import Domain.Exception.MyException;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class TextMenu {
    private Map<String,Command> commands = new HashMap();
    public TextMenu(){}
    public void addCommand(Command c){commands.put(c.getKey(),c);}
    private void printMenu(){
        for(Command com : commands.values()){
            String line = String.format("%4s:%s",com.getKey(),com.getDescription());
            System.out.println(line);
        }
    }
    public void show() throws MyException{
        try {
            Scanner scanner = new Scanner(System.in);
            while (true) {
                printMenu();
                System.out.println("Input the option: ");
                String key = scanner.nextLine();
                Command com = commands.get(key);
                if (com == null) {
                    System.out.println("Invalid Option");
                    continue;
                }
                com.execute();
            }
        }catch(MyException e){
            throw new MyException("error");
        }
    }
}
