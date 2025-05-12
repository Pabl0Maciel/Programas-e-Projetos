package academy.devdojo.maratonajava.poo.colecoes.test;

public class EqualsTest01 {
    public static void main(String[] args) {
        String nome = "William Suane";
        String nome2 = "William Suane";
        String nome3 = new String("William Suane");

        System.out.println(nome == nome2);
        System.out.println(nome == nome3);
        System.out.println(nome.equals(nome3));
    }
}
