#include <iostream>
#include <utility>

#include "RBLSet"


int main()
{
    rbl::Set<int> set = {4, 5, 4, 4, 2, 7, 1, -6, 8};
    rbl::Set< std::pair<int, double> > map;

    map << std::pair<int, double>({1, 2});
    map << std::pair<int, double>({5, 7});
    map << std::pair<int, double>({4, 8});

    for (auto it = map.begin(), end = map.end(); it != end; it++)
    {
        std::cout << "(" << it->first << ", " << it->second << ")" << " ";
    }
    std::cout << '\n';

    std::cout << set << '\n';
    set << 24 << 2 << 57;
    set -= 4;
    std::cout << set << '\n';

    for (auto rit = set.rbegin(); rit != set.crend(); rit++)
    {
        std::cout << *rit << " ";
    }
    std::cout << '\n';

    if (set)
    {
        std::cout << "set size = " << set.size() << '\n';
    }

    rbl::Set<int> s1 = {1, 2, 3, 4};
    rbl::Set<int> s2 = {3, 4, 5, 6};

    std::cout << s1 << " + " << s2 << " = " << (s1 + s2) << '\n';
    std::cout << s1 << " * " << s2 << " = " << (s1 * s2) << '\n';
    std::cout << s1 << " - " << s2 << " = " << (s1 - s2) << '\n';
    std::cout << s1 << " ^ " << s2 << " = " << (s2 ^ s1) << '\n';

    s1 += s2;
    std::cout << s1 << '\n';
    std::cout << s2 << '\n';

    s1.swap(s2);
    s2.swap(s1);
    s2.swap(s1);
    std::cout << s1 << '\n';
    std::cout << s2 << '\n';

    try
    {
        s1 >> s2.end();
    }
    catch (rbl::UnknownException e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}
