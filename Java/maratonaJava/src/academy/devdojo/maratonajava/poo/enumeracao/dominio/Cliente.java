package academy.devdojo.maratonajava.poo.enumeracao.dominio;

public class Cliente {
    private String nome;
    private TipoCliente tipoCliente;
    private TipoPagamento tipoPagamento;

    // Construtor
    public Cliente(String nome, TipoCliente tipoCliente, TipoPagamento tipoPagamento) {
        this.nome = nome;
        this.tipoCliente = tipoCliente;
        this.tipoPagamento = tipoPagamento;
    }

    // Metodos
    @Override
    public String toString() {
        return "Cliente: " + this.nome
                + " | " + "Tipo: " + this.tipoCliente.nomeRelatorio
                + " | " + "TipoInt: " + this.tipoCliente.VALOR
                + " | " + "Tipo de Pagamento: " + this.tipoPagamento;
    }

    // Getters
    public String getNome() {
        return nome;
    }

    public TipoCliente getTipoCliente() {
        return tipoCliente;
    }

    // Setters
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setTipoCliente(TipoCliente tipoCliente) {
        this.tipoCliente = tipoCliente;
    }
}
