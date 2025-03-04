package condicional;

public class If_Else {
    
    public static void main(String[] args) {
        
        int anoDeLancamento = 2022;
        boolean incluidoNoPlano = false;
        double notaDoFIlme = 8.1;
        String tipoDePlano = "normal";

        if (anoDeLancamento >= 2022){
            System.out.println("Lancamento que os clientes estao curtindo");
        }
        else {
            System.out.println("Filme retro que vale a pena assistir");
        }

        if (incluidoNoPlano || tipoDePlano.equals("plus")){
            System.out.println("Filme liberado");
        }
        else {
            System.out.println("Deve pagar a locacao");
        }
    }
}
