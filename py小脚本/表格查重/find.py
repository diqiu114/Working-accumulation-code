# 这个小脚本用来寻找同一文件夹下的.xlsx、.xls表格下特定列/行下的重复数据
# 要求特定格式：并以空格分隔

import os
import xlrd

 
file_path = os.getcwd()
print("当前脚本工作路径：" + file_path)
file_ext = ['.xls', '.xlsx']
 


i = 0
filePath = ""
for path in os.listdir(file_path): 
    path_list = os.path.join(file_path, path)  # 连接当前目录及文件或文件夹名称
    if os.path.isfile(path_list):  # 判断当前文件或文件夹是否是文件，把文件夹排除
        if (os.path.splitext(path_list)[1]) in file_ext:  # 判断取得文件的扩展名是否是.xls、.xlsx
            if "~$" not in path_list:
                filePath = path_list
print("当前读取到的文件路径：" + filePath)
xlsx = xlrd.open_workbook(filePath)
table = xlsx.sheet_by_index(0)


# 获取表格行数
nrows = table.nrows
print("表格一共有",nrows,"行")

# 获取第B列，第二行开始的所有列表值，要求表格固定格式，这一列是物料的位号
name_list = [str(table.cell_value(i, 1)) for i in range(2, nrows)]
# print("第4列所有的值：",name_list)

num = 0
strlist = []
repetitionName = []
for path in name_list:
    # 空格分割数据
    strlist += name_list[num].split(' ')
    num += 1

cnt = 0
for val in strlist:
    circulation = cnt+1
    for val in strlist:
        # 产生重复记录
        if circulation < len(strlist):
            if strlist[cnt] == strlist[circulation]:
                if strlist[cnt] not in repetitionName:
                    repetitionName.append(strlist[cnt])
        circulation += 1
    cnt += 1

print("重复数据有：")
print(repetitionName)

input("按任意键退出")

