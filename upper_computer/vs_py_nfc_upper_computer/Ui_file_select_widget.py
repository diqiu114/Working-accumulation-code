# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'file_select_widget.ui'
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
from PySide6.QtWidgets import (QApplication, QDialog, QGridLayout, QHBoxLayout,
    QPushButton, QSizePolicy, QSpacerItem, QTextEdit,
    QWidget)

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        if not Dialog.objectName():
            Dialog.setObjectName(u"Dialog")
        Dialog.resize(339, 196)
        self.gridLayout = QGridLayout(Dialog)
        self.gridLayout.setObjectName(u"gridLayout")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.dialog_open_button = QPushButton(Dialog)
        self.dialog_open_button.setObjectName(u"dialog_open_button")

        self.horizontalLayout.addWidget(self.dialog_open_button)

        self.dialog_new_button = QPushButton(Dialog)
        self.dialog_new_button.setObjectName(u"dialog_new_button")

        self.horizontalLayout.addWidget(self.dialog_new_button)

        self.dialog_cancel_button = QPushButton(Dialog)
        self.dialog_cancel_button.setObjectName(u"dialog_cancel_button")

        self.horizontalLayout.addWidget(self.dialog_cancel_button)


        self.gridLayout.addLayout(self.horizontalLayout, 2, 1, 1, 1)

        self.horizontalSpacer_2 = QSpacerItem(0, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout.addItem(self.horizontalSpacer_2, 2, 2, 1, 1)

        self.horizontalSpacer = QSpacerItem(0, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout.addItem(self.horizontalSpacer, 2, 0, 1, 1)

        self.verticalSpacer = QSpacerItem(20, 0, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer, 0, 1, 1, 1)

        self.verticalSpacer_2 = QSpacerItem(20, 0, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer_2, 3, 1, 1, 1)

        self.textEdit = QTextEdit(Dialog)
        self.textEdit.setObjectName(u"textEdit")
        self.textEdit.setEnabled(True)
        self.textEdit.setMinimumSize(QSize(27, 15))

        self.gridLayout.addWidget(self.textEdit, 1, 1, 1, 1)


        self.retranslateUi(Dialog)

        QMetaObject.connectSlotsByName(Dialog)
    # setupUi

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QCoreApplication.translate("Dialog", u"Dialog", None))
        self.dialog_open_button.setText(QCoreApplication.translate("Dialog", u"\u6253\u5f00", None))
        self.dialog_new_button.setText(QCoreApplication.translate("Dialog", u"\u65b0\u5efa", None))
        self.dialog_cancel_button.setText(QCoreApplication.translate("Dialog", u"\u53d6\u6d88", None))
        self.textEdit.setHtml(QCoreApplication.translate("Dialog", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:700;\">\u63d0\u793a\uff1a\u7528\u4e8e\u4fdd\u5b58\u5386\u53f2\u6570\u636e\u7684\u6587\u4ef6\uff0c\u8981\u7531\u4e0b\u65b9\u7684\u65b0\u5efa\u6309\u94ae\u53bb\u65b0\u5efa\uff0c\u5f53\u5b58\u5728\u5df2\u7ecf\u7531\u672c\u7a0b\u5e8f\u65b0\u5efa\u597d\u7684\uff0c\u70b9\u51fb\u6253\u5f00\u6309\u94ae\uff0c\u627e\u5230\u6587\u4ef6\u6253\u5f00\u5373\u53ef</"
                        "span></p></body></html>", None))
    # retranslateUi

