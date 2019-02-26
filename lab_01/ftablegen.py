import sys
import fprocess as fp
from math import *


def showRef():
    
    print('\t{:s} -\n'
          '\t\tДанный сценарий производит создание таблицы\n'
          '\t\tзначений вида \"Абсцисса-Ордината\" для\n'
          '\t\tдля заданной функции.\n'
          '\t\tА так же вычисляет значение функции\n'
          '\t\tдля специально заданного аргумента.\n'
          '\n'
          '\tЗначения по умолчанию:\n'
          '\t\tfString = x\t\t- заданная математическая функция\n'
          '\t\txArg = 0\t\t- значение аргумента для подстановки в функцию.\n'
          '\t\txStart = -1\t\t- начальное значения аргумента для таблицы.\n'
          '\t\txFinish = 1\t\t- конечное значение аргумента для таблицы.\n'
          '\t\txQuantity = 20\t\t- кол-во записей таблицы.\n'
          '\t\toutput = \'ftable.out\'\t- название выходного файла.\n'
          '\n'
          '\tЧтобы изменить тот ли иной параметр программы, передайте\n'
          '\tв аргументы командой строки конструкцию вида:\n'
          '\t--[НАЗВАНИЕ-ПАРАМЕТРА]=[ЗНАЧЕНИЕ]'.format(sys.argv[0]))

    exit(0)


def main():

    f = None
    xArg = 0
    xString = '0'
    xSStart = '-1'
    xStart = -1
    xSFinish = '1'
    xFinish = 1
    fString = 'x'
    pQuantity = 20
    step = (xFinish - xStart) / pQuantity
    output = 'ftable.out'
    EPSILON = 1e-12

    argc = len(sys.argv)
    argv = sys.argv.copy()

    for i in range(argc):
        
        arg = argv[i].lower()
        ind = 0

        if '=' in arg:
            ind = arg.index('=') + 1

        if (arg.startswith('--xarg=')):
            xString = arg[ind:].strip()
        elif (arg.startswith('--xstart=')):
            xSStart = arg[ind:].strip()
        elif (arg.startswith('--xfinish=')):
            xSFinish = arg[ind:].strip()
        elif (arg.startswith('--fstring=')):
            fString = arg[ind:].strip()
        elif (arg.startswith('--pquantity=')):
            pQuantity = int(arg[ind:])
        elif (arg.startswith('--output=')):
            output = arg[ind:].strip()
        elif (arg == '-h' or arg == '--help'):
            showRef()

    if not (fp.isMathExp(xString)) or not (fp.isMathExp(fString)):
        exit(1)

    if not (fp.isMathExp(xSStart)) or not (fp.isMathExp(xSFinish)):
        exit(1)

    if (fabs(xStart - xFinish) < EPSILON) or (xStart > xFinish):
        exit(1)

    xArg = float(eval(xString))
    xStart = float(eval(xSStart))
    xFinish = float(eval(xSFinish))
    step = (xFinish - xStart) / (pQuantity - 1)

    print ('f(x) = {:s}'.format(fString))

    print('x = ', end = '')
    if (xString != str(xArg)) and (xString != '{:g}'.format(xArg)):
        print('{:s} = '.format(xString), end = '')
    print('{:g}'.format(xArg))

    print('x0 = ', end = '')
    if (xSStart != str(xStart)) and (xSStart != '{:g}'.format(xStart)):
        print('{:s} = '.format(xSStart), end = '')
    print('{:g}'.format(xStart))

    print('xf = ', end = '')
    if (xSFinish != str(xFinish)) and (xSFinish != '{:g}'.format(xFinish)):
        print('{:s} = '.format(xSFinish), end = '')
    print('{:g}'.format(xFinish))

    print('h = {:g}'.format(step))
   
    f = fp.function(fString)

    fout = open(output, 'w')
    cx = xStart

    print()
    # while (xFinish - cx > 0):
    for i in range(pQuantity):

        cf = None

        try:
            cf = f(cx)
        except ZeroDivisionError:
            cf = float('Nan')

        fout.write('{:15g} {:15g}\n'.format(cx, cf))
        print('{:15g} {:15g}'.format(cx, cf))
        cx += step

    fout.close()
    print()

    print('f({:g}) = {:g}'.format(xArg, f(xArg)))


if (__name__ == '__main__'):
    main()

