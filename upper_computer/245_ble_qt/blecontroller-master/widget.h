#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTreeWidget>
#include "bluetooth/ble.h"
#include <QTableWidgetItem>
#include "framedate.h"

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
    void on_pushButton_scan_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_service_clicked();

    void on_pushButtonGetBandInfo_clicked();

    void on_pushButtonGainSet_clicked();

    void on_pushButtonEnableSet_clicked();

    void activeDataReception();

    void on_pushButtonSave_clicked();

private:
    Ui::Widget *ui;

    bool txBandIsLegal(QString Str);
    bool txDiverIsLegal(QString Str);

    FrameDate *pFrameDate;

    FrameDate::Band_t whichBandInCheckBoxSelected();
    FrameDate::RuMuId_t whichDeviceInCheckBoxSelected();
    QByteArray AddFrameHeadAndTail(QByteArray);

};
#endif // WIDGET_H
