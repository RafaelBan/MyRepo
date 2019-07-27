import sys
import fprocess as fp

from math import fabs


def ftable_read(inputf):

    ftable = []

    for line in inputf:
        
        x = float(line.split()[0])
        y = float(line.split()[1])

        ftable.append([x, y])

    return ftable


def ftable_swap(ftable):

    ft_len = len(ftable)

    for i in range(ft_len):

        ftable[i][0], ftable[i][1] = ftable[i][1], ftable[i][0]


def ftable_write(outputf, ftable):

    ft_len = len(ftable)

    for i in range(ft_len):

        outputf.write('{:15g} {:15g}\n'.format(ftable[i][0], ftable[i][1]))


def ftable_xsort(ftable):

    swapFlag = True
    ft_len = len(ftable)

    i = 0
    while (i < ft_len) and (swapFlag):

        swapFlag = False

        for j in range(0, ft_len - 1 - i):

            if (ftable[j][0] > ftable[j + 1][0]):
                
                swapFlag = True
                ftable[j], ftable[j + 1] = ftable[j + 1], ftable[j]

        i += 1


def ftable_xremdups(ftable):

    ft_len = len(ftable)

    i = 0
    while (i < ft_len):

        other_x = [ftable[j][0] for j in (list(range(i)) +
                                          list(range(i + 1, ft_len)))]

        if ftable[i][0] in other_x:

            ftable.pop(i)
            ft_len -= 1

        i += 1


def main():

    if (len(sys.argv) < 3):
        return 1

    doSort = False
    doFilter = False

    argv = sys.argv
    argc = len(argv)

    for i in range(3, argc):

        if (argv[i] == 's'):
            doSort = True

        elif (argv[i] == 'r'):
            doFilter = True

    fileName1 = argv[1]
    fileName2 = argv[2]

    inputf = open(fileName1, 'r')
    ftable = ftable_read(inputf)
    inputf.close()

    ftable_swap(ftable)
    
    if (doSort):
        ftable_xsort(ftable)

    if (doFilter):
        ftable_xremdups(ftable)

    outputf = open(fileName2, 'w')
    ftable_write(outputf, ftable)
    outputf.close()


if (__name__ == '__main__'):
    main()

