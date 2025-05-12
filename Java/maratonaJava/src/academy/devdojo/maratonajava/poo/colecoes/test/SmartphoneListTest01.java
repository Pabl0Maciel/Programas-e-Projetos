package academy.devdojo.maratonajava.poo.colecoes.test;

import academy.devdojo.maratonajava.poo.colecoes.dominio.Smartphone;

import java.util.ArrayList;
import java.util.List;

public class SmartphoneListTest01 {
    public static void main(String[] args) {
        Smartphone smartphone = new Smartphone("1ABC1", "Iphone");
        Smartphone smartphone2 = new Smartphone("22222", "Pixel");
        Smartphone smartphone3 = new Smartphone("33333", "Samsung");

        List<Smartphone> smartphones = new ArrayList<>(6);
        smartphones.add(smartphone);
        smartphones.add(smartphone2);
        smartphones.add(smartphone3);

        for (Smartphone s : smartphones){
            System.out.println(s);
        }

        System.out.println(smartphones.contains(smartphone));

    }
}
