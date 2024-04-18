from PySide6.QtWidgets import QApplication, QMainWindow
from PySide6.QtCore import QStringListModel, Signal, Qt
 
import sys
from Ui_untitled import Ui_MainWindow

from threading import Thread
from my_ble import MyBle

SERVICE_UUID = "000000ff-0000-1000-8000-00805f9b34fb"
# CHARACTERISTIC_UUID = "0000ff01-0000-1000-8000-00805f9b34fb"
CHARACTERISTIC_UUID = "0000ff02-0000-1000-8000-00805f9b34fb"

class MyMainWindow(QMainWindow, MyBle):
    ble_updata = Signal()
    ble_connet_state = Signal(bool)
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ble_name_list = []
        self.slm = QStringListModel(); #创建mode
        self.ui.listView.setModel(self.slm)##绑定 listView 和 model

        self.banding()

        self.ui_test()

    def ui_test(self):
        self.ui.textEdit_3.setText("sdfsdfsf")

    def connect_ble(self):
        # 连接前删除蓝牙对象
        self.disconnet_ble()
        index = self.ui.listView.currentIndex()
        if index.isValid():
            name = self.slm.data(index, Qt.DisplayRole)
            print("即将连接到：" + name)
            super().connect_ble(name)
    
    def connect_state(self, state = False):
        self.ble_connet_state.emit(state)

    def connect_state_ui(self, state = False):
        self.ui.textEdit_3.clear()
        if state:
            self.ui.textEdit_3.setText("蓝牙连接成功")
            self.notify_ble(CHARACTERISTIC_UUID)
        else:
            self.ui.textEdit_3.setText("蓝牙连接失败")

    def notify_update(self, sender, data):
        self.ui.textEdit_3.clear()
        self.ui.textEdit_3.setText(data)
        print(sender , data)

    def test_lick(self):
        print("click")
        str = self.ui.textEdit.toPlainText()
        self.write_ble(CHARACTERISTIC_UUID, str.encode())

    def banding(self):
        self.ui.pushButton.clicked.connect(self.scan_btn_clicked)
        self.ble_updata.connect(self.ble_updata_cb)
        self.ui.pushButton_2.clicked.connect(self.connect_ble)
        # self.ui.pushButton_3.clicked.connect(lambda:(self.notify_ble(CHARACTERISTIC_UUID)))
        self.ui.pushButton_3.clicked.connect(self.test_lick)
        self.ble_connet_state.connect(self.connect_state_ui)

    def scan_btn_clicked(self):
        # 扫描前删除蓝牙对象
        self.disconnet_ble()
        self.scan_ble(2)

    # ======== 蓝牙 ===========
    def ble_updata_cb(self):
        self.slm.setStringList(self.ble_name_list)

    # 蓝牙部分，扫描结束回调
    def scan_ble_end(self):
        self.ble_name_list = self.ble_dev_list_queue.get_nowait()
        if self.ble_name_list == None:
            print("扫描失败")
            return
        self.ble_updata.emit()
        
def main():
    app = QApplication(sys.argv)
    main_window = MyMainWindow()
    main_window.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
    

