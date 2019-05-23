import math


def leftside(X, Y):

    if len(X) != len(Y):
        return None

    Z = ['-'] * len(X)

    for i in range(1, len(X)):
        
        h = X[i] - X[i - 1]
        Z[i] = (Y[i] - Y[i - 1]) / h

    return Z


def rightside(X, Y):

    if len(X) != len(Y):
        return None

    Z = ['-'] * len(X)

    for i in range(0, len(X) - 1):
        
        h = X[i] - X[i + 1]
        h *= -1

        Z[i] = (Y[i + 1] - Y[i]) / h

    return Z


def central(X, Y):

    if len(X) != len(Y):
        return None

    Z = ['-'] * len(X)

    for i in range(1, len(X) - 1):
        
        h = X[i] - X[i + 1]
        h *= -1
        Z[i] = (Y[i + 1] - Y[i - 1]) / (2 * h)

    return Z


def leftspace(X, Y):

    if len(X) != len(Y):
        return None

    Z = ['-'] * len(X)
    
    h = X[1] - X[0]
    Z[0] = (4*Y[1] - 3*Y[0] - Y[2]) / (2 * h)
    
    return Z


def rightspace(X, Y):

    if len(X) != len(Y):
        return None

    Z = ['-'] * len(X)
    
    h = X[-2] - X[-1]
    h *= -1
    Z[-1] = (Y[-3] + 3*Y[-1] - 4*Y[-2]) / (2 * h)
    
    return Z


def runge_r(X, Y):

    p = 1
    r = 2

    Z = ['-'] * len(Y)
    Z2 = ['-'] * len(Y)
    Z1 = rightside(X, Y)

    for i in range(len(Y) - 2):

        h = X[i] - X[i + 1]
        h *= -1

        Z2[i] = (Y[i + 2] - Y[i]) / (2 * h)
        psi = (Z1[i] - Z2[i]) / (r**p - 1)
        Z[i] = Z1[i] + psi

    return Z


def runge_l(X, Y):

    p = 1
    r = 2

    Z = ['-'] * len(Y)
    Z2 = ['-'] * len(Y)
    Z1 = leftside(X, Y)

    for i in range(2, len(Y)):

        h = X[i] - X[i - 1]

        Z2[i] = (Y[i] - Y[i - 2]) / (2 * h)
        psi = (Z1[i] - Z2[i]) / (r**p - 1)
        Z[i] = Z1[i] + psi

    return Z


def leveling_variables_r(X, Y, xi, eta):
    
    Z = ['-'] * len(X)

    xi_res = [xi(x) for x in X]
    eta_res = [eta(x) for x in xi_res]

    Z1 = rightside(xi_res, eta_res)

    for i in range(len(X) - 1):

        if X[i] != 0:
            Z[i] = -(Y[i] ** 2) / -(X[i] ** 2) * Z1[i]
    
    return Z

def leveling_variables_l(X, Y, xi, eta):
    
    Z = ['-'] * len(X)

    xi_res = [xi(x) for x in X]
    eta_res = [eta(x) for x in xi_res]

    Z1 = leftside(xi_res, eta_res)

    for i in range(1, len(X)):

        if X[i] != 0:
            Z[i] = -(Y[i] ** 2) / -(X[i] ** 2) * Z1[i]
    
    return Z
