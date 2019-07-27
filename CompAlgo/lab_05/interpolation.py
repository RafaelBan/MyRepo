def find_nearest(X, x):

    pos = 0
    delta = abs(X[0] - x)

    for i in range(1, len(X)):
        cur_delta = abs(X[i] - x)
        if cur_delta < delta:
            delta = cur_delta
            pos = i

    return pos


def subtable(X, Y, x, pol_exp):

    idx = find_nearest(X, x)
    nodesq = pol_exp + 1

    if X[idx] < x:
        idx += 1

    idx -= int(nodesq / 2)

    if idx < 0:
        idx = 0
    elif idx > len(X) - nodesq:
        idx = len(X) - nodesq

    sX, sY = [], []

    for i in range(0, nodesq):
        sX.append(X[idx + i])
        sY.append(Y[idx + i])

    return sX, sY


def ptable(X, Y):

    ptbl = [[0] * len(Y) for i in range(len(Y))]
    
    for i in range(0, len(Y)):
        ptbl[i][0] = Y[i]

    for j in range(1, len(ptbl)):
        for i in range(0, len(ptbl) - j):
            ptbl[i][j] = (ptbl[i][j - 1] - ptbl[i + 1][j - 1]) / (X[i] - X[i + j])
    
    return ptbl


def NewtonPolynom(X, ptbl, x):

    polynom = ptbl[0][0]
    subPolX = 1

    for i in range(1, len(X)):
        subPolX *= x - X[i - 1]
        polynom += subPolX * ptbl[0][i]

    return polynom


def interpolate(X, Y, pol_exp, x):

    sX, sY = subtable(X, Y, x, pol_exp)
    ptbl = ptable(sX, sY)

    return NewtonPolynom(sX, ptbl, x)
