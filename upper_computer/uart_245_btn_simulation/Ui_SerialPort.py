# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'SerialPort.ui'
##
## Created by: Qt User Interface Compiler version 6.6.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QCheckBox, QComboBox, QFormLayout,
    QGridLayout, QHBoxLayout, QLabel, QLineEdit,
    QPushButton, QRadioButton, QSizePolicy, QTextEdit,
    QVBoxLayout, QWidget)

class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.setWindowModality(Qt.NonModal)
        Form.setEnabled(True)
        Form.resize(898, 647)
        font = QFont()
        font.setFamilies([u"\u65b9\u6b63\u5170\u4ead\u4e2d\u9ed1_GBK"])
        font.setPointSize(9)
        font.setBold(False)
        font.setItalic(False)
        Form.setFont(font)
        Form.setCursor(QCursor(Qt.PointingHandCursor))
        Form.setMouseTracking(False)
        Form.setStyleSheet(u"")
        self.label = QLabel(Form)
        self.label.setObjectName(u"label")
        self.label.setGeometry(QRect(40, 40, 71, 21))
        self.label_2 = QLabel(Form)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setGeometry(QRect(40, 355, 54, 12))
        self.label_2.setTextFormat(Qt.AutoText)
        self.Send_Button = QPushButton(Form)
        self.Send_Button.setObjectName(u"Send_Button")
        self.Send_Button.setGeometry(QRect(330, 350, 75, 23))
        self.ClearButton = QPushButton(Form)
        self.ClearButton.setObjectName(u"ClearButton")
        self.ClearButton.setGeometry(QRect(330, 40, 75, 23))
        self.textEdit_Recive = QTextEdit(Form)
        self.textEdit_Recive.setObjectName(u"textEdit_Recive")
        self.textEdit_Recive.setGeometry(QRect(40, 70, 361, 251))
        self.textEdit_Recive.setStyleSheet(u"")
        self.textEdit_Send = QTextEdit(Form)
        self.textEdit_Send.setObjectName(u"textEdit_Send")
        self.textEdit_Send.setGeometry(QRect(40, 385, 351, 16))
        self.textEdit_Send.setStyleSheet(u"")
        self.gridLayoutWidget = QWidget(Form)
        self.gridLayoutWidget.setObjectName(u"gridLayoutWidget")
        self.gridLayoutWidget.setGeometry(QRect(40, 410, 221, 171))
        self.gridLayout = QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.Com_Baud_Label = QLabel(self.gridLayoutWidget)
        self.Com_Baud_Label.setObjectName(u"Com_Baud_Label")
        self.Com_Baud_Label.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.Com_Baud_Label, 1, 0, 1, 1)

        self.Com_Close_Button = QPushButton(self.gridLayoutWidget)
        self.Com_Close_Button.setObjectName(u"Com_Close_Button")

        self.gridLayout.addWidget(self.Com_Close_Button, 4, 1, 1, 1)

        self.Com_Name_Label = QLabel(self.gridLayoutWidget)
        self.Com_Name_Label.setObjectName(u"Com_Name_Label")
        self.Com_Name_Label.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.Com_Name_Label, 2, 0, 1, 1)

        self.Com_Name_Combo = QComboBox(self.gridLayoutWidget)
        self.Com_Name_Combo.setObjectName(u"Com_Name_Combo")

        self.gridLayout.addWidget(self.Com_Name_Combo, 2, 1, 1, 1)

        self.Com_Refresh_Label = QLabel(self.gridLayoutWidget)
        self.Com_Refresh_Label.setObjectName(u"Com_Refresh_Label")
        self.Com_Refresh_Label.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.Com_Refresh_Label, 0, 0, 1, 1)

        self.Com_Refresh_Button = QPushButton(self.gridLayoutWidget)
        self.Com_Refresh_Button.setObjectName(u"Com_Refresh_Button")

        self.gridLayout.addWidget(self.Com_Refresh_Button, 0, 1, 1, 1)

        self.Com_State_Label = QLabel(self.gridLayoutWidget)
        self.Com_State_Label.setObjectName(u"Com_State_Label")
        self.Com_State_Label.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.Com_State_Label, 3, 0, 1, 1)

        self.Com_Baud_Combo = QComboBox(self.gridLayoutWidget)
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.addItem("")
        self.Com_Baud_Combo.setObjectName(u"Com_Baud_Combo")
        self.Com_Baud_Combo.setEditable(True)
        self.Com_Baud_Combo.setDuplicatesEnabled(False)
        self.Com_Baud_Combo.setModelColumn(0)

        self.gridLayout.addWidget(self.Com_Baud_Combo, 1, 1, 1, 1)

        self.Com_Open_Button = QPushButton(self.gridLayoutWidget)
        self.Com_Open_Button.setObjectName(u"Com_Open_Button")

        self.gridLayout.addWidget(self.Com_Open_Button, 3, 1, 1, 1)

        self.Com_isOpenOrNot_Label = QLabel(self.gridLayoutWidget)
        self.Com_isOpenOrNot_Label.setObjectName(u"Com_isOpenOrNot_Label")
        self.Com_isOpenOrNot_Label.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.Com_isOpenOrNot_Label, 4, 0, 1, 1)

        self.hexSending_checkBox = QCheckBox(Form)
        self.hexSending_checkBox.setObjectName(u"hexSending_checkBox")
        self.hexSending_checkBox.setGeometry(QRect(240, 345, 91, 31))
        self.hexShowing_checkBox = QCheckBox(Form)
        self.hexShowing_checkBox.setObjectName(u"hexShowing_checkBox")
        self.hexShowing_checkBox.setGeometry(QRect(240, 40, 81, 20))
        self.layoutWidget = QWidget(Form)
        self.layoutWidget.setObjectName(u"layoutWidget")
        self.layoutWidget.setGeometry(QRect(40, 590, 132, 36))
        self.formLayout_2 = QFormLayout(self.layoutWidget)
        self.formLayout_2.setObjectName(u"formLayout_2")
        self.formLayout_2.setContentsMargins(0, 0, 0, 0)
        self.label_4 = QLabel(self.layoutWidget)
        self.label_4.setObjectName(u"label_4")

        self.formLayout_2.setWidget(0, QFormLayout.LabelRole, self.label_4)

        self.label_rx_cnt = QLabel(self.layoutWidget)
        self.label_rx_cnt.setObjectName(u"label_rx_cnt")

        self.formLayout_2.setWidget(0, QFormLayout.FieldRole, self.label_rx_cnt)

        self.label_5 = QLabel(self.layoutWidget)
        self.label_5.setObjectName(u"label_5")

        self.formLayout_2.setWidget(1, QFormLayout.LabelRole, self.label_5)

        self.label_tx_cnt = QLabel(self.layoutWidget)
        self.label_tx_cnt.setObjectName(u"label_tx_cnt")

        self.formLayout_2.setWidget(1, QFormLayout.FieldRole, self.label_tx_cnt)

        self.layoutWidget1 = QWidget(Form)
        self.layoutWidget1.setObjectName(u"layoutWidget1")
        self.layoutWidget1.setGeometry(QRect(470, 80, 160, 182))
        self.verticalLayout = QVBoxLayout(self.layoutWidget1)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_6 = QHBoxLayout()
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.radioBtn_sim_enable = QRadioButton(self.layoutWidget1)
        self.radioBtn_sim_enable.setObjectName(u"radioBtn_sim_enable")

        self.horizontalLayout_6.addWidget(self.radioBtn_sim_enable)


        self.verticalLayout.addLayout(self.horizontalLayout_6)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.label_3 = QLabel(self.layoutWidget1)
        self.label_3.setObjectName(u"label_3")

        self.horizontalLayout.addWidget(self.label_3)

        self.pushButton_pre = QPushButton(self.layoutWidget1)
        self.pushButton_pre.setObjectName(u"pushButton_pre")

        self.horizontalLayout.addWidget(self.pushButton_pre)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.label_6 = QLabel(self.layoutWidget1)
        self.label_6.setObjectName(u"label_6")

        self.horizontalLayout_2.addWidget(self.label_6)

        self.pushButton_next = QPushButton(self.layoutWidget1)
        self.pushButton_next.setObjectName(u"pushButton_next")

        self.horizontalLayout_2.addWidget(self.pushButton_next)


        self.verticalLayout.addLayout(self.horizontalLayout_2)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.label_7 = QLabel(self.layoutWidget1)
        self.label_7.setObjectName(u"label_7")

        self.horizontalLayout_3.addWidget(self.label_7)

        self.pushButton_ok = QPushButton(self.layoutWidget1)
        self.pushButton_ok.setObjectName(u"pushButton_ok")

        self.horizontalLayout_3.addWidget(self.pushButton_ok)


        self.verticalLayout.addLayout(self.horizontalLayout_3)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.label_8 = QLabel(self.layoutWidget1)
        self.label_8.setObjectName(u"label_8")

        self.horizontalLayout_4.addWidget(self.label_8)

        self.pushButton_exit = QPushButton(self.layoutWidget1)
        self.pushButton_exit.setObjectName(u"pushButton_exit")

        self.horizontalLayout_4.addWidget(self.pushButton_exit)


        self.verticalLayout.addLayout(self.horizontalLayout_4)

        self.horizontalLayout_5 = QHBoxLayout()
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.label_9 = QLabel(self.layoutWidget1)
        self.label_9.setObjectName(u"label_9")

        self.horizontalLayout_5.addWidget(self.label_9)

        self.pushButton_menu = QPushButton(self.layoutWidget1)
        self.pushButton_menu.setObjectName(u"pushButton_menu")

        self.horizontalLayout_5.addWidget(self.pushButton_menu)


        self.verticalLayout.addLayout(self.horizontalLayout_5)

        self.label_10 = QLabel(Form)
        self.label_10.setObjectName(u"label_10")
        self.label_10.setGeometry(QRect(480, 50, 81, 21))
        self.label_11 = QLabel(Form)
        self.label_11.setObjectName(u"label_11")
        self.label_11.setGeometry(QRect(470, 350, 91, 21))
        self.layoutWidget_2 = QWidget(Form)
        self.layoutWidget_2.setObjectName(u"layoutWidget_2")
        self.layoutWidget_2.setGeometry(QRect(470, 380, 164, 225))
        self.verticalLayout_2 = QVBoxLayout(self.layoutWidget_2)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_7 = QHBoxLayout()
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.radioBtn_sim_esp32 = QRadioButton(self.layoutWidget_2)
        self.radioBtn_sim_esp32.setObjectName(u"radioBtn_sim_esp32")

        self.horizontalLayout_7.addWidget(self.radioBtn_sim_esp32)


        self.verticalLayout_2.addLayout(self.horizontalLayout_7)

        self.horizontalLayout_8 = QHBoxLayout()
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.pushButton_get_band_info = QPushButton(self.layoutWidget_2)
        self.pushButton_get_band_info.setObjectName(u"pushButton_get_band_info")

        self.horizontalLayout_8.addWidget(self.pushButton_get_band_info)


        self.verticalLayout_2.addLayout(self.horizontalLayout_8)

        self.horizontalLayout_9 = QHBoxLayout()
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.pushButton_close_band = QPushButton(self.layoutWidget_2)
        self.pushButton_close_band.setObjectName(u"pushButton_close_band")

        self.horizontalLayout_9.addWidget(self.pushButton_close_band)

        self.lineEdit_close_band = QLineEdit(self.layoutWidget_2)
        self.lineEdit_close_band.setObjectName(u"lineEdit_close_band")

        self.horizontalLayout_9.addWidget(self.lineEdit_close_band)


        self.verticalLayout_2.addLayout(self.horizontalLayout_9)

        self.horizontalLayout_10 = QHBoxLayout()
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.pushButton_open_band = QPushButton(self.layoutWidget_2)
        self.pushButton_open_band.setObjectName(u"pushButton_open_band")

        self.horizontalLayout_10.addWidget(self.pushButton_open_band)

        self.lineEdit__open_band = QLineEdit(self.layoutWidget_2)
        self.lineEdit__open_band.setObjectName(u"lineEdit__open_band")

        self.horizontalLayout_10.addWidget(self.lineEdit__open_band)


        self.verticalLayout_2.addLayout(self.horizontalLayout_10)


        self.retranslateUi(Form)
        self.ClearButton.clicked.connect(self.textEdit_Recive.clear)

        self.Com_Close_Button.setDefault(False)


        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.label.setText(QCoreApplication.translate("Form", u"\u63a5\u6536\u533a", None))
        self.label_2.setText(QCoreApplication.translate("Form", u"\u53d1\u9001\u533a", None))
        self.Send_Button.setText(QCoreApplication.translate("Form", u"\u53d1\u9001", None))
        self.ClearButton.setText(QCoreApplication.translate("Form", u"\u6e05\u9664", None))
        self.textEdit_Recive.setHtml(QCoreApplication.translate("Form", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'\u65b9\u6b63\u5170\u4ead\u4e2d\u9ed1_GBK'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", None))
        self.Com_Baud_Label.setText(QCoreApplication.translate("Form", u"\u6ce2\u7279\u7387", None))
        self.Com_Close_Button.setText(QCoreApplication.translate("Form", u"Close", None))
        self.Com_Name_Label.setText(QCoreApplication.translate("Form", u"\u4e32\u53e3\u9009\u62e9", None))
        self.Com_Refresh_Label.setText(QCoreApplication.translate("Form", u"\u4e32\u53e3\u641c\u7d22", None))
        self.Com_Refresh_Button.setText(QCoreApplication.translate("Form", u"\u5237\u65b0", None))
        self.Com_State_Label.setText(QCoreApplication.translate("Form", u"\u4e32\u53e3\u64cd\u4f5c", None))
        self.Com_Baud_Combo.setItemText(0, QCoreApplication.translate("Form", u"921600", None))
        self.Com_Baud_Combo.setItemText(1, QCoreApplication.translate("Form", u"2400", None))
        self.Com_Baud_Combo.setItemText(2, QCoreApplication.translate("Form", u"4800", None))
        self.Com_Baud_Combo.setItemText(3, QCoreApplication.translate("Form", u"9600", None))
        self.Com_Baud_Combo.setItemText(4, QCoreApplication.translate("Form", u"14400", None))
        self.Com_Baud_Combo.setItemText(5, QCoreApplication.translate("Form", u"19200", None))
        self.Com_Baud_Combo.setItemText(6, QCoreApplication.translate("Form", u"38400", None))
        self.Com_Baud_Combo.setItemText(7, QCoreApplication.translate("Form", u"43000", None))
        self.Com_Baud_Combo.setItemText(8, QCoreApplication.translate("Form", u"57600", None))
        self.Com_Baud_Combo.setItemText(9, QCoreApplication.translate("Form", u"76800", None))
        self.Com_Baud_Combo.setItemText(10, QCoreApplication.translate("Form", u"115200", None))
        self.Com_Baud_Combo.setItemText(11, QCoreApplication.translate("Form", u"128000", None))
        self.Com_Baud_Combo.setItemText(12, QCoreApplication.translate("Form", u"230400", None))
        self.Com_Baud_Combo.setItemText(13, QCoreApplication.translate("Form", u"256000", None))
        self.Com_Baud_Combo.setItemText(14, QCoreApplication.translate("Form", u"460800", None))
        self.Com_Baud_Combo.setItemText(15, QCoreApplication.translate("Form", u"921600", None))
        self.Com_Baud_Combo.setItemText(16, QCoreApplication.translate("Form", u"1382400", None))

        self.Com_Baud_Combo.setCurrentText(QCoreApplication.translate("Form", u"921600", None))
        self.Com_Open_Button.setText(QCoreApplication.translate("Form", u"Open", None))
        self.Com_isOpenOrNot_Label.setText("")
        self.hexSending_checkBox.setText(QCoreApplication.translate("Form", u"16\u8fdb\u5236\u53d1\u9001", None))
        self.hexShowing_checkBox.setText(QCoreApplication.translate("Form", u"16\u8fdb\u5236\u663e\u793a", None))
        self.label_4.setText(QCoreApplication.translate("Form", u"\u63a5\u6536\u6570\u636e\u8ba1\u6570", None))
        self.label_rx_cnt.setText(QCoreApplication.translate("Form", u"TextLabel", None))
        self.label_5.setText(QCoreApplication.translate("Form", u"\u53d1\u9001\u6570\u636e\u8ba1\u6570", None))
        self.label_tx_cnt.setText(QCoreApplication.translate("Form", u"TextLabel", None))
        self.radioBtn_sim_enable.setText(QCoreApplication.translate("Form", u"\u4f7f\u80fd\u6a21\u62df\u6309\u952e\u529f\u80fd", None))
        self.label_3.setText(QCoreApplication.translate("Form", u"\u4e0a\u4e00\u4e2a", None))
        self.pushButton_pre.setText(QCoreApplication.translate("Form", u"\u4e0a\u4e00\u4e2a", None))
        self.label_6.setText(QCoreApplication.translate("Form", u"\u4e0b\u4e00\u4e2a", None))
        self.pushButton_next.setText(QCoreApplication.translate("Form", u"\u4e0b\u4e00\u4e2a", None))
        self.label_7.setText(QCoreApplication.translate("Form", u"\u786e\u8ba4", None))
        self.pushButton_ok.setText(QCoreApplication.translate("Form", u"\u786e\u8ba4", None))
        self.label_8.setText(QCoreApplication.translate("Form", u"\u9000\u51fa", None))
        self.pushButton_exit.setText(QCoreApplication.translate("Form", u"\u9000\u51fa", None))
        self.label_9.setText(QCoreApplication.translate("Form", u"\u83dc\u5355", None))
        self.pushButton_menu.setText(QCoreApplication.translate("Form", u"\u83dc\u5355", None))
        self.label_10.setText(QCoreApplication.translate("Form", u"\u4e3b\u677f\u6a21\u62df", None))
        self.label_11.setText(QCoreApplication.translate("Form", u"esp32\u677f\u5b50\u6a21\u62df", None))
        self.radioBtn_sim_esp32.setText(QCoreApplication.translate("Form", u"\u4f7f\u80fd\u83b7\u53d6\u8bbe\u5907\u9891\u6bb5\u4fe1\u606f", None))
        self.pushButton_get_band_info.setText(QCoreApplication.translate("Form", u"\u83b7\u53d6\u9891\u6bb5\u4fe1\u606f", None))
        self.pushButton_close_band.setText(QCoreApplication.translate("Form", u"\u5173\u95ed\u9891\u6bb5", None))
        self.lineEdit_close_band.setText(QCoreApplication.translate("Form", u"698", None))
        self.pushButton_open_band.setText(QCoreApplication.translate("Form", u"\u6253\u5f00\u9891\u6bb5", None))
        self.lineEdit__open_band.setText(QCoreApplication.translate("Form", u"698", None))
    # retranslateUi

