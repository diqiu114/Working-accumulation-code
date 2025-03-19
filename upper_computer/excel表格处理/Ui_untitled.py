# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'untitled.ui'
##
## Created by: Qt User Interface Compiler version 6.6.1
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
from PySide6.QtWidgets import (QApplication, QGridLayout, QHBoxLayout, QLabel,
    QLineEdit, QMainWindow, QMenuBar, QPushButton,
    QSizePolicy, QSpacerItem, QStatusBar, QVBoxLayout,
    QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(635, 341)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayout = QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.verticalSpacer = QSpacerItem(20, 54, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer, 0, 2, 1, 1)

        self.horizontalSpacer_2 = QSpacerItem(70, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout.addItem(self.horizontalSpacer_2, 1, 0, 1, 1)

        self.widget_5 = QWidget(self.centralwidget)
        self.widget_5.setObjectName(u"widget_5")
        self.verticalLayout_3 = QVBoxLayout(self.widget_5)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.widget_4 = QWidget(self.widget_5)
        self.widget_4.setObjectName(u"widget_4")
        self.verticalLayout_2 = QVBoxLayout(self.widget_4)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.widget_2 = QWidget(self.widget_4)
        self.widget_2.setObjectName(u"widget_2")
        self.horizontalLayout = QHBoxLayout(self.widget_2)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.btn_select_file = QPushButton(self.widget_2)
        self.btn_select_file.setObjectName(u"btn_select_file")

        self.horizontalLayout.addWidget(self.btn_select_file)

        self.line_edit_select_file = QLineEdit(self.widget_2)
        self.line_edit_select_file.setObjectName(u"line_edit_select_file")
        self.line_edit_select_file.setEnabled(True)
        self.line_edit_select_file.setMinimumSize(QSize(400, 0))

        self.horizontalLayout.addWidget(self.line_edit_select_file)


        self.verticalLayout_2.addWidget(self.widget_2)

        self.widget_3 = QWidget(self.widget_4)
        self.widget_3.setObjectName(u"widget_3")
        self.horizontalLayout_2 = QHBoxLayout(self.widget_3)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.btn_save_feil = QPushButton(self.widget_3)
        self.btn_save_feil.setObjectName(u"btn_save_feil")

        self.horizontalLayout_2.addWidget(self.btn_save_feil)

        self.line_edit_save_file = QLineEdit(self.widget_3)
        self.line_edit_save_file.setObjectName(u"line_edit_save_file")

        self.horizontalLayout_2.addWidget(self.line_edit_save_file)


        self.verticalLayout_2.addWidget(self.widget_3)

        self.widget = QWidget(self.widget_4)
        self.widget.setObjectName(u"widget")
        self.verticalLayout = QVBoxLayout(self.widget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.label_2 = QLabel(self.widget)
        self.label_2.setObjectName(u"label_2")

        self.verticalLayout.addWidget(self.label_2)

        self.line_edit_out_file_title = QLineEdit(self.widget)
        self.line_edit_out_file_title.setObjectName(u"line_edit_out_file_title")

        self.verticalLayout.addWidget(self.line_edit_out_file_title)

        self.btn_start = QPushButton(self.widget)
        self.btn_start.setObjectName(u"btn_start")

        self.verticalLayout.addWidget(self.btn_start)


        self.verticalLayout_2.addWidget(self.widget)


        self.verticalLayout_3.addWidget(self.widget_4)


        self.gridLayout.addWidget(self.widget_5, 1, 1, 1, 2)

        self.horizontalSpacer = QSpacerItem(70, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout.addItem(self.horizontalSpacer, 1, 3, 1, 1)

        self.verticalSpacer_2 = QSpacerItem(20, 53, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer_2, 2, 1, 1, 1)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 635, 21))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.btn_select_file.setText(QCoreApplication.translate("MainWindow", u"\u9009\u62e9\u6587\u4ef6", None))
        self.btn_save_feil.setText(QCoreApplication.translate("MainWindow", u"\u6587\u4ef6\u4fdd\u5b58\u4f4d\u7f6e", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"\u8bbe\u7f6e\u8f93\u51fa\u6807\u9898", None))
        self.btn_start.setText(QCoreApplication.translate("MainWindow", u"\u5f00\u59cb\u5904\u7406", None))
    # retranslateUi

