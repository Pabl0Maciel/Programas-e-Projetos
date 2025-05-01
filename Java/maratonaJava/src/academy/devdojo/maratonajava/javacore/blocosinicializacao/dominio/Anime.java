package academy.devdojo.maratonajava.javacore.blocosinicializacao.dominio;

public class Anime {
    private String nome;
    private int[] episodios;

    // Bloco de inicializacao
    {
        System.out.println("Bloco de inicializacao");
        episodios = new int[100];

        for (int i = 0; i < episodios.length; i++){
            episodios[i] = i+1;
        }
    }
    // Construtor
    public Anime(){
        for (int ep : this.episodios){
            System.out.println(ep + " ");
        }
    }

    // Getters
    public String getNome() {
        return nome;
    }

    public int[] getEpisodios() {
        return episodios;
    }

    // Setters
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setEpisodios(int[] episodios) {
        this.episodios = episodios;
    }
}
