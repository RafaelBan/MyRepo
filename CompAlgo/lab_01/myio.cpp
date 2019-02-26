#include "myio.hpp"

#include <string>

using namespace std;

ftable_t ftable_read(istream &sin)
{
	ftable_t ftable;

	while (!sin.eof())
	{
		string buff1 = "nan";
		string buff2 = "nan";

		sin >> buff1 >> buff2;

		if (buff1 != "nan" && buff2 != "nan")
		{
			char *ptr;
			double x;
			double y;
			vector<double> row(2);

			x = strtod(buff1.c_str(), &ptr);

			if (buff1.c_str() == ptr)
			{
				ftable.clear();
				return ftable;
			}

			y = strtod(buff2.c_str(), &ptr);

			if (buff2.c_str() == ptr)
			{
				ftable.clear();
				return ftable;
			}

			row[0] = x;
			row[1] = y;

			ftable.push_back(row);
		}
	}

	return ftable;
}

