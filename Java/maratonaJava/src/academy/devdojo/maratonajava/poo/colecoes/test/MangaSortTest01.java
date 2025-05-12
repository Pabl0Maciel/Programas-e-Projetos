package academy.devdojo.maratonajava.poo.colecoes.test;

import academy.devdojo.maratonajava.poo.colecoes.dominio.Manga;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class MangaSortTest01 {
    public static void main(String[] args) {
        List<Manga> mangas = new ArrayList<>(6);

        mangas.add(new Manga(5L, "Hellsing ultimate", 19.9));
        mangas.add(new Manga(1L, "Berserk", 9.5));
        mangas.add(new Manga(4L, "Pokemon", 3.2));
        mangas.add(new Manga(3L, "Attack on titan", 11.2));
        mangas.add(new Manga(2L, "Dragon ball z", 2.99));

        for (Manga m : mangas){
            System.out.println(m);
        }

        System.out.println("-----------------");
        Collections.sort(mangas);

        for (Manga m : mangas){
            System.out.println(m);
        }

    }
}
