#include "ninterp.hpp"

void vector_fill(std::vector<double> &vec, const double low, const double high)
{
    int len = static_cast<int>(vec.size());
    double step = (high - low) / (len - 1);

    for (int i = 0; i < len; i++)
    {
        vec[i] = low + step * i;
    }
}

std::vector< std::vector<double> >
genZ(const std::vector<double> &X, const std::vector<double> &Y, double f(double,double))
{
    int rowsn = static_cast<int>(Y.size());
    int colsn = static_cast<int>(X.size());
    std::vector< std::vector<double> > Z;

    for (int i = 0; i < rowsn; i++)
    {
		std::vector<double> row;

        for (int j = 0; j < colsn; j++)
        {
            row.push_back(f(X[j], Y[i]));
        }

		Z.push_back(row);
    }

	return Z;
}

int find_nearest(const std::vector<double> &vec, double num)
{
	int pos = 0;
	double delta = fabs(vec[0] - num);

	for (int i = 0, len = int(vec.size()); i < len; i++)
	{
		double temp;

		temp = fabs(vec[i] - num);

		if (delta > temp)
		{
			delta = temp;
			pos = i;
		}
	}

	return pos;
}

std::vector<int> get_work_idxs(const std::vector<double> &vec, double num, int quantity)
{
	int idxBegin;
	int idxCenter;
	std::vector<int> idxs;

	idxCenter = find_nearest(vec, num);

	if (idxCenter < int(vec.size()) - 1 && vec[idxCenter] < num)
	{
		idxCenter++;
	}

	idxBegin = idxCenter - (quantity / 2);

	if (idxBegin > int(vec.size()) - quantity)
	{
		idxBegin = int(vec.size()) - quantity;
	}

	if (idxBegin < 0)
	{
		idxBegin = 0;
	}

	for (int i = idxBegin, len = int(vec.size()); i < len && i < (idxBegin + quantity); i++)
	{
		idxs.push_back(i);
	}

	return idxs;
}

ftable_t ftable_create(const std::vector<double> &col1, const std::vector<double> &col2)
{
	ftable_t ftable(col1.size());

	for (int i = 0, len = int(ftable.size()); i < len; i++)
	{
		ftable[i] = {col1[i], col2[i]};
	}

	return ftable;
}

ptable_t ptable_create(const ftable_t &ftable)
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

void ptable_fill(ptable_t &ptable, const std::vector<double> &vec)
{
    for (size_t i = 1, len = ptable.size(); i < len; i++)
    {
        for (size_t j = 0; j < (len - i); j++)
        {
            ptable[i][j] = (ptable[i - 1][j] - ptable[i - 1][j + 1]) / (vec[j] - vec[j + i]);
        }
    }
}

double nPolynomial(const ptable_t &ptable, const std::vector<double> &vec, double num)
{
    double nPol;
    double subPol;

    subPol = 1;
    nPol = ptable[0][0];

    for (size_t i = 1, len = vec.size(); i < len; i++)
    {
        subPol *= (num - vec[i - 1]);

        nPol += subPol * ptable[i][0];
    }

    return nPol;
}


