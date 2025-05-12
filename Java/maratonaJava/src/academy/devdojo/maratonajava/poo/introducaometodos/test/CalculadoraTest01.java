package academy.devdojo.maratonajava.poo.introducaometodos.test;

import academy.devdojo.maratonajava.poo.introducaometodos.dominio.Calculadora;

public class CalculadoraTest01 {
    public static void main(String[] args) {
        Calculadora calculadora = new Calculadora();

        calculadora.somaDoisNumeros();
        calculadora.subtraiDoisNumeros();
        calculadora.multiplicaDoisNumeros(5, 10);
        System.out.println(calculadora.divideDoisNumeros(10, 5));

        System.out.println("Depois de criar o metodo de impressao:");
        calculadora.imprimeDivisaoDoisNumeros(10, 5);

    }
}
