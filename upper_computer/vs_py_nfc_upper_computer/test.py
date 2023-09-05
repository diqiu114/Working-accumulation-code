import subprocess
import ndef as ndef
# 启动一个控制台应用程序
print("启动一个控制台应用程序")
process = subprocess.Popen(["Release/Project1.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
# 向控制台应用程序的stdin写入数据
# input_data = "world!\n"  # 换行符是为了模拟用户按下回车
# process.stdin.write(input_data)
# process.stdin.flush()  # 刷新输入流

# 读取控制台应用程序的输出
output = process.stdout.read(2000)
print(output)

# 如果需要发送更多输入，重复上述步骤
# ...

# 编码ndef消息记录
# record1 = ndef.UriRecord(f"https://www.bilibili.com")
# record2 = ndef.TextRecord(f"杨志强大帅哥")
# message = [record1, record2]
# buf = b"".join((ndef.message_encoder(message)))
# lenth = len(bytes.fromhex(buf.hex()))
# print("长度为：" + str(lenth))

# write_hex_str = "03"+ hex(lenth)[2:] + buf.hex()

# input_data = write_hex_str + "\n"  # 换行符是为了模拟用户按下回车

# print("====pyton写入：" + input_data)

# process.stdin.write(input_data)
# process.stdin.flush()  # 刷新输入流
# output = process.stdout.read(2000)
# print(output)

# 关闭控制台应用程序的stdin
process.stdin.close()

# 等待控制台应用程序完成
process.wait()

# 关闭所有流
process.stdout.close()
process.stderr.close()

print("运行完成")