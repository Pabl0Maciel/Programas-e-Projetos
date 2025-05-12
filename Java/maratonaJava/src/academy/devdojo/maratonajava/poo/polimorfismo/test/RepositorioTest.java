package academy.devdojo.maratonajava.poo.polimorfismo.test;

import academy.devdojo.maratonajava.poo.polimorfismo.repositorio.Repositorio;
import academy.devdojo.maratonajava.poo.polimorfismo.servico.RepositorioBancoDeDados;

public class RepositorioTest {
    public static void main(String[] args) {
        Repositorio repositorio = new RepositorioBancoDeDados();
        repositorio.salvar();
    }
}
