#ifndef NINTERP_HPP
#define NINTERP_HPP

#include <vector>
#include <cmath>

using ftable_t = std::vector< std::vector<double> >;
using ptable_t = std::vector< std::vector<double> >;

int find_nearest(const std::vector<double> &vec, double num);

void vector_fill(std::vector<double> &vec, const double low, const double high);

void ptable_fill(ptable_t &ptable, const std::vector<double> &vec);

double nPolynomial(const ptable_t &ptable, const std::vector<double> &vec, double num);

ftable_t ftable_create(const std::vector<double> &col1, const std::vector<double> &col2);

ptable_t ptable_create(const ftable_t &ftable);

std::vector<int> get_work_idxs(const std::vector<double> &vec, double num, int quantity);

std::vector< std::vector<double> > genZ(const std::vector<double> &X, const std::vector<double> &Y, double f(double,double));

#endif

