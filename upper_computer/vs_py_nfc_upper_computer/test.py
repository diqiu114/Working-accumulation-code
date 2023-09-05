import subprocess
import ndef as ndef
import os as os
import time

def Read_card(process):
    process.stdin.write("读卡" + "\n")
    process.stdin.flush()
    return process.stdout.readline()

def Write_card(process, write_data):
    process.stdin.write("写卡" + "\n")
    process.stdin.flush()  # 刷新输入流
    time.sleep(0.05)
    write_state = process.stdout.readline()
    if "_false_" in write_state :
        print("写卡前准备失败：" + write_state)
        return False
    process.stdin.write(write_data + "\n")
    process.stdin.flush()  # 刷新输入流
    time.sleep(0.05)
    write_state = process.stdout.readline()
    if "_false_" in write_state :
        print("写卡失败：" + write_state)
        return False
    return True

def Open_device():
    process = subprocess.Popen(["Release/Project1.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    time.sleep(0.5)
    return process

def Close_device(process):
        # 关闭控制台应用程序的stdin
    process.stdin.close()

    # 等待控制台应用程序完成
    process.wait()

    # 关闭所有流
    process.stdout.close()
    process.stderr.close()

    print("运行完成")

def Test(process):
    # 编码ndef消息记录
    record1 = ndef.UriRecord(f"https://www.bilibili.com")
    record2 = ndef.TextRecord(f"杨志强大帅哥...")
    message = [record1, record2]
    buf = b"".join((ndef.message_encoder(message)))
    lenth = len(bytes.fromhex(buf.hex()))
    print("长度为：" + str(lenth))

    write_hex_str = "03"+ hex(lenth)[2:] + buf.hex()

    input_data = write_hex_str + "\n"  # 换行符是为了模拟用户按下回车

    print("====pyton写入：" + input_data)
    print(Write_card(process, input_data))
    print(Read_card(process))



