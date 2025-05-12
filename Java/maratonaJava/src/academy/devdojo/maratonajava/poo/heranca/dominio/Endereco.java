package academy.devdojo.maratonajava.poo.heranca.dominio;

public class Endereco {
    private String rua;
    private String cep;

    // Construtor
    public Endereco(String rua, String cep) {
        this.rua = rua;
        this.cep = cep;
    }

    // Getters
    public String getRua() {
        return rua;
    }

    public String getCep() {
        return cep;
    }

    // Setters
    public void setRua(String rua) {
        this.rua = rua;
    }

    public void setCep(String cep) {
        this.cep = cep;
    }
}
