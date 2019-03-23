#ifndef ROTATIONUI_H
#define ROTATIONUI_H

#include <QWidget>

#include <QString>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

class RotationUI : public QWidget
{

    Q_OBJECT

public:
    QLabel *title;
    QLabel *TxLabel;
    QLabel *TyLabel;
    QLabel *ThetaLabel;

    QLineEdit *TxEntry;
    QLineEdit *TyEntry;
    QLineEdit *ThetaEntry;

    QPushButton *rotationButton;

    QVBoxLayout *layout;
    QGridLayout *entryLayout;
    QHBoxLayout *ThetaLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *buttonLayout;

    QSpacerItem *spacing1;
    QSpacerItem *spacing2;

    void widgetsInit();
    void widgetsPose();
    void widgetsFill();
    void widgetsFree();

public:
    explicit RotationUI(QWidget *parent = nullptr);
    ~RotationUI();
};

#endif // ROTATIONUI_H
