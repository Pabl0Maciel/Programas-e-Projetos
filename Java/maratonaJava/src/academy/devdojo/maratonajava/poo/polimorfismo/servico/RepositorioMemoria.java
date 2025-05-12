package academy.devdojo.maratonajava.poo.polimorfismo.servico;

import academy.devdojo.maratonajava.poo.polimorfismo.repositorio.Repositorio;

public class RepositorioMemoria implements Repositorio {

    @Override
    public void salvar() {
        System.out.println("Salvando em Memoria");
    }
}
