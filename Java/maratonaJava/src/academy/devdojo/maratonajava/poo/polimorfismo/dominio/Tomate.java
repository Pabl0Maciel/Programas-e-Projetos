package academy.devdojo.maratonajava.poo.polimorfismo.dominio;

public class Tomate extends Produto{
    public static final double IMPOSTO_POR_CENTO = 0.06;
    private String dataValidade;

    // Construtor
    public Tomate(String nome, double valor) {
        super(nome, valor);
    }

    // Metodos
    @Override
    public double calcularImposto() {
        System.out.println("Calculando o Imposto do Tomate");
        return this.valor * IMPOSTO_POR_CENTO;
    }

    // Getters
    public String getDataValidade() {
        return dataValidade;
    }

    // Setters
    public void setDataValidade(String dataValidade) {
        this.dataValidade = dataValidade;
    }
}
