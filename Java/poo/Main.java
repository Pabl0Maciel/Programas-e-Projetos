package poo;

public class Main {
    public static void main(String[] args) {
        Filme meuFilme = new Filme();

        meuFilme.nome = "O poderoso chefao";
        meuFilme.anoDeLancamento = 1972;

        meuFilme.exibeFichaTecnica();

        meuFilme.avalia(8);
        meuFilme.avalia(5);
        meuFilme.avalia(10);
        
        System.out.println(meuFilme.somaAvaliacoes);
        System.out.println(meuFilme.mediaDasAvaliacoes());
    }

}
