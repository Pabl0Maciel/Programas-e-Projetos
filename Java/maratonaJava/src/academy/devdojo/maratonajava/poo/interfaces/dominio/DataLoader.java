package academy.devdojo.maratonajava.poo.interfaces.dominio;

public interface DataLoader {
    int MAX_DATA_SIZE = 10;

    void load();

    default void checkPermission(){
        System.out.println("Fazendo checagem de permissoes");
    }

    public static void retrieveMaxDataSize(){
        System.out.println(MAX_DATA_SIZE);
    }
}
