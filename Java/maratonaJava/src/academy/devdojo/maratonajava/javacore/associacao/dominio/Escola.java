package academy.devdojo.maratonajava.javacore.associacao.dominio;

public class Escola {
    private String nome;
    private Professor[] professores;

    // Construtores
    public Escola(String nome) {
        this.nome = nome;
    }

    public Escola(String nome, Professor[] professores) {
        this.nome = nome;
        this.professores = professores;
    }

    // Metodos
    public void imprime(){
        System.out.println("Nome da escola: " + this.nome);

        if (professores == null) return;
        System.out.println("Professores:");
        for (Professor p : professores){
            System.out.println(p.getNome());
        }
    }

    // Getters
    public String getNome() {
        return nome;
    }

    public Professor[] getProfessores() {
        return professores;
    }

    // Setters
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setProfessores(Professor[] professores) {
        this.professores = professores;
    }
}
