// Project1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "windows.h"
#include "hfrdapi.h"

#include <sstream>
#include <vector>
#include <map>

using namespace std;

#define RETURN_FALSE_FLAGE      "_false_"

// 将十六进制字符转换为对应的整数值
unsigned char hexCharToUint(char c) {
    if (c >= '0' && c <= '9') {
        return static_cast<unsigned char>(c - '0');
    } else if (c >= 'a' && c <= 'f') {
        return static_cast<unsigned char>(c - 'a' + 10);
    } else if (c >= 'A' && c <= 'F') {
        return static_cast<unsigned char>(c - 'A' + 10);
    }
    return 0; // 非法字符，默认返回0
}

// 将十六进制字符串转换为字节数组
std::vector<unsigned char> hexStringToByteArray(const std::string& hexString) {
    std::vector<unsigned char> byteArray;

    for (size_t i = 0; i < hexString.length(); i += 2) {
        unsigned char byte = (hexCharToUint(hexString[i]) << 4) | hexCharToUint(hexString[i + 1]);
        byteArray.push_back(byte);
    }

    return byteArray;
}

bool Error_check(int error)
{
    if (error != 0) {
        cout << RETURN_FALSE_FLAGE << error;
        return false;
    }
    return true;
}

int Connect_nfc_card(HID_DEVICE device)
{
    WORD status;
    WORD serch = 0;

    // 读取当前在读卡器上的nfc卡
    status = TyA_Request(device, 0x52, &serch);
    if(status==0) {
        std::cout << "卡信息:";
        std::cout << hex << serch << endl;
    } else {
        std::cout << "TyA_Anticollision" << endl;
        std::cout << "失败原因：" << status << endl;
        return status;
    }

    // 获取卡序列并激活卡
    BYTE snr[20] = {0};
    BYTE snr_len;
    status = TyA_UL_Select(device,  snr,  &snr_len);
    if(status==0) {
        std::cout << "获取序列号：";
        for(int i = 0; i < snr_len; i++)
            std::cout << hex << (int)snr[i] << " ";
        std::cout << endl;
    } else {
        std::cout << "TyA_UL_Select 失败" << endl;
        std::cout << "失败原因：" << status << endl;
        return status;
    }

    // 获取卡信息
    BYTE buffer[20] = {0};
    BYTE buffer_lenth = 0;
    //status = TyA_Anticollision(g_hDevice, 0,  buffer, &buffer_lenth);
    status = TyA_UL_GetVersion(device, buffer, &buffer_lenth);
    if(status==0) {
        std::cout << "获取到版本信息为：";
        for (int i = 0 ; i < buffer_lenth; i++)
            std::cout << hex << (int)buffer[i] << " ";
        std::cout << endl;
    } else {
        std::cout << "TyA_NTAG_GetVersion 失败" << endl;
        std::cout << "失败原因：" << status << endl;
        return status;
    }

    return 0;
}

int Wirte_card(HID_DEVICE device, string hexString)
{
    WORD status;
    // 04扇区写网址
    std::cout << "写扇区：" << endl;
    // std::string hexString = "03189101075502676d782e61745101095402656ee5bf97e5bcba"; // 十六进制字符串
    //string hexString;

    // 将十六进制字符串转换为字节数组
    std::vector<unsigned char> byteArray = hexStringToByteArray(hexString);

    // 输出字节数组
    int lenth = byteArray.size();
    BYTE *hex_buffer = new BYTE[lenth];
    //BYTE hex_buffer[];
    int hex_buffer_tempcnt = 0;
    for (const BYTE& byte : byteArray) {
        //std::cout << static_cast<int>(byte) << " "; // 将字节作为整数输出
        hex_buffer[hex_buffer_tempcnt] = byte;
        hex_buffer_tempcnt++;
    }
    //std::cout << std::endl;

    int addr_cnt = 0;
    int temp_cnt = 0;
    for(int cnt = 4; cnt < 15; cnt++) {
        temp_cnt = addr_cnt*4;
        status = TyA_UL_Write(device, cnt, &hex_buffer[temp_cnt]);

        if(status==0) {
            
        } else {
            std::cout << "TyA_UL_Write 错误" << endl;
            std::cout << "错误原因:" << status;

            goto end;
        }
        std::cout << "写：" << temp_cnt << "：";
        for(int buffer_cnt = temp_cnt; buffer_cnt < temp_cnt +4; buffer_cnt++) {
            std::cout << hex << (int)hex_buffer[buffer_cnt] << " ";
        }
        std::cout << endl;
        addr_cnt ++;
    }

    // 校验


    delete []hex_buffer;
    end: return status;
}

enum
{
    Wirte_Card = 1,
    Read_Card,

};

static HID_DEVICE g_hDevice = HID_DEVICE(-1);  //g_hDevice must be initialized as -1 before use
int main()
{
    int status;
    
    if(FALSE != Sys_IsOpen(g_hDevice))
    {
        status = Sys_Close(&g_hDevice);
        if(status != 0)
        {
            std::cout << "打开失败";
        }
    }
    
    //Connect
    status = Sys_Open(&g_hDevice, 0, 0x0416, 0x8020);
    if(status != 0)
    {
        std::cout << "打开失败";
        return -1;
    }
    std::cout << "打开成功";
    std::cout << "Hello World!\n";

    //========== Init the reader before operating the card ==========
    //Close antenna of the reader
    status = Sys_SetAntenna(g_hDevice, 0);
    if(status != 0)
    {
        std::cout << "Sys_SetAntenna failed !";
        return 0;
    }
    Sleep(5); //Appropriate delay after Sys_SetAntenna operating
    
    //Set the reader's working mode
    status = Sys_InitType(g_hDevice, 'A');
    if(status != 0)
    {
        std::cout << "Sys_InitType failed !";
        return 0;
    }
    Sleep(5); //Appropriate delay after Sys_InitType operating
    
    //Open antenna of the reader
    status = Sys_SetAntenna(g_hDevice, 1);
    if(status != 0)
    {
        std::cout << "Sys_SetAntenna failed !";
        return 0;
    }
    Sleep(5); //Appropriate delay after Sys_SetAntenna operating
    //Tips
    std::cout << "Connect reader succeed !" << endl;	

    // 连接、激活卡
    string get_cmd_str;
    map<string, int> cmd_map;
    cmd_map["写卡"] = Wirte_Card;
    cmd_map["读卡"] = 1;
    while(1) {
        std::cout << "请给命令" << endl;
        std::cin >> get_cmd_str;
        switch (cmd_map[get_cmd_str]){
            case Wirte_Card: {
                // 连接卡
                if(!Error_check(Connect_nfc_card(g_hDevice)))
                    break;
                // 写入卡
                std::cout << "请输入写入的hex串：" << endl;
                string hexString;
                std::cin >> hexString;
                if(!Error_check(Wirte_card(g_hDevice, hexString)))
                   break;
            }break;

            case Read_Card: {
            
            }break;
            default:
                break;
        }
        Sleep(10);
    }
    



    // 读取4页数据，总共有142字节
    BYTE page_data[1024] = { 0 };
    BYTE page_data_lenth = 0;

    int data_cnt = 0;

    int addr_end = 10;

    int page_data_lenth_cnt = 0;
    int page_data_addr = 0;
    TyA_UL_Read(g_hDevice, page_data_addr, &page_data[page_data_lenth_cnt], &page_data_lenth);
    page_data_lenth_cnt += page_data_lenth; page_data_addr += 4;
    TyA_UL_Read(g_hDevice, page_data_addr, &page_data[page_data_lenth_cnt], &page_data_lenth);
    page_data_lenth_cnt += page_data_lenth; page_data_addr += 4;
    TyA_UL_Read(g_hDevice, page_data_addr, &page_data[page_data_lenth_cnt], &page_data_lenth);
    page_data_lenth_cnt += page_data_lenth; page_data_addr += 4;
    TyA_UL_Read(g_hDevice, page_data_addr, &page_data[page_data_lenth_cnt], &page_data_lenth);
    std::cout << "数据：" << endl;
    for(BYTE data: page_data) {
        printf("%02x", data);
    }



    if(FALSE != Sys_IsOpen(g_hDevice))
    {
        status = Sys_Close(&g_hDevice);
        if (status == 0)
        {
            std::cout << "关闭成功" << endl;
        }
        else
        {
            std::cout << "关闭失败" << endl;
            std::cout << "失败原因:" << status;
        }
    }
}
