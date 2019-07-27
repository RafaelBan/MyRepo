#ifndef HANDLER_H
#define HANDLER_H

#include <variant>

#include "geometry.h"

namespace control
{
    enum hcommand_t
    {
        DO_WAITING = 0,
        DO_CIRCLE,
        DO_CCONC,
        DO_ELLIPSE,
        DO_ECONC
    };

    struct circle_base
    {
        double R;
    };

    struct circle_conc
    {
        int N;
        double R0;
        double Rf;
    };

    struct ellipse_base
    {
        double a;
        double b;
    };

    struct ellipse_conc
    {
        int N;
        double a0;
        double af;
        double b0;
    };

    class Handler
    {
    public:
        static Handler &access();

        static void setCenter(double x0, double y0);
        static void setCommand(hcommand_t command);
        static void setCircleBase(double radius);
        static void setCircleConc(double R0, double Rf, int n);
        static void setEllipseBase(double a, double b);
        static void setEllipseConc(double a0, double af, double b0, int n);

        static point2d_t getCenter();
        static hcommand_t getCommand();
        static circle_base getCircleBase();
        static circle_conc getCircleConc();
        static ellipse_base getEllipseBase();
        static ellipse_conc getEllipseConc();

    private:
        Handler();
        Handler(const Handler &root) = delete;
        Handler &operator=(const Handler &) = delete;

        hcommand_t command;

        point2d_t center;

        std::variant<circle_base, ellipse_base> figure;
        std::variant<circle_conc, ellipse_conc> concenter;
    };
}

#endif // HANDLER_H
