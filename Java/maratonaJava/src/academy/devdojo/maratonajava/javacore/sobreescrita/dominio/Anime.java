package academy.devdojo.maratonajava.javacore.sobreescrita.dominio;

public class Anime {
    private String nome;

    // Construtor
    public Anime(String nome) {
        this.nome = nome;
    }

    // Metodos
    @Override
    public String toString(){
        return "Anime: " + this.nome;
    }

    // Getters
    public String getNome() {
        return nome;
    }

    // Setters
    public void setNome(String nome) {
        this.nome = nome;
    }
}
