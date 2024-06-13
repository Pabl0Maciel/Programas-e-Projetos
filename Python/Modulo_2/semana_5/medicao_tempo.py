import random, time

class Ordenador:
    def SelectionSort(self, lista):

        fim = len(lista)

        for i in range(fim-1):
            pos_menor = i

            for j in range(i+1, fim):
                if lista[j] < lista[pos_menor]:
                    pos_menor = j
            
            lista[i], lista[pos_menor] = lista[pos_menor], lista[i]
        return lista
    
    def BubbleSort(self, lista):
        fim = len(lista)

        for i in range(fim-1, 0, -1):
            for j in range(i):
                if lista[j] > lista[j+1]:
                    lista[j], lista[j+1] = lista[j+1], lista[j]

class MedeTempo:
    def lista_aleatoria(self, n):
        lista = []
        for i in range(n):
            lista.append(random.randint(0,1000))
        return lista
    
    def compara_tempos(self,n):
        lista1 = self.lista_aleatoria(n)
        lista2 = lista1[:]

        start = time.time()
        Ordenador().BubbleSort(lista1)
        end = time.time()

        print("Bubble demorou:", end - start)

        start = time.time()
        Ordenador().SelectionSort(lista2)
        end = time.time()

        print("Selection demorou:", end - start)

def main():
    print(MedeTempo().compara_tempos(1000))
print(main())
        

    
    
