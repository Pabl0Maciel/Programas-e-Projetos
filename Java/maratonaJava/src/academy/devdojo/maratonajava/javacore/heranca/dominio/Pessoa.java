package academy.devdojo.maratonajava.javacore.heranca.dominio;

public class Pessoa  {
    protected String nome;
    protected String CPF;
    protected Endereco endereco;

    static {
        System.out.println("Dentro do bloco de inicializacao de Pessoa");
    }
    {
        System.out.println("Dentro do bloco de inicializacao de Pessoa1");
    }
    {
        System.out.println("Dentro do bloco de inicializacao de Pessoa2");
    }


    // Construtores
    public Pessoa(String nome, String CPF, Endereco endereco) {
        System.out.println("Dentro do construtor de Pessoa");
        this.nome = nome;
        this.CPF = CPF;
        this.endereco = endereco;
    }

    public Pessoa (String nome){
        System.out.println("Dentro do construtor de Pessoa");
        this.nome = nome;
    }

    // Metodos
    public void imprime(){
        System.out.println(this.nome);
        System.out.println(this.CPF);
        System.out.println(this.endereco.getRua() + " " + this.endereco.getCep());

    }

    // Getters
    public String getNome() {
        return nome;
    }

    public String getCPF() {
        return CPF;
    }

    public Endereco getEndereco() {
        return endereco;
    }

    // Setters
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setCPF(String CPF) {
        this.CPF = CPF;
    }

    public void setEndereco(Endereco endereco) {
        this.endereco = endereco;
    }
}
