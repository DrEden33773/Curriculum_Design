#include "user_interface.h"
#include "daily_health_check_user.h"
#include "necessary_affairs_manager.h"
#include "NAT_user.h"
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

user_interface::user_interface(
    const string& c_account,
    const string& real_name,
    const string& student_number,
    const string& dorm_number)
{
    this->c_account = c_account;
    this->real_name = real_name;
    this->student_number = student_number;
    this->dorm_number = dorm_number;
    goto_necessary_affairs_check(true); // 进入待办事项平台，并且强制进行催促
}

void user_interface::shell_of_user_interface() const
{
    system("cls");
    cout << endl;
    cout << "欢迎使用 [疫情防控一体化管理平台 <用户端>] !" << endl;
    cout << endl;
    show_current_user_info();
    Sleep(250);
    cout << "下面显示 <用户端功能菜单> ... " << endl;
    while (true) {
        cout << "<用户端功能菜单>" << endl;
        cout << "=======================================================" << endl;
        cout << "\t" << "0.进入 <当前用户待办事项> 综合管理平台" << endl;
        cout << "\t" << "1.进入 <健康打卡> 平台" << endl;
        cout << "\t" << "2.进入 <核酸检测信息发布> 平台" << endl;
        cout << "\t" << "3.进入 <志愿者服务> 平台 (未开发)" << endl;
        cout << "\t" << "4.进入 <防疫政策信息发布> 平台 (未开发)" << endl;
        cout << "\t" << "5.进入 <留言板> 模块 (未开发)" << endl;
        cout << "\t" << "6.再次显示 <此账号> 具体信息" << endl;
        cout << "\t" << "7.再次显示 <用户端功能菜单>" << endl;
        cout << "\t" << "8.直接退出程序" << endl;
        cout << "=======================================================" << endl;
        cout << "请输入 相应的数字 >> ";
        string flag;
        cin >> flag;
        if (flag == "1") {
            goto_daily_check();
        } else if (flag == "2") {
            goto_nat_check();
        } else if (flag == "3") {
            cout << R"(目前尚未开发 <志愿者服务> 平台！即将重新显示 <用户端功能菜单> ... )" << endl;
            Sleep(250);
        } else if (flag == "4") {
            cout << R"(目前尚未开发 <防疫政策信息发布> 平台！即将重新显示 <用户端功能菜单> ... )" << endl;
            Sleep(250);
        } else if (flag == "5") {
            cout << R"(目前尚未开发 <留言板> 平台！即将重新显示 <用户端功能菜单> ... )" << endl;
            Sleep(250);
        } else if (flag == "6") {
            cout << "收到，即将重新显示 <当前账号信息> ... " << endl;
            Sleep(250);
            show_current_user_info();
        } else if (flag == "7") {
            cout << "收到，即将重新显示 <用户端功能菜单> ... " << endl;
            Sleep(250);
        } else if (flag == "0") {
            goto_necessary_affairs_check(false);
        } else if (flag == "8") {
            cout << "即将退出 [疫情防控一体化管理平台]，感谢您的使用 (*^ω^*) ... " << endl;
            Sleep(500);
            exit(1); // 正常退出
        } else {
            cout << "抱歉，尚未开发此功能！即将重新显示 <用户端功能菜单> ... " << endl;
            Sleep(350);
        }
    }
}

void user_interface::show_current_user_info() const
{
    cout << "当前登录的用户信息如下：" << endl;
    cout.setf(ios::left);
    cout << "\t" << "用户名：" << c_account;
    cout << "\t" << "真实姓名：" << real_name;
    cout << "\t" << "学号：" << student_number;
    cout.unsetf(ios::left);
    cout << endl;
}

void user_interface::goto_daily_check() const
{
    // 形参顺序 => real_name, c_account, student_number
    daily_health_check_user daily_health_check(this->real_name, this->c_account, this->student_number);
    system("cls");
    // END OF MODULE
}

void user_interface::goto_nat_check() const
{
    // 形参顺序 =>
    NAT_user user_NAT_check(this->real_name, this->student_number, this->dorm_number, false);
    user_NAT_check.shell_of_user_NAT_check();
    system("cls");
    // END OF MODULE
}

void user_interface::goto_necessary_affairs_check(const bool& if_ask_to_finish) const
{
    necessary_affairs_manager unfinished_affairs_manager
        (c_account, real_name, student_number, dorm_number, if_ask_to_finish);
    system("cls");
}

// 接口函数
string user_interface::return_c_account()
{
    return this->c_account;
}

string user_interface::return_real_name()
{
    return this->real_name;
}

string user_interface::return_student_number()
{
    return this->student_number;
}
