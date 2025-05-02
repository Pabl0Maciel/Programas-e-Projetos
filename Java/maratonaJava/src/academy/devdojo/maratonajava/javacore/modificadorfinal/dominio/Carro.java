package academy.devdojo.maratonajava.javacore.modificadorfinal.dominio;

public class Carro {
    private String nome;
    public static final double VELOCIDADE_LIMITE = 250;
    public final Comprador COMPRADOR = new Comprador();

    // Construtor
    public Carro(String nome) {
        this.nome = nome;
    }

    // Metodos
    public final void imprime(){
        System.out.println(this.nome);
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
