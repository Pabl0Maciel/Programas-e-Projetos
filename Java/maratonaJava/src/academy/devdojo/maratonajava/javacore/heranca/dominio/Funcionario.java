package academy.devdojo.maratonajava.javacore.heranca.dominio;

public class Funcionario extends Pessoa {
    private double salario;

    static {
        System.out.println("Dentro do bloco de inicializacao de Funcionario");
    }
    {
        System.out.println("Dentro do bloco de inicializacao de Funcionario1");
    }
    {
        System.out.println("Dentro do bloco de inicializacao de Funcionario2");
    }

    // Construtores
    public Funcionario(String nome){
        super(nome);
        System.out.println("Dentro do construtor de Funcionario");
    }

    public Funcionario(String nome, String CPF, Endereco endereco) {
        super(nome, CPF, endereco);
        System.out.println("Dentro do construtor de Funcionario");
    }

    // Metodos
    @Override
    public void imprime(){
        super.imprime();
        System.out.println(this.salario);
    }

    public void relatorioPagamento(){
        System.out.println("Eu " + this.nome + " recebi o salario de " + this.salario);
    }

    // Getters
    public double getSalario() {
        return salario;
    }

    // Setters
    public void setSalario(double salario) {
        this.salario = salario;
    }
}
