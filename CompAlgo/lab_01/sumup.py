import sys


def main():

    f = open(sys.argv[1])

    num1 = float(f.readline())
    num2 = float(f.readline())

    print()
    print('Итог:')
    print('Точное значение = {:g}'.format(num1))
    print('Приближенное значение = {:g}'.format(num2))
    print('Погрешность = {:g} ({:g}%)'.format((num1 - num2) / num1, 100 * (num1 - num2) / num1))


if (__name__ == '__main__'):
    main()

