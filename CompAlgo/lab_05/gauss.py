def gauss(eqsys):
    
    n = len(eqsys)
    
    for k in range(n):
        for i in range(k + 1, n):
            
            ratio = -(eqsys[i][k] / eqsys[k][k])

            for j in range(k, n + 1):
                eqsys[i][j] += ratio * eqsys[k][j]
    
    roots = [0] * n

    for i in range(n - 1, -1, -1):

        for j in range(n - 1, i, -1):
            eqsys[i][n] -= roots[j] * eqsys[i][j]

        roots[i] = eqsys[i][n] / eqsys[i][i]

    return roots
