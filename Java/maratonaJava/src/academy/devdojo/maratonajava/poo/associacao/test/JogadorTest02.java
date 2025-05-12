package academy.devdojo.maratonajava.poo.associacao.test;

import academy.devdojo.maratonajava.poo.associacao.dominio.Jogador;
import academy.devdojo.maratonajava.poo.associacao.dominio.Time;

public class JogadorTest02 {
    public static void main(String[] args) {
        Jogador jogador1 = new Jogador("Pele");
        Time time = new Time("Selecao Brasileira");

        jogador1.setTime(time);
        jogador1.imprime();

    }
}
