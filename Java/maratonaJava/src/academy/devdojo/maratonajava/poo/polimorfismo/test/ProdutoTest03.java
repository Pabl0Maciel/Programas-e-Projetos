package academy.devdojo.maratonajava.poo.polimorfismo.test;

import academy.devdojo.maratonajava.poo.polimorfismo.dominio.Computador;
import academy.devdojo.maratonajava.poo.polimorfismo.dominio.Produto;
import academy.devdojo.maratonajava.poo.polimorfismo.dominio.Tomate;
import academy.devdojo.maratonajava.poo.polimorfismo.servico.CalculadoraImposto;

public class ProdutoTest03 {
    public static void main(String[] args) {
        Produto produto = new Computador("Ryzen 9", 3000);
        Tomate tomate = new Tomate("Americano", 20);

        tomate.setDataValidade("11/12/2021");
        CalculadoraImposto.calcularImposto(tomate);
        System.out.println("--------------");
        CalculadoraImposto.calcularImposto(produto);
    }

}
