// ReSharper disable CppClangTidyConcurrencyMtUnsafe
#include "province_information_manager.h"

#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

province_information_manager::province_information_manager()
{
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

void province_information_manager::show_input_province_status() const
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

void province_information_manager::show_all_province_status() const
{
    cout.setf(ios::left); // formatter
    vector<string> high_risks;
    vector<string> mid_risks;
    vector<string> low_risks;
    for (int i = 0; i < 34; ++i) {
        if (status_of_province[i] == 2) {
            high_risks.push_back(province_list[i]);
        } else if (status_of_province[i] == 1) {
            mid_risks.push_back(province_list[i]);
        } else {
            low_risks.push_back(province_list[i]);
        }
    }
    const bool if_0 = !low_risks.empty();
    const bool if_1 = !mid_risks.empty();
    const bool if_2 = !high_risks.empty();
    cout << "下面将按照 <状态信息> 输出所有 <省级区域> 的相关信息：" << endl
         << endl;
    cout << "==================================================================" << endl;
    //高风险地区：
    cout << endl
         << "  高风险地区：" << endl;
    if (!if_2) {
        cout << endl;
        cout << "\t" << setw(10) << "无高风险地区！" << endl;
    } else {
        int num_of_high_risks = 0;
        for (const auto& high_risk : high_risks) {
            if (num_of_high_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << high_risk;
            ++num_of_high_risks;
        }
        cout << endl;
    }
    //中风险地区：
    cout << endl
         << "  中风险地区：" << endl;
    if (!if_1) {
        cout << endl;
        cout << "\t" << setw(10) << "无中风险地区！" << endl;
    } else {
        int num_of_mid_risks = 0;
        for (const auto& mid_risk : mid_risks) {
            if (num_of_mid_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << mid_risk;
            ++num_of_mid_risks;
        }
        cout << endl;
    }
    //低风险地区：
    cout << endl
         << "  低风险地区：" << endl;
    if (!if_0) {
        cout << endl;
        cout << "\t" << setw(10) << "无低风险地区！" << endl;
    } else {
        int num_of_low_risks = 0;
        for (const auto& low_risk : low_risks) {
            if (num_of_low_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << low_risk;
            ++num_of_low_risks;
        }
        cout << endl;
    }
    cout << endl
         << "==================================================================" << endl;
    cout << endl
         << "输出完毕！" << endl;
    cout << "按任意键继续 ... ";
    _getch();
    cout << endl;
    cout.unsetf(ios::left); // de_formatter
}

void province_information_manager::try_to_load_province_information_file()
{
    fstream file;
    file.open(province_file, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "预加载阶段，生成 province_information.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    file.open(province_file, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "打开 province_information.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    } else {
        for (int i = 0; i < 34; ++i) {
            file.read(reinterpret_cast<char*>(status_of_province + i), sizeof(int));
        }
    }
    file.close();
}

void province_information_manager::write_province_information_file_trunc()
{
    fstream file;
    file.open(province_file, ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "打开 province_information.dat 失败，程序即将退出！" << endl;
        Sleep(250);
        exit(-1);
    } else {
        for (int i = 0; i < 34; ++i) {
            file.write(reinterpret_cast<char*>(status_of_province + i), sizeof(int)); // 一次只写入一个内存单元，防止出现问题
        }
    }
    file.close();
}

int province_information_manager::if_input_province_valid(const string& input_province) const
{
    int result = -1;
    for (int i = 0; i < 34; ++i) {
        if (province_list[i] == input_province) {
            result = i;
        }
    }
    return result;
}

void province_information_manager::show_high_and_medium_risk_regions() const
{
    cout.setf(ios::left); // formatter
    vector<string> high_risks;
    vector<string> mid_risks;
    for (int i = 0; i < 34; ++i) {
        if (status_of_province[i] == 2) {
            high_risks.push_back(province_list[i]);
        } else if (status_of_province[i] == 1) {
            mid_risks.push_back(province_list[i]);
        }
    }
    const bool if_1 = !mid_risks.empty();
    const bool if_2 = !high_risks.empty();
    cout << endl;
    cout << "==================================================================" << endl;
    //高风险地区：
    cout << endl
         << "  高风险地区：" << endl;
    if (!if_2) {
        cout << endl;
        cout << "\t" << setw(10) << "无高风险地区！" << endl;
    } else {
        int num_of_high_risks = 0;
        for (const auto& high_risk : high_risks) {
            if (num_of_high_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << high_risk;
            ++num_of_high_risks;
        }
        cout << endl;
    }
    //中风险地区：
    cout << endl
         << "  中风险地区：" << endl;
    if (!if_1) {
        cout << endl;
        cout << "\t" << setw(10) << "无中风险地区！" << endl;
    } else {
        int num_of_mid_risks = 0;
        for (const auto& mid_risk : mid_risks) {
            if (num_of_mid_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << mid_risk;
            ++num_of_mid_risks;
        }
        cout << endl;
    }
    cout << endl
         << "==================================================================" << endl;
    cout << endl;
    cout.unsetf(ios::left); // de_formatter
}

bool province_information_manager::if_have_high_and_medium_risk_regions()
{
    bool result = false;
    for (const int i : status_of_province) {
        if (i == 1 || i == 2) {
            result = true;
        }
    }
    return result;
}

void province_information_manager::shell_admin()
{
    system("cls");
    cout << endl;
    cout << "欢迎进入 [省级行政区疫情防控信息] 管理平台, 下面显示功能菜单 ... " << endl;
    bool if_continue = true;
    while (true) {
        cout << endl;
        cout << "[省级行政区疫情防控信息] 管理平台 <功能菜单>" << endl;
        cout << "=====================================================" << endl;
        cout << "\t"
             << "1. 显示所有省级区域的 风险状态" << endl;
        cout << "\t"
             << "2. 显示指定省级区域的 风险状态" << endl;
        cout << "\t"
             << "3. 更改特定省级区域的 风险状态" << endl;
        cout << "\t"
             << "4. 再次显示 功能菜单" << endl;
        cout << "\t"
             << "5. 返回 [管理员界面]" << endl;
        cout << "=====================================================" << endl;
        cout << "请输入对应的数字 >> ";
        char flag;
        cin >> flag;
        system("cls");
        switch (flag) {
        case '1':
            show_all_province_status();
            break;
        case '2':
            show_input_province_status();
            break;
        case '3':
            change_province_status();
            break;
        case '4':
            cout << "收到，即将重新显示 [功能菜单] ... " << endl;
            Sleep(250);
            break;
        case '5':
            cout << "收到，即将退出该平台，返回 [管理员界面] ..." << endl;
            Sleep(250);
            if_continue = false;
            break;
        default:
            cout << "功能未开发！即将重新显示 功能菜单 ... " << endl;
            Sleep(250);
            break;
        }
        if (!if_continue)
            break;
    }
}

void province_information_manager::shell_user() { }
