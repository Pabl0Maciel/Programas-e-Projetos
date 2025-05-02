package academy.devdojo.maratonajava.javacore.classesabstratas.dominio;

public class Gerente extends Funcionario{

    // Construtor
    public Gerente(String nome, double salario) {
        super(nome, salario);
    }

    // Metodos
    @Override
    public String toString(){
        return "Gerente: " + this.nome + ", Salario: " + this.salario;
    }

    public void calculaBonus(){
        this.salario += this.salario * 0.05;
    }
}
