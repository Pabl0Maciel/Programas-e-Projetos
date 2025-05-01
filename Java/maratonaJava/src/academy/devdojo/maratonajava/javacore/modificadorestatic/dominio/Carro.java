package academy.devdojo.maratonajava.javacore.modificadorestatic.dominio;

public class Carro {
    private String nome;
    private double velocidadeMaxima;
    private static double velocidadeLimite = 250; // variavel que pertence a classe e nao ao objeto

    // Construtor
    public Carro(String nome, double velocidadeMaxima) {
        this.nome = nome;
        this.velocidadeMaxima = velocidadeMaxima;
    }

    // Metodos
    public void imprime(){
        System.out.println("-------------");
        System.out.println("Nome: " + this.nome);
        System.out.println("Vel. Maxima: " + this.velocidadeMaxima);
        System.out.println("Vel. Limite: " + Carro.velocidadeLimite);
    }


    // Getters
    public String getNome() {
        return nome;
    }

    public double getVelocidadeMaxima() {
        return velocidadeMaxima;
    }

    public static double getVelocidadeLimite(){
        return Carro.velocidadeLimite;
    }

    // Setters
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setVelocidadeMaxima(double velocidadeMaxima) {
        this.velocidadeMaxima = velocidadeMaxima;
    }

    public static void setVelocidadeLimite(double velocidadeLimite) {
        Carro.velocidadeLimite = velocidadeLimite;
    }
}
