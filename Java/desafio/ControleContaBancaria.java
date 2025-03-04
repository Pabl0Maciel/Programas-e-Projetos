package desafio;

import java.util.Scanner;

public class ControleContaBancaria {
    public static void main(String[] args) {
        String nome = "Pablo";
        String tipoConta = "Conta Corrente";
        double saldo = 1000.00;
        int opcao = 0;

        System.out.println("**************");
        System.out.println("Nome do cliente: " + nome);
        System.out.println("Tipo de conta: " + tipoConta);
        System.out.println("Saldo: " + saldo);
        System.out.println("**************");

        String menu = """
                \n** Digite sua opcao **
                1 - Consultar saldo
                2 - Transferir valor
                3 - Receber valor
                4 - Sair
                """;

        Scanner leitura = new Scanner(System.in);
        while (opcao != 4) {
            System.out.println(menu);
            opcao = leitura.nextInt();

            if (opcao == 1) {

                System.out.println("\nSaldo: " + saldo);
            } 
            else if (opcao == 2) {
                System.out.println("Digite o valor a ser transferido: ");
                double valor = leitura.nextDouble();

                if (valor > saldo) {
                    System.out.println("Saldo insuficiente");
                } 
                else {
                    saldo -= valor;
                    System.out.println("Saldo atualizado: \n" + saldo);
                }
            } 
            else if (opcao == 3) {
                System.out.println("Digite o valor a ser recebido: ");
                double valor = leitura.nextDouble();
                saldo += valor;
                System.out.println("Saldo atualizado: \n" + saldo);
            } 
            else if (opcao != 4) {
                System.out.println("Opcao invalida\n");
            }
        }
        leitura.close();
    }
}
