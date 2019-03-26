import sys
import matplotlib.pyplot as pyplot


EPS = 1e-7


def read_table(f):
    
    table = []

    for line in f.readlines():

        table.append(list(map(float, line.strip().split())))

    return table


def getEqSystem(table, n):

    eqsystem = [ [ 0 for j in range(n + 1 + 1) ] for i in range(n + 1) ]

    for i in range(n + 1):

        eqsystem[i][n + 1] = sum([table[k][2] * table[k][0] ** i * table[k][1] for k in range(len(table))])

        for j in range(n + 1):

            eqsystem[i][j] = sum([table[k][2] ** 2 * table[k][0] ** (i + j) for k in range(len(table))])

    return eqsystem


def gauss(eqsystem):

    n = len(eqsystem)

    for k in range(n):

        for j in range(k, n):

            if abs(eqsystem[j][k]) > EPS:

                eqsystem[k], eqsystem[j] = eqsystem[j], eqsystem[k]
                # break

        if abs(eqsystem[k][k]) < EPS:

            continue

        for i in range (k + 1, n):

            ratio = -1 * eqsystem[i][k] / eqsystem[k][k]

            for j in range(k, n + 1):

                eqsystem[i][j] += ratio * eqsystem[k][j]

    for i in range(n):
        print(('{:9.3f}\t' * (n + 1)).format(*eqsystem[i]))
    print()

    roots = [0] * n

    for i in range(n - 1, 0 - 1, -1):
        
        for j in range(n - 1, i, -1):

            eqsystem[i][n] -= roots[j] * eqsystem[i][j]

        roots[i] = (eqsystem[i][n]) / eqsystem[i][i]

    return roots


def main():

    filename = ''

    if len(sys.argv) < 2:
        filename = input('Введите имя входного файла: ')
    else:
        filename = sys.argv[1]

    f = open(filename, 'r')
    table = read_table(f)
    f.close()

    for row in table:
        print("{:9.3f}\t{:9.3f}\t{:9.3f}".format(*row))
    print()

    n = int(input('Введите n: '))
    print()
    eqsystem = getEqSystem(table, n)

    for i in range(n + 1):
        print(('{:9.3f}\t' * (n + 2)).format(*eqsystem[i]))
    print()

    coefs = gauss(eqsystem)
    print(coefs)

    x = []
    y = []

    x_cur = table[0][0]
    x_end = table[len(table) - 1][0]
    # x_step = (x_end - x_cur) / (len(table) * 2)
    x_step = 1e-5

    while (x_cur < x_end):

        y_cur = 0

        for i in range(len(coefs)):

            y_cur += coefs[i] * x_cur ** i

        x.append(x_cur)
        y.append(y_cur)

        x_cur += x_step

    pyplot.plot(x, y)

    x = []
    y = []

    for i in range(len(table)):

        x.append(table[i][0])
        y.append(table[i][1])

    pyplot.scatter(x, y, c = "red")

    pyplot.gcf().canvas.set_window_title("Набиев Фарис. ИУ7-43Б. Вычислительные алгоритмы. ЛР4")
    pyplot.title("Аппроксимация функции\nНаилучшее среднеквадратичное значение");
    pyplot.xlabel("x")
    pyplot.ylabel("y")
    pyplot.show()


if (__name__ == '__main__'):
    main()

