# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'untitled.ui'
##
## Created by: Qt User Interface Compiler version 6.5.2
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
from PySide6.QtWidgets import (QApplication, QCheckBox, QFormLayout, QGridLayout,
    QHBoxLayout, QLabel, QMainWindow, QMenuBar,
    QPushButton, QSizePolicy, QSpacerItem, QStatusBar,
    QTextBrowser, QTextEdit, QVBoxLayout, QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(734, 375)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayout = QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.verticalSpacer_2 = QSpacerItem(20, 0, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer_2, 0, 0, 1, 1)

        self.formLayout = QFormLayout()
        self.formLayout.setObjectName(u"formLayout")
        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.read_text_widegt = QTextBrowser(self.centralwidget)
        self.read_text_widegt.setObjectName(u"read_text_widegt")
        self.read_text_widegt.setMinimumSize(QSize(250, 170))

        self.verticalLayout.addWidget(self.read_text_widegt)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.open_button = QPushButton(self.centralwidget)
        self.open_button.setObjectName(u"open_button")

        self.horizontalLayout.addWidget(self.open_button)

        self.close_button = QPushButton(self.centralwidget)
        self.close_button.setObjectName(u"close_button")

        self.horizontalLayout.addWidget(self.close_button)

        self.read_button = QPushButton(self.centralwidget)
        self.read_button.setObjectName(u"read_button")

        self.horizontalLayout.addWidget(self.read_button)


        self.verticalLayout.addLayout(self.horizontalLayout)


        self.formLayout.setLayout(0, QFormLayout.LabelRole, self.verticalLayout)

        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")

        self.verticalLayout_2.addWidget(self.label)

        self.write_url_widegt = QTextEdit(self.centralwidget)
        self.write_url_widegt.setObjectName(u"write_url_widegt")
        self.write_url_widegt.setMaximumSize(QSize(16777215, 100))

        self.verticalLayout_2.addWidget(self.write_url_widegt)

        self.label_2 = QLabel(self.centralwidget)
        self.label_2.setObjectName(u"label_2")

        self.verticalLayout_2.addWidget(self.label_2)

        self.write_text_widegt = QTextEdit(self.centralwidget)
        self.write_text_widegt.setObjectName(u"write_text_widegt")
        self.write_text_widegt.setMaximumSize(QSize(16777215, 100))

        self.verticalLayout_2.addWidget(self.write_text_widegt)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.auto_add_check_box = QCheckBox(self.centralwidget)
        self.auto_add_check_box.setObjectName(u"auto_add_check_box")

        self.verticalLayout_3.addWidget(self.auto_add_check_box)

        self.save_histry_file_check_box = QCheckBox(self.centralwidget)
        self.save_histry_file_check_box.setObjectName(u"save_histry_file_check_box")

        self.verticalLayout_3.addWidget(self.save_histry_file_check_box)


        self.horizontalLayout_3.addLayout(self.verticalLayout_3)

        self.file_save_addr_textEdit = QTextEdit(self.centralwidget)
        self.file_save_addr_textEdit.setObjectName(u"file_save_addr_textEdit")

        self.horizontalLayout_3.addWidget(self.file_save_addr_textEdit)


        self.verticalLayout_2.addLayout(self.horizontalLayout_3)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.write_button = QPushButton(self.centralwidget)
        self.write_button.setObjectName(u"write_button")

        self.horizontalLayout_2.addWidget(self.write_button)

        self.lock_button = QPushButton(self.centralwidget)
        self.lock_button.setObjectName(u"lock_button")

        self.horizontalLayout_2.addWidget(self.lock_button)

        self.less_button = QPushButton(self.centralwidget)
        self.less_button.setObjectName(u"less_button")

        self.horizontalLayout_2.addWidget(self.less_button)


        self.verticalLayout_2.addLayout(self.horizontalLayout_2)


        self.formLayout.setLayout(0, QFormLayout.FieldRole, self.verticalLayout_2)


        self.gridLayout.addLayout(self.formLayout, 1, 0, 1, 2)

        self.verticalSpacer = QSpacerItem(20, 139, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer, 2, 1, 1, 1)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 734, 21))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.open_button.setText(QCoreApplication.translate("MainWindow", u"\u8fde\u63a5\u8bfb\u5361\u5668", None))
        self.close_button.setText(QCoreApplication.translate("MainWindow", u"\u65ad\u5f00\u8bfb\u5361\u5668", None))
        self.read_button.setText(QCoreApplication.translate("MainWindow", u"\u8bfb\u5361", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"\u7f51\u5740", None))
#if QT_CONFIG(accessibility)
        self.write_url_widegt.setAccessibleName("")
#endif // QT_CONFIG(accessibility)
        self.write_url_widegt.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">https://h5.clewm.net/?url=qr61.cn%2FooCZ0Y%2Fq3TEwEl&amp;hasredirect=1</p></body></html>", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"\u5e8f\u5217\u53f7", None))
        self.auto_add_check_box.setText(QCoreApplication.translate("MainWindow", u"\u5e8f\u5217\u53f7\u81ea\u52a8+1", None))
        self.save_histry_file_check_box.setText(QCoreApplication.translate("MainWindow", u"\u4fdd\u5b58\u5199\u5361\u5386\u53f2", None))
        self.write_button.setText(QCoreApplication.translate("MainWindow", u"\u5199\u5361", None))
        self.lock_button.setText(QCoreApplication.translate("MainWindow", u"\u9501\u5361", None))
        self.less_button.setText(QCoreApplication.translate("MainWindow", u"\u5e8f\u5217\u53f7-1", None))
    # retranslateUi

