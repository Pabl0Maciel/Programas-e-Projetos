package poo;

public class Filme {
    String nome;
    int anoDeLancamento;
    boolean incluidoNoPlano;
    double somaAvaliacoes;
    int totalDeAvaliacoes;
    int duracaoEmMinutos;

    void exibeFichaTecnica(){
        System.out.println("Nome: " + this.nome);
        System.out.println("Ano de lancamento: " + this.anoDeLancamento);
        System.out.println("Incluido no plano: " + this.incluidoNoPlano);
        System.out.println("Total de avaliacoes: " + this.totalDeAvaliacoes);
        System.out.println("Duracao em minutos: " + this.duracaoEmMinutos);
    }

    void avalia(double nota){
        somaAvaliacoes += nota;
        totalDeAvaliacoes++;
    }

    double mediaDasAvaliacoes(){
        return somaAvaliacoes / totalDeAvaliacoes;
    }
}
