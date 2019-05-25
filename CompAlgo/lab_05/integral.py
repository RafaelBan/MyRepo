def trapezoidal(a, b, f):

    if a > b:
        a, b = b, a

    h = (b - a) / 40
    res = 0

    while a <= b:

        l = a
        a = a + h
        r = a

        res += (f(l) + f(r)) / 2 * h

    return res
