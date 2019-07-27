import sys
import fprocess as fp
import random as rnd

from math import *


def main():

    argv = sys.argv

    if (len(argv) < 2):

        argv.append(input("Введите имя выходного файла: "))

    fstr = input('Введите функцию: ').strip()
    if (not fp.isMathExp(fstr)):
        return 1
    f = fp.function(fstr)

    xstart = input('Введите начальное значение x: ')
    if (not fp.isMathExp(xstart)):
        return 1
    xstart = float(eval(xstart))

    xstepl = input('Введите нижнюю границу шага: ')
    if (not fp.isMathExp(xstepl)):
        return 1
    xstepl = float(eval(xstepl))

    xsteph = input('Введите верхнюю границу шага: ')
    if (not fp.isMathExp(xsteph)):
        return 1
    xsteph = float(eval(xsteph))

    amount = int(input('Введите кол-во узлов таблицы: '))

    output = open(argv[1], 'w')

    x = xstart
    for i in range(amount):
        
        output.write('{:15g}\t{:15g}\n'.format(x, f(x)))
        x += rnd.uniform(xstepl, xsteph)

    output.close()



if (__name__ == '__main__'):
    main()

