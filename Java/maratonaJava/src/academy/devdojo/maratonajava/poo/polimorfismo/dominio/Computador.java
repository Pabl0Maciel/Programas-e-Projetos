package academy.devdojo.maratonajava.poo.polimorfismo.dominio;

public class Computador extends Produto{
    public static final double IMPOSTO_POR_CENTO = 0.21;

    // Construtor
    public Computador(String nome, double valor) {
        super(nome, valor);
    }

    // Metodos
    @Override
    public double calcularImposto() {
        System.out.println("Calculando o Imposto do Computador");
        return this.valor * IMPOSTO_POR_CENTO;
    }
}
