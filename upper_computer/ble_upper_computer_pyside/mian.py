from PySide6.QtWidgets import QApplication, QMainWindow
import sys
from Ui_untitled import Ui_MainWindow

from threading import Thread
from my_ble import MyBle

class MyMainWindow(QMainWindow, MyBle):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.banding()

    def banding(self):
        self.ui.pushButton.clicked.connect(self.scan_btn_clicked)

    def scan_btn_clicked(self):
        print("start scan ble")

def main():
    app = QApplication(sys.argv)
    main_window = MyMainWindow()
    main_window.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
    

