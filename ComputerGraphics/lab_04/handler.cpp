#include "handler.h"

control::Handler::Handler() :
    command(hcommand_t::DO_WAITING)
{

}

control::Handler &control::Handler::access()
{
    static Handler instance;
    return  instance;
}

void control::Handler::setCommand(hcommand_t command)
{
    access().command = command;
}

void control::Handler::setCenter(double x0, double y0)
{
    access().center.x = x0;
    access().center.y = y0;
}

void control::Handler::setCircleBase(double radius)
{
    access().figure = circle_base({ radius });
}

void control::Handler::setCircleConc(double R0, double Rf, int n)
{
    access().concenter = circle_conc({ n, R0, Rf });
}

void control::Handler::setEllipseBase(double a, double b)
{
    access().figure = ellipse_base({  a, b });
}

void control::Handler::setEllipseConc(double a0, double af, double b0, int n)
{
    access().concenter = ellipse_conc({ n, a0, af, b0 });
}

point2d_t control::Handler::getCenter()
{
    return  access().center;
}

control::hcommand_t control::Handler::getCommand()
{
    return  access().command;
}

control::circle_base control::Handler::getCircleBase()
{
    return  std::get<control::circle_base>(access().figure);
}

control::circle_conc control::Handler::getCircleConc()
{
    return  std::get<control::circle_conc>(access().concenter);
}

control::ellipse_base control::Handler::getEllipseBase()
{
    return  std::get<control::ellipse_base>(access().figure);
}

control::ellipse_conc control::Handler::getEllipseConc()

{
    return  std::get<control::ellipse_conc>(access().concenter);
}
