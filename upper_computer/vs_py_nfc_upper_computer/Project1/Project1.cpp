// Project1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "windows.h"
#include "hfrdapi.h"

//#include <sstream>
#include <vector>
#include <map>
#include<iomanip>

using namespace std;

//#define   // DEBUG_OUT 
#define   CMD_OUT   std::cout

#define RETURN_FALSE_FLAGE      "_false_"
#define RETURN_TURE_FLAGE      "_true_"
#define NDEF_START_PAGE_DEC         4   // ndef起始区域
#define NDEF_END_PAGE_DEC           39  
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
    // 只有失败有命令输出
    if (error != 0) {
        CMD_OUT << RETURN_FALSE_FLAGE << error << endl;
        return false;
    }
    //CMD_OUT << RETURN_TURE_FLAGE << endl;
    return true;
}

int Connect_nfc_card(HID_DEVICE device)
{
    WORD status;
    WORD serch = 0;

    // 读取当前在读卡器上的nfc卡
    status = TyA_Request(device, 0x52, &serch);
    if(status==0) {
        // DEBUG_OUT << "卡信息:";
        // DEBUG_OUT << hex << serch << endl;
    } else {
        // DEBUG_OUT << "TyA_Anticollision" << endl;
        // DEBUG_OUT << "失败原因：" << status << endl;
        return status;
    }

    // 获取卡序列并激活卡
    BYTE snr[20] = {0};
    BYTE snr_len;
    status = TyA_UL_Select(device,  snr,  &snr_len);
    if(status==0) {
        // DEBUG_OUT << "获取序列号：";
        for(int i = 0; i < snr_len; i++) {
            // DEBUG_OUT << hex << (int)snr[i] << " ";
        }
        // DEBUG_OUT << endl;
    } else {
        // DEBUG_OUT << "TyA_UL_Select 失败" << endl;
        // DEBUG_OUT << "失败原因：" << status << endl;
        return status;
    }

    // 获取卡信息
    BYTE buffer[20] = {0};
    BYTE buffer_lenth = 0;
    //status = TyA_Anticollision(g_hDevice, 0,  buffer, &buffer_lenth);
    status = TyA_UL_GetVersion(device, buffer, &buffer_lenth);
    if(status==0) {
        // DEBUG_OUT << "获取到版本信息为：";
        for (int i = 0; i < buffer_lenth; i++) {
            // DEBUG_OUT << hex << (int)buffer[i] << " ";
        }
        // DEBUG_OUT << endl;
    } else {
        // DEBUG_OUT << "TyA_NTAG_GetVersion 失败" << endl;
        // DEBUG_OUT << "失败原因：" << status << endl;
        return status;
    }

    return 0;
}

int Wirte_card(HID_DEVICE device, string hexString)
{
    WORD status = 0;
    // 04扇区写网址
    // DEBUG_OUT << "写扇区：" << endl;
    // std::string hexString = "03189101075502676d782e61745101095402656ee5bf97e5bcba"; // 十六进制字符串
    //string hexString;

    // 将十六进制字符串转换为字节数组
    std::vector<unsigned char> byteArray = hexStringToByteArray(hexString);

    // 输出字节数组
    int write_lenth = byteArray.size();
    // DEBUG_OUT << "byteArray.size：" << dec << write_lenth << endl;
    // write_lenth取4的整数倍，因为一个页是4字节，这样可以避免对write_hex_buffer的越界访问
    if(write_lenth % 4)
        write_lenth += 4 - write_lenth % 4;
    // DEBUG_OUT << "write_lenth取4整数倍：" << dec << write_lenth << endl;
    BYTE *write_hex_buffer = nullptr;
    BYTE *read_hex_buffer = nullptr;

    if(write_lenth < 1) {
        cout << "没有写卡数据" << endl;
        status = -1;
        write_hex_buffer = new BYTE[1];
        goto end;
    } else if (write_lenth > (NDEF_END_PAGE_DEC - NDEF_START_PAGE_DEC) * 4) { // 超出能写范围
        cout << "超出能写范围" << endl;
        status = -1;
        write_hex_buffer = new BYTE[1];
        goto end;
    } else {
        write_hex_buffer = new BYTE[write_lenth +2];
        ::memset(write_hex_buffer, 0, write_lenth);
        //BYTE write_hex_buffer[];
        int hex_buffer_tempcnt = 0;
        for (const BYTE& byte : byteArray) {
            //// DEBUG_OUT << static_cast<int>(byte) << " "; // 将字节作为整数输出
            write_hex_buffer[hex_buffer_tempcnt] = byte;
            hex_buffer_tempcnt++;
        }
        //// DEBUG_OUT << std::endl;

        int addr_cnt = 0;
        int temp_cnt = 0;
        // 单页写
        for(int cnt = NDEF_START_PAGE_DEC; cnt < NDEF_END_PAGE_DEC; cnt++) {
            temp_cnt = addr_cnt*4;
            // 避免越界
            if(temp_cnt >= write_lenth)
                break;
            status = TyA_UL_Write(device, cnt, &write_hex_buffer[temp_cnt]);

            if(status==0) {
            
            } else {
                // DEBUG_OUT << "TyA_UL_Write 错误" << endl;
                // DEBUG_OUT << "错误原因:" << status;

                goto end;
            }
            // DEBUG_OUT << "写：" << temp_cnt << "：";
            int temp = 0;
            for(int buffer_cnt = temp_cnt; buffer_cnt < temp_cnt +4; buffer_cnt++) {
                temp = write_hex_buffer[buffer_cnt];
                // DEBUG_OUT << hex << temp << " ";
            }
            // DEBUG_OUT << endl;
            addr_cnt ++;
        }

        // 校验
        // 读flash
        addr_cnt = 0;
        temp_cnt = 0;
        // 单页读
        int read_lenth = write_lenth;
        // read_lenth取16的整数倍，因为读一次是16字节，这样可以避免对read_hex_buffer的越界访问
        if(read_lenth % 16)
            read_lenth += 16 - read_lenth % 16;

        read_hex_buffer = new BYTE[read_lenth +2];
        ::memset(read_hex_buffer, 0, read_lenth);
        BYTE read_lenth_temp = 0;
        // page += 4一次性会读4页
        for(int page = NDEF_START_PAGE_DEC; page < NDEF_END_PAGE_DEC; page += 4) {
            // 一次性会读16个字节
            temp_cnt = addr_cnt*16;
            // 避免越界
            if(temp_cnt >= read_lenth)
                break;
            status = TyA_UL_Read(device, page, &read_hex_buffer[temp_cnt], &read_lenth_temp);

            if(status==0) {
            
            } else {
                // DEBUG_OUT << "TyA_UL_Write 错误" << endl;
                // DEBUG_OUT << "错误原因:" << status;
                goto end;
            }
            // DEBUG_OUT << "读到长度：" << dec << (int)read_lenth_temp << "， ";
            // DEBUG_OUT << "读：" << temp_cnt << "：";
            int temp = 0;
            for(int buffer_cnt = temp_cnt; buffer_cnt < temp_cnt +16; buffer_cnt++) {
                temp = read_hex_buffer[buffer_cnt];
                // DEBUG_OUT << hex << temp << " ";
            }
            // DEBUG_OUT << endl;
            addr_cnt ++;
        }

        //校验
        if(memcmp(read_hex_buffer, write_hex_buffer, write_lenth)!=0) {
            cout << "校验不过" << endl;
            status = -2; // 校验不过
            goto end;
        }
    }


end:
    if (read_hex_buffer!=nullptr) {
        delete[] read_hex_buffer;
    }
    delete[] write_hex_buffer;
    return status;
}

int Read_card(HID_DEVICE device, BYTE* read_buffer, int lenth)
{
    int status = 0;
    int addr_cnt = 0;
    int temp_cnt = 0;
    // 单页读
    int read_lenth = lenth;
    // read_lenth取16的整数倍，因为读一次是16字节，这样可以避免对read_hex_buffer的越界访问
    if(read_lenth % 16)
        read_lenth += 16 - read_lenth % 16;

    BYTE* read_hex_buffer = nullptr;
    read_hex_buffer = new BYTE[read_lenth +2];
    ::memset(read_hex_buffer, 0, read_lenth);
    BYTE read_lenth_temp = 0;
    // page += 4一次性会读4页
    for (int page = NDEF_START_PAGE_DEC; page < NDEF_END_PAGE_DEC; page += 4) {
        int temp = 0;
        // 一次性会读16个字节
        temp_cnt = addr_cnt * 16;
        // 避免越界
        if (temp_cnt >= read_lenth)
            break;

        status = TyA_UL_Read(device, page, &read_hex_buffer[temp_cnt], &read_lenth_temp);

        if (status == 0) {

        }
        else {
            // DEBUG_OUT << "TyA_UL_Write 错误" << endl;
            // DEBUG_OUT << "错误原因:" << status;
            goto end;
        }
        // DEBUG_OUT << "读到长度：" << dec << (int)read_lenth_temp << "， ";
        // DEBUG_OUT << "读：" << temp_cnt << "：";

        for (int buffer_cnt = temp_cnt; buffer_cnt < temp_cnt + 16; buffer_cnt++) {
            temp = read_hex_buffer[buffer_cnt];
            // DEBUG_OUT << hex << temp << " ";
        }
        // DEBUG_OUT << endl;
        addr_cnt++;
    }

    end:
        if (status==0) {
            memcpy(read_buffer, read_hex_buffer, lenth);
        }
        if (read_hex_buffer!=nullptr) {
            delete[] read_hex_buffer;
        }
        return status;
}

int Lock_card(HID_DEVICE device)
{
    // 根据数据手册，锁卡就是对page页的写权限失效，那么锁卡就只需要对
    // Dynamic Lock Bytes和Static Lock Bytes每位全写1即可，就会3h后的所有页
    int status = 0;
    // 锁静态页，即写Static Lock Bytes
    BYTE read_buffer_static[4] = {0};
    BYTE read_buffer_dynamic[4] = {0};

    BYTE temp_lenth = 0;
    TyA_UL_FastRead(device, 2, 2, read_buffer_static, &temp_lenth);
    // 除能写权限
    read_buffer_static[2] = 0xff;
    read_buffer_static[3] = 0xff;
    // 这里必须两个区域全部写完，不能因为前一个TyA_UL_Write出错就返回
    status = TyA_UL_Write(device, 2, read_buffer_static);
    for(int cnt = 0; cnt < sizeof(read_buffer_dynamic) / sizeof(*read_buffer_dynamic); cnt++) {
        read_buffer_dynamic[cnt] = 0xff;
        //DEBUG_OUT << (int)read_buffer_dynamic[cnt];
    }
    if(status==0) {
        status = TyA_UL_Write(device, 40, read_buffer_dynamic);
    }
    // 实验证明，调用函数TyA_UL_Write对锁卡标位置位写时，尽管已经锁卡，但是函数并不会返回错误
    //DEBUG_OUT << status << endl;
    return status;
}

enum
{
    Wirte_Card = 1,
    Read_Card,
    Lock_Card,
    Close_Device,
};

static HID_DEVICE g_hDevice = HID_DEVICE(-1);  //g_hDevice must be initialized as -1 before use
int main()
{
    int status;
    string get_cmd_str;
    map<string, int> cmd_map;
    cmd_map["写卡"] = Wirte_Card;
    cmd_map["读卡"] = Read_Card;
    cmd_map["锁卡"] = Lock_Card;
    cmd_map["关闭读卡器"] = Close_Device;

    if(FALSE != Sys_IsOpen(g_hDevice))
    {
        status = Sys_Close(&g_hDevice);
        if(status != 0)
        {
            // DEBUG_OUT << "打开失败";
        }
    }
    
    //Connect
    status = Sys_Open(&g_hDevice, 0, 0x0416, 0x8020);
    if(status != 0)
    {
        // DEBUG_OUT << "打开失败";
        return -1;
    }
    // DEBUG_OUT << "打开成功";

    //========== Init the reader before operating the card ==========
    //Close antenna of the reader
    status = Sys_SetAntenna(g_hDevice, 0);
    if(status != 0)
    {
        // DEBUG_OUT << "Sys_SetAntenna failed !";
        return 0;
    }
    Sleep(5); //Appropriate delay after Sys_SetAntenna operating
    
    //Set the reader's working mode
    status = Sys_InitType(g_hDevice, 'A');
    if(status != 0)
    {
        // DEBUG_OUT << "Sys_InitType failed !";
        return 0;
    }
    Sleep(5); //Appropriate delay after Sys_InitType operating
    
    //Open antenna of the reader
    status = Sys_SetAntenna(g_hDevice, 1);
    if(status != 0)
    {
        // DEBUG_OUT << "Sys_SetAntenna failed !";
        return 0;
    }
    Sleep(5); //Appropriate delay after Sys_SetAntenna operating
    // 蜂鸣器叫两声
    Sys_SetBuzzer(g_hDevice, 5);
    Sleep(100);
    Sys_SetBuzzer(g_hDevice, 5);

    //Tips
    // DEBUG_OUT << "Connect reader succeed !" << endl;	
    // DEBUG_OUT << "请给命令" << endl;
    // 连接、激活卡
    while (1) {
        std::cin >> get_cmd_str;
        switch (cmd_map[get_cmd_str]) {
            case Wirte_Card: {
                // 连接卡
                if (!Error_check(Connect_nfc_card(g_hDevice))) {
                    break;
                }
                CMD_OUT << RETURN_TURE_FLAGE << endl;
                // 写入卡
                // DEBUG_OUT << "请输入写入的hex串：" << endl;
                string hexString;
                std::cin >> hexString;
                if (!Error_check(Wirte_card(g_hDevice, hexString))) {
                    Sys_SetBuzzer(g_hDevice, 30);
                    break;
                }
                CMD_OUT << RETURN_TURE_FLAGE << endl;
                Sys_SetBuzzer(g_hDevice, 5);
            }break;

            case Read_Card: {
                constexpr int lenth = (NDEF_END_PAGE_DEC - NDEF_START_PAGE_DEC) * 4;
                BYTE buffer[lenth];
                if (!Error_check(Connect_nfc_card(g_hDevice)))
                    break;
                if (!Error_check(Read_card(g_hDevice, buffer, lenth)))
                    break;
                for (int hex_val : buffer) {
                    // 格式化输出，不足填零
                     CMD_OUT << setw(2) << setfill('0') << hex << hex_val;
                }
                 CMD_OUT << endl;
                 Sys_SetBuzzer(g_hDevice, 5);
            }break;

            case Lock_Card: {
                if (!Error_check(Connect_nfc_card(g_hDevice)))
                    break;
                if (!Error_check(Lock_card(g_hDevice)))
                    break;
                CMD_OUT << RETURN_TURE_FLAGE << endl;
                Sys_SetBuzzer(g_hDevice, 5);
            }break;

            case Close_Device :{
                goto out_even;   
            }
            default: {
                CMD_OUT << RETURN_FALSE_FLAGE << endl;
            }break;
        }
        Sleep(10);
    }

out_even:

    // 蜂鸣器叫声
    Sys_SetBuzzer(g_hDevice, 30);
    Sleep(300);
    if(FALSE != Sys_IsOpen(g_hDevice))
    {
        status = Sys_Close(&g_hDevice);
        if (status == 0)
        {
            // DEBUG_OUT << "关闭成功" << endl;
        }
        else
        {
            // DEBUG_OUT << "关闭失败" << endl;
            // DEBUG_OUT << "失败原因:" << status;
        }
    }

    return status;
}
