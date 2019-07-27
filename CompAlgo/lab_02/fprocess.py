from math import *

EPS = 10e-12

math_funcs = [
        'ceil',
        'fabs',
        'factorial',
        'floor',
        'fsum',
        'trunc',
        'exp',
        'expm1',
        'log',
        'log1p',
        'log10',
        'log2',
        'pow',
        'sqrt',
        'acos',
        'asin',
        'atan',
        'cos',
        'sin',
        'tan',
        'degrees',
        'radians',
        'cosh',
        'sinh',
        'tanh',
        'acosh',
        'asinh',
        'atanh',
        'gamma',
        'lgamma'
        ]
math_consts = ['pi', 'e']
math_arg = 'x'
math_ops = ['+', '-', '*', '/', '%', '**', '//']
math_seps = ['(', ')']


def convert(value, value_type):

    try:
        return value_type(value)

    except:
        return None


def isMathExp(string, ignore = math_seps + math_ops, check = math_funcs +
              math_consts + [math_arg]):

    for element in ignore:
        string = string.replace(element, ' ')

    words = [word for word in string.split(' ') if word != '']

    if len(words) == 0:
        return False

    for i in range(len(words)):
        if not((words[i] in check) or (convert(words[i], float) != None)):
            if ('e' in words[i]) and (i + 1 < len(words)):
                if convert(words[i] + words[i + 1], float) == None:
                    return False
            else:            
                return False

    return True


def function(string):

    try:
        if (isMathExp(string)):
            def f(x):
                return float(eval(string))
            return f
        return None

    except Exception:
        return None


def main():

    f = function(input())

    if (f != None):
        print(f(float(input())))


if (__name__ == '__main__'):
    main()

