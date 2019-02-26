#ifndef __NINTERP_HPP
#define __NINTERP_HPP

#include <vector>
#include <iostream>

using ftable_t = std::vector< std::vector<double> >;
using ptable_t = std::vector< std::vector<double> >;

size_t find_nearest(ftable_t ftable, double x);

ftable_t ftable_subtable(ftable_t ftable, double x, size_t polExp);

ptable_t ptable_create(ftable_t ftable);

void ptable_fill(ptable_t &ptable, std::vector<double> vec_x);

void ptablePrint(std::ostream &sout, const ptable_t &ptable);

void nPolPrint(std::ostream &sout, ptable_t ptable, std::vector<double> vec_x);

double nPolynomial(ptable_t ptable, std::vector<double> vec_x, double x);

#endif

