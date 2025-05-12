package academy.devdojo.maratonajava.poo.associacao.test;

import academy.devdojo.maratonajava.poo.associacao.dominio.Jogador;

public class JogadorTest01 {
    public static void main(String[] args) {
        Jogador jogador1 = new Jogador("Pele");
        Jogador jogador2 = new Jogador("Romario");
        Jogador jogador3 = new Jogador("Cafu");

        Jogador[] jogadores = {jogador1, jogador2, jogador3};
        for (Jogador j : jogadores){
            j.imprime();
        }
    }
}
