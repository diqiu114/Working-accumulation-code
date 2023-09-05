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
from PySide6.QtWidgets import (QApplication, QHBoxLayout, QPlainTextEdit, QPushButton,
    QSizePolicy, QSpacerItem, QTextBrowser, QTextEdit,
    QVBoxLayout, QWidget)

class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(943, 333)
        self.verticalLayout = QVBoxLayout(Form)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.widget_3 = QWidget(Form)
        self.widget_3.setObjectName(u"widget_3")
        self.horizontalLayout_3 = QHBoxLayout(self.widget_3)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_3.addItem(self.verticalSpacer_2)

        self.read_text_widegt = QTextBrowser(self.widget_3)
        self.read_text_widegt.setObjectName(u"read_text_widegt")

        self.verticalLayout_3.addWidget(self.read_text_widegt)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.open_button = QPushButton(self.widget_3)
        self.open_button.setObjectName(u"open_button")

        self.horizontalLayout_2.addWidget(self.open_button)

        self.close_button = QPushButton(self.widget_3)
        self.close_button.setObjectName(u"close_button")

        self.horizontalLayout_2.addWidget(self.close_button)

        self.read_button = QPushButton(self.widget_3)
        self.read_button.setObjectName(u"read_button")

        self.horizontalLayout_2.addWidget(self.read_button)


        self.verticalLayout_3.addLayout(self.horizontalLayout_2)

        self.verticalSpacer_3 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_3.addItem(self.verticalSpacer_3)


        self.horizontalLayout_3.addLayout(self.verticalLayout_3)

        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalSpacer_4 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_2.addItem(self.verticalSpacer_4)

        self.write_url_widegt = QPlainTextEdit(self.widget_3)
        self.write_url_widegt.setObjectName(u"write_url_widegt")
        self.write_url_widegt.setMaximumSize(QSize(16777215, 100))

        self.verticalLayout_2.addWidget(self.write_url_widegt)

        self.write_text_widegt = QTextEdit(self.widget_3)
        self.write_text_widegt.setObjectName(u"write_text_widegt")
        self.write_text_widegt.setMaximumSize(QSize(16777215, 100))

        self.verticalLayout_2.addWidget(self.write_text_widegt)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.write_button = QPushButton(self.widget_3)
        self.write_button.setObjectName(u"write_button")

        self.horizontalLayout.addWidget(self.write_button)

        self.add_button = QPushButton(self.widget_3)
        self.add_button.setObjectName(u"add_button")

        self.horizontalLayout.addWidget(self.add_button)

        self.less_button = QPushButton(self.widget_3)
        self.less_button.setObjectName(u"less_button")

        self.horizontalLayout.addWidget(self.less_button)


        self.verticalLayout_2.addLayout(self.horizontalLayout)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_2.addItem(self.verticalSpacer)


        self.horizontalLayout_3.addLayout(self.verticalLayout_2)


        self.verticalLayout.addWidget(self.widget_3)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.open_button.setText(QCoreApplication.translate("Form", u"\u6253\u5f00", None))
        self.close_button.setText(QCoreApplication.translate("Form", u"\u5173\u95ed", None))
        self.read_button.setText(QCoreApplication.translate("Form", u"\u8bfb\u53d6", None))
        self.write_url_widegt.setPlainText(QCoreApplication.translate("Form", u"https://h5.clewm.net/?url=qr61.cn%2FooCZ0Y%2Fq3TEwEl&hasredirect=1", None))
        self.write_button.setText(QCoreApplication.translate("Form", u"\u5199\u5165", None))
        self.add_button.setText(QCoreApplication.translate("Form", u"+1", None))
        self.less_button.setText(QCoreApplication.translate("Form", u"-1", None))
    # retranslateUi

