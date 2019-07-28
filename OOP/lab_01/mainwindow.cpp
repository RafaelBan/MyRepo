#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "object.h"
#include "geometry.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loadAction, SIGNAL(triggered()), this, SLOT(loadFileAction()));
    connect(ui->saveAction, SIGNAL(triggered()), this, SLOT(saveFileAction()));

    connect(ui->transferButton, SIGNAL(clicked()), this, SLOT(transferReadAction()));
    connect(ui->scalingButton, SIGNAL(clicked()), this, SLOT(scalingReadAction()));
    connect(ui->rotationButton, SIGNAL(clicked()), this, SLOT(rotationReadAction()));

    this->resize(0, 0);
}

MainWindow::~MainWindow()
{
    Handler handler = handler_create();

    handle(handler, DO_LEAVING);

    delete ui;
}

void MainWindow::transferReadAction()
{
    int return_code;
    Handler handler = handler_create();

    return_code = entry_check_double(ui->dxEntry);
    return_code = convert_exit_input_code(return_code, __EXIT_EMPTY_DX, __EXIT_INVALID_DX);

    if (return_code == __EXIT_SUCCESS)
    {
        return_code = entry_check_double(ui->dyEntry);
        return_code = convert_exit_input_code(return_code, __EXIT_EMPTY_DY, __EXIT_INVALID_DY);
    }

    if (return_code == __EXIT_SUCCESS)
    {
        return_code = entry_check_double(ui->dzEntry);
        return_code = convert_exit_input_code(return_code, __EXIT_EMPTY_DZ, __EXIT_INVALID_DZ);
    }

    if (return_code == __EXIT_SUCCESS)
    {
        translation_base tdata = { .dx = -ui->dxEntry->text().toDouble(),
                                   .dy = +ui->dyEntry->text().toDouble(),
                                   .dz = -ui->dzEntry->text().toDouble() };

        handler.tdata = tdata;

        return_code = handle(handler, DO_TRASNLATE);

        if (return_code == __EXIT_SUCCESS)
        {
            return_code = handle(handler, DO_RENDERING);
        }
    }

    this->update(handler, return_code);
}

void MainWindow::scalingReadAction()
{
    int return_code;
    Handler handler = handler_create();

    return_code = entry_check_double(ui->kxEntry);
    return_code = convert_exit_input_code(return_code, __EXIT_EMPTY_KX, __EXIT_INVALID_KX);

    if (return_code == __EXIT_SUCCESS)
    {
        return_code = entry_check_double(ui->kyEntry);
        return_code = convert_exit_input_code(return_code, __EXIT_EMPTY_KY, __EXIT_INVALID_KY);
    }

    if (return_code == __EXIT_SUCCESS)
    {
        return_code = entry_check_double(ui->kzEntry);
        return_code = convert_exit_input_code(return_code, __EXIT_EMPTY_KZ, __EXIT_INVALID_KZ);
    }

    if (return_code == __EXIT_SUCCESS)
    {
        scaling_base sdata = { .kx = ui->kxEntry->text().toDouble(),
                               .ky = ui->kyEntry->text().toDouble(),
                               .kz = ui->kzEntry->text().toDouble() };

        handler.sdata = sdata;

        return_code = handle(handler, DO_SCALING);

        if (return_code == __EXIT_SUCCESS)
        {
            return_code = handle(handler, DO_RENDERING);
        }
    }

    this->update(handler, return_code);
}

void MainWindow::rotationReadAction()
{
    int return_code;
    Handler handler = handler_create();

    return_code = entry_check_double(ui->alphaxEntry);
    return_code = convert_exit_input_code(return_code, __EXIT_EMPTY_AX, __EXIT_INVALID_AX);

    if (return_code == __EXIT_SUCCESS)
    {
        return_code = entry_check_double(ui->alphayEntry);
        return_code = convert_exit_input_code(return_code, __EXIT_EMPTY_AY, __EXIT_INVALID_AY);
    }

    if (return_code == __EXIT_SUCCESS)
    {
        return_code = entry_check_double(ui->alphazEntry);
        return_code = convert_exit_input_code(return_code, __EXIT_EMPTY_AZ, __EXIT_INVALID_AZ);
    }

    if (return_code == __EXIT_SUCCESS)
    {
        rotation_base rdata = { .alphax = ui->alphaxEntry->text().toDouble(),
                                .alphay = ui->alphayEntry->text().toDouble(),
                                .alphaz = ui->alphazEntry->text().toDouble() };

        handler.rdata = rdata;

        return_code = handle(handler, DO_ROTATION);

        if (return_code == __EXIT_SUCCESS)
        {
            return_code = handle(handler, DO_RENDERING);
        }
    }

    this->update(handler, return_code);
}

void MainWindow::loadFileAction()
{
    int return_code = __EXIT_SUCCESS;

    Handler handler = handler_create();
    QString fileName = QFileDialog::getOpenFileName(this);

    if (fileName != "")
    {
        handler_set_filename(handler, fileName.toStdString().c_str());
        return_code = handle(handler, DO_LOADING);

        if (return_code == __EXIT_SUCCESS)
        {
            return_code = handle(handler, DO_RENDERING);
        }
    }

    this->update(handler, return_code);
}

void MainWindow::saveFileAction()
{
    int return_code = __EXIT_SUCCESS;

    Handler handler = handler_create();
    QString fileName = QFileDialog::getSaveFileName(this);

    if (fileName != "")
    {
        handler_set_filename(handler, fileName.toStdString().c_str());
        return_code = handle(handler, DO_SAVING);
    }

    this->update(handler, return_code);
}

void MainWindow::update(Handler &handler, int exit_code)
{
    if (exit_code == __EXIT_SUCCESS)
    {
        this->update_display(handler.points, handler.pointsq);
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", error_string(exit_code));
    }
}

void MainWindow::update_display(const point2d_t *points, size_t pointsq)
{
    if (points != NULL)
    {
        qDebug() << pointsq;

        ui->display->clear();

        for (size_t i = 1; i < pointsq; i += 2)
        {
            QPoint first;
            QPoint second;

            first.setX(points[i - 1].x * ui->display->scalingRatio());
            first.setY(points[i - 1].y * ui->display->scalingRatio());

            second.setX(points[i].x * ui->display->scalingRatio());
            second.setY(points[i].y * ui->display->scalingRatio());

            ui->display->drawLine(first, second);
        }

        ui->display->repaint();
    }
}
