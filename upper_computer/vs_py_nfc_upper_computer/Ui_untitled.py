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
    QHBoxLayout, QMainWindow, QMenuBar, QPlainTextEdit,
    QPushButton, QSizePolicy, QSpacerItem, QStatusBar,
    QTextBrowser, QTextEdit, QVBoxLayout, QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(692, 279)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayout = QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.verticalSpacer_2 = QSpacerItem(20, 0, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer_2, 0, 0, 1, 1)

        self.verticalSpacer = QSpacerItem(20, 139, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer, 2, 0, 1, 1)

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
        self.write_url_widegt = QPlainTextEdit(self.centralwidget)
        self.write_url_widegt.setObjectName(u"write_url_widegt")
        self.write_url_widegt.setMaximumSize(QSize(16777215, 100))

        self.verticalLayout_2.addWidget(self.write_url_widegt)

        self.write_text_widegt = QTextEdit(self.centralwidget)
        self.write_text_widegt.setObjectName(u"write_text_widegt")
        self.write_text_widegt.setMaximumSize(QSize(16777215, 100))

        self.verticalLayout_2.addWidget(self.write_text_widegt)

        self.auto_add_check_box = QCheckBox(self.centralwidget)
        self.auto_add_check_box.setObjectName(u"auto_add_check_box")

        self.verticalLayout_2.addWidget(self.auto_add_check_box)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.write_button = QPushButton(self.centralwidget)
        self.write_button.setObjectName(u"write_button")

        self.horizontalLayout_2.addWidget(self.write_button)

        self.less_button = QPushButton(self.centralwidget)
        self.less_button.setObjectName(u"less_button")

        self.horizontalLayout_2.addWidget(self.less_button)


        self.verticalLayout_2.addLayout(self.horizontalLayout_2)


        self.formLayout.setLayout(0, QFormLayout.FieldRole, self.verticalLayout_2)


        self.gridLayout.addLayout(self.formLayout, 1, 0, 1, 1)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 692, 21))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.open_button.setText(QCoreApplication.translate("MainWindow", u"\u6253\u5f00", None))
        self.close_button.setText(QCoreApplication.translate("MainWindow", u"\u5173\u95ed", None))
        self.read_button.setText(QCoreApplication.translate("MainWindow", u"\u8bfb\u53d6", None))
#if QT_CONFIG(accessibility)
        self.write_url_widegt.setAccessibleName("")
#endif // QT_CONFIG(accessibility)
        self.write_url_widegt.setPlainText(QCoreApplication.translate("MainWindow", u"https://h5.clewm.net/?url=qr61.cn%2FooCZ0Y%2Fq3TEwEl&hasredirect=1", None))
        self.auto_add_check_box.setText(QCoreApplication.translate("MainWindow", u"\u81ea\u52a8+1", None))
        self.write_button.setText(QCoreApplication.translate("MainWindow", u"\u5199\u5165", None))
        self.less_button.setText(QCoreApplication.translate("MainWindow", u"-1", None))
    # retranslateUi

