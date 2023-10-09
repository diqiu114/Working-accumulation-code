from PySide6.QtWidgets import QApplication, QMainWindow, QPushButton, QLabel

class MyWindows(QMainWindow):
    def __init__(self):
        super().__init__()
        # btn = QPushButton("按钮", self)
        # btn.setGeometry(100, 100, 100, 100)

        label = QLabel("我是一个标签", self)
        label.setGeometry(100, 100, 100, 100)

if __name__=="__main__":
    app = QApplication([])
    window = MyWindows()
    window.show()
    app.exec()https://cloud.tencent.com/developer/news/609716