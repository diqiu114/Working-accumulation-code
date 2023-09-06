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
from PySide6.QtWidgets import (QApplication, QCheckBox, QHBoxLayout, QPlainTextEdit,
    QPushButton, QSizePolicy, QTextBrowser, QTextEdit,
    QVBoxLayout, QWidget)

class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(701, 296)
        self.layoutWidget = QWidget(Form)
        self.layoutWidget.setObjectName(u"layoutWidget")
        self.layoutWidget.setGeometry(QRect(40, 20, 318, 225))
        self.verticalLayout = QVBoxLayout(self.layoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.read_text_widegt = QTextBrowser(self.layoutWidget)
        self.read_text_widegt.setObjectName(u"read_text_widegt")

        self.verticalLayout.addWidget(self.read_text_widegt)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.open_button = QPushButton(self.layoutWidget)
        self.open_button.setObjectName(u"open_button")

        self.horizontalLayout.addWidget(self.open_button)

        self.close_button = QPushButton(self.layoutWidget)
        self.close_button.setObjectName(u"close_button")

        self.horizontalLayout.addWidget(self.close_button)

        self.read_button = QPushButton(self.layoutWidget)
        self.read_button.setObjectName(u"read_button")

        self.horizontalLayout.addWidget(self.read_button)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.widget = QWidget(Form)
        self.widget.setObjectName(u"widget")
        self.widget.setGeometry(QRect(400, 10, 258, 239))
        self.verticalLayout_2 = QVBoxLayout(self.widget)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.write_url_widegt = QPlainTextEdit(self.widget)
        self.write_url_widegt.setObjectName(u"write_url_widegt")
        self.write_url_widegt.setMaximumSize(QSize(16777215, 100))

        self.verticalLayout_2.addWidget(self.write_url_widegt)

        self.write_text_widegt = QTextEdit(self.widget)
        self.write_text_widegt.setObjectName(u"write_text_widegt")
        self.write_text_widegt.setMaximumSize(QSize(16777215, 100))

        self.verticalLayout_2.addWidget(self.write_text_widegt)

        self.auto_add_check_box = QCheckBox(self.widget)
        self.auto_add_check_box.setObjectName(u"auto_add_check_box")

        self.verticalLayout_2.addWidget(self.auto_add_check_box)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.write_button = QPushButton(self.widget)
        self.write_button.setObjectName(u"write_button")

        self.horizontalLayout_2.addWidget(self.write_button)

        self.less_button = QPushButton(self.widget)
        self.less_button.setObjectName(u"less_button")

        self.horizontalLayout_2.addWidget(self.less_button)


        self.verticalLayout_2.addLayout(self.horizontalLayout_2)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.open_button.setText(QCoreApplication.translate("Form", u"\u6253\u5f00", None))
        self.close_button.setText(QCoreApplication.translate("Form", u"\u5173\u95ed", None))
        self.read_button.setText(QCoreApplication.translate("Form", u"\u8bfb\u53d6", None))
#if QT_CONFIG(accessibility)
        self.write_url_widegt.setAccessibleName("")
#endif // QT_CONFIG(accessibility)
        self.write_url_widegt.setPlainText(QCoreApplication.translate("Form", u"https://h5.clewm.net/?url=qr61.cn%2FooCZ0Y%2Fq3TEwEl&hasredirect=1", None))
        self.auto_add_check_box.setText(QCoreApplication.translate("Form", u"\u81ea\u52a8+1", None))
        self.write_button.setText(QCoreApplication.translate("Form", u"\u5199\u5165", None))
        self.less_button.setText(QCoreApplication.translate("Form", u"-1", None))
    # retranslateUi

