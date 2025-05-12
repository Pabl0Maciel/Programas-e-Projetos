package academy.devdojo.maratonajava.poo.colecoes.test;

import academy.devdojo.maratonajava.poo.colecoes.dominio.Smartphone;

public class EqualsTest02 {
    public static void main(String[] args) {
        Smartphone smartphone = new Smartphone("1ABC1", "Iphone");
        Smartphone smartphone2 = new Smartphone("1ABC1", "Iphone");

        System.out.println(smartphone.equals(smartphone2));

        smartphone2 = smartphone;
        System.out.println(smartphone.equals(smartphone2));
    }
}
