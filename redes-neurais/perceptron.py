#!/usr/bin/env python3
# coding=utf-8

from neuron import Neuron

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
    print("Neuronio Zero")
    n0 = Neuron(random=True)
    n0.fit([zero, one, two, three, four, five], [1, 0, 0, 0, 0, 0])
    print(n0.predict(zero), n0.predict(one), n0.predict(two), n0.predict(three),
        n0.predict(four), n0.predict(five))
    print("Neuronio Um")
    n1 = Neuron(random=True)
    n1.fit([zero, one, two, three, four, five], [0, 1, 0, 0, 0, 0])
    print(n1.predict(zero), n1.predict(one), n1.predict(two), n1.predict(three),
        n1.predict(four), n1.predict(five))
    print("Neuronio Dois")
    n2 = Neuron(random=True)
    n2.fit([zero, one, two, three, four, five], [0, 0, 1, 0, 0, 0])
    print(n2.predict(zero), n2.predict(one), n2.predict(two), n2.predict(three),
        n2.predict(four), n2.predict(five))
    print("Neuronio Tres")
    n3 = Neuron(random=True)
    n3.fit([zero, one, two, three, four, five], [0, 0, 0, 1, 0, 0])
    print(n3.predict(zero), n3.predict(one), n3.predict(two), n3.predict(three),
        n3.predict(four), n3.predict(five))
    print("Neuronio Quatro")
    n4 = Neuron(random=True)
    n4.fit([zero, one, two, three, four, five], [0, 0, 0, 0, 1, 0])
    print(n4.predict(zero), n4.predict(one), n4.predict(two), n4.predict(three),
        n4.predict(four), n4.predict(five))
    print("Neuronio Cinco")
    n5 = Neuron(random=True)
    n5.fit([zero, one, two, three, four, five], [0, 0, 0, 0, 0, 1])
    print(n5.predict(zero), n5.predict(one), n5.predict(two), n5.predict(three),
        n5.predict(four), n5.predict(five))
