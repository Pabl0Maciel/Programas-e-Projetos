package academy.devdojo.maratonajava.poo.modificadorfinal.test;

import academy.devdojo.maratonajava.poo.modificadorfinal.dominio.Carro;
import academy.devdojo.maratonajava.poo.modificadorfinal.dominio.Ferrari;

public class CarroTest01 {
    public static void main(String[] args) {
        Carro carro = new Carro("BMW");
        Ferrari ferrari = new Ferrari("Enzo");

        System.out.println(Carro.VELOCIDADE_LIMITE);

        System.out.println(carro.COMPRADOR);
        carro.COMPRADOR.setNome("Kuririn");
        System.out.println(carro.COMPRADOR);

        ferrari.imprime();
    }
}
