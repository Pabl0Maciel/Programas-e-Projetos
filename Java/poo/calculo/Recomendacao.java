package poo.calculo;

public class Recomendacao {
    public void filtra(Classificavel c) {

        if (c.getClassificacao() >= 4) {
            System.out.println("Esta entre os preferidos do momento");
        } else if (c.getClassificacao() >= 2) {
            System.out.println("Muito bem avaliado no momento");
        } else {
            System.out.println("Coloque na lista para assistir depois");
        }
    }
}
