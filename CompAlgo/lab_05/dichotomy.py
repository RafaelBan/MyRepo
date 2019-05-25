def dichotomy(a, b, f, EPS):

    c = (a + b) / 2

    fa = f(a)
    fb = f(b)
    fc = f(c)

    if (fa * fb > 0):
        print('на отрезке [%g, %g] нет корня'%(a, b))
        return None

    while abs(b - a) > EPS:

        if fa * fc < 0:
            b = c
        else:
            a = c
            fa = f(a)

        c = (a + b) / 2
        fc = f(c)

    return c
