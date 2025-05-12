package academy.devdojo.maratonajava.poo.interfaces.test;

import academy.devdojo.maratonajava.poo.interfaces.dominio.DataBaseLoader;
import academy.devdojo.maratonajava.poo.interfaces.dominio.FileLoader;

public class DataLoaderTest01 {
    public static void main(String[] args) {
        DataBaseLoader dataBaseLoader = new DataBaseLoader();
        FileLoader fileLoader = new FileLoader();

        dataBaseLoader.load();
        fileLoader.load();

        dataBaseLoader.remove();
        fileLoader.remove();

        dataBaseLoader.checkPermission();
        fileLoader.checkPermission();
    }
}
