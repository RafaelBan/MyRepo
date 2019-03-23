#ifndef SCALINGUI_H
#define SCALINGUI_H

#include <QWidget>

#include <QString>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QSpacerItem>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

class ScalingUI : public QWidget
{

    Q_OBJECT

public:
    QLabel *title;
    QLabel *MxLabel;
    QLabel *MyLabel;
    QLabel *kxLabel;
    QLabel *kyLabel;

    QLineEdit *MxEntry;
    QLineEdit *MyEntry;
    QLineEdit *kxEntry;
    QLineEdit *kyEntry;

    QPushButton *scalingButton;

    QVBoxLayout *layout;
    QGridLayout *entryLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *buttonLayout;

    QSpacerItem *spacing1;
    QSpacerItem *spacing2;

    void widgetsInit();
    void widgetsPose();
    void widgetsFill();
    void widgetsFree();

public:
    explicit ScalingUI(QWidget *parent = nullptr);
    ~ScalingUI();
};

#endif // SCALINGUI_H
