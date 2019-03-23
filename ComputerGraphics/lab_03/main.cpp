#include "mainwindow.h"
#include <QApplication>

#include <QFile>
#include <QFont>
#include <QFontDatabase>

int main(int argc, char *argv[])
{

    // Загрузка таблицы стилей
    QFile styleSrc(":/base/MyTheme.qss");

    QApplication a(argc, argv);

    // Загрузка шрифта
    QFontDatabase::addApplicationFont(":/base/Roboto-Regular.ttf");

    // Установка шрифта
    QFont mainFont("Roboto Regular");
    mainFont.setPointSize(10);
    a.setFont(mainFont);

    // Установка таблицы стилей
    styleSrc.open(QFile::ReadOnly);
    a.setStyleSheet(styleSrc.readAll());
    styleSrc.close();

    // Загрузка и установка иконки приложения
    a.setWindowIcon(QIcon(":/base/ApplicationIcon.png"));

    MainWindow w;
    w.show();

    return a.exec();
}
