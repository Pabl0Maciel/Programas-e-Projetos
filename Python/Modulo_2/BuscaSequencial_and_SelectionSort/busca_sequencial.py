def busca_sequencial(seq, x):
    for i in range(len(seq)):
        if seq[i] == x:
            return True
    return False

#exemplo 2

class musica:
    def __init__(self, titulo, interprete, compositor, ano):
        self.titulo = titulo
        self.interprete = interprete
        self.compositor = compositor
        self.ano = ano

class buscador:
    def busca_por_titulo(self, seq, x):
        for i in range(len(seq)):
            if seq[i].titulo == x:
                return i
        return -1
    
    def vamos_buscar(self):
        playlist = [musica("ponta de areia", "milton nascimento", "milton nascimento", 1975),
                    musica("podres poderes", "caetano veloso", "caetano veloso", "1984"),
                    musica("baby", "gal costa", "caetano veloso", "1969")]
        onde_achou = self.busca_por_titulo(playlist, "baby")

        if onde_achou == -1:
            print("a musica buscada nao esta na playlist!")
        else:
            preferida = playlist[onde_achou]
            print(preferida.titulo, preferida.interprete, preferida.compositor,preferida.ano, sep=', ')

b = buscador()
print(b.vamos_buscar())