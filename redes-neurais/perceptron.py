#!/usr/bin/env python3
# coding=utf-8

from neuron import Neuronio

d0 = [1, 1, 1, 1, 1,
      1, 0, 0, 0, 1,
      1, 0, 0, 0, 1,
      1, 0, 0, 0, 1,
      1, 0, 0, 0, 1,
      1, 1, 1, 1, 1]
[0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0]
[0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0]
[0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0]
[0, 1, 1, 1, 0, 
1, 1, 1, 1, 1,
1, 0, 1, 0, 1,
1, 0, 1, 0, 1,
1, 1, 1, 1, 1,
0, 1, 1, 1, 0]

d1 = [0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0]
[0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1]
[0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1]
[0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1]
[0, 1, 1, 0, 0,
0, 0, 1, 0, 0,
0, 0, 1, 0, 1,
1, 0, 1, 0, 1,
1, 0, 1, 0, 1,
0, 1, 1, 1, 0]



d2 = [1, 1, 1, 1, 0,
      1, 0, 0, 1, 0,
      0, 0, 0, 1, 0,
      0, 0, 1, 0, 0,
      0, 1, 0, 0, 0,
      1, 1, 1, 1, 1]

d3 = [0, 1, 1, 1, 1,
      0, 0, 0, 0, 1,
      0, 0, 0, 0, 0,
      0, 1, 1, 1, 1,
      0, 0, 0, 0, 1,
      0, 1, 1, 1, 1]

d4 = [0, 0, 0, 0, 0,
      1, 0, 0, 1, 0,
      1, 0, 0, 1, 0,
      1, 1, 1, 1, 0,
      0, 0, 0, 1, 0,
      0, 0, 0, 1, 0]

d5 = [0, 1, 1, 1, 1,
      0, 1, 0, 0, 0,
      0, 1, 0, 0, 0,
      0, 1, 1, 1, 1,
      0, 0, 0, 0, 1,
      0, 1, 1, 1, 1]

x1 = [0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1]

x2 = [0, 1, 1, 1, 0,
        0, 1, 0, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 0, 0,
        0, 1, 1, 1, 0]

x4 = [0, 1, 0, 0, 1,
      0, 1, 0, 0, 1,
      0, 1, 0, 0, 1,
      0, 1, 1, 1, 1,
      0, 0, 0, 0, 1,
      0, 0, 0, 0, 1]

x5 = [1, 1, 1, 1, 1,
      1, 0, 0, 0, 0,
      1, 1, 1, 1, 1,
      0, 0, 0, 0, 1,
      0, 0, 0, 0, 1,
      1, 1, 1, 1, 1]

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

aaaa = [1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1]

eeee = [1, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 0,
        0, 0, 0, 0, 0]

tttt = [1, 1, 1, 1, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0]

hhhh = [1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 0, 0, 0, 0]

cccc = [1, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 0]

nnnn = [1, 0, 0, 0, 1,
        1, 1, 0, 0, 0,
        1, 0, 1, 0, 1,
        1, 0, 0, 1, 1,
        1, 0, 0, 0, 1,
        0, 0, 0, 0, 0]

if __name__ == '__main__':
    print("Neuronio Zero")
    n0 = Neuronio()
    n0.fit([zero, one, two, three, four, five], [1, 0, 0, 0, 0, 0])
    print(n0.predict(zero), n0.predict(one), n0.predict(two), n0.predict(three),
        n0.predict(four), n0.predict(five))
    print("Neuronio Um")
    n1 = Neuronio()
    n1.fit([zero, one, two, three, four, five], [0, 1, 0, 0, 0, 0])
    print(n1.predict(zero), n1.predict(one), n1.predict(two), n1.predict(three),
        n1.predict(four), n1.predict(five))
    print("Neuronio Dois")
    n2 = Neuronio()
    n2.fit([zero, one, two, three, four, five], [0, 0, 1, 0, 0, 0])
    print(n2.predict(zero), n2.predict(one), n2.predict(two), n2.predict(three),
        n2.predict(four), n2.predict(five))
    print("Neuronio Tres")
    n3 = Neuronio()
    n3.fit([zero, one, two, three, four, five], [0, 0, 0, 1, 0, 0])
    print(n3.predict(zero), n3.predict(one), n3.predict(two), n3.predict(three),
        n3.predict(four), n3.predict(five))
    print("Neuronio Quatro")
    n4 = Neuronio()
    n4.fit([zero, one, two, three, four, five], [0, 0, 0, 0, 1, 0])
    print(n4.predict(zero), n4.predict(one), n4.predict(two), n4.predict(three),
        n4.predict(four), n4.predict(five))
    print("Neuronio Cinco")
    n5 = Neuronio()
    n5.fit([zero, one, two, three, four, five], [0, 0, 0, 0, 0, 1])
    print(n5.predict(zero), n5.predict(one), n5.predict(two), n5.predict(three),
        n5.predict(four), n5.predict(five))

    print(n0.predict(d0), n1.predict(d0), n2.predict(d0), n3.predict(d0),
        n4.predict(d0), n5.predict(d0))
    print(n0.predict(d1), n1.predict(d1), n2.predict(d1), n3.predict(d1),
        n4.predict(d1), n5.predict(d1))
    print(n0.predict(d2), n1.predict(d2), n2.predict(d2), n3.predict(d2),
        n4.predict(d2), n5.predict(d2))
    print(n0.predict(d3), n1.predict(d3), n2.predict(d3), n3.predict(d3),
        n4.predict(d3), n5.predict(d3))
    print(n0.predict(d4), n1.predict(d4), n2.predict(d4), n3.predict(d4),
        n4.predict(d4), n5.predict(d4))
    print(n0.predict(d5), n1.predict(d5), n2.predict(d5), n3.predict(d5),
        n4.predict(d5), n5.predict(d5))

    print(n0.predict(x1), n1.predict(x1), n2.predict(x1), n3.predict(x1),
        n4.predict(x1), n5.predict(x1))
    print(n0.predict(x2), n1.predict(x2), n2.predict(x2), n3.predict(x2),
        n4.predict(x2), n5.predict(x2))
    print(n0.predict(x4), n1.predict(x4), n2.predict(x4), n3.predict(x4),
        n4.predict(x4), n5.predict(x4))
    print(n0.predict(x5), n1.predict(x5), n2.predict(x5), n3.predict(x5),
        n4.predict(x5), n5.predict(x5))

    print()
    print(n0.predict(aaaa), n1.predict(aaaa), n2.predict(aaaa), n3.predict(aaaa),
        n4.predict(aaaa), n5.predict(aaaa))
    print(n0.predict(eeee), n1.predict(eeee), n2.predict(eeee), n3.predict(eeee),
        n4.predict(eeee), n5.predict(eeee))
    print(n0.predict(tttt), n1.predict(tttt), n2.predict(tttt), n3.predict(tttt),
        n4.predict(tttt), n5.predict(tttt))
    print(n0.predict(hhhh), n1.predict(hhhh), n2.predict(hhhh), n3.predict(hhhh),
        n4.predict(hhhh), n5.predict(hhhh))
    print(n0.predict(cccc), n1.predict(cccc), n2.predict(cccc), n3.predict(cccc),
        n4.predict(cccc), n5.predict(cccc))
    print(n0.predict(nnnn), n1.predict(nnnn), n2.predict(nnnn), n3.predict(nnnn),
        n4.predict(nnnn), n5.predict(nnnn))
