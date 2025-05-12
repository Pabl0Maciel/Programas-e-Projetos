package academy.devdojo.maratonajava.poo.enumeracao.teste;

import academy.devdojo.maratonajava.poo.enumeracao.dominio.Cliente;
import academy.devdojo.maratonajava.poo.enumeracao.dominio.TipoCliente;
import academy.devdojo.maratonajava.poo.enumeracao.dominio.TipoPagamento;

public class ClienteTest01 {
    public static void main(String[] args) {
        Cliente cliente1 = new Cliente("Tsubasa", TipoCliente.PESSOA_FISICA, TipoPagamento.DEBITO);
        Cliente cliente2 = new Cliente("Akira", TipoCliente.PESSOA_JURIDICA, TipoPagamento.CREDITO);

        System.out.println(cliente1);
        System.out.println(cliente2);

        System.out.println(TipoPagamento.DEBITO.calcularDesconto(100));
        System.out.println(TipoPagamento.CREDITO.calcularDesconto(100));


    }
}
