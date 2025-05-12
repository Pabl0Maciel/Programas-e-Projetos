package academy.devdojo.maratonajava.poo.associacao.dominio;

public class Jogador {
    private String nome;
    private Time time;

    // Construtor
    public Jogador(String nome) {
        this.nome = nome;
    }

    // Metodos
    public void imprime(){
        System.out.println(this.nome);

        if (this.time != null){
            System.out.println(time.getNome());
        }
    }

    // Getters
    public String getNome() {
        return nome;
    }

    public Time getTime() {
        return time;
    }

    // Setters
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setTime(Time time) {
        this.time = time;
    }
}
