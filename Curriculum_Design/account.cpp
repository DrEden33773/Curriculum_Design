#include "account.h"
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random> // 生成随机数
#include <string>
#include <utility>
#include <windows.h>
#include <winerror.h>

using namespace std;

/*  不必在派生类的构造函数中调用基类的构造函数，
    load_used_time_from_file内含初始化基类的过程  */
account_manager::account_manager()
{ // 先初始化
    load_used_time_from_file(); // 再读文件
}

//后处理函数
auto account_manager::if_password_legal(string temp_password) -> bool
{
    bool result = false;
    bool if_length = false;
    bool if_number = false;
    bool if_letter = false;
    int len = temp_password.length(); // 获取长度
    if (len >= 8)
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

void account_manager::write_account_to_list(
    string temp_account,
    string temp_password,
    bool if_admin,
    char* temp_sp_code)
{
    auto* c = new account_info;
    c->account = std::move(temp_account);
    c->password = std::move(temp_password);
    c->if_admin = if_admin;
    strcpy_s(c->sp_code, temp_sp_code);
    c->next = nullptr;
    c->prev = nullptr;
    if (!head) {
        head = c;
        tail = c;
    } else {
        tail->next = c;
        c->prev = tail;
        tail = c;
    }
}

void account_manager::write_account_to_cache(
    string temp_account,
    string temp_password,
    bool if_admin,
    char* temp_sp_code)
{
    // 已重构
    cache2 = new account_info;
    cache2->account = std::move(temp_account);
    cache2->password = std::move(temp_password);
    cache2->if_admin = if_admin;
    strcpy_s(cache2->sp_code, temp_sp_code);
    cache2->next = nullptr;
    cache2->prev = nullptr;
    // 不要解除空间
}

void account_manager::write_list_to_file_trunc()
{
    fstream file;
    file.open(file_location, ios::binary | ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "打开account_info.dat失败，即将退出程序" << endl;
        Sleep(150);
        exit(-1);
    } else {
        account_info* c;
        for (c = head; c; c = c->next) {
            file.write((char*)(c), sizeof(account_info));
        }
        file.close();
        //此时c指空，没必要delete
    }
}

// write_list_to_file_app
void account_manager::write_list_to_file_app()
{
    fstream file;
    file.open(file_location, ios::binary | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "写入文件过程中，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    } else {
        file.write((char*)(cache2), sizeof(account_info));
    }
    delete cache2;
    file.close();
}

// change_account_password_in_file
void account_manager::change_account_password_in_file(const string& changed_account)
{
    int POS;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "修改密码前，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    }
    auto* temp = new account_info;
    while (file.read((char*)(temp), sizeof(account_info))) {
        if (changed_account == temp->account) {
            POS = file.tellg(); // g => 读指针
            break;
        }
    }
    delete temp;
    file.close();
    file.open(file_location, ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "修改密码前，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    }
    file.seekp(POS, ios::beg);
    file.write((char*)(cache2), sizeof(account_info));
    file.close();
}

void account_manager::load_file_to_list()
{
    auto* c = new account_info;
    fstream file;
    file.open(file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开account_info.dat失败，即将退出程序" << endl;
        Sleep(150);
        exit(-1);
    } else {
        while (file.read((char*)(cache), sizeof(account_info))) {
            write_account_to_list(
                c->account,
                c->password,
                c->if_admin,
                c->sp_code);
        }
        // delete cache; //加上就报错
        file.close();
    }
}

auto account_manager::check_account(
    const string& input_account,
    const string& input_password) -> int
{
    // 全新的逻辑 -- 直接从文件检索
    bool if_account_exists = false;
    bool if_password_correct = false;
    int result = -2;
    cache2 = new account_info;
    fstream file(account_info_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "检索账号信息时，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read((char*)(cache), sizeof(account_info))) {
        if (cache2->account == input_account) {
            if_account_exists = true;
            if (cache2->password == input_password) {
                if_password_correct = true;
                if (cache2->if_admin)
                    result = 1;
                else
                    result = 0;
            }
        }
    }
    if (!if_account_exists)
        result = -2;
    else if (!if_password_correct)
        result = -1;
    delete cache2;
    file.close();
    return result;
}

account_manager::account_info* account_manager::if_account_exists(const string& temp_account)
{
    account_info* c;
    for (c = head; c; c = c->next) {
        if (c->account == temp_account) {
            break;
        }
    }
    return c;
}

auto account_manager::generate_sp_code() -> char*
{
    char* temp = new char[11];
    uniform_int_distribution<unsigned> u(0, 9);
    default_random_engine e(time(nullptr)); // 种子=当前时间，确保种子不重样，确保真随机数的产生
    for (int i = 0; i < 11; i++) {
        temp[i] = ('0' + u(e));
    }
    temp[10] = '\0';
    return temp;
}

void account_manager::change_account_in_list(
    account_manager::account_info* changed_account,
    string changed_password,
    char* changed_sp_code)
{
    changed_account->password = std::move(changed_password);
    strcpy_s(changed_account->sp_code, changed_sp_code);
}

void account_manager::change_account_in_cache(
    account_manager::account_info* changed_account,
    string changed_password,
    char* changed_sp_code)
{
    changed_account->password = std::move(changed_password);
    strcpy_s(changed_account->sp_code, changed_sp_code);
}

auto account_manager::if_sp_code_is_correct(
    const string& temp_account,
    char* temp_sp_code) -> account_manager::account_info*
{
    cache2 = new account_info;
    account_info* result = nullptr;
    fstream account_into_file(account_info_file_location, ios::in | ios::binary);
    if (!account_into_file.is_open()) {
        cout << "检索账号信息时，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (account_into_file.read((char*)(cache), sizeof(account_info))) {
        if (cache2->account == temp_account && strcmp(cache2->sp_code, temp_sp_code) == 0) {
            result = cache2;
            break;
        }
    }
    account_into_file.close();
    return result;
}

auto account_manager::if_sp_code_exits(char* temp_sp_code) -> account_manager::account_info*
{
    bool if_found = false;
    cache2 = new account_info;
    account_info* result = nullptr;
    fstream account_into_file(account_info_file_location, ios::in | ios::binary);
    if (!account_into_file.is_open()) {
        cout << "检索账号信息前，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (account_into_file.read((char*)(cache2), sizeof(account_info))) {
        if (strcmp(cache2->sp_code, temp_sp_code) == 0) {
            if_found = true;
            result = cache2;
            break;
        }
    }
    account_into_file.close();
    return result;
}

// interface-函数
auto account_manager::shell_of_account_login() -> int // 需要在调试层，主动进入，并不会在构造函数中进入
{
    int judger = -1;
    int temp_used_time = get_used_time();
    if (temp_used_time == 0) { //还未使用过软件
        first_create_account();
    }
    if (temp_used_time != 0) {
        // load_file_to_list(); //不是第一次使用，才把"账号信息"导入缓存
        // 重构之后，不用完全加载了，DFD [Direct from disk]
    }
    cout << "欢迎使用 [疫情防控一体化管理系统]，即将进入登录页面" << endl
         << endl;
    for (;;) {
        cout << "下面显示登录选项：" << endl;
        cout << "====================================================" << endl;
        cout << "     1.使用--账号密码--登录" << endl;
        cout << "     2.使用--凭据文件--登录" << endl;
        cout << "     3.新建账号" << endl;
        cout << "     4.忘记密码/修改密码" << endl;
        cout << "     5.再次显示功能列表" << endl;
        cout << "     6.取消登录并退出程序" << endl;
        cout << "====================================================" << endl;
        cout << "请输入对应序号(输入5再次显示功能列表): ";
        int temp;
        cin >> temp;
        cout << endl
             << endl;
        if (temp == 6) { // 这里也需要更新 账号个数 对应的 文件
            cout << "取消登录，程序即将自动退出" << endl;
            Sleep(300);
            exit(1);
        } else if (temp == 1) {
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
                break;
            }
        } else if (temp == 2) {
            judger = sign_in_by_sp_code();
            if (judger == -2) {
                cout << "不存在与这个凭据码匹配的账户，即将再次显示登录选项" << endl
                     << endl;
                Sleep(150);
                // system("cls"); //清屏
            } else if (judger == -1) { // sp_code登录，不存在返回-1的情况
                cout << "账户存在，但是密码错误！即将再次显示登录选项" << endl
                     << endl;
                Sleep(150);
                // system("cls"); //清屏
            } else {
                break;
            }
        } else if (temp == 3) {
            create_account();
        } else if (temp == 4) {
            change_password();
        } else if (temp == 5) {
            system("cls");
            continue;
        } else {
            cout << "没有与" << temp << "对应的功能，即将再次显示登录选项" << endl
                 << endl;
            Sleep(150);
            // system("cls"); //清屏
        }
    }
    delete_list();
    return judger;
}

void account_manager::first_create_account()
{
    string temp_account;
    string temp_password;
    string temp_password_check;
    bool if_this_is_admin = true;
    bool if_try_again = false;
    //输入信息
    cout << "首次使用系统，请先创建一个管理员账号！" << endl;
    while (true) {
        cout << "请输入 <用户名> ： ";
        cin >> temp_account;
        if (if_account_exists(temp_account)) {
            system("cls");
            cout << "已存在该账号，请重新输入 <用户名> ！" << endl;
            Sleep(250);
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
            cout << "请输入刚刚设置的 <密码> ： ";
            cin >> temp_password_check; //需要“密文显示”
            if (temp_password_check == temp_password) {
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
    char* temp_so_code = generate_sp_code();
    //存入链表
    write_account_to_list(temp_account, temp_password, if_this_is_admin, temp_so_code);
    //链表存入文件
    write_list_to_file_trunc();
    //根据条件，选择是否更新“管理员账号数目”
    if (cache2->if_admin == true)
        update_used_time();
    //新的账号数量写入文件
    write_used_time_into_file();
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
        cout << "请输入 <用户名> ： ";
        cin >> temp_account;
        if (if_account_exists(temp_account)) {
            system("cls");
            cout << "已存在该账号，请重新输入 <用户名> ！" << endl;
            Sleep(250);
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
            cout << "请输入刚刚设置的 <密码> ： ";
            cin >> temp_password_check; //需要“密文显示”
            if (temp_password_check == temp_password) {
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
    char* temp_so_code = generate_sp_code();
    // 写入cache
    write_account_to_cache(temp_account, temp_password, if_this_is_admin, temp_so_code);
    // cache写入文件尾部
    write_list_to_file_app();
    // 根据条件更新--管理员账号数目
    if (cache2->if_admin == true)
        update_used_time();
    // 新的账号数量写入文件
    write_used_time_into_file();
    // 展示凭据码
    cout << "已创建账户，生成的凭据码为：" << temp_so_code << endl;
    cout << "请务必牢记您的凭据码，这将是您找回的[管理员账户<密码>]的唯一凭据，也将是您找回[普通账户<密码>]的重要凭据！" << endl;
    cout << "牢记凭据码后，输入任意字符继续 >>> ";
    char skipper;
    cin >> skipper;
    Sleep(100);
    system("cls");
}

auto account_manager::sign_in_by_account() -> int
{
    string temp_account;
    string temp_password;
    int temp_result;
    cout << "请输入用户名：";
    cin >> temp_account;
    cout << "请输入密码：";
    cin >> temp_password;
    temp_result = check_account(temp_account, temp_password);
    if (temp_result != -2 && temp_result != -1) {
        give_the_plug_of_account(temp_account, temp_password);
    }
    return temp_result;
}

auto account_manager::sign_in_by_sp_code() -> int
{
    // 待会用 cache2，记得解除占用
    int temp_result = 0;
    char temp_sp_code[11];
    account_info* c;
    cout << "请输入<凭据码>：";
    cin >> temp_sp_code;
    c = if_sp_code_exits(temp_sp_code);
    if (!c) {
        temp_result = -2;
    } else {
        give_the_plug_of_account(temp_sp_code);
    }
    if (temp_result != -2) {
        if (c->if_admin)
            temp_result = 1;
    }
    delete cache2; // 这里终于可以删除了
    return temp_result;
}

void account_manager::change_password()
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
            if (!if_account_exists(temp_account)) {
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
            temp_account_ptr = if_sp_code_is_correct(temp_account, temp_sp_code); // 用到 cache2
            if (temp_account_ptr) {
                if_go_next = true;
                break;
            } else {
                cout << "<凭据码> 和 <账号> 不匹配，输入Y=>再次输入<凭据码>，输入其他字符=>重新输入<用户名>" << endl;
                char temp;
                cin.get(temp);
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
    cout << "<凭据码>和<用户名>成功匹配，即将允许您设置<新密码>" << endl;
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
            cout << "请输入刚刚设置的 <新密码> ： ";
            cin >> temp_password_check; //需要“密文显示”
            if (temp_password_check == temp_password) {
                system("cls");
                cout << "密码修改成功" << endl
                     << endl;
                Sleep(150);
                break;
            } else {
                cout << "两次输入的密码不一致，按A=>重新设置密码，输入其他字符=>再次尝试输入刚刚设置的新密码：" << endl;
                char temp;
                cin.get(temp);
                if (temp == 'B') {
                    continue;
                } else {
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
    char* temp_so_code = generate_sp_code();
    // 改写缓存
    change_account_in_list(temp_account_ptr, temp_password, temp_so_code);
    // 更改文件中对应的密码
    change_account_password_in_file(temp_account);
    // 展示凭据码
    cout << "重新生成的凭据码为：" << temp_so_code << endl;
    cout << "请务必牢记您的凭据码，这将是您找回的[管理员账户<密码>]的唯一凭据，也将是您找回[普通账户<密码>]的重要凭据！" << endl;
    cout << "牢记凭据码后，请输入任意字符后继续 >>> ";
    char skipper;
    cin >> skipper;
    delete cache2; // 解除cache2
    Sleep(100);
    system("cls");
}

//接口函数
void account_manager::give_the_plug_of_account(
    const string& input_account,
    const string& input_password)
{
    login = new account_info;
    account_info* c;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "传递参数时，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    }
    while (file.read((char*)(c), sizeof(account_info))) {
        if (c->account == input_account) {
            if (c->password == input_password) {
                login->account = c->account;
                login->password = c->password;
                strcpy_s(login->sp_code, c->sp_code); // unsafe函数应该禁止，所以是strcpy_s，如有报错，后续处理
                login->if_admin = c->if_admin;
                break;
            }
        }
    }
}

void account_manager::give_the_plug_of_account(char* input_sp_code)
{
    login = new account_info;
    account_info* c;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "传递参数时，打开 account_info.dat 失败！即将退出程序 ... " << endl;
        Sleep(150);
        exit(-1);
    }
    while (file.read((char*)(c), sizeof(account_info))) {
        if (strcmp(c->sp_code, input_sp_code) == 0) {
            login->account = c->account;
            login->password = c->password;
            strcpy_s(login->sp_code, c->sp_code); // unsafe函数应该禁止，所以是strcpy_s，如有报错，后续处理
            login->if_admin = c->if_admin;
            break;
        }
    }
}

//解析接口函数
auto account_manager::return_account_name() -> string
{
    return login->account;
}
auto account_manager::return_account_password() -> string
{
    return login->password;
}

//解除链表空间占用
void account_manager::delete_list()
{
    account_info* t = head;
    if ((!t->next) && (!t->prev)) { // 孤节点
        delete t;
    } else {
        for (t = tail->prev; t; t = t->prev) {
            delete t->next;
        }
        // now, t comes to head
        delete head; // the same to " delete t; "
    }
}
