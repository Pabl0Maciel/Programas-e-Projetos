package loop;

import java.util.Scanner;

public class While {
    public static void main(String[] args) {
        Scanner leitura = new Scanner(System.in);

        double media_avaliacao = 0;
        double nota = 0;
        int totalDeNotas = 0;

        while (nota != -1) {
            System.out.println("Digite sua nota ou -1 para encerrar: ");
            nota = leitura.nextDouble();

            if (nota != -1){
                media_avaliacao += nota;
                totalDeNotas++;
            }          
        }
        System.out.println("Media das notas: " + media_avaliacao / totalDeNotas);
    }
}
