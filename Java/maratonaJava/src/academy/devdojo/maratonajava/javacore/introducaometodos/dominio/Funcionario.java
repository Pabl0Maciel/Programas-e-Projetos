package academy.devdojo.maratonajava.javacore.introducaometodos.dominio;

public class Funcionario {
    private String nome;
    private int idade;
    private double[] salarios;
    private double media;

    // Getters
    public String getNome() {
        return nome;
    }

    public int getIdade() {
        return idade;
    }

    public double[] getSalarios() {
        return salarios;
    }

    public double getMedia() {
        return media;
    }

    // Setters
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setIdade(int idade) {
        this.idade = idade;
    }

    public void setSalarios(double[] salarios) {
        this.salarios = salarios;
    }

    // Metodos
    public void imprime(){
        System.out.println(this.nome);
        System.out.println(this.idade);

        if (salarios == null) return;
        for (double s : salarios){
            System.out.println(s + " ");
        }
        imprimeMediaSalarios();
    }

    public void imprimeMediaSalarios(){
        if (salarios == null) return;

        for (double s : salarios){
            media += s;
        }
        media /= salarios.length;
        System.out.println("Media salarial: " + media);
    }

}
