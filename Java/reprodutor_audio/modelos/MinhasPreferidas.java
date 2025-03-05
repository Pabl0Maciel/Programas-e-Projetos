package reprodutor_audio.modelos;

public class MinhasPreferidas {
    
    public void inclui(Audio a){

        if (a.getClassificacao() >= 9){
            System.out.println(a.getTitulo() + " eh uma das minhas preferidas");
        } else{
            System.out.println(a.getTitulo() + " tambem eh umas das boas opcoes");
        }
    }
}
