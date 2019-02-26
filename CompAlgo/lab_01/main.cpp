#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "myio.hpp"
#include "ninterp.hpp"

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		return EXIT_FAILURE;
	}

	double x;
    double res;
	size_t polExp;
	ifstream input;
    ptable_t ptable;
	ftable_t ftable;
	ftable_t subtable;
    vector<double> vec_x;

	input.open(argv[1]);

	ftable = ftable_read(input);

	input.close();

	cerr << "Введите x: ";
	cin >> x;

	cerr << "Введите степень полинома: ";
	cin >> polExp;

    subtable = ftable_subtable(ftable, x, polExp);

    for (size_t i = 0, len = subtable.size(); i < len; i++)
    {
        vec_x.push_back(subtable[i][0]);
    }

    if (x < *min_element(vec_x.begin(), vec_x.end()))
	{
		cout << "Значение заданного аргумента ниже заданного отрезка. Экстраполяция" << '\n';
	}
	else if (x > *max_element(vec_x.begin(), vec_x.end()))
	{
		cout << "Значение заданного аргумента выше заданного отрезка. Экстраполяция" << '\n';
	}

    ptable = ptable_create(subtable);
    ptable_fill(ptable, vec_x);

    nPolPrint(cout, ptable, vec_x);
    res = nPolynomial(ptable, vec_x, x);
    cout << "P" << polExp << "(" << x << ") = " << res << '\n';

    if (argc == 3)
    {
        ofstream output(argv[2], ofstream::app);
        output << res << '\n';
    }

	return EXIT_SUCCESS;
}

