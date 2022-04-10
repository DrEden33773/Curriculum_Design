#define _CRT_SECURE_NO_WARNINGS
#include "account.h"
#include <Windows.h>
#include <conio.h>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random> // 生成随机数
#include <string>

#include "time_manager.h"

using namespace std;

account_manager::account_manager(const string& any)
{
    // var_initialization
    cache = nullptr;
    cache_base = nullptr;
    login = nullptr;
    // 已经重构
    // make sure account_list exists
    fstream file;
    file.open(account_info_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预加载 account_info.dat 失败！ 即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    // check if file is empty
    if_acct_info_file_have_admin = false;
    file.open(account_info_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开 account_info.dat 失败！ 即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cache_base = new account_info;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (cache_base->if_admin) {
            if_acct_info_file_have_admin = true;
            break;
        }
    }
    file.close();
}

account_manager::account_manager()
{
    if_acct_info_file_have_admin = true;
    // Reason => the constructor without any parameter will be called in derived class,
    // and you won't have the chance to use the derived class without successfully used the base class,
    // which means, you must have created an "admin" account in the account_info.dat
    cache = nullptr;
    cache_base = nullptr;
    login = nullptr;
}

//后处理函数
bool account_manager::if_password_legal(const string& temp_password)
{
    bool result = false;
    bool if_length = false;
    bool if_number = false;
    bool if_letter = false;
    const int len = temp_password.length(); // 获取长度
    if (len >= 8 && len <= 24) // 密码长度 => 小于24
        if_length = true;
    for (int x = 0; x < len; ++x) {
        if (temp_password[x] >= '0' && temp_password[x] <= '9')
            if_number = true;
        if (temp_password[x] >= 'a' && temp_password[x] <= 'z')
            if_letter = true;
        if (temp_password[x] >= 'A' && temp_password[x] <= 'Z')
            if_letter = true;
    }
    if (if_number && if_length && if_letter)
        result = true;
    return result; // return
}

bool account_manager::if_account_legal(const string& temp_account)
{
    bool result = false;
    bool if_length = false;
    bool if_number = false;
    bool if_letter = false;
    const int len = temp_account.length(); // 获取长度
    if (len >= 8 && len <= 16) // 账号名长度 => 不超过16
        if_length = true;
    for (int x = 0; x < len; ++x) {
        if (temp_account[x] >= '0' && temp_account[x] <= '9')
            if_number = true;
        if (temp_account[x] >= 'a' && temp_account[x] <= 'z')
            if_letter = true;
        if (temp_account[x] >= 'A' && temp_account[x] <= 'Z')
            if_letter = true;
    }
    if (if_number && if_length && if_letter)
        result = true;
    return result; // return
}

void account_manager::write_account_to_cache(
    const string& temp_account,
    const string& temp_password,
    bool if_admin,
    const char* temp_sp_code)
{
    // 已重构
    cache_base = new account_info;
    strcpy(cache_base->account_str, temp_account.c_str());
    strcpy(cache_base->password_str, temp_password.c_str());
    cache_base->if_admin = if_admin;
    strcpy(cache_base->sp_code, temp_sp_code);
    // 不要解除空间
}

// write_cache_to_file_app
void account_manager::write_cache_to_file_app() const
{
    fstream file;
    file.open(file_location, ios::binary | ios::app); // 有 ios::app 就没必要有 ios::out
    if (!file.is_open()) {
        cout << "写入文件过程中，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    } else {
        file.write(reinterpret_cast<char*>(cache_base), sizeof(account_info));
    }
    // delete cache_base;
    file.close();
}

// change_account_password_in_file
void account_manager::change_account_password_in_file(const account_info* changed_account) const
{
    int POS;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "修改密码前，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    }
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (!strcmp(changed_account->account_str, cache_base->account_str)) {
            POS = file.tellg(); // g => 读指针
            break;
        }
    }
    file.close();
    strcpy(cache_base->password_str, changed_account->password_str);
    file.open(file_location, ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "修改密码前，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    }
    file.seekp(POS, ios::beg);
    file.write(reinterpret_cast<char*>(cache_base), sizeof(account_info));
    file.close();
}

int account_manager::check_account(
    const string& input_account,
    const string& input_password) const
{
    // 全新的逻辑 -- 直接从文件检索
    bool if_account_exists = false;
    bool if_password_correct = false;
    int result = -2;
    fstream file(account_info_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "检索账号信息时，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // cache_base = new account_info;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (!strcmp(cache_base->account_str, input_account.c_str())) {
            if_account_exists = true;
            if (!strcmp(cache_base->password_str, input_password.c_str())) {
                if_password_correct = true;
                if (cache_base->if_admin)
                    result = 1;
                else
                    result = 0;
                break;
            }
        }
    }
    // delete cache_base;
    if (!if_account_exists)
        result = -2;
    else if (!if_password_correct)
        result = -1;
    file.close();
    return result;
}

bool account_manager::if_account_exists_new(const string& input) const
{
    bool result = false;
    fstream file;
    file.open(account_info_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "读取信息时，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (!strcmp(cache_base->account_str, input.c_str())) {
            result = true;
            break;
        }
    }
    file.close();
    return result;
}

char* account_manager::generate_sp_code()
{
    const auto temp = new char[11]; // 在堆上创建字符数组，指针为temp
    const uniform_int_distribution<unsigned> u(0, 9);
    default_random_engine e(time(nullptr)); // 种子=当前时间，确保种子不重样，确保真随机数的产生
    for (int i = 0; i < 11; i++) {
        temp[i] = '0' + u(e);
    }
    temp[10] = '\0';
    return temp;
}

void account_manager::change_account_in_cache(
    account_manager::account_info* changed_account,
    const string& changed_password,
    const char* changed_sp_code)
{
    strcpy(changed_account->password_str, changed_password.c_str());
    strcpy(changed_account->sp_code, changed_sp_code);
}

account_manager::account_info* account_manager::if_sp_code_is_correct(
    const string& temp_account,
    const char* temp_sp_code) const
{
    account_info* result = nullptr;
    fstream account_into_file(account_info_file_location, ios::in | ios::binary);
    if (!account_into_file.is_open()) {
        cout << "检索账号信息时，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // cache_base = new account_info;
    while (!account_into_file.eof()) {
        account_into_file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (strcmp(cache_base->account_str, temp_account.c_str()) == 0
            && strcmp(cache_base->sp_code, temp_sp_code) == 0) {
            result = cache_base;
            break;
        }
    }
    account_into_file.close();
    return result;
}

account_manager::account_info* account_manager::if_sp_code_exists(const char* temp_sp_code) const
{
    account_info* result = nullptr;
    fstream account_into_file(account_info_file_location, ios::in | ios::binary);
    if (!account_into_file.is_open()) {
        cout << "检索账号信息前，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // cache_base = new account_info;
    while (!account_into_file.eof()) {
        account_into_file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (strcmp(cache_base->sp_code, temp_sp_code) == 0) {
            bool if_found = true;
            result = cache_base;
            break;
        }
    }
    account_into_file.close();
    return result;
}

// interface-函数
int account_manager::shell_of_account_login()
{
    time_manager today;
    delete cache_base;
    cache_base = nullptr;
    cache_base = new account_info;
    int judger = -1;
    if (!if_acct_info_file_have_admin) {
        //还未使用过软件
        first_create_admin_account();
    }
    cout << endl;
    cout << "今天是 >> " << today << endl;
    cout << endl;
    cout << "欢迎使用 [疫情防控一体化管理系统]，即将进入登录页面" << endl
        << endl;
    for (;;) {
        cout << "下面显示登录选项：" << endl;
        cout << "====================================================" << endl;
        cout << "\t";
        cout << "1.使用--账号密码--登录" << endl;
        cout << "\t";
        cout << "2.使用--账号凭据码--登录" << endl;
        cout << "\t";
        cout << "3.新建账号" << endl;
        cout << "\t";
        cout << "4.忘记密码/修改密码" << endl;
        cout << "\t";
        cout << "5.再次显示功能列表" << endl;
        cout << "\t";
        cout << "6.取消登录并退出程序" << endl;
        cout << "====================================================" << endl;
        cout << "请输入对应序号(输入5再次显示功能列表): ";
        string temp;
        cin >> temp;
        cout << endl
            << endl;
        if (temp == "6") {
            // 这里也需要更新 账号个数 对应的 文件
            cout << "取消登录，程序即将自动退出" << endl;
            Sleep(300);
            exit(1);
        }
        if (temp == "1") {
            judger = sign_in_by_account();
            if (judger == -2) {
                cout << "不存在该账户，即将再次显示登录选项" << endl
                    << endl;
                Sleep(150);
                // system("cls"); //清屏
            } else if (judger == -1) {
                cout << "账户存在，但是密码错误！即将再次显示登录选项" << endl
                    << endl;
                Sleep(150);
                // system("cls"); //清屏
            } else {
                system("cls"); //清屏
                break;
            }
        } else if (temp == "2") {
            judger = sign_in_by_sp_code();
            if (judger == -2) {
                cout << "不存在与这个凭据码匹配的账户，即将再次显示登录选项" << endl
                    << endl;
                Sleep(150);
                // system("cls"); //清屏
            } else if (judger == -1) {
                // sp_code登录，不存在返回-1的情况
                cout << "账户存在，但是密码错误！即将再次显示登录选项" << endl
                    << endl;
                Sleep(150);
                // system("cls"); //清屏
            } else {
                system("cls"); //清屏
                break;
            }
        } else if (temp == "3") {
            create_account();
        } else if (temp == "4") {
            change_password();
        } else if (temp == "5") {
            system("cls");
            continue;
        } else {
            cout << "没有与" << temp << "对应的功能，即将再次显示登录选项" << endl
                << endl;
            Sleep(150);
            // system("cls"); //清屏
        }
    }
    return judger;
}

void account_manager::first_create_admin_account()
{
    string temp_account;
    string temp_password;
    string temp_password_check;
    constexpr bool if_this_is_admin = true;
    bool if_try_again = false;
    //输入信息
    cout << "检测到当前系统中没有 <管理员账号> ，请先创建一个管理员账号！" << endl;
    while (true) {
        cout << "请输入 <账户名> (至少8位，至多16位，需要包含数字与英文字母)： ";
        cin >> temp_account;
        if (if_account_exists_new(temp_account)) {
            // system("cls");
            cout << "已存在该账号，请重新输入 <用户名> ！" << endl;
            Sleep(250);
        } else if (!if_account_legal(temp_account)) {
            cout << "账户名不合法！请重新设置" << endl;
            Sleep(150);
        } else {
            break;
        }
    }
    while (true) {
        while (true) {
            cout << "请设置 <密码> (至少8位，至多24位，需要包含数字与英文字母)： ";
            cin >> temp_password;
            if (if_password_legal(temp_password)) {
                system("cls"); // 清屏，再次输入密码，核验时，屏幕显示密文
                break;
            } else {
                cout << "密码不合法！请重新设置" << endl;
            }
        }
        while (true) {
            system("cls"); // 清屏，再次输入密码，核验时，屏幕显示密文
            cout << "请输入刚刚设置的 <密码> ： ";
            // cin >> temp_password_check; //需要“密文显示”
            if (password_input_judger_with_fmt(temp_password)) {
                cout << "管理员账号创建成功！" << endl
                    << endl;
                // Sleep(150);
                // system("cls");
                if_try_again = false;
                break;
            } else {
                cout << "两次输入的密码不一致，按A=>重新设置密码，输入其他字符=>再次尝试输入刚刚设置的密码：" << endl;
                char temp;
                cin >> temp;
                if (temp == 'A' || temp == 'a') {
                    if_try_again = true;
                    system("cls");
                    break;
                } else {
                    continue;
                }
            }
        }
        if (!if_try_again) {
            break;
        }
    }
    //生成随机的凭据码
    const char* temp_so_code = generate_sp_code();
    //存入缓存
    write_account_to_cache(temp_account, temp_password, if_this_is_admin, temp_so_code);
    //缓存存入文件尾部
    write_cache_to_file_app();
    //展示凭据码
    cout << "已创建账户，生成的凭据码为：" << temp_so_code << endl;
    cout << "请务必牢记您的凭据码，这将是您找回的[管理员账户<密码>]的唯一凭据，也将是您找回[普通账户<密码>]的重要凭据！" << endl;
    cout << "牢记凭据码后，输入任意字符继续 >>> ";
    char skipper;
    cin >> skipper;
    Sleep(100);
    system("cls");
}

void account_manager::create_account()
{
    string temp_account;
    string temp_password;
    string temp_password_check;
    bool if_this_is_admin;
    bool if_try_again = false;
    //输入信息
    cout << "请指定创建账户的类型(输入A=>管理员，输入其他字符=>普通用户)：";
    char temp_judge;
    cin >> temp_judge; // 只读入一个字符
    if (temp_judge == 'A' || temp_judge == 'a')
        if_this_is_admin = true;
    else
        if_this_is_admin = false;
    while (true) {
        cout << "请输入 <账户名> (至少8位，至多16位，需要包含数字与英文字母)： ";
        cin >> temp_account;
        if (if_account_exists_new(temp_account)) {
            // system("cls");
            cout << "已存在该账号，请重新输入 <用户名> ！" << endl;
            Sleep(250);
        } else if (!if_account_legal(temp_account)) {
            cout << "账户名不合法！请重新设置" << endl;
            Sleep(150);
        } else {
            break;
        }
    }
    while (true) {
        while (true) {
            cout << "请设置 <密码> (至少八位，包含数字与英文字母)： ";
            cin >> temp_password;
            if (if_password_legal(temp_password)) {
                system("cls"); // 清屏，再次输入密码，核验时，屏幕显示密文
                break;
            } else {
                cout << "密码不合法！请重新设置" << endl;
            }
        }
        while (true) {
            system("cls"); // 清屏，再次输入密码，核验时，屏幕显示密文
            cout << "请输入刚刚设置的 <密码> ： ";
            // cin >> temp_password_check; //需要“密文显示”
            if (password_input_judger_with_fmt(temp_password)) {
                cout << "账号创建成功！" << endl
                    << endl;
                // Sleep(150);
                // system("cls");
                if_try_again = false;
                break;
            } else {
                cout << "两次输入的密码不一致，按A=>重新设置密码，输入其他字符=>再次尝试输入刚刚设置的密码：" << endl;
                char temp;
                cin >> temp;
                if (temp == 'A' || temp == 'a') {
                    if_try_again = true;
                    system("cls");
                    break;
                } else {
                    continue;
                }
            }
        }
        if (!if_try_again) {
            break;
        }
    }
    // 生成随机的凭据码
    const char* temp_so_code = generate_sp_code();
    // 写入cache
    write_account_to_cache(temp_account, temp_password, if_this_is_admin, temp_so_code);
    // cache写入文件尾部
    write_cache_to_file_app();
    // 展示凭据码
    cout << "已创建账户，生成的凭据码为：" << temp_so_code << endl;
    cout << "请务必牢记您的凭据码，这将是您找回的[管理员账户<密码>]的唯一凭据，也将是您找回[普通账户<密码>]的重要凭据！" << endl;
    cout << "牢记凭据码后，输入任意字符继续 >>> ";
    char skipper;
    cin >> skipper;
    Sleep(100);
    system("cls");
}

int account_manager::sign_in_by_account()
{
    string temp_account;
    cout << "请输入用户名：";
    cin >> temp_account;
    cout << "请输入密码："; // 密文显示
    const string temp_password = password_input_with_fmt_then_return_it();
    const int temp_result = check_account(temp_account, temp_password);
    if (temp_result != -2 && temp_result != -1) {
        // give_the_plug_of_account(temp_account, temp_password);
        login = cache_base;
    }
    return temp_result;
}

int account_manager::sign_in_by_sp_code()
{
    // 待会用 cache_base，记得解除占用
    int temp_result = 0;
    char temp_sp_code[11];
    cout << "请输入<凭据码>：";
    cin >> temp_sp_code;
    const account_info* c = if_sp_code_exists(temp_sp_code);
    if (!c) {
        temp_result = -2;
    } else {
        // give_the_plug_of_account(temp_sp_code);
        login = cache_base;
    }
    if (temp_result != -2) {
        if (c->if_admin)
            temp_result = 1;
    }
    // delete cache_base;
    // delete c;
    return temp_result;
}

void account_manager::change_password() const
// 这个函数，逻辑太容易乱了
{
    string temp_account;
    string temp_password;
    string temp_password_check;
    char temp_sp_code[11];
    bool if_go_next = false;
    bool if_try_again = false;
    account_info* temp_account_ptr;
    while (true) {
        while (true) {
            cout << "请输入要修改密码的 <用户名> ： ";
            cin >> temp_account;
            if (!if_account_exists_new(temp_account)) {
                system("cls");
                cout << "不存在该账号，请重新输入 <用户名> ！" << endl;
                Sleep(250);
            } else {
                break;
            }
        }
        while (true) {
            cout << "请输入 <账号> 的 <凭据码> ：";
            cin.width(11);
            cin >> temp_sp_code;
            temp_account_ptr = if_sp_code_is_correct(temp_account, temp_sp_code); // 用到 cache_base
            if (temp_account_ptr) {
                if_go_next = true;
                break;
            } else {
                cout << "<凭据码> 和 <账号> 不匹配，输入Y=>再次输入<凭据码>，输入其他字符=>重新输入<用户名>" << endl;
                char temp;
                cin >> temp;
                if (temp == 'y' || temp == 'Y')
                    continue;
                else {
                    system("cls");
                    Sleep(150);
                    break;
                }
            }
        }
        if (if_go_next)
            break;
    }
    system("cls");
    cout << "<凭据码>和<用户名>成功匹配，允许设置<新密码>，请稍等片刻" << endl;
    Sleep(200);
    while (true) {
        while (true) {
            cout << "请为 {" << temp_account << "} 设置 <新密码> (至少八位，包含数字与英文字母)： ";
            cin >> temp_password;
            if (if_password_legal(temp_password)) {
                system("cls"); // 清屏，再次输入密码，核验时，屏幕显示密文
                break;
            } else {
                cout << "密码不合法！请重新设置" << endl;
            }
        }
        while (true) {
            system("cls"); // 清屏，再次输入密码，核验时，屏幕显示密文
            cout << "请输入刚刚设置的 <新密码> ： ";
            // cin >> temp_password_check; //需要“密文显示”
            if (password_input_judger_with_fmt(temp_password)) {
                system("cls");
                cout << "密码修改成功" << endl
                    << endl;
                if_try_again = false;
                Sleep(150);
                break;
            } else {
                cout << "两次输入的密码不一致，按A=>重新设置密码，输入其他字符=>再次尝试输入刚刚设置的新密码：" << endl;
                char temp;
                cin >> temp;
                if (temp == 'A' || temp == 'a') {
                    if_try_again = true;
                    system("cls");
                    break;
                }
            }
        }
        if (!if_try_again) {
            break;
        }
    }
    cout << " == 密码更改后，即将生成新的凭据码 == " << endl;
    // 新生成随机的凭据码
    const char* temp_so_code = generate_sp_code();
    // 改写缓存
    change_account_in_cache(temp_account_ptr, temp_password, temp_so_code);
    // 更改文件中对应的密码
    change_account_password_in_file(temp_account_ptr);
    // 展示凭据码
    cout << "重新生成的凭据码为：" << temp_so_code << endl;
    cout << "请务必牢记您的凭据码，这将是您找回的[管理员账户<密码>]的唯一凭据，也将是您找回[普通账户<密码>]的重要凭据！" << endl;
    cout << "牢记凭据码后，请输入任意字符后继续 >>> ";
    char skipper;
    cin >> skipper;
    // delete cache_base; // 解除 cache_base
    Sleep(100);
    system("cls");
}

//接口函数
void account_manager::give_the_plug_of_account(
    const string& input_account,
    const string& input_password)
{
    login = new account_info;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "传递参数时，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    }
    account_info* c = new account_info;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(c), sizeof(account_info));
        if (strcmp(c->account_str, input_account.c_str()) == 0) {
            if (strcmp(c->password_str, input_password.c_str()) == 0) {
                login = c;
                break;
            }
        }
    }
    // delete c;
    file.close();
}

void account_manager::give_the_plug_of_account(const char* input_sp_code)
{
    login = new account_info;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "传递参数时，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    }
    account_info* c = new account_info;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(c), sizeof(account_info));
        if (strcmp(c->sp_code, input_sp_code) == 0) {
            login = c;
        }
    }
    // delete c;
    file.close();
}

bool account_manager::password_input_judger_with_fmt(const string& judged_str)
{
    string input;
    char chr = '\0';
    while (chr != '\r') { // 未输入 回车
        chr = _getch(); // 获取键入的字符
        if (chr != '\r' && chr != '\b') { // 未输入 退格 / 回车
            input += chr; // 字符串尾附输入字符
            cout << '*'; // 输出 *
        } else if (chr == '\b') { // 输入了 退格
            if (!input.empty()) { // 还没有清空
                cout << "\b \b"; // 清空刚刚的一个*，用" "替代
                input.pop_back(); // 拿走字符串中最后一个字符
            }
        }
    }
    cout << endl;
    return input == judged_str;
}

string account_manager::password_input_with_fmt_then_return_it()
{
    string input;
    char chr = '\0';
    while (chr != '\r') { // 未输入 回车
        chr = _getch(); // 获取键入的字符
        if (chr != '\r' && chr != '\b') { // 未输入 退格 / 回车
            input += chr; // 字符串尾附输入字符
            cout << '*'; // 输出 *
        } else if (chr == '\b') { // 输入了 退格
            if (!input.empty()) { // 还没有清空
                cout << "\b \b"; // 清空刚刚的一个*，用" "替代
                input.pop_back(); // 拿走字符串中最后一个字符
            }
        }
    }
    cout << endl;
    return input;
}

//解析接口函数
string account_manager::return_account_name() const
{
    string result = login->account_str;
    return result;
}

string account_manager::return_account_password() const
{
    string result = login->password_str;
    return result;
}

account_manager::~account_manager()
{
    delete cache_base;
    cache_base = nullptr;
}
