package academy.devdojo.maratonajava.javacore.classesabstratas.dominio;

public class Desenvolvedor extends Funcionario{

    // Construtor
    public Desenvolvedor(String nome, double salario) {
        super(nome, salario);
    }

    // Metodos
    @Override
    public String toString(){
        return "Desenvolvedor: " + this.nome + ", Salario: " + this.salario;
    }

    @Override
    public void calculaBonus(){
        this.salario += this.salario * 0.05;
    }

}
