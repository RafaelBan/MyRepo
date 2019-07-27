#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include "ninterp.hpp"

using namespace std;

double f(double x, double y)
{
    return (x * x + y * y);
}

int main(int argc, char **argv)
{
    int xQ;
    int yQ;
    int xPolExp;
    int yPolExp;
    double x;
    double y;
    double xL, xH;
    double yL, yH;
    vector<double> X;
    vector<double> Y;
    vector< vector<double> > Z;
    
    cerr << "Введите кол-во узлов по оси X: ";
    cin >> xQ;
    cerr << "Введите нижнее и верхнее значения по оси X: ";
    cin >> xL >> xH;

    cerr << "Введите уол-во узлов по оси Y: ";
    cin >> yQ;
    cerr << "Введите нижнее и верхнее значения по оси Y: ";
    cin >> yL >> yH;

    X = vector<double>(xQ);
    Y = vector<double>(yQ);

    vector_fill(X, xL, xH);
    vector_fill(Y, yL, yH);
    Z = genZ(X, Y, f);

    cout << "Исходная таблица значений функции: " << '\n';
    cout << std::setw(9) << std::left << "Y/X" << "  ";

    cout << std::right;
    cout << setprecision(3);
    cout.setf(std::ios::fixed);

    for (int i = 0; i < xQ; i++)
        cout << std::setw(9) << X[i] << " ";
    cout << '\n' << '\n';

    for (int i = 0; i < yQ; i++)
    {
        for (int j = 0; j < xQ; j++)
        {
            if (j == 0)
            {
                cout << std::setw(9) << Y[i] << "  ";
            }

            cout << std::setw(9) << Z[i][j] << " ";
        }

        cout << '\n';
    }

    cout.unsetf(std::ios::fixed);
    cout << setprecision(5);
    cout << '\n';

    cerr << "Введите x: ";
    cin >> x;
    cerr << "Введите степень полинома по оси X: ";
    cin >> xPolExp;

    cerr << "Введите y: ";
    cin >> y;
    cerr << "Введите степень полинома по оси Y: ";
    cin >> yPolExp;

    vector<int> xIdxs = get_work_idxs(X, x, xPolExp + 1);
    vector<int> yIdxs = get_work_idxs(Y, y, yPolExp + 1);

    cout << "Таблица значений функции для интерполяции: " << '\n';
    cout << std::setw(9) << std::left << "Y/X" << "  ";

    cout << std::right;
    cout << setprecision(3);
    cout.setf(std::ios::fixed);

    for (int i = 0; i < xPolExp + 1; i++)
        cout << std::setw(9) << X[xIdxs[i]] << " ";
    cout << '\n' << '\n';

    for (int i = 0; i < yPolExp + 1; i++)
    {
        for (int j = 0; j < xPolExp + 1; j++)
        {
            if (j == 0)
            {
                cout << std::setw(9) << Y[yIdxs[i]] << "  ";
            }

            cout << std::setw(9) << Z[yIdxs[i]][xIdxs[j]] << " ";
        }

        cout << '\n';
    }

    cout.unsetf(std::ios::fixed);
    cout << setprecision(5);
    cout << '\n';

    vector<double> ZX(yIdxs.size());
    vector<double> col1(xIdxs.size());

    for (int i = 0, len = int(xIdxs.size()); i < len; i++)
    {
        col1[i] = X[xIdxs[i]];
    }

    for (int i = 0, len = int(yIdxs.size()); i < len; i++)
    {
        ftable_t zX_table;
        ptable_t ptable;
        vector<double> col2(xIdxs.size());

        for (int j = 0, cnt = int(xIdxs.size()); j < cnt; j++)
        {
            col2[j] = Z[yIdxs[i]][xIdxs[j]];
        }

        zX_table = ftable_create(col1, col2);
        ptable = ptable_create(zX_table);
        ptable_fill(ptable, col1);

        ZX[i] = nPolynomial(ptable, col1, x);
    }

    ptable_t ptable;
    ftable_t yzx_table;
    vector<double> vec_y(yIdxs.size());

    for (int i = 0, len = int(vec_y.size()); i < len; i++)
    {
        vec_y[i] = Y[yIdxs[i]];
    }

    yzx_table = ftable_create(vec_y, ZX);
    ptable = ptable_create(yzx_table);
    ptable_fill(ptable, vec_y);

    double P = nPolynomial(ptable, vec_y, y);

    cout << "f(" << x << ", " << y << ") = " << f(x, y) << '\n';
    cout << "P(" << x << ", " << y << ") = " << P << '\n';
    cout << "Погрешность: " << (1 - P / f(x, y)) << " (" << 100 * (1 - P / f(x, y)) << "%)" << '\n';

    return 0;  
}

