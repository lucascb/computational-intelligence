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
    """ Implementa um neuronio de uma RNA Perceptron """

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
        #for xi in x:
        #    xi.insert(0, -self.theta)
        input_size = len(x[0])
        # Cria o vetor de pesos inicial
        if self.random_w:
            self.w = [randrange(-1, 2) for i in range(input_size)]
        else:
            self.w = [0 for i in range(input_size)]
        # Inicializa as variaveis de controle
        converged, epoch = False, 0
        while not converged and epoch < self.max_epochs:
            errors = [0 for i in range(len(inputs))]
            # Para cada entrada de treinamento
            for i in range(len(inputs)):
                y = step(dot_product(self.w, x[i])) # y = f(W.Xi)
                errors[i] = outputs[i] - y          # Ei = Di - y
                for j in range(len(x[i])):
                    self.w[j] += (self.alpha * errors[i] * x[i][j])
            # Converge se todos os erros forem zero
            #print(errors)
            converged = not any(errors)
            epoch += 1
        print("Epocas necessarias para treinar: " + str(epoch))
        print("Vetor de pesos: " + str(self.w))

    def predict(self, x):
        """ Testa o conhecimento do neuronio com base no vetor de pesos """
        return step(dot_product(self.w, x))
