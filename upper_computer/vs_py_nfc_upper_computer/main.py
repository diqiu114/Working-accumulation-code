import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QLabel
from untitled_ui import Ui_Form

import test

class MyMainForm(QMainWindow, Ui_Form):
    def __init__(self, parent=None):
        super(MyMainForm, self).__init__(parent)
        self.setupUi(self)
        self.read_button.clicked.connect(self.Read_button_clicked)
        self.write_button.clicked.connect(self.Write_button_clicked)
    process = ""
    def Read_button_clicked(self):
        print("read button点击")
        test.Test(self.process)
    def Write_button_clicked(self):
        print("Write_button_clicked点击")
        self.process = test.Open_device()



def main():
    #固定的，PyQt5程序都需要QApplication对象。sys.argv是命令行参数列表，确保程序可以双击运行
    # 这里用的是qtside6
    app = QApplication(sys.argv)
    #初始化
    myWin = MyMainForm()
    #将窗口控件显示在屏幕上
    myWin.show()
    #程序运行，sys.exit方法确保程序完整退出。
    sys.exit(app.exec())

if __name__ == '__main__':
    main()