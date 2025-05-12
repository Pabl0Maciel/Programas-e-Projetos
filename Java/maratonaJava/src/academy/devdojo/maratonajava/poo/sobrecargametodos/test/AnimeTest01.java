package academy.devdojo.maratonajava.poo.sobrecargametodos.test;

import academy.devdojo.maratonajava.poo.sobrecargametodos.dominio.Anime;

public class AnimeTest01 {
    public static void main(String[] args) {
        Anime anime = new Anime();

        anime.init("Akudama Drive", "TV", 12, "Acao");
        anime.imprime();
    }
}
