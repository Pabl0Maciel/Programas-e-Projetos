package Scanner;
import java.util.Scanner;

public class Leitura {
    public static void main(String[] args) {
        
        Scanner leitura = new Scanner(System.in);

        System.out.println("Digite seu filme favorito: ");
        String filme = leitura.nextLine();

        System.out.println("Digite o ano de lancamento do filme: ");
        int anoDeLancamento = leitura.nextInt();

        System.out.println("Digite a nota do filme: ");
        double nota = leitura.nextDouble();

        System.out.println("Seu filme favorito eh: " + filme);
        System.out.println("O filme foi lancado em: " + anoDeLancamento);
        System.out.println("A nota do filme eh: " + nota);

        leitura.close();
    }
}
