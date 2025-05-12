package academy.devdojo.maratonajava.poo.colecoes.dominio;

import java.util.Comparator;
import java.util.Objects;

public class Manga implements Comparable<Manga> {
    private Long id;
    private String nome;
    private double preco;

    // Construtor
    public Manga(Long id, String nome, double preco) {
        Objects.requireNonNull((id));
        Objects.requireNonNull((nome));
        this.id = id;
        this.nome = nome;
        this.preco = preco;
    }

    // Metodos


    @Override
    public int compareTo(Manga manga) {
//        // negativo se this < manga
//        // 0 se this == manga
//        // positivo se this > manga
//
//        if (this.id < manga.getId()) return -1;
//
//        if (this.id.equals((manga.getId()))) return 0;
//
//        return 1;

//        return this.nome.compareTo(manga.getNome());
//        return Double.valueOf(preco).compareTo(manga.getPreco());
//        return Double.compare(preco, manga.getPreco());
        return this.id.compareTo(manga.getId());
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Manga manga = (Manga) o;
        return Double.compare(preco, manga.preco) == 0 && Objects.equals(id, manga.id) && Objects.equals(nome, manga.nome);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, nome, preco);
    }

    @Override
    public String toString() {
        return "Manga{" +
                "id=" + id +
                ", nome='" + nome + '\'' +
                ", preco=" + preco +
                '}';
    }

    // Getters
    public Long getId() {
        return id;
    }

    public String getNome() {
        return nome;
    }

    public double getPreco() {
        return preco;
    }
}
