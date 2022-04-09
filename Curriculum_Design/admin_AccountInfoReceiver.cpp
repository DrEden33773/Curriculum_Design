#include "admin_AccountInfoReceiver.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h> // Sleep() 使用
using namespace std;

auto admin_info_receiver::if_profession_type_valid(int input) -> bool
{
    if (input >= 1 && input <= 20) {
        return true;
    } else {
        return false;
    }
}

inline void admin_info_receiver::make_sure_admin_list_file_exists()
{
    fstream file;
    /// now, tries to new the file
    file.open(admin_list_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预创建 admin_list.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // 及时关闭
}

auto admin_info_receiver::if_admin_list_file_empty() -> bool
{
    make_sure_admin_list_file_exists(); // 确保文件正常的产生
    fstream file;
    file.open(admin_list_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 admin_list.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    checker = new current_admin_info;
    bool if_empty = true;
    while (file.read((char*)(checker), sizeof(current_admin_info))) {
        if_empty = false;
        break;
    }
    delete checker;
    if_admin_list_file_is_empty = if_empty;
    return if_empty;
}

admin_info_receiver::admin_info_receiver()
{
    string trans_account = return_account_name();
    admin_import_from_login_interface(trans_account);
    try_to_load_admin_file(trans_account);
}

admin_info_receiver::admin_info_receiver(
    const string& input_account,
    const string& input_password)
{
    // Empty
}

void admin_info_receiver::admin_import_from_login_interface(const string& input_account)
{
    ca_info = new current_admin_info;
    ca_info->c_account = input_account;
    ca_info->if_first_use = true; // 默认参数
}

void admin_info_receiver::try_to_load_admin_file(const string& correct_account)
{
    ca_cache = new current_admin_info; // 缓存，用于比对信息
    fstream file;
    bool if_file_is_empty = if_admin_list_file_empty();
    if (if_file_is_empty) { // 文件是空的
        // 保持默认参数
    } else {
        file.open(admin_list_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            delete ca_cache;
            // 现在一定存在这个文件，打不开就是失败
            cout << "无法打开 admin_list.dat！即将自动退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        while (file.read((char*)(ca_cache), sizeof(current_admin_info))) {
            if (ca_cache->c_account == ca_info->c_account) {
                // move value
                ca_info = std::move(ca_cache); // 贼好用这个
                break;
            }
        }
        file.close(); // 及时关闭
        delete ca_cache; // 解除缓存
    }
}

void admin_info_receiver::write_to_admin_file()
{
    ca_cache = new current_admin_info;
    fstream file(admin_list_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "信息写入阶段，打开 admin_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (!if_admin_list_file_is_empty) { // 文件里不是空的 => 需要找到正确的位置
        int POS;
        while (file.read((char*)(ca_cache), sizeof(current_admin_info))) {
            if (ca_cache->c_account == ca_info->c_account) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        file.open(admin_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "信息写入阶段，打开 admin_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)(ca_cache), sizeof(current_admin_info));
        file.close();
    } else { // 文件是空的 => 直接不用找位置了，写到头上就完全OK
        file.close();
        file.open(admin_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "信息写入阶段，打开 admin_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.write((char*)(ca_cache), sizeof(current_admin_info));
        file.close();
    }
}

void admin_info_receiver::ask_to_set_profession_type()
{
    if (ca_info->if_first_use) {
        cout << "本账号是第一次使用 ... 但系统暂时不开放 [指定分管学院] 功能 ... " << endl;
        cout << "所有的 <管理员账号> ，都有管理 <所有用户> 的权限 ... " << endl;
        cout << "现在系统已经更新了您的使用状态，稍等片刻后，进入 <管理员界面> ... " << endl;
        // 暂时不开放 => 分管学院功能
        // while (false) {
        //     cout << "第一次使用 "
        //          << ca_info->c_account
        //          << " 这个账号，稍等片刻，请按照提示填入真实且正确的信息："
        //          << endl;
        //     Sleep(600);
        //     system("cls");
        //     // 变量池
        //     int temp_profession_code, temp_profession_code_check;
        //     bool if_back_to_first_step_when_code_conflict;
        //     // 管理员不要求姓名
        //     // 输入分管专业代号
        //     while (true) {
        //         cout << "请输入分管学院的代号：";
        //         cin >> temp_profession_code;
        //         while (true) {
        //             char temp_flag;
        //             cout << "请再次输入你 (刚刚输入的) 分管学院的代号：";
        //             cin >> temp_profession_code_check;
        //             if (temp_profession_code_check == temp_profession_code) {
        //                 if_back_to_first_step_when_code_conflict = false;
        //                 break;
        //             } else {
        //                 cout << "两次输入的代号不同" << endl
        //                      << "输入A/a -> 再次输入最初输入的代号"
        //                      << "输入其他内容 -> 重新指定代号 >>> ";
        //                 cin >> temp_flag;
        //                 if (temp_flag == 'A' || temp_flag == 'a') {
        //                     system("cls");
        //                     cout << "稍等片刻，准备 [再次输入最初输入的代号]" << endl;
        //                     Sleep(1000);
        //                 } else {
        //                     system("cls");
        //                     cout << "稍等片刻，准备 [重新指定代号]" << endl;
        //                     Sleep(1000);
        //                     if_back_to_first_step_when_code_conflict = true;
        //                     break;
        //                 }
        //             }
        //             if (!if_back_to_first_step_when_code_conflict) {
        //                 break;
        //             }
        //         }
        //         cout << "请 ==最后一次== 确认你输入的必要信息：" << endl
        //              << endl;
        //         cout << "==============================================" << endl;
        //         // cout.setf(ios::left); // 左对齐 => 修正，这里不需要
        //         cout << "   分管学院代号：  " << setw(5) << temp_profession_code << endl;
        //         cout << "==============================================" << endl
        //              << endl;
        //         cout << "是否正确？正确请输入Y/y，不正确请输入其他任意非空字符(稍后将自动重新引导您输入 分管学院代号) >>> ";
        //         char flag_of_flush;
        //         cin >> flag_of_flush;
        //         if (flag_of_flush == 'Y' && flag_of_flush == 'y') {
        //             system("cls");
        //             break;
        //         } else {
        //             cout << "请稍后，系统将自动重新引导您输入 分管学院代号" << endl;
        //             Sleep(1000);
        //             system("cls");
        //         }
        //     }
        // }

        //更新管理员状态 -> 是否第一次使用
        ca_info->if_first_use = false;

        //写入文件
        write_to_admin_file();

        // end of function
        // cout << "已成功输入 [必要信息]，稍等片刻将进入 <管理员界面>" << endl;
        Sleep(1000);
        system("cls");
    }
}

//接口函数
auto admin_info_receiver::return_c_account() -> string
{
    return ca_info->c_account;
}