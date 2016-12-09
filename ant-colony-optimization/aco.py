#!/usr/bin/env python3
# coding=utf-8

from random import uniform

ALPHA = 3       # Influencia do feromonio
BETA = 1        # Influencia da informacao heuristica
Q = 1.0         # Quantidade de feromonio excretada por uma formiga
RO = 0.2        # Taxa de evaporacao do feromonio
T_INI = 1.0     # Quantidade de feromônio inicial em uma aresta

def roulette(probs):
    acc_probs = [prob[1] for prob in probs]
    for i in range(1, len(acc_probs)):
        acc_probs[i] += acc_probs[i-1]
    n = uniform(0.0, acc_probs[len(acc_probs)-1])
    #print("a:" + str(acc_probs) + "n:" + str(n))
    for i in range(len(acc_probs)):
        if acc_probs[i] > n:
            return probs[i][0]


class Ant(object):

    def __init__(self, start_node):
        self.path = []
        self.start_node = start_node

    def walk(self, graph, pheromones):
        path = []
        current_node = self.start_node
        path.append(current_node)
        path_cost = 0
        for c in range(len(graph)-1):
            next_nodes = [i for i in range(len(graph[current_node]))
                            if i not in path and i != current_node]
            #print("next: "+str(next_nodes))
            #print("current: "+str(self.current_node))
            prob = [(n, (pheromones[current_node][n] ** ALPHA) *
                    ((1 / graph[current_node][n]) ** BETA)) for n in next_nodes]
            probs = sum([p[1] for p in prob])
            prob_norm = [(n, p / probs) for (n, p) in prob]
            #print(prob_norm, path)
            next_node = roulette(prob_norm)
            path_cost += graph[current_node][next_node]
            path.append(next_node)
            current_node = next_node
        path.append(self.start_node)
        path_cost += graph[current_node][self.start_node]
        return path, path_cost

    def has_path(self, path):
        x, y = path[0], path[1]
        paths = [(self.path[i], self.path[i+1]) for i in range(len(self.path)-1)]
        if (x, y) in paths or (y, x) in paths:
            return True
        else:
            return False


class AntColony(object):

    def __init__(self, graph, max_iter):
        self.max_iter = max_iter
        self.graph = [[column for column in line] for line in graph.map]
        self.ants = [Ant(i) for i in range(len(self.graph))]
        self.pheromones = [[T_INI for i in self.graph] for j in self.graph]

    def path_length(self, path):
        paths = [(path[i], path[i+1]) for i in range(len(path)-1)]
        paths.append((path[len(path)-1], path[0]))
        length = 0
        for x, y in paths:
            length += self.graph[x][y]
        #print(length)
        return length

    def solve(self):
        cont, best_solution, best_cost = 0, None, 0
        while cont < self.max_iter:
            solutions = [ant.walk(self.graph, self.pheromones) for ant in self.ants]
            #print(solutions)
            self.update_pheromones()
            solution, cost = min(solutions, key=lambda t: t[1])
            if best_solution is None or cost < best_cost:
                best_solution, best_cost = solution, cost
                cont = -1
            cont += 1
        return best_solution, best_cost

    def update_pheromones(self):
        for i in range(len(self.graph)):
            for j in range(len(self.graph)):
                if i != j:
                    deposit = 0
                    for ant in self.ants:
                        if ant.has_path((i, j)):
                            deposit += (Q / self.path_length(ant.path))
                    self.pheromones[i][j] = ((1 - RO) * self.pheromones[i][j]) + deposit
        #print(self.pheromones)
