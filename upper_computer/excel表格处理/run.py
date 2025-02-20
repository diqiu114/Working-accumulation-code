#-*- coding:utf8 -*-
import os
import xlrd
from openpyxl import Workbook
from openpyxl import load_workbook
from openpyxl.styles import Alignment

#将指定的xls文件转换为xlsx格式
def xls_to_xlsx(src_file_path,dst_file_path):
    """
    将指定的xls文件转换为xlsx格式
    :param src_file_path: xls文件路径
    :param dst_file_path: xlsx文件路径
    """
    #打开xls文件
    wb_xls = xlrd.open_workbook(f'{src_file_path}')
    #获取所有sheet名称
    names = wb_xls.sheet_names()
    #我们以第一个sheet内容复制到xlsx文件为例，如有多个sheet要复制加循环即可
    #获取xls文件第一个sheet对象
    ws_xls = wb_xls.sheet_by_name(names[0])
    #查看第一个sheet有多少行和列数据
    nrows = ws_xls.nrows
    ncols = ws_xls.ncols
    print(nrows,ncols)
    
    #读取xls第一个sheet内容存到写入列表中
    sheet_msg_xls = []
    for i in range(nrows):
        sheet_msg_xls.append(ws_xls.row_values(i))
    print(len(sheet_msg_xls))
    #创建xlsx文件并写入到对应文件中，一般文件同名,sheet名称一致
    wb_xlsx = Workbook()
    #在xlsx创建同名sheet
    ws_xlxs = wb_xlsx.create_sheet(f'{names[0]}')
    #把xls sheet内容写入到 xlsx同名sheet中
    for row in sheet_msg_xls:
        #一行一行的写入
        ws_xlxs.append(row)
    new_sheet_names = wb_xlsx.sheetnames
    del wb_xlsx[new_sheet_names[0]]
    #保存xlsx格式文件
    wb_xlsx.save(f'{dst_file_path}')

def run(in_file_path = "", out_file_path = "", title = ""):
    # print(f"{in_file_path}, {out_file_path}, {title}")
    stash_in_file = "temp.xlsx"
    if os.path.splitext(in_file_path)[1] == ".xls":
        xls_to_xlsx(in_file_path, stash_in_file)
    else:
        stash_in_file = in_file_path
    in_sheet_name = os.path.splitext(os.path.basename(in_file_path))[0]
    #载入工作表
    in_wb = load_workbook(filename = stash_in_file)
    in_sheet = in_wb[in_sheet_name]
    if in_sheet == None:
        in_sheet = in_wb.worksheets[0]
        
    # 旧表筛选重复供应商并保存到数据中
    row_index = 3
    column_index = 1
    data = {}  # 初始化data为一个空字典
    while True:
        cell_value = in_sheet.cell(row=row_index, column=column_index).value
        if cell_value is None:
            break  # 如果当前单元格为空，结束循环
        if cell_value in data:  # 如果data中已有此值
            data[cell_value].append(row_index)  # 将当前行号加入对应的列表
        else:
            data[cell_value] = [row_index]  # 如果是第一次遇到该值，创建新的列表
        row_index += 1

    # 创建新表
    new_wb = Workbook()
    # 新表填入各种工作薄
    new_sheets = []
    for sheet_name in data:
        new_sheets.append(new_wb.create_sheet(sheet_name))

    max_column = in_sheet.max_column +1
    #处理各个工作薄
    for new_sheet in new_sheets:
        # 标题
        new_sheet.cell(row=1, column=1).value = new_sheet.title + title
        # 合并单元格
        new_sheet.merge_cells(start_row=1, start_column=1, end_row=1, end_column=max_column)
        # 居中显示
        center_alignment = Alignment(horizontal='center', vertical='center')
        new_sheet.cell(row=1, column=1).alignment  = center_alignment
        # 表格内容里的分类，从旧表复制到新表
        for col in range(1, max_column):
            source_cell = in_sheet.cell(row=2, column=col)
            new_sheet.cell(row=2, column=col).value = source_cell.value
        # 从数据结构中获取到同意名称的多个行数
        in_sheet_row = 3
        for write_row in data[new_sheet.title]:
            # 复制整行数据
            for write_col in range(1, max_column):
                # print(f"{write_row}, {write_col}")
                # 获取源单元格的值
                source_cell = in_sheet.cell(row=write_row, column=write_col)
                # 将值复制到目标单元格
                new_sheet.cell(row=in_sheet_row, column=write_col).value = source_cell.value
            in_sheet_row += 1

    del_sheet_name = new_wb.sheetnames
    del new_wb[del_sheet_name[0]]
    new_wb.save(out_file_path)