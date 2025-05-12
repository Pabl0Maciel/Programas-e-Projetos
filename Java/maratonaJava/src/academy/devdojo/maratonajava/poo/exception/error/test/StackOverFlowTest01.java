package academy.devdojo.maratonajava.poo.exception.error.test;

public class StackOverFlowTest01 {
    public static void main(String[] args) {
        recursividade();
    }

    public static void recursividade(){
        recursividade();
    }
}
