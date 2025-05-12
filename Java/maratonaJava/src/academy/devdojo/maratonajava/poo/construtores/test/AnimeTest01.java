package academy.devdojo.maratonajava.poo.construtores.test;

import academy.devdojo.maratonajava.poo.construtores.dominio.Anime;

public class AnimeTest01 {
    public static void main(String[] args) {
        Anime anime = new Anime("Haikyuu", "TV", 12, "Acao");
        Anime anime2 = new Anime();

        anime.imprime();
        anime2.imprime();
    }
}
