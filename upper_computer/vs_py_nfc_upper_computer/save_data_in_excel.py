import enum
import sys
import os

from Ui_file_select_widget import Ui_Dialog

from PySide6.QtWidgets import (
    QApplication, 
    QWidget, 
    QFileDialog, 
    QGridLayout,
    QPushButton, 
    QLabel,
    QListWidget,
    QDialog,
    QDialogButtonBox,
    QVBoxLayout,
)
from PySide6.QtCore import Qt


from pathlib import Path

class CustomDialog(QDialog):
    run_path = ""
    open_file = ""
    return_state = 0
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)

        self.setWindowTitle("选择以什么方式保存")
        self.ui.dialog_open_button.clicked.connect(self.open_handler)
        self.ui.dialog_new_button.clicked.connect(self.new_handler)
        self.ui.dialog_cancel_button.clicked.connect(self.cancel_handler)

        self.run_path = os.getcwd()

    def open_handler(self):
        print("用户点击了'打开'按钮")
        self.return_state = 1
        self.accept()  # 关闭对话框

    def cancel_handler(self):
        self.return_state = 0
        print("用户点击了'取消'按钮")
        self.reject()  # 关闭对话框

    def new_handler(self):
        self.return_state = 2
        print("用户点击了'新建'按钮")
        self.accept()  # 关闭对话框

    def create_file(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly  # 可以更改为QFileDialog.WriteOnly以仅允许写入
        file_dialog = QFileDialog(self)
        file_path, _ = file_dialog.getSaveFileName(self, '新建文件', '', 'Text Files (*.xlsx);;All Files (*)', options=options)

        if file_path:
            try:
                with open(file_path, 'w') as file:
                    # 可以在这里写入文件内容
                    pass
                print(f'文件已成功创建：{file_path}')
                return file_path
            except Exception as e:
                print(f'创建文件时发生错误：{e}')
                return ""
            
    def Open_file(self):
        dialog = QFileDialog(self)
        dialog.setDirectory(self.run_path)
        dialog.setFileMode(QFileDialog.FileMode.ExistingFiles)
        dialog.setNameFilter("表格 (*.xlsx)")
        dialog.setViewMode(QFileDialog.ViewMode.List)
        if dialog.exec():
            filenames = dialog.selectedFiles()
            if filenames:
                return filenames[0]
            else:
                return ""
    
def Open_file(widegt):
    dialog_main = CustomDialog(widegt)
    if dialog_main.exec():
        match dialog_main.return_state:
            case 1:
                return dialog_main.Open_file()
            case 2:
                return dialog_main.create_file()


class MainWindow(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.setWindowTitle('PyQt File Dialog')
        self.setGeometry(100, 100, 300, 150)

        layout = QGridLayout()
        self.setLayout(layout)

        # file selection
        file_browser_btn = QPushButton('Browse')
        file_browser_btn.clicked.connect(self.open_file_dialog)

        self.file_list = QListWidget(self)

        layout.addWidget(QLabel('Files:'), 0, 0)
        layout.addWidget(self.file_list, 1, 0)
        layout.addWidget(file_browser_btn, 2 ,0)

        self.show()
        

    def open_file_dialog(self):
        Open_file(self)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec())