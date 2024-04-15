#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTreeWidget>
#include "bluetooth/ble.h"
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    BLE * m_ble;
private slots:
    void discover_btn_clicked(void);
private:
    Ui::Widget *ui;

    void Widget:: banding(void);
};
#endif // WIDGET_H
