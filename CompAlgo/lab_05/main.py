import sys

import math
import dichotomy as dt 
import gauss as gs 
import integral as ig 
import interpolation as ip 


EPSILON = 10e-4

Pn = 0.5
Tn = 300
T0 = 12000
Tw = 6000
m = 12

F_const_part = 7243 * (Pn / Tn)

Z = [0, 1, 2, 3, 4, 5]
E = [12.13, 20.98, 31.00, 45.00]

Td = [  2000,   4000,   6000,   8000,  10000,  12000,  14000,  16000,  18000,  20000,  22000,  24000,  26000]
Qd = [
     [1.0000, 1.0000, 1.0000, 1.0001, 1.0025, 1.0198, 1.0895, 1.2827, 1.6973, 2.4616, 3.3652, 5.3749, 7.6838],
     [4.0000, 4.0000, 4.1598, 4.3006, 4.4392, 4.5661, 4.6817, 4.7923, 4.9099, 5.0511, 5.2354, 5.4841, 5.8181],
     [5.5000, 5.5000, 5.5116, 5.9790, 6.4749, 6.9590, 7.4145, 7.8370, 8.2289, 8.5970, 8.9509, 9.3018, 9.6621],
     [11.000, 11.000, 11.000, 11.000, 11.000, 11.000, 11.000, 11.000, 11.000, 11.000, 11.000, 11.000, 11.000],
     [15.000, 15.000, 15.000, 15.000, 15.000, 15.000, 15.000, 15.000, 15.000, 15.000, 15.000, 15.000, 15.000]
]


def update_consts():
    global F_const_part
    F_const_part = 7243 * (Pn / Tn)


def F(p):
    return F_const_part - 2 * ig.trapezoidal(0, 1, lambda z: (Nt(T(z), p) * z))


def T(z):
    return T0 + (Tw - T0) * z**m


def Gamma(gamma, t, X):

    res = math.exp(X[0]) / (1 + gamma/2)

    for i in range (2, 6):
        res += math.exp(X[i]) * Z[i]**2 / (1 + Z[i]**2 * gamma/2)

    res *= 5.87 * 10**10 * 1/t**3
    res = gamma**2 - res

    return res


def deltaE(t, gamma):
    return \
    [8.61 * 10**-5 * t * math.log( (1 + Z[i + 1]**2 * gamma/2) * (1 + gamma/2) / (1 + Z[i]**2 * gamma/2)) \
     for i in range(len(Z) - 1)]


def K(t, gamma):

    dE = deltaE(t, gamma)
    Q = [ip.interpolate(Td, Qd[i], 4, t) for i in range(len(Qd))]

    return \
    [2 * 2.415 * 10**-3 * (Q[i+1] / Q[i]) * t**(3/2) * math.exp(-(E[i] - dE[i]) * 11603 / t) for i in range(len(E))]


def Nt(t, p):

    X = [-1, 3, -1, -10, -20, -35]
    dX = [0] * len(X)
    dx_x = 1

    while dx_x >= EPSILON:

        for i in range(len(X)):
            X[i] += dX[i]

        gamma = dt.dichotomy(0, 3, lambda g: Gamma(g, t, X), EPSILON)
        k = K(t, gamma)
        alpha = 0.285 * 10**-11 * (gamma * t)**3

        expV = math.exp(X[0])
        expX1 = math.exp(X[1])
        expX2 = math.exp(X[2])
        expX3 = math.exp(X[3])
        expX4 = math.exp(X[4])
        expX5 = math.exp(X[5])

        lnK0 = math.log(k[0])
        lnK1 = math.log(k[1])
        lnK2 = math.log(k[2])
        lnK3 = math.log(k[3])

        z_right = Z[1]*expX2 + Z[2]*expX3 + Z[3]*expX4 + Z[4]*expX5 - expV
        a_right = expV + expX1 + expX2 + expX3 + expX4 + expX5 - alpha - p*7243/t;

        eqsystem = [
            [      1,           -1,            1,            0,            0,            0,  lnK0 + X[1] - X[2] - X[0]],
            [      1,            0,           -1,            1,            0,            0,  lnK1 + X[2] - X[3] - X[0]],
            [      1,            0,            0,           -1,            1,            0,  lnK2 + X[3] - X[4] - X[0]],
            [      1,            0,            0,            0,           -1,            1,  lnK3 + X[4] - X[5] - X[0]],
            [   expV,  -Z[0]*expX1,  -Z[1]*expX2,  -Z[2]*expX3,  -Z[3]*expX4,  -Z[4]*expX5,                    z_right],
            [  -expV,       -expX1,       -expX2,       -expX3,       -expX4,       -expX5,                    a_right]
        ]
        
        dX = gs.gauss(eqsystem)
        dx_x = max([ (dX[i] / X[i]) for i in range(len(X)) ])
    
    return sum([math.exp(x) for x in X])
    

def input_data():

    global Pn
    global Tn
    global T0
    global Tw
    global m

    Pn = float(input('Введите Pn: '))
    Tn = float(input('Введите Tn: '))
    T0 = float(input('Введите T0: '))
    Tw = float(input('Введите Tw: '))
    m = float(input('Введите m: '))
    print()

    update_consts()


def print_data():
    print('Pn = %g\n'
          'Tn = %g\n'
          'T0 = %g\n'
          'Tw = %g\n'
          'm = %g\n'
          ''%(Pn, Tn, T0, Tw, m))


def main():
    
    input_is_enabled = False

    for i in range(1, len(sys.argv)):
        if sys.argv[i] == '--input':
            input_is_enabled = True

    if input_is_enabled:
        input_data()
    else:
        print_data()

    p = dt.dichotomy(3, 25, F, EPSILON)
    print("P = %g"%(p))


if __name__ == '__main__':
    main()
