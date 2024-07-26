# Problema de negocio: Construir um modelo de IA capaz de classificar imagens em 10 categorias: ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 
# 'frog', 'horse', 'ship', 'truck']. Dada uma imagem de uma dessas categorias, o modelo de e ser capaz de classificar e indicar o que e a imagem

import tensorflow as tf, matplotlib.pyplot as plt, numpy as np, time
from tensorflow import keras 
from keras import datasets, layers, models
from PIL import Image

# carregamento de dados
(imagens_treino, labels_treino), (imagens_teste, labels_teste) = datasets.cifar10.load_data()

nomes_classes = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']

# Pre-Processamento e visualizacao das imagens
imagens_treino = imagens_treino / 255.0 # normaliza os valores dos pixels 
imagens_teste = imagens_teste / 255.0   # para que os dados fiquem na mesma escala

def visualiza_imagens(images, labels):
    plt.figure(figsize = (10,10))
    for i in range(25):
        plt.subplot(5, 5, i+1)
        plt.xticks([])
        plt.yticks([])
        plt.grid(False)
        plt.imshow(images[i], cmap = plt.cm.binary)
        plt.xlabel(nomes_classes[labels[i][0]])
    plt.show()

visualiza_imagens(imagens_treino, labels_treino)

# construcao do modelo
modelo = models.Sequential() # cria o objeto de sequencia de camadas

modelo.add(layers.Conv2D(32, (3, 3), activation = 'relu', input_shape = (32, 32, 3))) # add o primeiro bloco de convolucao
modelo.add(layers.MaxPooling2D((2, 2)))                                               # e max pooling (camada de entrada)

modelo.add(layers.Conv2D(64, (3, 3), activation = 'relu')) # add o segundo bloco de convolucao
modelo.add(layers.MaxPooling2D((2, 2)))                    # e max pooling (camada intermediaria)

modelo.add(layers.Conv2D(64, (3, 3), activation = 'relu')) # add o terceiro bloco de convolucao
modelo.add(layers.MaxPooling2D((2, 2)))                    # e max pooling (camada intermediaria)

modelo.add(layers.Flatten())                         # adiciona
modelo.add(layers.Dense(64, activation = 'relu'))    # camadas de 
modelo.add(layers.Dense(10, activation = 'softmax')) # classificacao

print(modelo.summary()) # sumario, mostra os parametros aprendidos

# compilacao do modelo
modelo.compile(optimizer = 'adam',
               loss = 'sparse_categorical_crossentropy',
               metrics = ['accuracy'])

# treina o modelo
start = time.time()
history = modelo.fit(imagens_treino,                                    
                     labels_treino,                                     
                     epochs = 10,
                     validation_data = (imagens_teste, labels_teste))
end = time.time()
print('Tempo de treinamento: %f segundos' % (end - start))

# avalia o modelo
erro_teste, acc_teste = modelo.evaluate(imagens_teste, labels_teste, verbose = 2)
print('\nAcuracia com Dados de Teste:', acc_teste)

# deploy
nova_imagem = Image.open('arquivos/nova_imagem.jpg') # abre a imagem
print(nova_imagem.size) # tamanho da imagem

largura = nova_imagem.width
altura = nova_imagem.height

print('A largura da imagem e', largura)
print('A altura da imagem e', altura)

nova_imagem = nova_imagem.resize((32, 32)) # redimensiona a imagem

plt.figure(figsize = (1, 1)) # 
plt.imshow(nova_imagem)      # 
plt.xticks([])               # mostra a imagem
plt.yticks([])               #
plt.show()                   #

nova_imagem_array = np.array(nova_imagem) / 255.0 # converte a imagem para array numpy e normaliza
nova_imagem_array = np.expand_dims(nova_imagem_array, axis = 0) # expande a dimensao do array para (1, 32, 32, 3)

previsoes = modelo.predict(nova_imagem_array) # previsoes
print(previsoes)

classe_prevista = np.argmax(previsoes)
nome_classe_prevista = nomes_classes[classe_prevista]

print('A nova imagem foi classificada como:', nome_classe_prevista)



