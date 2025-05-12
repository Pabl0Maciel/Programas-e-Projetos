package academy.devdojo.maratonajava.poo.polimorfismo.test;

import academy.devdojo.maratonajava.poo.polimorfismo.dominio.Computador;
import academy.devdojo.maratonajava.poo.polimorfismo.dominio.Tomate;
import academy.devdojo.maratonajava.poo.polimorfismo.servico.CalculadoraImposto;

public class ProdutoTest01 {
    public static void main(String[] args) {
        Computador computador = new Computador("NUC10i7", 11000);
        Tomate tomate = new Tomate("Tomate Cereja", 10);

        CalculadoraImposto.calcularImposto(computador);
        System.out.println("--------------");
        CalculadoraImposto.calcularImposto(tomate);
    }
}
