/*
 * Curriculum_Design
 * By: Eden Wang (162110335_���ĺ�)
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
    cout << R"(����ʽ��¼ǰ���������Ҫ��ʱ����һ������ʱĿ¼�����Դ�������ļ�)" << endl;
    Sleep(350);
    cout << R"(�����·��Ϊ => C:\Users(����Դ�������У���һ��Ŀ¼��ʾΪ���û���)\edwar\Desktop\cpp_final_task)" << endl;
    Sleep(350);
    // const string main_file_root_ = R"(C:\Users\edwar\Desktop\cpp_final_task)";
    const string first = R"(C:\Users\edwar)";
    const string second = R"(C:\Users\edwar\Desktop)";
    const string third = R"(C:\Users\edwar\Desktop\cpp_final_task)";
    if (_access(first.c_str(), 0) == -1) {
        if (_mkdir(first.c_str()) == 0) {
            // success
        } else {
            cout << "����" << first << " Ŀ¼ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
    if (_access(second.c_str(), 0) == -1) {
        if (_mkdir(second.c_str()) == 0) {
            // success
        } else {
            cout << "����" << second << " Ŀ¼ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
    if (_access(third.c_str(), 0) == -1) {
        if (_mkdir(third.c_str()) == 0) {
            // success
        } else {
            cout << "����" << third << " Ŀ¼ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
}

int main()
{
    pre_generate_folders();
    // ���� �ǿչ��캯�� �� ר��ռλ���
    const string param = "initialization_flag";
    // ��¼
    auto* login_kernel = new account_manager(param);
    int returned_value = login_kernel->shell_of_account_login();
    string returned_account_name = login_kernel->return_account_name();
    // ��¼�ɹ�
    delete login_kernel;
    /* ---- �����֧ ---- */
    if (returned_value == 1) {
        // admin_info_receiver ������Ϣ
        // admin_info_receiver admin_transmitter(returned_account_name);
        auto* admin_trans = new admin_info_receiver(returned_account_name);
        delete admin_trans;
        // ���յ�ǰ admin ����
        const string& current_account = returned_account_name;
        /// argv = current_account
        // ���� ����Ա����
        auto* admin_module = new admin_interface(current_account);
        admin_module->shell_of_admin_interface();
        delete admin_module;
    } else {
        // user_info_receiver ������Ϣ
        // user_info_receiver user_transmitter(returned_account_name);
        auto* user_trans = new user_info_receiver(returned_account_name);
        // ���յ�ǰ user ����
        const string& current_account = returned_account_name;
        const string& real_name = user_trans->return_real_name();
        const string& student_number = user_trans->return_student_number();
        const string& dorm_number = user_trans->return_dorm_number();
        delete user_trans;
        /// argv = current_account, real_name, student_number, dorm_number
        // ���� �û�����
        auto* user_module = new user_interface(current_account, real_name, student_number, dorm_number);
        user_module->shell_of_user_interface();
        delete user_module;
    }
    /* ----------------- */

    // ------------------------ END OF PROGRAM ------------------------ //

    // ���мܹ������� [�û�/����Ա ����] ���޷�ע���ص�¼���棬ֻ�ܽ�������ȫ�˳� //
}
