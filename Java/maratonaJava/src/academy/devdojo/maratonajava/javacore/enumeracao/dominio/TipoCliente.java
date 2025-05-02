package academy.devdojo.maratonajava.javacore.enumeracao.dominio;

public enum TipoCliente {
    PESSOA_FISICA(1, "Pessoa Fisica"),
    PESSOA_JURIDICA(2, "Pessoa Juridica");
    public final int VALOR;
    public final String nomeRelatorio;

    // Construtor
    TipoCliente(int valor, String nomeRelatorio){
        this.VALOR = valor;
        this.nomeRelatorio = nomeRelatorio;
    }

    // Getters
    public int getVALOR() {
        return VALOR;
    }
}
