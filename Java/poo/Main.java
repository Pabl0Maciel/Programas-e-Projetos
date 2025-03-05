package poo;

import poo.calculo.CalculadoraDeTempo;
import poo.calculo.Recomendacao;
import poo.modelos.Episodio;
import poo.modelos.Filme;
import poo.modelos.Serie;

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

        Filme outroFilme = new Filme();

        outroFilme.setNome("Avatar");
        outroFilme.setAnoDeLancamento(2009);
        outroFilme.setDuracaoEmMinutos(162);
        

        Serie lost = new Serie();

        lost.setNome("Lost");
        lost.setAnoDeLancamento(2004);
        lost.setTemporadas(10);
        lost.setEpisodiosPorTemporada(24);
        lost.setMinutosPorEpisodio(50);

        System.out.println("Tempo para maratonar Lost: " + lost.getDuracaoEmMinutos());

        CalculadoraDeTempo calculadora = new CalculadoraDeTempo();
        calculadora.inclui(meuFilme);
        calculadora.inclui(outroFilme);
        calculadora.inclui(lost);
        System.out.println("Tempo total: " + calculadora.getTempoTotal());

        Recomendacao recomendacao = new Recomendacao();

        recomendacao.filtra(meuFilme);

        Episodio episodio = new Episodio();
        episodio.setNome("A casa amarela");
        episodio.setNumero(4);
        episodio.setSerie(lost);
        episodio.setTotalVisualizacoes(3000);

        recomendacao.filtra(episodio);
    }
}
