package poo;

import poo.modelos.Filme;

public class Main {
    public static void main(String[] args) {
        Filme meuFilme = new Filme();

        meuFilme.setNome("O poderoso chefao");
        meuFilme.setAnoDeLancamento(1972);
        meuFilme.setDuracaoEmMinutos(180);

        meuFilme.exibeFichaTecnica();

        meuFilme.avalia(8);
        meuFilme.avalia(5);
        meuFilme.avalia(10);
        
        System.out.println("Total das avaliacoes: " + meuFilme.getTotalDeAvaliacoes());
        System.out.println("Soma das avaliacoes: " + meuFilme.getSomaDeAvaliacoes());
        System.out.println(meuFilme.mediaDasAvaliacoes());
    }

}
