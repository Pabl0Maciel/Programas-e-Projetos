package academy.devdojo.maratonajava.poo.introducaometodos.test;

import academy.devdojo.maratonajava.poo.introducaometodos.dominio.Funcionario;

public class FuncionarioTest01 {
    public static void main(String[] args) {
        Funcionario funcionario = new Funcionario();

        funcionario.setNome("Sanji");
        funcionario.setIdade(23);
        funcionario.setSalarios(new double[]{1200, 987.32, 2000});

        funcionario.imprime();
    }
}
