#ifndef TRANSFERUI_H
#define TRANSFERUI_H

#include <QWidget>

#include <QString>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QSpacerItem>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

class TransferUI : public QWidget
{

    Q_OBJECT

public:
    QLabel *title;
    QLabel *dxLabel;
    QLabel *dyLabel;

    QLineEdit *dxEntry;
    QLineEdit *dyEntry;

    QPushButton *transferButton;

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
    explicit TransferUI(QWidget *parent = nullptr);
    ~TransferUI();
};

#endif // TRANSFERUI_H
