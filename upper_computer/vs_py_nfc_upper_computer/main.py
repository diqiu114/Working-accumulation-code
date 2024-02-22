import os
import sys
import time
from PySide6.QtCore import Qt
from PySide6.QtWidgets import QApplication, QMainWindow, QMessageBox, QSystemTrayIcon, QMenu

from PySide6.QtGui import QIcon, QAction

from Ui_untitled import Ui_MainWindow

from qt_material import apply_stylesheet
# from Ui_file_select_widget import Ui_MainWindow as Second_window

import save_data_in_excel

import nfc_cmd_io as nfc_cmd_io
import ndef as ndef

class MyMainWindow(QMainWindow):
    save_file_addr = ""

    def __init__(self, run_path, app_name):
        self.basedir = run_path
        self.icon_resource = os.path.join(self.basedir, 'my_resource/nfc_blue.png')
        self.app_name = app_name

        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.create_system_tray_icon()
# class MyMainForm(QMainWindow, Ui_Form):
#     def __init__(self, parent=None):
#         super(MyMainForm, self).__init__(parent)
#         self.setupUi(self)
        self.ui.read_button.clicked.connect(self.Read_button_clicked)
        self.ui.write_button.clicked.connect(self.Write_button_clicked)
        self.ui.open_button.clicked.connect(self.Open_dev_button_clicked)
        self.ui.close_button.clicked.connect(self.Close_dev_button_clicked)
        self.ui.less_button.clicked.connect(self.Less_button_clicked)
        self.ui.lock_button.clicked.connect(self.Lock_button_clicked)
        
        self.ui.save_histry_file_check_box.stateChanged.connect(self.Check_box_changed)

        # self.ui.auto_add_check_box.stateChanged.connect()
    # 设置窗口名称、图标等等
    def create_system_tray_icon(self):
        self.setWindowTitle(self.app_name)
        appIcon = QIcon(self.icon_resource)
        self.setWindowIcon(appIcon)

        tray_icon = QSystemTrayIcon(self)
        tray_icon.setIcon(QIcon(self.icon_resource))  # 设置任务栏图标
        tray_icon.show()
        
    def __del__(self):
        if self.process:
            nfc_cmd_io.Close_device(self.process)

    def Check_box_changed(self, state):
        if state == Qt.CheckState.Checked.value:
            temp_file_addr = save_data_in_excel.Open_file(self)
            # 清空数据
            self.ui.file_save_addr_textEdit.clear()
            self.save_file_addr = ""

            if temp_file_addr:
                self.save_file_addr = temp_file_addr
                self.ui.file_save_addr_textEdit.setText(
                    "当前历史记录文件:" + temp_file_addr
                )
            else:
                self.ui.file_save_addr_textEdit.setText(
                    "文件不存在或被占用"
                )
                # 提示错误:
                dlg = QMessageBox(self)
                dlg.setWindowTitle("错误")
                dlg.setText("文件不存在或被占用")
                dlg.exec()
                # 恢复复选框非选中状态
                self.ui.save_histry_file_check_box.setCheckState(Qt.CheckState.Unchecked)
        
    process = ""
    def Read_button_clicked(self):
        if not self.process:
            self.ui.read_text_widegt.setText("控制台错误")
            return

        print("read button点击")
        # 读取到数据
        ndef_data = nfc_cmd_io.Read_card(self.process)
        # 解码
        try:
            byte_data = bytes.fromhex(ndef_data)
        except ValueError as e:
            self.ui.read_text_widegt.clear()
            self.ui.read_text_widegt.setText("没有nfc消息")
            return
        else:
            pass

        print("读取到消息：")
        for tmp in byte_data:
            print(hex(tmp)[2:], end=" ")
        print("")

        messge_type = byte_data[0]
        messge_lenth = byte_data[1]
        # 切片出ndef数据
        ndef_data = byte_data[2:]

        ndef_decode = ndef.message_decoder(ndef_data)

        # 初始化两个变量用于存储解码后的记录
        text_record = None
        uri_record = None

        # 遍历解码后的NFC记录并分别存储TextRecord和UriRecord
        try:
            for record in ndef_decode:
                if isinstance(record, ndef.TextRecord):
                    text_record = record
                elif isinstance(record, ndef.UriRecord):
                    uri_record = record
        except:
            pass
        else:
            pass

        # 打印解码后的TextRecord和UriRecord
        try:
            text = text_record.text
        except :
            text = " "
        else:
            pass

        try:
            uri = uri_record.uri
        except AttributeError as e:
            uri = " "
        else:
            pass

        self.ui.read_text_widegt.clear()
        self.ui.read_text_widegt.setText(
            "消息类型:" + str(messge_type) + "\n"
            +"消息承载长度：" + str(messge_lenth) + "\n"
            +"链接：" +  uri + "\n"
            +"文本：" + text + "\n"
        )

    # 写入的链接准备
    def add_url(self, to_list):
        if to_list==None:
            return
        # 从url文本框获取url
        url = self.ui.write_url_widegt.toPlainText()
        url_len = len(url)
        if url_len > 0:
            print("获取到链接：" + url)
            record = ndef.UriRecord(url)
            to_list.append(record)
        else:
            print("===== 链接为空 =====")
        return url
        
    def add_text(self, to_list):
        if to_list==None:
            return
        # 从text文本框获取text
        text = self.ui.write_text_widegt.toPlainText()
        if len(text):
            print("获取到文本：" + text)
            # 编码ndef消息记录
            record = ndef.TextRecord(text)
            to_list.append(record)
        else:
            print("===== 文本为空 =====")
        return text

    def Write_button_clicked(self):
        if not self.process:
            return
        print("Write_button_clicked点击")
        message_list = []
        url = self.add_url(message_list)
        text = self.add_text(message_list)
        buf = b"".join((ndef.message_encoder(message_list)))
        lenth = len(bytes.fromhex(buf.hex()))
        print("长度为：" + str(lenth))
        # print("ndef编码的到的字符串：", end=" ")
        # print(buf.hex())
        # format中02x表示以小写方式输出数据长度为2，不足补0，用hex(lenth)[2:]切片
        # 会出现lenth小于0x0f时，0被吞掉
        # "03"描述了后续TLV（类型、长度、值）的格式
        write_hex_str = "03"+ format(lenth, "02x") + buf.hex()
        input_data = write_hex_str + "\n"  # 换行符是为了模拟用户按下回车
        print("编码结束，得到字符串：" + input_data)

        if nfc_cmd_io.Write_card(self.process, input_data):
            # 写入成功,如果需要保存历史则记录历史到表格中
            if self.save_file_addr:
                state = save_data_in_excel.Save_in_file(self.save_file_addr, text, url, input_data)
                if not state:
                    # 提示错误:
                    dlg = QMessageBox(self)
                    dlg.setWindowTitle("错误")
                    dlg.setText("文件不存在或被占用")
                    dlg.exec()
                    # 后续自加操作不再进行
                    return
            else:
                print("self.save_file_addr"+"为空")
            # 复选框选择，则自动加1
            if self.ui.auto_add_check_box.isChecked():
                text = self.ui.write_text_widegt.toPlainText()
                if text:
                    write_text = str(int(text) +1)
                    self.ui.write_text_widegt.setText(write_text)

    def Lock_button_clicked(self):
        if self.process:
            nfc_cmd_io.Lock_card( self.process)

    def Open_dev_button_clicked(self):
        self.process = nfc_cmd_io.Open_device()

    def Close_dev_button_clicked(self):
        if self.process:
            nfc_cmd_io.Close_device(self.process)

    def Less_button_clicked(self):
        text = self.ui.write_text_widegt.toPlainText()
        if text:
            write_text = str(int(text) -1)
            self.ui.write_text_widegt.setText(write_text)


def main():
    app_name = "nfc tool"
    try:
        from ctypes import windll  # Only exists on Windows.
        windll.shell32.SetCurrentProcessExplicitAppUserModelID(app_name)
        time.sleep(1)
    except ImportError:
        pass


    app = QApplication(sys.argv)

    main_window = MyMainWindow(os.path.dirname(__file__), app_name)
    
    apply_stylesheet(app, theme='light_red.xml')
    
    main_window.show()
    main_window.create_system_tray_icon()
    
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
