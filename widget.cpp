#include "widget.h"
#include "./ui_widget.h"

#include <QPushButton>
#include <QLineEdit>
#include <cctype>
#include <cmath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , a{}, b{}, to_clear{false}
    , prev_operation{}
    , memory{}
{
    ui->setupUi(this);

    connect(ui->button_0, &QPushButton::clicked, this, [this](){ append('0'); });
    connect(ui->button_1, &QPushButton::clicked, this, [this](){ append('1'); });
    connect(ui->button_2, &QPushButton::clicked, this, [this](){ append('2'); });
    connect(ui->button_3, &QPushButton::clicked, this, [this](){ append('3'); });
    connect(ui->button_4, &QPushButton::clicked, this, [this](){ append('4'); });
    connect(ui->button_5, &QPushButton::clicked, this, [this](){ append('5'); });
    connect(ui->button_6, &QPushButton::clicked, this, [this](){ append('6'); });
    connect(ui->button_7, &QPushButton::clicked, this, [this](){ append('7'); });
    connect(ui->button_8, &QPushButton::clicked, this, [this](){ append('8'); });
    connect(ui->button_9, &QPushButton::clicked, this, [this](){ append('9'); });

    connect(ui->comma_button, &QPushButton::clicked, this, [this](){ // comma
        QString text{ui->output_line_edit->text()};
        if(ui->output_line_edit->text().isEmpty())
            text = "0";
        text += '.';
        ui->output_line_edit->setText(text);
        ui->comma_button->setEnabled(false);
    });

    connect(ui->backspace_button, &QPushButton::clicked, this, [this](){ // backspace
        QString text{ui->output_line_edit->text()};
        if(text.back() == '.')
            ui->comma_button->setDisabled(false);

        text.chop(1);
        ui->output_line_edit->setText(text);
    });

    connect(ui->plus_button, &QPushButton::clicked, this, [this](){ operation(operation::add); }); // +
    connect(ui->minus_button, &QPushButton::clicked, this, [this](){ operation(operation::subtract); }); // -
    connect(ui->multiply_button, &QPushButton::clicked, this, [this](){ operation(operation::multiply); }); // *
    connect(ui->divide_button, &QPushButton::clicked, this, [this](){ operation(operation::divide); }); // /
    connect(ui->equals_buttons, &QPushButton::clicked, this, [this](){ operation(operation::equals); }); // =
    connect(ui->power_button, &QPushButton::clicked, this, [this](){ operation(operation::power); }); // power
    connect(ui->root_button, &QPushButton::clicked, this, [this](){ operation(operation::root); }); // root

    connect(ui->sign_button, &QPushButton::clicked, this, [this](){
        QString text{ui->output_line_edit->text()};
        if(text.front() == '-')
            text.erase(text.cbegin(), text.cbegin() + 1);
        else
            text.push_front("-");
        ui->output_line_edit->setText(text);
    });

    connect(ui->invert_button, &QPushButton::clicked, this, [this](){
        QString text{ui->output_line_edit->text()};
        QTextStream validator{&text};
        validator >> a;
        a = 1 / a;
        text.setNum(a);
        ui->output_line_edit->setText(text);
        to_clear = true;
    });

    connect(ui->clear_all_button, &QPushButton::clicked, this, [this](){
        ui->comma_button->setDisabled(false);
        ui->output_line_edit->setText("");
        a = 0;
        b = 0;
    });



    connect(ui->memory_button, &QPushButton::clicked, this, [this](){
        QString text{QString::number(memory)};
        ui->output_line_edit->setText(text);

        to_clear = true;
        ui->comma_button->setDisabled(false);
    });
    connect(ui->save_to_memory_button, &QPushButton::clicked, this, [this](){
        QString text{ui->output_line_edit->text()};
        QTextStream validator{&text};
        validator >> a;
        memory = a;
    });
    connect(ui->add_to_memory_button, &QPushButton::clicked, this, [this](){
        QString text{ui->output_line_edit->text()};
        QTextStream validator{&text};
        validator >> a;
        memory += a;
    });
    connect(ui->subtract_from_memory_button, &QPushButton::clicked, this, [this](){
        QString text{ui->output_line_edit->text()};
        QTextStream validator{&text};
        validator >> a;
        memory -= a;
    });
    connect(ui->clear_memory_button, &QPushButton::clicked, this, [this](){
        memory = 0;
    });
}

void Widget::append(QChar c){
    QString text{ui->output_line_edit->text()};
    if(to_clear)
        text = "";
    to_clear = false;
    text += c;
    ui->output_line_edit->setText(text);
}

void Widget::operation(int operation)
{
    QString text{ui->output_line_edit->text()};
    QTextStream validator{&text};
    validator >> a;

    switch(prev_operation){
    case operation::add:
        b += a;
        break;
    case operation::subtract:
        b -= a;
        break;
    case operation::multiply:
        b *= a;
        break;
    case operation::divide:
        b /= a;
        break;
    case operation::power:
        b = std::pow(b, a);
        break;
    case operation::root:
        b = std::pow(b, 1/a);
        break;
    default:
        b = a;
    }

    prev_operation = operation;

    text.setNum(b);
    ui->output_line_edit->setText(text);

    to_clear = true;
    ui->comma_button->setDisabled(false);
}

Widget::~Widget()
{
    delete ui;
}

