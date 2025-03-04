public class Variaveis{
    public static void main(String[] args) {
        System.out.println("Esse eh o Screen Match");
        System.out.println("Filme: Top Gun: Maverick");

        int anoDeLancamento = 2022;
        System.out.println("Ano de lancamento: " + anoDeLancamento);
        boolean incluidoNoPlano = true;
        double notaDoFIlme = 8.1;

        // media da nota
        double media = (9.8 + 6.3 + 8.0) / 3;
        System.out.println("media: " + media);

        // string eh uma classe
        String sinopse;
        sinopse = "Filme de aventura com gala dos anos 80";
        System.out.println("Sinopse: " + sinopse);

        // casting da media de decimal para inteiro
        int classificacao = (int) media;
        System.out.println("Classificacao: " + classificacao);
    }
}