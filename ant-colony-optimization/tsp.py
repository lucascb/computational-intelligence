#!/usr/bin/env python3
# coding=utf-8

from aco import AntColony

def euclidean_distance(p1, p2):
    return ((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2) ** 0.5


class Graph(object):

    def __init__(self):
        self.map = []

    def load_from_matrix(self, filename):
        with open(filename, "r") as f:
            i = 0
            for line in f:
                if i > 0:
                    self.map.append(list(map(int, line.split())))
                i += 1

    def load_from_table(self, filename):
        pos = {}
        with open(filename, "r") as f:
            i = 0
            for line in f:
                if i == 0:
                    n = int(line)
                else:
                    x, y = line.split()
                    pos[i-1] = (float(x), float(y))
                i += 1
        self.map = [[0 for col in range(n)] for lin in range(n)]
        for i in range(n):
            for j in range(n):
                if i != j:
                    self.map[i][j] = euclidean_distance(pos[i], pos[j])
        #print(self.map)

if __name__ == '__main__':
    g = Graph()
    #g.load_from_matrix("mapa1")
    g.load_from_table("mapa3")

    media_cost, melhor_path, melhor_cost, conv = 0, None, 0, 0
    for i in range(10):
        c = AntColony(g, 50)
        sol, cost = c.solve()
        media_cost += cost
        if melhor_path is None or cost < melhor_cost:
            melhor_path, melhor_cost = sol, cost
        #if cost == 2011:
        #    conv += 1
    print("Media custo = " + str(media_cost / 10))
    print("Melhor caminho = " + str(melhor_path))
    print("Melhor custo = " + str(melhor_cost))
    #print("Convergencia = " + str(conv / 50))

    #g2 = Graph()
    #g2.load_from_table("mapa3")
    #c = AntColony(g2, 50)
    #print(c.solve())
