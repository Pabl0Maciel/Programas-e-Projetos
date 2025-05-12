package academy.devdojo.maratonajava.poo.associacao.dominio;

public class Time {
    private String nome;
    private Jogador[] jogadores;

    // Construtores
    public Time(String nome) {
        this.nome = nome;
    }

    public Time(String nome, Jogador[] jogadors) {
        this.nome = nome;
        this.jogadores = jogadors;
    }

    // Metodos
    public void imprime(){
        System.out.println(this.nome);

        if (jogadores == null) return;
        for (Jogador j : jogadores){
            System.out.println(j.getNome());
        }
    }

    // Getters
    public String getNome() {
        return nome;
    }

    public Jogador[] getJogadores() {
        return jogadores;
    }

    // Setters
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setJogadores(Jogador[] jogadores) {
        this.jogadores = jogadores;
    }
}
