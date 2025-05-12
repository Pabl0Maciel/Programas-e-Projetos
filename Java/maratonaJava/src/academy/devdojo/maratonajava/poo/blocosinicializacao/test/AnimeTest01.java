package academy.devdojo.maratonajava.poo.blocosinicializacao.test;

import academy.devdojo.maratonajava.poo.blocosinicializacao.dominio.Anime;

public class AnimeTest01 {
    public static void main(String[] args) {
        Anime anime = new Anime();

        System.out.println(anime.getEpisodios());
    }
}
