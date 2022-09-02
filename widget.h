#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    enum operation{equals, add, subtract, divide, multiply, root, power};

    double a;
    double b;

    double memory;

    bool to_clear;

    void append(QChar c);
    void operation(int operation);
    int prev_operation;
};
#endif // WIDGET_H
