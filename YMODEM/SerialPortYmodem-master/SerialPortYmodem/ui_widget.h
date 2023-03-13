/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comPort;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *comBaudRate;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *comButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *transmitPath;
    QPushButton *transmitBrowse;
    QPushButton *transmitButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QProgressBar *transmitProgress;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *receivePath;
    QPushButton *receiveBrowse;
    QPushButton *receiveButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QProgressBar *receiveProgress;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(444, 255);
        Widget->setMinimumSize(QSize(444, 255));
        Widget->setMaximumSize(QSize(444, 255));
        verticalLayout_3 = new QVBoxLayout(Widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comPort = new QComboBox(groupBox);
        comPort->setObjectName(QString::fromUtf8("comPort"));
        comPort->setMaxVisibleItems(12);

        horizontalLayout->addWidget(comPort);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comBaudRate = new QComboBox(groupBox);
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->addItem(QString());
        comBaudRate->setObjectName(QString::fromUtf8("comBaudRate"));
        comBaudRate->setMaxVisibleItems(12);

        horizontalLayout->addWidget(comBaudRate);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        comButton = new QPushButton(groupBox);
        comButton->setObjectName(QString::fromUtf8("comButton"));

        horizontalLayout->addWidget(comButton);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        transmitPath = new QLineEdit(groupBox_2);
        transmitPath->setObjectName(QString::fromUtf8("transmitPath"));
        transmitPath->setReadOnly(true);

        horizontalLayout_2->addWidget(transmitPath);

        transmitBrowse = new QPushButton(groupBox_2);
        transmitBrowse->setObjectName(QString::fromUtf8("transmitBrowse"));
        transmitBrowse->setEnabled(false);

        horizontalLayout_2->addWidget(transmitBrowse);

        transmitButton = new QPushButton(groupBox_2);
        transmitButton->setObjectName(QString::fromUtf8("transmitButton"));
        transmitButton->setEnabled(false);

        horizontalLayout_2->addWidget(transmitButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        transmitProgress = new QProgressBar(groupBox_2);
        transmitProgress->setObjectName(QString::fromUtf8("transmitProgress"));
        transmitProgress->setValue(0);

        horizontalLayout_3->addWidget(transmitProgress);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        receivePath = new QLineEdit(groupBox_3);
        receivePath->setObjectName(QString::fromUtf8("receivePath"));
        receivePath->setReadOnly(true);

        horizontalLayout_4->addWidget(receivePath);

        receiveBrowse = new QPushButton(groupBox_3);
        receiveBrowse->setObjectName(QString::fromUtf8("receiveBrowse"));
        receiveBrowse->setEnabled(false);

        horizontalLayout_4->addWidget(receiveBrowse);

        receiveButton = new QPushButton(groupBox_3);
        receiveButton->setObjectName(QString::fromUtf8("receiveButton"));
        receiveButton->setEnabled(false);

        horizontalLayout_4->addWidget(receiveButton);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        receiveProgress = new QProgressBar(groupBox_3);
        receiveProgress->setObjectName(QString::fromUtf8("receiveProgress"));
        receiveProgress->setValue(0);

        horizontalLayout_5->addWidget(receiveProgress);


        verticalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout_3->addWidget(groupBox_3);


        retranslateUi(Widget);

        comBaudRate->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "SerialPortYmodem", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\351\205\215\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\253\257\345\217\243\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        comBaudRate->setItemText(0, QCoreApplication::translate("Widget", "921600", nullptr));
        comBaudRate->setItemText(1, QCoreApplication::translate("Widget", "460800", nullptr));
        comBaudRate->setItemText(2, QCoreApplication::translate("Widget", "230400", nullptr));
        comBaudRate->setItemText(3, QCoreApplication::translate("Widget", "115200", nullptr));
        comBaudRate->setItemText(4, QCoreApplication::translate("Widget", "57600", nullptr));
        comBaudRate->setItemText(5, QCoreApplication::translate("Widget", "38400", nullptr));
        comBaudRate->setItemText(6, QCoreApplication::translate("Widget", "19200", nullptr));
        comBaudRate->setItemText(7, QCoreApplication::translate("Widget", "9600", nullptr));
        comBaudRate->setItemText(8, QCoreApplication::translate("Widget", "4800", nullptr));
        comBaudRate->setItemText(9, QCoreApplication::translate("Widget", "2400", nullptr));
        comBaudRate->setItemText(10, QCoreApplication::translate("Widget", "1200", nullptr));

        comBaudRate->setCurrentText(QCoreApplication::translate("Widget", "115200", nullptr));
        comButton->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\346\226\207\344\273\266\345\217\221\351\200\201", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        transmitBrowse->setText(QCoreApplication::translate("Widget", "\346\265\217\350\247\210...", nullptr));
        transmitButton->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\344\274\240\350\276\223\350\277\233\345\272\246\357\274\232", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Widget", "\346\226\207\344\273\266\346\216\245\346\224\266", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        receiveBrowse->setText(QCoreApplication::translate("Widget", "\346\265\217\350\247\210...", nullptr));
        receiveButton->setText(QCoreApplication::translate("Widget", "\346\216\245\346\224\266", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "\344\274\240\350\276\223\350\277\233\345\272\246\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
