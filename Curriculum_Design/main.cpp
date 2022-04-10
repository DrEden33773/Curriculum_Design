/*
 * Curriculum_Design
 * By: Eden Wang (162110335_王文翰)
 *
 * Used IDE: Clion 2021.3, Visual Studio Code, Visual Studio 2022, Rider 2022.1
 * Makefile_tools: MSBuild, CMAKE
 * Compiler: CLANG(in VS2022), MSVC(MSVC_v143) => ALL SUCCESS
 * Debugger: Clang-LLDB, MSVC-LLDB => ALL SUCCESS
 * Critical plugins: ReSharper, Clangd, Clang-Format, Clang-Tidy
 * CppStandard: C++14
 * Formatting Style: WebKit
 * File encoding system: GBK/GB18030/GB2312
 *
 * WARNING: DO NOT Read/Write Any Class With String From/Into A Binary File
 *
 */

#define _CRT_SECURE_NO_WARNINGS
#include <corecrt_io.h>
#include <direct.h>

#include "account.h"
#include "admin_AccountInfoReceiver.h"
#include "admin_interface.h"
#include "user_AccountInfoReceiver.h"
#include "user_interface.h"
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

void pre_generate_folders()
{
    cout << R"(在正式登录前，本软件需要暂时创建一个“临时目录”用以存放数据文件)" << endl;
    Sleep(350);
    cout << R"(其绝对路径为 => C:\Users(在资源管理器中，这一级目录显示为“用户”)\edwar\Desktop\cpp_final_task)" << endl;
    Sleep(350);
    // const string main_file_root_ = R"(C:\Users\edwar\Desktop\cpp_final_task)";
    const string first = R"(C:\Users\edwar)";
    const string second = R"(C:\Users\edwar\Desktop)";
    const string third = R"(C:\Users\edwar\Desktop\cpp_final_task)";
    if (_access(first.c_str(), 0) == -1) {
        if (_mkdir(first.c_str()) == 0) {
            // success
        } else {
            cout << "创建" << first << " 目录失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
    if (_access(second.c_str(), 0) == -1) {
        if (_mkdir(second.c_str()) == 0) {
            // success
        } else {
            cout << "创建" << second << " 目录失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
    if (_access(third.c_str(), 0) == -1) {
        if (_mkdir(third.c_str()) == 0) {
            // success
        } else {
            cout << "创建" << third << " 目录失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
}

int main()
{
    pre_generate_folders();
    // 调用 非空构造函数 的 专用占位标记
    const string param = "initialization_flag";
    // 登录
    auto* login_kernel = new account_manager(param);
    int returned_value = login_kernel->shell_of_account_login();
    string returned_account_name = login_kernel->return_account_name();
    // 登录成功
    delete login_kernel;
    /* ---- 两大分支 ---- */
    if (returned_value == 1) {
        // admin_info_receiver 过渡信息
        // admin_info_receiver admin_transmitter(returned_account_name);
        auto* admin_trans = new admin_info_receiver(returned_account_name);
        delete admin_trans;
        // 接收当前 admin 参数
        const string& current_account = returned_account_name;
        /// argv = current_account
        // 进入 管理员界面
        auto* admin_module = new admin_interface(current_account);
        admin_module->shell_of_admin_interface();
        delete admin_module;
    } else {
        // user_info_receiver 过渡信息
        // user_info_receiver user_transmitter(returned_account_name);
        auto* user_trans = new user_info_receiver(returned_account_name);
        // 接收当前 user 参数
        const string& current_account = returned_account_name;
        const string& real_name = user_trans->return_real_name();
        const string& student_number = user_trans->return_student_number();
        const string& dorm_number = user_trans->return_dorm_number();
        delete user_trans;
        /// argv = current_account, real_name, student_number, dorm_number
        // 进入 用户界面
        auto* user_module = new user_interface(current_account, real_name, student_number, dorm_number);
        user_module->shell_of_user_interface();
        delete user_module;
    }
    /* ----------------- */

    // ------------------------ END OF PROGRAM ------------------------ //

    // 现有架构，进入 [用户/管理员 界面] 后，无法注销回登录界面，只能将程序完全退出 //
}
