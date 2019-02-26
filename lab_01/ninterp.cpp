#include "ninterp.hpp"

#define my_fabs(number) (((number) > 0) ? (number) : (-(number)))

size_t find_nearest(ftable_t ftable, double x)
{
	if (ftable.size() == 1)
	{
		return 0;
	}

	size_t pos;
	double delta;

	delta = my_fabs(ftable[0][0] - x);
	pos = 0;

	for (size_t i = 1, len = ftable.size(); i < len; i++)
	{
		double temp;

		temp = my_fabs(ftable[i][0] - x);

		if (temp < delta)
		{
			delta = temp;
			pos = i;
		}
	}

	return pos;
}

ftable_t ftable_subtable(ftable_t ftable, double x, size_t polExp)
{
	int begInd;
	int nodesQ;
	ftable_t subtable;

	nodesQ = polExp + 1;
	begInd = (int)find_nearest(ftable, x) - (nodesQ / 2);

	if (begInd < 0)
	{
		begInd = 0;
	}
	if (begInd > (int)ftable.size() - nodesQ)
		begInd = (int)ftable.size() - nodesQ;

	for (int i = 0; i < nodesQ; i++)
	{
		std::vector<double> temp(2);
	
		temp[0] = ftable[begInd + i][0];
		temp[1] = ftable[begInd + i][1];

		subtable.push_back(temp);
	}

	return subtable;
}

ptable_t ptable_create(ftable_t ftable)
{
	ptable_t ptable;

	for (size_t len = ftable.size(); len > 0; len--)
	{
		std::vector<double> vec_y(len, 0);
		ptable.push_back(vec_y);
	}

	for (size_t i = 0, len = ftable.size(); i < len; i++)
	{
		ptable[0][i] = ftable[i][1];
	}

	return ptable;
}

void ptable_fill(ptable_t &ptable, std::vector<double> vec_x)
{
	for (size_t i = 1, len = ptable.size(); i < len; i++)
	{
		for (size_t j = 0; j < (len - i); j++)
		{
			ptable[i][j] = (ptable[i - 1][j] - ptable[i - 1][j + 1]) / (vec_x[j] - vec_x[j + i]);
		}
	}
}

double nPolynomial(ptable_t ptable, std::vector<double> vec_x, double x)
{
	double nPol;
	double	subPolX;

	subPolX = 1;
	nPol = ptable[0][0];

	for (size_t i = 1, len = vec_x.size(); i < len; i++)
	{
		subPolX *= (x - vec_x[i - 1]);

		nPol += subPolX * ptable[i][0]; 
	}

	return nPol;
}

