import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QMessageBox
from PySide6.QtCore import Qt


from Ui_untitled import Ui_MainWindow

# from Ui_file_select_widget import Ui_MainWindow as Second_window

from qt_material import apply_stylesheet


import save_data_in_excel

import nfc_cmd_io as nfc_cmd_io
import ndef as ndef

class MyMainWindow(QMainWindow):
    save_file_addr = ""

    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setWindowTitle("PySide6 Main Window")
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

    def Write_button_clicked(self):
        if not self.process:
            return
        print("Write_button_clicked点击")
        # 从url文本框获取url
        url = self.ui.write_url_widegt.toPlainText()
        print("获取到链接：" + url)
        # 从text文本框获取text
        text = self.ui.write_text_widegt.toPlainText()
        print("获取到文本：" + text)
        # 编码
#     # 编码ndef消息记录
        record1 = ndef.UriRecord(url)
        record2 = ndef.TextRecord(text)
        message = [record1, record2]
        buf = b"".join((ndef.message_encoder(message)))
        lenth = len(bytes.fromhex(buf.hex()))
        print("长度为：" + str(lenth))

        write_hex_str = "03"+ hex(lenth)[2:] + buf.hex()

        input_data = write_hex_str + "\n"  # 换行符是为了模拟用户按下回车

        print(input_data)

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
    app = QApplication(sys.argv)
    main_window = MyMainWindow()
    
    apply_stylesheet(app, theme='light_red.xml')
    
    main_window.show()
    
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
