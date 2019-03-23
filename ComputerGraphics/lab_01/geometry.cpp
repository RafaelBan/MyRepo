#include "geometry.h"

#include <sstream>
#include <cstdlib>
#include <cmath>

// Проверка двух вещественных чисел на равенство
bool isEqual(double num1, double num2)
{
    return (fabs(num1 - num2) < EPSILON);
}

point_t::point_t(double x, double y)
{
    this->x = x;
    this->y = y;
}

point_t point_t::copy()
{
    return point_t(this->x, this->y);
}

bool operator==(point_t const &A, point_t const &B)
{
    return (fabs(A.x - B.x) < EPSILON) && (fabs(A.y - B.y) < EPSILON);
}

bool point_t::isBetween(point_t A, point_t B)
{
    if (!isOnSingleStraight(A, B, *this))
    {
        return false;
    }

    return (fmin(A.x, B.x) < this->x < fmax(A.x, B.x)) && (fmin(A.y, B.y) < this->x < fmax(A.y, B.y));
}

std::string point_t::toStr() const noexcept
{
    std::string strX;
    std::string strY;
    std::stringstream ss;

    ss << this->x;
    ss >> strX;

    ss.clear();

    ss << this->y;
    ss >> strY >> strY;

    return "(" + strX + ", " + strY + ")";
}

point_t point_t::parseStr(std::string str, bool *isOK)
{
    int commaCounter;
    int firstCommaInd;
    size_t stod_ind;
    point_t point;
    std::string strX;
    std::string strY;

    if (isOK != nullptr)
    {
        *isOK = false;
    }

    if (!(str[0] == '(' && str[str.length() - 1] == ')'))
    {
        return point;
    }

    str = str.substr(1, str.length() - 2);
    commaCounter = 0;
    firstCommaInd = -1;

    for (size_t i = 0, len = str.length(); i < len; i++)
    {
        if (str[i] == ',')
        {
            if (firstCommaInd == -1)
            {
                firstCommaInd = static_cast<int>(i);
            }

            commaCounter++;
        }
    }

    if (commaCounter != 1)
    {
        return point;
    }

    double tempX;
    double tempY;
    size_t pos = static_cast<size_t>(firstCommaInd);

    strX = str.substr(0, pos);
    strY = str.substr(pos + 1, str.length() - (pos + 1));

    tempX = std::stod(strX.c_str(), &stod_ind);

    if (stod_ind != strX.size())
    {
        return point;
    }

    tempY = std::stod(strY.c_str(), &stod_ind);

    if (stod_ind != strY.size())
    {
        return point;
    }

    if (isOK != nullptr)
    {
        *isOK = true;
    }

    point.x = tempX;
    point.y = tempY;

    return point;
}

triangle_t::triangle_t(point_t A, point_t B, point_t C)
{
    this->_A = A;
    this->_B = B;
    this->_C = C;
}

triangle_t triangle_t::copy()
{
    return triangle_t(this->A().copy(), this->B().copy(), this->C().copy());
}

point_t triangle_t::A()
{
    return this->_A;
}

point_t triangle_t::B()
{
    return this->_B;
}

point_t triangle_t::C()
{
    return this->_C;
}

point_t triangle_t::orthocenter()
{
    double k1;
    double k2;
    double xo;
    double yo;
    point_t A = this->A();
    point_t B = this->B();
    point_t C = this->C();

    if (this->isRectangular())
    {
        double AB = edgeLen(this->A(), this->B());
        double AC = edgeLen(this->A(), this->C());
        double BC = edgeLen(this->B(), this->C());
        double maxSide = fmax(fmax(AB, AC), fmax(AC, BC));

        if (isEqual(maxSide, AB))
        {
            return point_t(C.x, C.y);
        }
        if (isEqual(maxSide, AC))
        {
            return point_t(B.x, B.y);
        }
        if (isEqual(maxSide, BC))
        {
            return point_t(A.x, A.y);
        }
    }

    if (isEqual(C.x, B.x))
    {
        std::swap(B, A);
    }
    else if (isEqual(B.x, A.x))
    {
        std::swap(B, C);
    }

    else if (isEqual(B.y, A.y))
    {
        std::swap(B, C);
    }
    else if (isEqual(C.y, B.y))
    {
        std::swap(B, A);
    }

    k1 = (B.y - A.y) / (B.x - A.x);
    k2 = (C.y - B.y) / (C.x - B.x);

    xo = (k1 * k2 * (C.y - A.y) + k2 * C.x - k1 * A.x) / (k2 - k1);
    yo = -1 / k2 * (xo - A.x) + A.y;

    return point_t(xo, yo);
}

bool isOnSingleStraight(point_t A, point_t B, point_t C)
{
    return (fabs((C.x - A.x) * (B.y - A.y) - (C.y - A.y) * (B.x - A.x)) < EPSILON);
}

bool isTriangle(point_t A, point_t B, point_t C)
{
    double AB;
    double AC;
    double BC;

    AB = edgeLen(A, B);
    AC = edgeLen(A, C);
    BC = edgeLen(B, C);

    if (AB + AC < BC || isEqual(AB + AC, BC))
        return false;
    if (AB + BC < AC || isEqual(AB + BC, AC))
        return false;
    if (AC + BC < AB || isEqual(AC + BC, AB))
        return false;

    return true;
}

double edgeLen(point_t A, point_t B)
{
    return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
}

bool triangle_t::isRectangular()
{
    double AB = edgeLen(this->A(), this->B());
    double AC = edgeLen(this->A(), this->C());
    double BC = edgeLen(this->B(), this->C());

    if (isEqual(AB * AB, AC * AC + BC * BC))
    {
        return true;
    }
    if (isEqual(AC * AC, AB * AB + BC * BC))
    {
        return true;
    }
    if (isEqual(BC * BC, AC * AC + AB * AB))
    {
        return true;
    }

    return false;
}

point_t triangle_t::aH()
{
    double k;
    double xh;
    double yh;
    point_t A = this->A();
    point_t B = this->B();
    point_t C = this->C();

    if (isEqual(B.x, C.x))
    {
        if (isEqual(A.y, B.y))
        {
            return B.copy();
        }
        if (isEqual(A.y, C.y))
        {
            return C.copy();
        }

        return point_t(B.x, A.y);
    }

    if (isEqual(B.y, C.y))
    {

        if (isEqual(A.x, B.x))
        {
            return B.copy();
        }
        if (isEqual(A.x, C.x))
        {
            return C.copy();
        }

        return point_t(A.x, C.y);
    }

    k = (C.y - B.y) / (C.x - B.x);

    xh = k * (A.y - B.y + 1/k * A.x + k * B.x) / (k * k + 1);
    yh = k * xh - k * B.x + B.y;

    return point_t(xh, yh);
}

point_t triangle_t::bH()
{
    return triangle_t(this->B(), this->C(), this->A()).aH();
}

point_t triangle_t::cH()
{
    return triangle_t(this->C(), this->A(), this->B()).aH();
}
