#include <QApplication>
#include <QFile>
#include <QFont>
#include <QFontDatabase>

#include "mainwindow.h"
#include "MainPresenter.h"

int main(int argc, char **argv)
{
    QFile styleSrc(":/base/MyTheme.qss");
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/base/Roboto-Regular.ttf");

    QCoreApplication::setAttribute(Qt::AA_UseStyleSheetPropagationInWidgetStyles, true);

    styleSrc.open(QFile::ReadOnly);
    a.setStyleSheet(styleSrc.readAll());
    styleSrc.close();

    QFont mainFont("Roboto Regular");
    mainFont.setPointSize(10);
    a.setFont(mainFont);

    a.setWindowIcon(QIcon(":/base/ApplicationIcon.png"));

    MainWindow w;

    MainPresenter presenter;
    presenter.addView(&w);

    w.show();

    return a.exec();
}

