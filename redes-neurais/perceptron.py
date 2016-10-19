#!/usr/bin/env python3
# coding=utf-8

""" Segundo trabalho de Inteligencia Computacional:
        Rede Neural Artificial Perceptron   """

from random import randrange

# Funcao degrau
step        = lambda x: 1 if x > 0 else 0
# Produto escalar de dois vetores
dot_product = lambda x, y: sum([i*j for i,j in zip(x, y)])

class Neuron(object):
    """ Implementa um neuronio de uma RNA """

    def __init__(self, alpha=1, epochs=100, random=False):
        self.alpha = alpha       # Taxa de aprendizagem
        self.max_epochs = epochs # Qtde max de iteracoes do alg de treinamento
        self.theta = -1          # Threshould
        self.w = []              # Vetor de pesos
        self.random_w = random   # Define se o vetor de pesos sera aleat ou nao

    def fit(self, inputs, outputs):
        """ Treina o neuronio para o conjunto de entradas e saidas """
        if len(inputs) != len(outputs):
            raise Exception("Inputs and ouputs length should be equal")
        # Insere o bias nas entradas de treinamento
        x = [i[:] for i in inputs]
        for inpt in x:
            inpt.insert(0, -self.theta)
        # Cria o vetor de pesos inicial
        if self.random_w:
            self.w = [randrange(3)-1 for i in range(len(x[0]))]
        else:
            self.w = [0 for i in range(len(x[0]))]
        # Inicializa as variaveis de controle
        converged, epoch = False, 0
        while not converged and epoch < self.max_epochs:
            errors = [0 for i in range(len(x))]
            # Para cada entrada de treinamento
            for i in range(len(x)):
                y = step(dot_product(self.w, x[i])) # y = f(W.Xi)
                errors[i] = outputs[i] - y          # Ei = Di - y
                for j in range(len(x[i])):
                    self.w[j] += (self.alpha * errors[i] * x[i][j])
            # Converge se todos os erros forem zero
            converged = not any(errors)
            epoch += 1
        print("Epocas necessarias para treinar: " + str(epoch))
        print(self.w)

    def predict(self, x):
        """ Testa o conhecimento do neuronio com base no vetor de pesos """
        return step(dot_product(self.w[1:], x))

zero = [0, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        0, 1, 1, 1, 0]

one  = [0, 0, 1, 0, 0,
        0, 1, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1]

two  = [0, 1, 1, 1, 0,
        0, 1, 0, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 0, 0,
        1, 1, 1, 1, 1]

three = [0, 1, 1, 1, 1,
         0, 0, 0, 0, 1,
         0, 1, 1, 1, 1,
         0, 0, 0, 0, 1,
         0, 0, 0, 0, 1,
         0, 1, 1, 1, 1]

four = [1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0]

five = [0, 1, 1, 1, 1,
        0, 1, 0, 0, 0,
        0, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1,
        0, 1, 1, 1, 1]

if __name__ == '__main__':
    n = Neuron(random=True)
    n.fit([zero, one], [0, 1])
    print(n.predict(zero))
    print(n.predict(one))
    print(n.predict(two))
    print(n.predict(three))
    print(n.predict(four))
    print(n.predict(five))
