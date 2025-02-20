import os
import sys
from Ui_untitled import Ui_MainWindow
from PySide6.QtWidgets import (
    QMainWindow,
    QApplication, 
    QWidget, 
    QFileDialog, 
    QGridLayout,
    QPushButton, 
    QDialog,
    QMessageBox,
)

import run

class MyMainWindow(QMainWindow):
    save_file_path = ""
    source_file_path = ""
    title = ""

    def __init__(self, run_path, app_name):
        self.basedir = run_path
        self.app_name = app_name

        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.btn_select_file.clicked.connect(self.btn_select_file_clicked)
        self.ui.btn_save_feil.clicked.connect(self.btn_save_feil_clicked)
        self.ui.btn_start.clicked.connect(self.btn_start_clicked)

    def btn_select_file_clicked(self):
        options = QFileDialog.Options()
        # 使用 getOpenFileName 来选择文件进行读取
        self.source_file_path, _ = QFileDialog.getOpenFileName(self, '选择文件', '', 'Excel Files (*.xlsx);(*.xls);;All Files (*)', options=options)
        self.ui.line_edit_select_file.setText(self.source_file_path)


    def btn_save_feil_clicked(self):
        options = QFileDialog.Options()
        file_dialog = QFileDialog(self)
        self.save_file_path, _ = file_dialog.getSaveFileName(self, '新建文件', '', 'Text Files (*.xlsx);;All Files (*)', options=options)
        self.ui.line_edit_save_file.setText(self.save_file_path)

    def btn_start_clicked(self):
        can_run = True
        if self.ui.line_edit_out_file_title.text() == "":
            can_run = False

        if self.ui.line_edit_save_file.text() == "":
            can_run = False

        if self.ui.line_edit_select_file.text() == "":
            can_run = False

        if can_run == False:
            # 创建一个警告消息框
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Warning)
            msg.setText("信息没填全")
            msg.setWindowTitle("警告")
            msg.setStandardButtons(QMessageBox.Ok)

            # 显示消息框
            msg.exec()
            return
        self.title = self.ui.line_edit_out_file_title.text()
        try:
            run.run(self.source_file_path, self.save_file_path, self.title) 
        except Exception as e:
            # 创建一个警告消息框
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Warning)
            msg.setText(f"转换错误，错误信息：{e}")
            msg.setWindowTitle("警告")
            msg.setStandardButtons(QMessageBox.Ok)
            # 显示消息框
            msg.exec()
            return
        else:
            # 创建一个警告消息框
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Information)
            msg.setText(f"处理完成")
            msg.setWindowTitle("提示")
            msg.setStandardButtons(QMessageBox.Ok)
            # 显示消息框
            msg.exec()
            return
        

def main():
    app_name = "..."

    app = QApplication(sys.argv)

    main_window = MyMainWindow(os.path.dirname(__file__), app_name)
        
    main_window.show()
    
    sys.exit(app.exec())

if __name__ == "__main__":
    main()