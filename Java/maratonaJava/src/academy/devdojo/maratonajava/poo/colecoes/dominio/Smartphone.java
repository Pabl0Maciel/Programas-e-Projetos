package academy.devdojo.maratonajava.poo.colecoes.dominio;

public class Smartphone {
    private String serialNumber;
    private String marca;

    // Construtor
    public Smartphone(String serialNumber, String marca) {
        this.serialNumber = serialNumber;
        this.marca = marca;
    }

    // Metodos
    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (this == obj) return true;
        if (this.getClass() != obj.getClass()) return false;

        Smartphone smartphone = (Smartphone) obj;
        return serialNumber != null && serialNumber.equals(smartphone.serialNumber);
    }

    @Override
    public int hashCode() {
        return serialNumber == null ? 0 : this.serialNumber.hashCode();
    }

    @Override
    public String toString() {
        return "Smartphone{" +
                "serialNumber='" + serialNumber + '\'' +
                ", marca='" + marca + '\'' +
                '}';
    }

    // Getters
    public String getSerialNumber() {
        return serialNumber;
    }

    public String getMarca() {
        return marca;
    }

    // Setters
    public void setSerialNumber(String serialNumber) {
        this.serialNumber = serialNumber;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }
}
