import sys
from PySide6.QtWidgets import QApplication, QDialog, QDialogButtonBox, QVBoxLayout

class MyDialog(QDialog):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('获取按钮状态示例')
        self.setGeometry(100, 100, 400, 200)

        layout = QVBoxLayout(self)

        button_box = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel | QDialogButtonBox.Apply, self)
        layout.addWidget(button_box)

        # 连接按钮的信号到相应的槽函数
        button_box.accepted.connect(self.ok_handler)
        button_box.rejected.connect(self.cancel_handler)
        button_box.button(QDialogButtonBox.Apply).clicked.connect(self.apply_handler)

    def ok_handler(self):
        print("用户点击了'确定'按钮")
        self.accept()  # 关闭对话框

    def cancel_handler(self):
        print("用户点击了'取消'按钮")
        self.reject()  # 关闭对话框

    def apply_handler(self):
        print("用户点击了'应用'按钮")
        # 执行应用按钮的逻辑
        self.accept()  # 关闭对话框

def main():
    app = QApplication(sys.argv)
    dialog = MyDialog()
    dialog.exec_()

if __name__ == '__main__':
    main()