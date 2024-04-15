#include "widget.h"
#include "ui_widget.h"

#include <QDialog>
#include <QMessageBox>

#include <iostream>

using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget:: discover_btn_clicked(void)
{
    cout <<  __FUNCTION__ << endl;
}
