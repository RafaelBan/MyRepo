#include "mainwindow.h"
#include <QApplication>

#include <QFile>
#include <QFont>
#include <QFontDatabase>
#include <QDesktopWidget>
#include <QRect>

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    // Загрузка таблицы стилей
    QFile styleSrc(":/base/MyTheme.qss");

    QApplication a(argc, argv);

    // Загрузка шрифта
    QFontDatabase::addApplicationFont(":/base/Roboto-Regular.ttf");

    // Установка шрифта
    QFont mainFont("Roboto Regular");
    mainFont.setPointSize(9);
    a.setFont(mainFont);

    // Установка таблицы стилей
    styleSrc.open(QFile::ReadOnly);
    a.setStyleSheet(styleSrc.readAll());
    styleSrc.close();

    // Загрузка и установка иконки приложения
    a.setWindowIcon(QIcon(":/base/ApplicationIcon.png"));

    MainWindow w;

    int scrWidth = a.desktop()->screenGeometry(&w).size().width();
    int scrHeight = int(a.desktop()->screenGeometry(&w).size().height() * .9);

    w.resize(0, 0);
    w.show();
    w.move(scrWidth / 2 - w.width() / 2, scrHeight / 2 - w.height() / 2);

    return a.exec();
}
