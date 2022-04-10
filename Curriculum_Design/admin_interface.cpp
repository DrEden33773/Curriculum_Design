#include "admin_interface.h"
#include "account_info_manager.h"
#include "province_information_manager.h"
#include "daily_health_check_admin.h"
#include "NAT_admin.h"
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

admin_interface::admin_interface(const string& input_account)
{
    this->c_account = input_account;
}

void admin_interface::shell_of_admin_interface() const
{
    system("cls");
    cout << endl;
    cout << "欢迎使用 [疫情防控一体化管理平台 <管理员端>] !" << endl;
    cout << endl;
    Sleep(250);
    show_current_user_info();
    cout << "下面显示 <管理员端功能菜单> ... " << endl;
    Sleep(250);
    while (true) {
        cout << "<管理员端功能菜单>" << endl;
        cout << "=======================================================" << endl;
        cout.setf(ios::right);
        cout << "\t" << "1.进入 <健康打卡> 管理平台" << endl;
        cout << "\t" << "2.进入 <核酸检测信息> 管理平台" << endl;
        cout << "\t" << "3.进入 <普通用户信息> 管理平台" << endl;
        cout << "\t" << "4.进入 <志愿者服务> 管理平台 (未开发)" << endl;
        cout << "\t" << "5.进入 <防疫政策信息> 管理平台 (未开发)" << endl;
        cout << "\t" << "6.进入 <留言板> 模块 (未开发)" << endl;
        cout << "\t" << "7.进入 <省级行政区疫情防控信息> 模块" << endl;
        cout << "\t" << "8.再次显示 <此账号> 具体信息" << endl;
        cout << "\t" << "9.再次显示 <用户端功能菜单>" << endl;
        cout << "\t" << "10.直接退出程序" << endl;
        cout << "=======================================================" << endl;
        cout << "请输入 相应的数字 >> ";
        string flag;
        cin >> flag;
        if (flag == "1") {
            // TODO: go to daily_health_check_admin module
            goto_daily_health_check_admin();
        } else if (flag == "2") {
            // TODO: go to NAT_admin module
            goto_nat_admin();
        } else if (flag == "8") {
            // TODO: show_current_user_info
            show_current_user_info();
        } else if (flag == "9") {
            // TODO: continue_the_loop
            cout << "收到！即将重新显示 <管理员端功能菜单> ... " << endl;
            Sleep(250);
        } else if (flag == "10") {
            // TODO: exit
            cout << "即将退出 [疫情防控一体化管理平台]，感谢您的使用 (*^ω^*) ... " << endl;
            Sleep(500);
            exit(1); // 正常退出
        } else if (flag == "3") {
            // TODO: go to account_info_manager module
            goto_account_info_manager();
        } else if (flag == "7") {
            // TODO: go to province_info_manager module
            goto_province_info_manager();
        } else {
            cout << "非常抱歉，暂未开发对应功能！即将重新显示 <管理员端管理菜单> ... " << endl;
            Sleep(250);
        }
    }
}

string admin_interface::return_c_account()
{
    return this->c_account;
}

void admin_interface::goto_province_info_manager()
{
    province_information_manager mod; // use its constructor
    mod.shell_admin();
    system("cls");
}

void admin_interface::show_current_user_info() const
{
    cout << "当前登录的用户信息如下：" << endl;
    cout.setf(ios::left);
    cout << "=======================================================" << endl;
    cout << "\t" << "用户名：" << c_account;
    cout << endl;
    cout << "=======================================================" << endl;
    cout << endl;
    cout.unsetf(ios::left);
    Sleep(250);
}

void admin_interface::goto_nat_admin()
{
    NAT_admin nat_admin_module; // use its constructor
    nat_admin_module.shell_of_NAT_admin();
    system("cls");
}

void admin_interface::goto_daily_health_check_admin()
{
    daily_health_check_admin daily_health_check_admin_module; // use its constructor
    daily_health_check_admin_module.shell_of_nat_admin();
    system("cls");
}

void admin_interface::goto_account_info_manager()
{
    account_info_manager account_info_manager_module; // use its constructor
    account_info_manager_module.shell_of_account_info_manager();
    system("cls");
}
