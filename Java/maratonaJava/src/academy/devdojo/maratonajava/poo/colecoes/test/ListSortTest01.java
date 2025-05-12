package academy.devdojo.maratonajava.poo.colecoes.test;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class ListSortTest01 {
    public static void main(String[] args) {
        List<String> mangas = new ArrayList<>(6);

        mangas.add("Hellsing ultimate");
        mangas.add("Berserk");
        mangas.add("Pokemon");
        mangas.add("Attack on titan");
        mangas.add("Dragon ball z");

        for (String m : mangas){
            System.out.println(m);
        }

        System.out.println("--------------");
        Collections.sort(mangas);

        for (String m : mangas){
            System.out.println(m);
        }

        System.out.println("/******************/");
        List<Double> dinheiros = new ArrayList<>(6);

        dinheiros.add(100.21);
        dinheiros.add(23.98);
        dinheiros.add(21.21);
        dinheiros.add(98.10);

        for (Double d : dinheiros){
            System.out.println(d);
        }

        System.out.println("--------------");
        Collections.sort(dinheiros);

        for (Double d : dinheiros){
            System.out.println(d);
        }

    }
}
