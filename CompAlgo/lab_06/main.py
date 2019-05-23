import sys
import derivative

def foo(X):

    YY = []
    for x in X:
        YY.append(-3 * x / (2 + 3*x)**2 + 1 / (2 + 3*x))

    return YY

def toStr(num):
    if (num != '-'):
        num = '{:9.5f}'.format(num)
    return num


def main():
    
    argc = len(sys.argv)
    fname = ''

    if argc <= 1:
        fname = input("Введите имя входного файла: ")
    else:
        fname = sys.argv[1]

    inputf = open(fname)
    X = []
    Y = []

    for line in inputf.readlines():

        if (str(line).strip() != ''):

            x, y = tuple(map(float, line.split()))
            X.append(x)
            Y.append(y)

    inputf.close()

    Z1l = derivative.leftside(X, Y)
    Z1r = derivative.rightside(X, Y)

    Z2l = derivative.leftspace(X, Y)
    Z2r = derivative.rightspace(X, Y)

    Z3 = derivative.central(X, Y)

    Z4l = derivative.runge_l(X, Y)
    Z4r = derivative.runge_r(X, Y)

    Z5r = derivative.leveling_variables_r(X, Y, lambda x: 1/x, lambda y: 2*y + 3)
    Z5l = derivative.leveling_variables_l(X, Y, lambda x: 1/x, lambda y: 2*y + 3)

    Z = foo(X)

    print("{:^10s}   {:^10s}   "
          "{:^23s}   {:^23s}   "
          "{:^10s}   {:^23s}   {:^23s}   "
          "{:^23s}".format("x", "y", "левая", "правая", "центр", "Рунге", "вырав.", "точное"))

    for i in range(len(X)):

        x = toStr(X[i])
        y = toStr(Y[i])

        z1l = toStr(Z1l[i])
        z2l = toStr(Z2l[i])

        z1r = toStr(Z1r[i])
        z2r = toStr(Z2r[i])

        z3 = toStr(Z3[i])

        z4l = toStr(Z4l[i])
        z4r = toStr(Z4r[i])

        z5r = toStr(Z5r[i])
        z5l = toStr(Z5l[i])

        z6 = toStr(Z[i])

        print("{:>10s} | {:>10s} | {:>10s} | "
              "{:>10s} | {:>10s} | {:>10s} | "
              "{:>10s} | {:>10s} | {:>10s} | "
              "{:>10s} | {:>10s} | {:>10s}".format(x, y, z1l, z2l, z1r, z2r, z3, z4l, z4r, z5l, z5r, z6))


if __name__ == '__main__':
    main()
