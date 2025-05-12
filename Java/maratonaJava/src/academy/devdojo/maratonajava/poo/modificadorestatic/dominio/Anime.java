package academy.devdojo.maratonajava.poo.modificadorestatic.dominio;

public class Anime {
    private String nome;
    private static int[] episodios;

    // Bloco de inicializacao
    static {
        System.out.println("Bloco de inicializacao");
        episodios = new int[100];

        for (int i = 0; i < episodios.length; i++){
            episodios[i] = i+1;
        }
    }

    // Construtor
    public Anime(){
        for (int ep : Anime.episodios){
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

}
