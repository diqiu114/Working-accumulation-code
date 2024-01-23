# 逻辑文件

import re
import sys
import binascii
import time
from PySide6.QtCore import QTimer, QUrl
from PySide6.QtWidgets import *
from PySide6.QtSerialPort import QSerialPort, QSerialPortInfo
from PySide6.QtWidgets import QApplication, QMainWindow
from PySide6.QtWebEngineWidgets import *
from Ui_SerialPort import Ui_Form
from PySide6.QtCore import QDate

import json

class MyMainWindow(QMainWindow, Ui_Form):
    rgb_refresh_time_handle = None
    tx_cnt = 0
    rx_cnt = 0

    def __init__(self, parent=None):
        super(MyMainWindow, self).__init__(parent)

        self.rgb_refresh_time_handle = QTimer() #初始化一个定时器

        self.setupUi(self)
        # 设置实例
        self.CreateItems()
        # 设置信号与槽
        self.CreateSignalSlot()
        self.create_my_signal_slot()

        # 设置一些其他项
        self.create_my_something()

    # 设置实例 
    def CreateItems(self):
        # Qt 串口类
        self.com = QSerialPort()
        # Qt 定时器类
        self.timer = QTimer(self) #初始化一个定时器
        self.timer.timeout.connect(self.ShowTime) #计时结束调用operate()方法
        self.timer.start(100) #设置计时间隔 100ms 并启动
    
    # 设置信号与槽
    def CreateSignalSlot(self):
        self.Com_Open_Button.clicked.connect(self.Com_Open_Button_clicked) 
        self.Com_Close_Button.clicked.connect(self.Com_Close_Button_clicked) 
        self.Send_Button.clicked.connect(self.SendButton_clicked) 
        self.Com_Refresh_Button.clicked.connect(self.Com_Refresh_Button_Clicked) 
        self.com.readyRead.connect(self.Com_Receive_Data) # 接收数据
        self.hexSending_checkBox.stateChanged.connect(self.hexShowingClicked)
        self.hexSending_checkBox.stateChanged.connect(self.hexSendingClicked)

    def create_my_signal_slot(self):
        self.radioBtn_sim_esp32.toggled.connect(self.send_get_band_info_cmd_set)

    def create_my_something(self):
        self.send_timer = QTimer(self)
        self.send_timer.timeout.connect(self.send_get_band_info_cmd)
        
    def send_get_band_info_cmd(self):
        send_data = {
            "info_get": {}
        }
        send_data_str = json.dumps(send_data)
        self.Com_Send_Data(send_data_str)

    def send_get_band_info_cmd_set(self):
        if self.radioBtn_sim_esp32.isChecked():
            self.send_timer.start(1000)
        else:
            self.send_timer.stop()

    # ====================== btn sim 回调 ======================

    def btn_sim_open_cb(self):
        pass

    def btn_sim_colse_cb(self):
        pass

    def btn_sim_cmd_analyse(self, json_str =""):
        # print("接受数据：" + repr(json_str))  # 打印原始字符串，查看是否有额外的字符

        try:
            # 移除字符串前后的空白字符和额外的非 JSON 字符
            cleaned_str = json_str.strip().rstrip('\x00')
            data = json.loads(cleaned_str)
            # print(data["btn_get"])
            # ... 剩余的处理逻辑
        except json.JSONDecodeError as e:
            print("JSON 解析错误: ", e)
            # 在这里处理 JSON 解析错误，确保不会访问未定义的变量
            return  # 返回，避免执行后面的代码
        if data["btn_get"] == True:
            send_data = {
                "btn_data": {
                    "pre": 0,
                    "next": 0,
                    "ok":0,
                    "exit":0,
                    "menu":0
                }
            }
            if self.pushButton_pre.isDown():
                send_data["btn_data"]["pre"] = 1
            if self.pushButton_next.isDown():
                send_data["btn_data"]["next"] = 1
            if self.pushButton_ok.isDown():
                send_data["btn_data"]["ok"] = 1
            if self.pushButton_exit.isDown():
                send_data["btn_data"]["exit"] = 1
            if self.pushButton_menu.isDown():
                send_data["btn_data"]["menu"] = 1
            send_data_str = json.dumps(send_data)
            # print(send_data_str)
            try:
                self.Com_Send_Data(str(send_data_str)) 
            except:
                QMessageBox.critical(self, '异常', '十六进制发送错误')
                return
        

    # 跳转到 GitHub 查看源代码
    def Goto_GitHub(self):
        self.browser = QWebEngineView()
        self.browser.load(QUrl('https://www.youdao.com/'))
        self.setCentralWidget(self.browser)
    
    # 显示时间
    def ShowTime(self):
        pass
        # self.Time_Label.setText(time.strftime("%B %d, %H:%M:%S", time.localtime()))

    # 串口发送数据
    def Com_Send_Data(self, text = None):
        if text:
            txData = text
        else:
            txData = self.textEdit_Send.toPlainText()

        print("发送数据" + txData)
        
        self.tx_cnt += len(txData)
        self.label_tx_cnt.setText(str(self.tx_cnt))

        if len(txData) == 0 :
            return
        if self.hexSending_checkBox.isChecked() == False:
            self.com.write(txData.encode('UTF-8'))
        else:
            Data = txData.replace(' ', '')
            # 如果16进制不是偶数个字符, 去掉最后一个, [ ]左闭右开
            if len(Data)%2 == 1:
                Data = Data[0:len(Data)-1]
            # 如果遇到非16进制字符
            if Data.isalnum() is False:
                QMessageBox.critical(self, '错误', '包含非十六进制数')
            try:
                hexData = binascii.a2b_hex(Data)
            except:
                QMessageBox.critical(self, '错误', '转换编码错误')
                return
            # 发送16进制数据, 发送格式如 ‘31 32 33 41 42 43’, 代表'123ABC'
            try:
                print(hexData.hex())
                self.com.write(hexData) 
            except:
                QMessageBox.critical(self, '异常', '十六进制发送错误')
                return
                
                
    
    # 串口接收数据
    def Com_Receive_Data(self):
        
        try:
            rxData = bytes(self.com.readAll())
        except:
            QMessageBox.critical(self, '严重错误', '串口接收数据错误')

        self.rx_cnt += len(rxData)
        self.label_rx_cnt.setText(str(self.rx_cnt))
        # =============== 自添加函数 ===============
        if self.radioBtn_sim_enable.isChecked():
            self.btn_sim_cmd_analyse(rxData.decode('UTF-8'))

        # =========================================
        if self.hexShowing_checkBox.isChecked() == False :
            try:
                self.textEdit_Recive.insertPlainText(rxData.decode('UTF-8'))
            except:
                pass
        else :
            Data = binascii.b2a_hex(rxData).decode('ascii')
            # re 正则表达式 (.{2}) 匹配两个字母
            hexStr = ' 0x'.join(re.findall('(.{2})', Data))
            # 补齐第一个 0x
            hexStr = '0x' + hexStr
            self.textEdit_Recive.insertPlainText(hexStr)
            self.textEdit_Recive.insertPlainText(' ')

        # 将光标移动到文本的末尾，以确保最后一行可见
        cursor = self.textEdit_Recive.textCursor()
        cursor.movePosition(cursor.MoveOperation.End)
        self.textEdit_Recive.setTextCursor(cursor)
        
     
    # 串口刷新
    def Com_Refresh_Button_Clicked(self):
        self.Com_Name_Combo.clear()
        com = QSerialPort()
        com_list = QSerialPortInfo.availablePorts()
        for info in com_list:
            com.setPort(info)
            if com.open(QSerialPort.ReadWrite):
                self.Com_Name_Combo.addItem(info.portName())
                com.close()
    
    # 16进制显示按下   
    def hexShowingClicked(self):
        if self.hexShowing_checkBox.isChecked() == True:
            # 接收区换行
            self.textEdit_Recive.insertPlainText('\n')
    
    # 16进制发送按下   
    def hexSendingClicked(self):
        if self.hexSending_checkBox.isChecked() == True:
            pass
    
    # 发送按钮按下
    def SendButton_clicked(self):
        self.Com_Send_Data()

        
    # 串口刷新按钮按下
    def Com_Open_Button_clicked(self):
        #### com Open Code here ####
        comName = self.Com_Name_Combo.currentText()
        comBaud = int(self.Com_Baud_Combo.currentText())
        self.com.setPortName(comName)
        try:
            if self.com.open(QSerialPort.ReadWrite) == False:
                QMessageBox.critical(self, '严重错误', '串口打开失败')
                return
        except:
            QMessageBox.critical(self, '严重错误', '串口打开失败')
            return
        self.Com_Close_Button.setEnabled(True)
        self.Com_Open_Button.setEnabled(False)
        self.Com_Refresh_Button.setEnabled(False)
        self.Com_Name_Combo.setEnabled(False)
        self.Com_Baud_Combo.setEnabled(False)
        self.Com_isOpenOrNot_Label.setText('  已打开')
        self.com.setBaudRate(comBaud)
    
    def Com_Close_Button_clicked(self):
        self.com.close()
        self.Com_Close_Button.setEnabled(False)
        self.Com_Open_Button.setEnabled(True)
        self.Com_Refresh_Button.setEnabled(True)
        self.Com_Name_Combo.setEnabled(True)
        self.Com_Baud_Combo.setEnabled(True)
        self.Com_isOpenOrNot_Label.setText('  已关闭')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    myWin = MyMainWindow()
    myWin.show()
    sys.exit(app.exec())
    
