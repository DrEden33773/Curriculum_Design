#include "account_info_manager.h"
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

account_info_manager::account_info_manager()
{
    // load_file_to_list(); // => 已经完成了对 登录模块的重构，现在不需要载入链表，可以直接从文件中读取
}

// 后处理函数
/* [mode => 1.学号精确搜索 2.姓名精确搜索 3.用户名精确搜索] */
auto account_info_manager::if_input_user_exists(
    const string& input, const int& mode, const bool& if_print) -> bool
{
    bool result = false;
    fstream account_info_file;
    fstream user_list_file;
    open_all_files(account_info_file, user_list_file);
    if (mode == 3) {
        cache = new account_info;
        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
            if (cache->account == input) {
                result = true;
                if (if_print) {
                    while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                        if (cu_cache->c_account == cache->account) {
                            break;
                        }
                    }
                    print_detail_info();
                }
                break;
            }
        }
    } else {
        cu_cache = new current_user_info;
        if (mode == 2) {
            while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                if (cu_cache->real_name == input) {
                    result = true;
                    if (if_print) {
                        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
                            if (cu_cache->c_account == cache->account) {
                                break;
                            }
                        }
                        print_detail_info();
                    }
                    break;
                }
            }
        } else if (mode == 1) {
            while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                if (cu_cache->student_number == input) {
                    result = true;
                    if (if_print) {
                        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
                            if (cu_cache->c_account == cache->account) {
                                break;
                            }
                        }
                        print_detail_info();
                    }
                    break;
                }
            }
        }
    }
    account_info_file.close();
    user_list_file.close();
    return result;
}

auto account_info_manager::if_input_user_exists_sub( // 模糊搜索
    const string& input, const int& mode, const bool& if_print) -> bool
{
    bool result = false;
    fstream account_info_file;
    fstream user_list_file;
    open_all_files(account_info_file, user_list_file);
    if (mode == 3) {
        cache = new account_info;
        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
            if (cache->account.find(input)) {
                result = true;
                if (if_print) {
                    while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                        if (cu_cache->c_account == cache->account) {
                            break;
                        }
                    }
                    print_partial_matched_info();
                }
            }
        }
    } else {
        cu_cache = new current_user_info;
        if (mode == 2) {
            while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                if (cu_cache->real_name.find(input)) {
                    result = true;
                    if (if_print) {
                        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
                            if (cu_cache->c_account == cache->account) {
                                break;
                            }
                        }
                        print_partial_matched_info();
                    }
                }
            }
        } else if (mode == 1) {
            while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                if (cu_cache->student_number.find(input)) {
                    result = true;
                    if (if_print) {
                        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
                            if (cu_cache->c_account == cache->account) {
                                break;
                            }
                        }
                        print_partial_matched_info();
                    }
                }
            }
        }
    }
    account_info_file.close();
    user_list_file.close();
    return result;
}

inline void account_info_manager::print_detail_info()
{
    cout << "=============================================================================================" << endl;
    cout << "姓名" << setw(7 + 3) << "用户名" << setw(14) << "密码" << setw(10) << "学号" << setw(9 + 4) << "宿舍号" << setw(3 + 4) << endl;
    cout << endl;
    cout << cu_cache->real_name << setw(7 + 3) << cache->account << setw(14) << cache->password << setw(10) << cu_cache->student_number << setw(9 + 4) << cu_cache->dorm_number << setw(3 + 4) << endl;
    cout << "=============================================================================================" << endl;
}

inline void account_info_manager::print_partial_matched_info()
{
    cout << "姓名：" << cu_cache->real_name << setw(7 + 3)
         << "用户名：" << cache->account << setw(14)
         << "密码：" << cache->password << setw(10)
         << "学号：" << cu_cache->student_number << setw(9 + 4)
         << "宿舍号：" << cu_cache->dorm_number << setw(3 + 4) << endl;
}

inline void account_info_manager::open_all_files(fstream& account_info_file, fstream& user_list_file)
{
    account_info_file.open(account_info_file_location, ios::in | ios::binary);
    if (!account_info_file.is_open()) {
        cout << "写入过程中，打开 account_info.dat 失败！即将自动退出程序" << endl;
        Sleep(250);
        exit(-1);
    }
    user_list_file.open(user_list_file_location, ios::in | ios::binary);
    if (!user_list_file.is_open()) {
        cout << "写入过程中，打开 user_list.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
}

//删除用户
void account_info_manager::delete_a_user()
{
    string temp_user_name;
    bool if_continue_func = true;
    while (true) {
        cout << "请输入您想要删除的用户的 [用户名] >> ";
        cin >> temp_user_name;
        if (if_input_user_exists(temp_user_name, 3, false)) { // 用户名检索
            break;
        } else {
            cout << "不存在该用户名" << endl
                 << "输入Y/y -> 重新输入用户名；输入其他字符 -> 返回 用户信息管理界面 >> ";
            char flag;
            cin >> flag;
            if (flag == 'y' || flag == 'Y') {
                continue;
            } else {
                if_continue_func = false;
                break;
            }
        }
    }
    if (if_continue_func) {
        cout << "是否确认删除 " << temp_user_name << " 这一用户？(确认请输入Y/y，否则输入其他字符) >> ";
        char flag;
        cin >> flag;
        if (flag == 'y' || flag == 'Y') {
            delete_input_user_in_account_info(temp_user_name);
            delete_input_user_in_user_list(temp_user_name);
        } else {
            cout << "收到，并未删除任何用户，即将回到用户信息管理界面" << endl;
            Sleep(200);
            system("cls");
        }
    }
}

void account_info_manager::delete_input_user_in_account_info(const string& input_user)
{
    // 全新的逻辑
    fstream temp_account_info(temp_account_info_file_location, ios::out | ios::binary | ios::trunc);
    if (!temp_account_info.is_open()) {
        cout << "删除过程中，创建临时文件失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    fstream account_info(account_info_file_location, ios::in | ios::binary);
    if (!account_info.is_open()) {
        cout << "删除过程中，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cache = new struct account_info;
    while (account_info.read((char*)(cache), sizeof(account_info))) {
        if (cache->account != input_user) {
            temp_account_info.write((char*)(cache), sizeof(account_info));
        }
    }
    account_info.close();
    temp_account_info.close();
    remove(account_info_file_location.c_str()); // 删除文件
    rename(temp_account_info_file_location.c_str(), account_info_file_location.c_str()); // 新文件重命名 [old-name to new-name]
    delete cache;
}

void account_info_manager::delete_input_user_in_user_list(const string& input_user)
{
    // 全新的逻辑
    fstream temp_user_list(temp_user_list_file_location, ios::out | ios::binary | ios::trunc);
    if (!temp_user_list.is_open()) {
        cout << "删除过程中，创建临时文件失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    fstream user_list(user_list_file_location, ios::in | ios::binary);
    if (!user_list.is_open()) {
        cout << "删除过程中，打开 user_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cu_cache = new current_user_info;
    while (user_list.read((char*)(cu_cache), sizeof(current_user_info))) {
        if (cu_cache->c_account != input_user) {
            temp_user_list.write((char*)(cu_cache), sizeof(current_user_info));
        }
    }
    user_list.close();
    temp_user_list.close();
    remove(user_list_file_location.c_str()); // 删除文件
    rename(temp_user_list_file_location.c_str(), user_list_file_location.c_str()); // 新文件重命名 [old-name to new-name]
    delete cu_cache;
}

// 展示信息
inline void account_info_manager::not_found()
{
    cout << "抱歉，您输入的用户不存在！" << endl;
}

void account_info_manager::precisely_show_specific_user_info()
{ // 精确搜索
    cout << "现在，将要进行精确查询 ... " << endl;
    Sleep(150);
    string t_sno;
    string t_username;
    string t_realname;
    bool if_finished_search = false;
    while (true) {
        cout << "请输入特定的数字以指定模式 [1->学号精确搜索 2->姓名精确搜索 3->用户名精确搜索 4->退出精确搜索] >> ";
        int mode;
        cin >> mode;
        if (mode < 1 || mode > 4) {
            cout << "输入无效，请重新输入！" << endl;
        } else if (mode != 4) {
            if (mode == 1) {
                cout << "请输入要精确查询的 学号 >> ";
                cin >> t_sno;
                if (!if_input_user_exists(t_sno, 1, true)) {
                    not_found();
                }
            } else if (mode == 2) {
                cout << "请输入要精确查询的 姓名 >> ";
                cin >> t_realname;
                if (!if_input_user_exists(t_realname, 2, true)) {
                    not_found();
                }
            } else if (mode == 3) {
                cout << "请输入要精确查询的 用户名 >> ";
                cin >> t_username;
                if (!if_input_user_exists(t_username, 3, true)) {
                    not_found();
                }
            }
            if_finished_search = true;
            break;
        } else {
            cout << "即将返回上一级菜单 ... " << endl;
            Sleep(250);
            system("cls");
            break;
        }
    }
    if (if_finished_search) {
        cout << "已完成精确搜索，即将返回上一级菜单 ... " << endl;
        Sleep(250);
        system("cls");
    }
}

void account_info_manager::show_all_user_info()
{
    fstream account_info_file;
    fstream user_list_file;
    open_all_files(account_info_file, user_list_file);
    cout << "是否显示用户的密码？" << endl
         << "( 输入Y/y => 显示 || 输入其它任意非空字符 => 不显示 ) >> ";
    char flag;
    cin >> flag;
    cout << endl
         << "即将显示所有用户的相关信息 >> " << endl;
    cout << "=============================================================================================" << endl;
    cout << "姓名" << setw(7 + 3) << "用户名" << setw(14) << "密码" << setw(10) << "学号" << setw(9 + 4) << "宿舍号" << setw(3 + 4) << endl;
    cout << endl;
    if (flag == 'y' || flag == 'Y') {
        while (account_info_file.read((char*)(cache), sizeof(account_info)) && user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
            cout << cu_cache->real_name << setw(7 + 3) << cache->account << setw(14) << cache->password << setw(10) << cu_cache->student_number << setw(9 + 4) << cu_cache->dorm_number << setw(3 + 4) << endl;
        }
    } else {
        while (account_info_file.read((char*)(cache), sizeof(account_info)) && user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
            cout << cu_cache->real_name << setw(7 + 3) << cache->account << setw(14) << "<密码不予显示>" << setw(10) << cu_cache->student_number << setw(9 + 4) << cu_cache->dorm_number << setw(3 + 4) << endl;
        }
    }
    cout << "=============================================================================================" << endl;
    cout << "显示完毕！" << endl;
    account_info_file.close();
    user_list_file.close();
}

void account_info_manager::search_then_show_specific_user()
{ // 模糊搜索
    cout << "现在，将要进行模糊查询 ... " << endl;
    Sleep(150);
    string t_sno;
    string t_username;
    string t_realname;
    bool if_finished_search = false;
    while (true) {
        cout << "请输入特定的数字以指定模式 [1->学号模糊搜索 2->姓名模糊搜索 3->用户名模糊搜索 4->退出模糊搜索] >> ";
        int mode;
        cin >> mode;
        if (mode < 1 || mode > 4) {
            cout << "输入无效，请重新输入！" << endl;
        } else if (mode != 4) {
            if (mode == 1) {
                cout << "请输入要精确查询的 学号 >> ";
                cin >> t_sno;
                if (!if_input_user_exists_sub(t_sno, 1, true)) {
                    not_found();
                }
            } else if (mode == 2) {
                cout << "请输入要精确查询的 姓名 >> ";
                cin >> t_realname;
                if (!if_input_user_exists_sub(t_realname, 2, true)) {
                    not_found();
                }
            } else if (mode == 3) {
                cout << "请输入要精确查询的 用户名 >> ";
                cin >> t_username;
                if (!if_input_user_exists_sub(t_username, 3, true)) {
                    not_found();
                }
            }
            if_finished_search = true;
            break;
        } else {
            cout << "即将返回上一级菜单 ... " << endl;
            Sleep(250);
            system("cls");
            break;
        }
    }
    if (if_finished_search) {
        cout << "已完成模糊搜索，即将返回上一级菜单 ... " << endl;
        Sleep(250);
        system("cls");
    }
}

// 增加用户 => 这个功能直接不给了
// 目前，只依赖 “用户” 完成操作即可
void account_info_manager::add_a_user()
{
    cout << "是否确定添加新用户 (确定则输入Y/y，否则输入其他字符) >> ";
    char flag;
    cin >> flag;
    if (flag == 'y' || flag == 'Y') {
        // TODO
        // 当前函数[冗余]
    } else {
        cout << "即将返回上一级菜单 ... " << endl;
        Sleep(250);
        system("cls");
    }
}

// 修改信息
void account_info_manager::change_specific_user_information()
{
    bool if_continue;
    string temp_user_name;
    while (true) {
        cout << "请输入想要修改信息的[用户名] >> ";
        cin >> temp_user_name;
        if (!if_input_user_exists(temp_user_name, 3, false)) {
            cout << "输入的用户不存在！若想重新输入信息，请输入Y/y，否则输入其他字符 >> ";
            char flag;
            cin >> flag;
            if (flag == 'y' || flag == 'Y') {
                cout << "收到，即将返回<信息修改>界面 ... " << endl;
                cout << endl;
            } else {
                if_continue = false;
                cout << "收到，即将返回上一级菜单 ... " << endl;
                cout << endl;
                break;
            }
        } else {
            if_continue = true;
            break;
        }
    }
    if (if_continue) {
        cout << "成功检索到用户的信息！接下来显示[选项]：" << endl;
        while (true) {
            cout << "当前 **待修改的用户** 是 >> " << temp_user_name << endl;
            cout << "==============================================================" << endl;
            cout << setw(6) << "1. 修改 用户 的 密码" << endl;
            cout << setw(6) << "2. 修改 用户 的 姓名" << endl;
            cout << setw(6) << "3. 修改 用户 的 学号" << endl;
            cout << setw(6) << "4. 修改 用户 的 宿舍号" << endl;
            cout << setw(6) << "5. 再次显示 本菜单" << endl;
            cout << setw(6) << "6. 返回 上一级菜单" << endl;
            cout << "==============================================================" << endl;
            cout << "请输入对应的数字 >> ";
            int case_judger;
            cin >> case_judger;
            if (case_judger == 1) {
                change_specific_user_password(temp_user_name);
            } else if (case_judger == 2) {
                change_specific_user_realname(temp_user_name);
            } else if (case_judger == 3) {
                change_specific_user_student_number(temp_user_name);
            } else if (case_judger == 4) {
                change_specific_user_student_dorm_number(temp_user_name);
            } else if (case_judger == 5) {
                cout << endl;
                cout << "再次显示选项" << endl
                     << endl;
            } else if (case_judger == 6) {
                cout << "收到，即将返回 [管理员界面] ... " << endl;
                Sleep(250);
                cout << endl;
                break;
            } else {
                cout << endl;
                cout << "对应功能未开发！再次显示[选项] ... " << endl
                     << endl;
            }
        }
    }
}

void account_info_manager::change_specific_user_password(const string& input_user)
{
    string temp_password;
    char flag;
    cout << "请注意，通过{管理员}修改密码时，并不会修改现有的 <凭据码> ... " << endl;
    Sleep(500);
    cout << "请在下一行输入修改后的密码 (放弃修改请输入-1) (密码长度应大于8位且至少包含一个英文字母)" << endl;
    cout << " >> ";
    cin >> temp_password;
    if (temp_password == "-1") {
        cout << "收到，没有执行任何修改，自动返回上一级菜单 ... " << endl
             << endl;
    } else if (if_password_legal(temp_password)) {
        cout << "再输入一个{任意非空字符}后，系统将完成修改" << endl;
        cin >> flag;
        // CORE =>
        int POS;
        fstream file(account_info_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "修改信息阶段，打开 account_info.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        cache = new account_info;
        while (file.read((char*)(cache), sizeof(account_info))) {
            if (cache->account == input_user) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        cache->password = temp_password;
        file.open(account_info_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "修改信息阶段，打开 account_info.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)cache, sizeof(account_info));
        file.close();
        cout << "您当前修改的用户，其 <凭据码> 是 >>" << cache->sp_code << " ，请提醒该用户牢记！" << endl;
        cout << "再输入一个{任意非空字符}后，系统将完成密码修改 ... ";
        char tmp;
        cin >> tmp;
        delete cache;
        cout << "成功修改密码！即将返回上一级菜单 ... " << endl
             << endl;
    } else {
        cout << "您输入的[新密码]并不合法！自动放弃修改，并返回上一级菜单 ... " << endl
             << endl;
    }
}

void account_info_manager::change_specific_user_realname(const string& input_user)
{
    string temp_real_name;
    char flag;
    cout << "请输入新姓名(放弃修改请输入-1) >> ";
    cin >> temp_real_name;
    if (temp_real_name == "-1") {
        cout << "收到，没有执行任何修改，自动返回上一级菜单 ... " << endl
             << endl;
    } else {
        cout << "再输入一个{任意非空字符}后，系统将完成修改" << endl;
        cin >> flag;
        // CORE =>
        int POS;
        fstream file(user_list_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "修改信息阶段，打开 user_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        cu_cache = new current_user_info;
        while (file.read((char*)(cu_cache), sizeof(current_user_info))) {
            if (cu_cache->c_account == input_user) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        cu_cache->real_name = temp_real_name;
        file.open(user_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "修改信息阶段，打开 user_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)cu_cache, sizeof(current_user_info));
        file.close();
        delete cu_cache;
        cout << "成功修改姓名！即将返回上一级菜单 ... " << endl
             << endl;
    }
}

void account_info_manager::change_specific_user_student_number(const string& input_user)
{
    string temp_student_number;
    char flag;
    cout << "请输入新学号(放弃修改请输入-1) >> ";
    cin >> temp_student_number;
    if (temp_student_number == "-1") {
        cout << "收到，没有执行任何修改，自动返回上一级菜单 ... " << endl
             << endl;
    } else {
        cout << "再输入一个{任意非空字符}后，系统将完成修改" << endl;
        cin >> flag;
        // CORE =>
        int POS;
        fstream file(user_list_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "修改信息阶段，打开 user_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        cu_cache = new current_user_info;
        while (file.read((char*)(cu_cache), sizeof(current_user_info))) {
            if (cu_cache->c_account == input_user) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        cu_cache->student_number = temp_student_number;
        file.open(user_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "修改信息阶段，打开 user_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)cu_cache, sizeof(current_user_info));
        file.close();
        delete cu_cache;
        cout << "成功修改学号！即将返回上一级菜单 ... " << endl
             << endl;
    }
}

void account_info_manager::change_specific_user_student_dorm_number(const string& input_user)
{
    int temp_dorm_number;
    char flag;
    cout << "请输入新宿舍号(放弃修改请输入-1) >> ";
    cin >> temp_dorm_number;
    if (temp_dorm_number == -1) {
        cout << "收到，没有执行任何修改，自动返回上一级菜单 ... " << endl
             << endl;
    } else {
        cout << "再输入一个{任意非空字符}后，系统将完成修改" << endl;
        cin >> flag;
        // CORE =>
        int POS;
        fstream file(user_list_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "修改信息阶段，打开 user_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        cu_cache = new current_user_info;
        while (file.read((char*)(cu_cache), sizeof(current_user_info))) {
            if (cu_cache->c_account == input_user) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        cu_cache->dorm_number = temp_dorm_number;
        file.open(user_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "修改信息阶段，打开 user_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)cu_cache, sizeof(current_user_info));
        file.close();
        delete cu_cache;
        cout << "成功修改宿舍号！即将返回上一级菜单 ... " << endl
             << endl;
    }
}

// 操作界面
void account_info_manager::shell_of_account_info_manager()
{
    cout << "欢迎使用 <用户信息管理模块> , 下面显示 [可用功能列表] >> " << endl;
    while (true) {
        cout << "=======================================================" << endl;
        cout << setw(6) << "1.展示所有的 用户信息" << endl;
        cout << setw(6) << "2.模糊搜索 用户信息 (支持用 学号/姓名/用户名 搜索)" << endl;
        cout << setw(6) << "3.精确搜索 用户信息 (支持用 学号/姓名/用户名 搜索)" << endl;
        cout << setw(6) << "4.修改 某个特定用户的 特定信息 (支持修改 密码/学号/姓名/宿舍号)" << endl;
        cout << setw(6) << "5.删除 某个特定用户的 所有信息" << endl;
        cout << setw(6) << "6.再次显示 [可用功能列表]" << endl;
        cout << setw(6) << "7.返回 [管理员界面]" << endl;
        cout << "=======================================================" << endl;
        cout << "请输入相应的数字 >> ";
        int flag;
        cin >> flag;
        cout << endl;
        if (flag == 1) {
            show_all_user_info();
        } else if (flag == 2) {
            search_then_show_specific_user();
        } else if (flag == 3) {
            precisely_show_specific_user_info();
        } else if (flag == 4) {
            change_specific_user_information();
        } else if (flag == 5) {
            delete_a_user();
        } else if (flag == 6) {
            cout << "再次显示 [可用功能菜单] ... " << endl;
            Sleep(250);
        } else if (flag == 7) {
            cout << "即将返回 [管理员界面] ... " << endl;
            Sleep(250);
            break;
        } else {
            cout << "该功能尚未被开发！即将再次显示 [可用功能菜单] ... " << endl;
        }
    }
}