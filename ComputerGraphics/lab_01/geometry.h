#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <string>

//! Точность при вычислениях с вещественными числами
const double EPSILON = 10e-7;

//! Структура точки
struct point_t
{
public:

    //! Конструктор
    point_t(double x = 0, double y = 0);

    //! Координаты
    double x;
    double y;

    //! Функция копирования точки
    point_t copy();

    //! Функция, определяющая, находится ли данная точки между двумя заданными
    bool isBetween(point_t A, point_t B);

    //! Функция конвертации точки в стандартную строку
    std::string toStr() const noexcept;

    //! Функция конвертации стандартной строки в точку
    static point_t parseStr(std::string str, bool *isOK = nullptr);

    //! Перегрузка операции проверки на равенство
    friend bool operator==(point_t const &A, point_t const &B);
};

//! Структура треугольника
class triangle_t
{
private:

    //! Вершины треугольника
    point_t _A;
    point_t _B;
    point_t _C;

public:

    //! Конструктор
    triangle_t(point_t A, point_t B, point_t C);

    //! Функция копирования треугольника
    triangle_t copy();

    //! Функции доступа чтения вершин треугольника
    point_t A();
    point_t B();
    point_t C();

    //! Функции доступа к точкам пересечения высот с основаниями
    point_t aH();
    point_t bH();
    point_t cH();

    //! Функция доступа к ортоцентру
    point_t orthocenter();

    //! Функция проверки треугольника на наличие прямого угла
    bool isRectangular();
};

//! Функция, определяющая, можно ли составить из заданных точек треугольник
bool isTriangle(point_t A, point_t B, point_t C);
//! Функция, определяющая, лежат ли три заданные точки на одной прямой
bool isOnSingleStraight(point_t A, point_t B, point_t C);

//! Функция, вычисляющая длину отрезка между двумя заданными точками
double edgeLen(point_t A, point_t B);

#endif /* GEOMETRY_H */
