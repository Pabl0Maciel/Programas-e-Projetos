package academy.devdojo.maratonajava.javacore.modificadorfinal.dominio;

public class Comprador {
    private String nome;

    @Override
    public String toString(){
        return "Comprador: " + this.nome;
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
