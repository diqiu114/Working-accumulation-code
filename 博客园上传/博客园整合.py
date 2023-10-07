import os as os
import shutil as shutil
import chardet as chardet
from urllib import parse


# 给需要解析的文件名
# file_name = "py_file_test.md"
file_name = ""

while True:
    print("输入当前需要整合的mark down文件：")
    file_name = input()

    # 获取所有当前文件夹下所有.md文件
    file_list = os.listdir()

    if(file_name in file_list):
        print("读取文件成功")
        break
    else :
        print("读取文件失败")

file_new_name = file_name

index_file_name = file_new_name.find(".md")
file_new_name = file_new_name[:index_file_name] + "_copy.md"

# print(file_new_name)

print("开始复制源文件")
shutil.copy(file_name, file_new_name)

def get_encoding(filePath):
    with open(filePath,'rb') as f:
        tmp = chardet.detect(f.read())
        return tmp['encoding']

encod = get_encoding(file_new_name)

# 文件文本数据全部记录在内存里
file_data = ""

img_addr = []

with open(file_new_name, "r", encoding=encod ) as f:
    head_index_id = "]("
    tail_index_id = ".assets"
    for line in f:
        if tail_index_id in line:
            # print("原始" + line)
            print("正在格式化图片链接：" + line[:line.find("\n")])
            tail_seq = line.find(tail_index_id)
            head_seq = line.find(head_index_id)

            tail_str = line[tail_seq + len(tail_index_id) :]
            head_str = line[: head_seq + len(head_index_id)]

            img_addr.append(line[head_seq + len(head_index_id): len(line)-2])

            line = head_str + "." + tail_str
            # print(line)
            # print("assets后：" + tail_str)
            # print("](前：" + head_str)
        #处理后数据全部写入
        file_data += line
#写入文本
with open(file_new_name, "w", encoding=encod ) as f:
    f.write(file_data)

print("格式化成功")

# 转移文本到新文件夹
new_file_addr = "a_cnblogs/"
if not os.path.exists(new_file_addr):
    os.makedirs(new_file_addr)
shutil.copy(file_new_name, new_file_addr)

print("正在删除临时文件")
if file_new_name in os.listdir():
    os.remove(file_new_name)

# 转移图片到新文件夹
print("正在转移图片到新文件夹：")
for str in img_addr:
    shutil.copy(parse.unquote(str), new_file_addr)
    print("转移成功：" + parse.unquote(str))

input("所有文件已整合到：" + new_file_addr + "，按任意键结束")