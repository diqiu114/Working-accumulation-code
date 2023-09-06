import sys
from PySide6.QtWidgets import QApplication, QMainWindow
from Ui_untitled import Ui_MainWindow

import test
import ndef as ndef


class MyMainWindow(QMainWindow):
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
        # self.ui.auto_add_check_box.stateChanged.connect()

    def __del__(self):
        if self.process:
            test.Close_device(self.process)


    process = ""
    def Read_button_clicked(self):
        if not self.process:
            self.ui.read_text_widegt.setText("控制台错误")
            return

        print("read button点击")
        # 读取到数据
        ndef_data = test.Read_card(self.process)
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
        for record in ndef_decode:
            if isinstance(record, ndef.TextRecord):
                text_record = record
            elif isinstance(record, ndef.UriRecord):
                uri_record = record

        # 打印解码后的TextRecord和UriRecord
        if text_record:
            print("TextRecord:", text_record.text)
        if uri_record:
            print("UriRecord:", uri_record.uri)

        self.ui.read_text_widegt.clear()
        self.ui.read_text_widegt.setText(
            "消息类型:" + str(messge_type) + "\n"
            +"消息承载长度：" + str(messge_lenth) + "\n"
            +"链接：" +  uri_record.uri + "\n"
            +"文本：" + text_record.text + "\n"
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

        # 复选框选择，则自动加1
        if test.Write_card(self.process, input_data):
            if self.ui.auto_add_check_box.isChecked():
                text = self.ui.write_text_widegt.toPlainText()
                if text:
                    write_text = str(int(text) +1)
                    self.ui.write_text_widegt.setText(write_text)
            

    def Open_dev_button_clicked(self):
        self.process = test.Open_device()

    def Close_dev_button_clicked(self):
        if self.process:
            test.Close_device(self.process)

    def Less_button_clicked(self):
        text = self.ui.write_text_widegt.toPlainText()
        if text:
            write_text = str(int(text) -1)
            self.ui.write_text_widegt.setText(write_text)

def main():
    app = QApplication(sys.argv)
    main_window = MyMainWindow()
    main_window.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()

# def main():
#     #固定的，PyQt5程序都需要QApplication对象。sys.argv是命令行参数列表，确保程序可以双击运行
#     # 这里用的是qtside6
#     app = QApplication(sys.argv)
#     #初始化
#     myWin = MyMainForm()
#     #将窗口控件显示在屏幕上
#     myWin.show()
#     #程序运行，sys.exit方法确保程序完整退出。
#     sys.exit(app.exec())

# if __name__ == '__main__':
#     main()