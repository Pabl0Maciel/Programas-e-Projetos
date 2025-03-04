package loop;

import java.util.Scanner;

public class For {
    
    public static void main(String[] args) {
        Scanner leitura = new Scanner(System.in);

        double media_avaliacao = 0;
        double nota = 0;

        for (int i = 0; i < 3; i++) {
            System.out.println("Digite sua nota: ");
            nota = leitura.nextDouble();
            media_avaliacao += nota;
        }
        System.out.println("Media das notas: " + media_avaliacao / 3);
    }
}
