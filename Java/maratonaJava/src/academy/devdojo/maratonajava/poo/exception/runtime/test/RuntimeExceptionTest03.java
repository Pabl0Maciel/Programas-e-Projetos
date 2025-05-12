package academy.devdojo.maratonajava.poo.exception.runtime.test;

public class RuntimeExceptionTest03 {
    public static void main(String[] args) {
        abreConexao();
        System.out.println("------------------");
        abreConexao2();
    }

    public static String abreConexao() {
        try{
            System.out.println("Abrindo arquivo");
            System.out.println("Escrevendo no arquivo");
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            System.out.println("Fechando arquivo");
        }
        return null;
    }

    public static String abreConexao2() {
        try{
            System.out.println("Abrindo arquivo");
            System.out.println("Escrevendo no arquivo");
            throw new RuntimeException();
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            System.out.println("Fechando arquivo");
        }
        return null;
    }
}
