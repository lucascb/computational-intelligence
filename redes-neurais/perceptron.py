#!/usr/bin/env python3
# coding=utf-8

dot_product = lambda x, y: sum([i * j for i, j in zip(x, y)])
step = lambda x: 1 if x > 0 else 0 # Funcao degrau

class Perceptron(object):
    """ Rede Neural Artificial Perceptron """

    def __init__(self, alpha, epochs):
        self.alpha = alpha       # Taxa de aprendizagem
        self.max_epochs = epochs # Qtde max de iteracoes do alg de treinamento
        self.theta = -1          # Threshoult
        self.w = []              # Vetor de pesos

    def fit(self, inputs, outputs):
        """ Treina a RNA para o conjunto de entradas e saidas """
        if len(inputs) != len(outputs):
            raise Exception("Inputs and ouputs length should be equal")
        # Insere o bias nas entradas de treinamento
        x = [i[:] for i in inputs]
        for inpt in x:
            inpt.insert(0, -self.theta)
        # Cria o vetor de pesos inicial
        self.w = [0 for i in range(len(x[0]))]
        # Inicializa as variaveis de controle
        epoch, converged = 0, False
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
