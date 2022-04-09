#include "province_information_manager.h"
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

province_information_manager::province_information_manager()
{
    for (int& i : status_of_province) {
        i = 0; // 优先初始化
    }
    try_to_load_province_information_file(); // 用文件初始化
}

void province_information_manager::change_province_status()
{
    string temp_province;
    int temp_status;
    int returned_code;
    while (true) {
        cout << "请输入想要改变 <风险状态> 的 <省级区域名称>：";
        cin >> temp_province;
        returned_code = if_input_province_valid(temp_province);
        if (returned_code != -1) {
            break;
        } else {
            system("cls");
            cout << "输入的 <省级区域名称> 无效！请重新输入" << endl;
        }
    }
    while (true) {
        cout << temp_province << " 当前的状态是：" << status_list[status_of_province[returned_code]] << endl;
        cout << "请输入 <更新后的状态编码> (0=低风险，1=中风险，2=高风险)：";
        cin >> temp_status;
        if (temp_status < 0 || temp_status > 2) {
            system("cls");
            cout << "输入的 <状态编码> 无效！请重新输入" << endl;
        } else {
            status_of_province[returned_code] = temp_status;
            cout << "已将 " << temp_province << " 更新为 " << status_list[temp_status] << " 状态" << endl;
            break;
        }
    }
    write_province_information_file_trunc();
}

void province_information_manager::show_input_province_status()
{
    string temp_province;
    int returned_code;
    while (true) {
        cout << "请输入想要查看 <风险状态> 的 <省级区域名称>：";
        cin >> temp_province;
        returned_code = if_input_province_valid(temp_province);
        if (returned_code != -1) {
            break;
        } else {
            system("cls");
            cout << "输入的 <省级区域名称> 无效！请重新输入" << endl;
        }
    }
    cout << endl;
    cout << temp_province << " 的状态是：" << status_list[status_of_province[returned_code]] << endl;
}

void province_information_manager::show_all_province_status()
{
    bool if_0 = false, if_1 = false, if_2 = false;
    cout << "下面将按照 <状态信息> 输出所有 <省级区域> 的相关信息：" << endl
         << endl;
    cout << "=========================================" << endl;
    //高风险地区：
    cout << endl
         << "  高风险地区：" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 2) {
                if_2 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_2) {
        cout << "    无高风险地区！" << endl;
    }
    //中风险地区：
    cout << endl
         << "  中风险地区：" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 1) {
                if_1 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_1) {
        cout << "    无中风险地区！" << endl;
    }
    //低风险地区：
    cout << endl
         << "  低风险地区：" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 0) {
                if_0 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_0) {
        cout << "    无低风险地区！" << endl;
    }
    cout << endl
         << "=========================================" << endl;
    cout << endl
         << "输出完毕！" << endl;
}

void province_information_manager::try_to_load_province_information_file()
{
    fstream file;
    file.open(province_file, ios::binary | ios::in);
    if (!file.is_open()) {
        //我们无法判断是“没有文件”还是“有文件但是打开失败”，暂时不做处理
    } else {
        for (int i = 0; i < 34; ++i) {
            file.read((char*)(status_of_province + i), sizeof(int));
        }
    }
    file.close();
}

void province_information_manager::write_province_information_file_trunc()
{
    fstream file;
    file.open(province_file, ios::binary | ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "打开province_information.dat失败，程序即将退出！" << endl;
        Sleep(250);
        exit(-1);
    } else {
        for (int i = 0; i < 34; ++i) {
            file.write((char*)(status_of_province + i), sizeof(int)); // 一次只写入一个内存单元，防止出现问题
        }
    }
    file.close();
}

auto province_information_manager::if_input_province_valid(const string& input_province)
    -> int
{
    int result = -1;
    for (int i = 0; i < 34; ++i) {
        if (province_list[i] == input_province) {
            result = i;
        }
    }
    return result;
}

void province_information_manager::show_high_and_medium_risk_regions()
{
    bool if_1 = false, if_2 = false;
    cout << "=========================================" << endl;
    //高风险地区：
    cout << "  高风险地区：" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 2) {
                if_2 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_2) {
        cout << "    无高风险地区！" << endl;
    }
    //中风险地区：
    cout << endl
         << "  中风险地区：" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 1) {
                if_1 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_1) {
        cout << "    无中风险地区！" << endl;
    }
    cout << "=========================================" << endl;
}

auto province_information_manager::if_have_high_and_medium_risk_regions() -> bool
{
    bool result = false;
    for (int i : status_of_province) {
        if (i == 1
            || i == 2) {
            result = true;
        }
    }
    return result;
}