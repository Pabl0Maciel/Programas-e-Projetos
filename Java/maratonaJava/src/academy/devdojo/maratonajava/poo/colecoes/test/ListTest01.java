package academy.devdojo.maratonajava.poo.colecoes.test;

import java.util.ArrayList;
import java.util.List;

public class ListTest01 {
    public static void main(String[] args) {
        List<String> nomes = new ArrayList<>();
        List<String> nomes2 = new ArrayList<>();

        nomes.add("William");
        nomes.add("DevDojo Academy");
        nomes2.add("Suane");
        nomes2.add("Academy");

        for (Object nome : nomes){
            System.out.println(nome);
        }

        nomes.addAll(nomes2);
        System.out.println("-----------------");

        for (int i = 0; i < nomes.size(); i++){
            System.out.println(nomes.get(i));
        }
    }
}
