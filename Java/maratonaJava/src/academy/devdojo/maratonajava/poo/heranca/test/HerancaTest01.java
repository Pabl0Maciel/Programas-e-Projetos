package academy.devdojo.maratonajava.poo.heranca.test;

import academy.devdojo.maratonajava.poo.heranca.dominio.Endereco;
import academy.devdojo.maratonajava.poo.heranca.dominio.Funcionario;
import academy.devdojo.maratonajava.poo.heranca.dominio.Pessoa;

public class HerancaTest01 {
    public static void main(String[] args) {
        Endereco endereco = new Endereco("Rua 3", "012345-209");
        Pessoa pessoa = new Pessoa("Toyohisa Shimazu", "11111111111", endereco);

        pessoa.imprime();

        System.out.println("------------");

        Funcionario funcionario = new Funcionario("Oda Nobunaga", "22222222222", endereco);
        funcionario.setSalario(20000);

        funcionario.imprime();
        funcionario.relatorioPagamento();
    }
}
