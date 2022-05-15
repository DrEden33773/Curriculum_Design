/*
 * Curriculum_Design
 * By: Eden Wang
 *
 * Used IDE: Clion 2021.3, Visual Studio Code, Visual Studio 2022, Rider 2022.1
 * File linker: MSBuild, CMAKE
 * Compiler: GCC, CLANG, MSVC => ALL SUCCESS
 * Debugger: GDB, Clang-LLDB, MSVC-LLDB => ALL SUCCESS
 * Useful plugins: ReSharper, Clangd, Clang-Format, Clang-Tidy
 * CppStandard: C++14
 * Formatting Style: WebKit
 * File encoding system: GBK <=> GB2312 <=> GB18030
 *
 * /// WARNING: DO NOT Read/Write Any Class With String From/Into A Binary File ///
 *
 */


#define _CRT_SECURE_NO_WARNINGS
#include "account.h"
#include "admin_AccountInfoReceiver.h"
#include "admin_interface.h"
#include "user_AccountInfoReceiver.h"
#include "user_interface.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    // ���� �ǿչ��캯�� �� ר��ռλ���
    const string argm = "initialization_flag";
    // ��¼
    auto* login_kernel = new account_manager(argm);
    int returned_value = login_kernel->shell_of_account_login();
    string returned_account_name = login_kernel->return_account_name();
    // ��¼�ɹ�
    delete login_kernel;

    /* ---- ������ ---- */
    {
        cout << "up to now(after login), everything goes normal!" << endl;
        cout << "input Y/y to exit, input any other letter(except empty ones) to continue >> ";
        string flag;
        cin >> flag;
        if (flag == "Y" || flag == "y") {
            exit(0);
        }
        system("cls");
    }
    /* --------------- */

    /* ---- �����֧ ---- */
    if (returned_value == 1) {
        // admin_info_receiver ������Ϣ
        admin_info_receiver admin_transmitter(returned_account_name);
        // ���յ�ǰ admin ����
        const string& current_account = returned_account_name;
        /// argv = current_account
        // ���� ����Ա����
        auto* admin_module = new admin_interface(current_account);
        admin_module->shell_of_admin_interface();
        delete admin_module;
    } else {
        // user_info_receiver ������Ϣ
        user_info_receiver user_transmitter(returned_account_name);
        // ���յ�ǰ user ����
        const string& current_account = returned_account_name;
        const string& real_name = user_transmitter.return_real_name();
        const string& student_number = user_transmitter.return_student_number();
        const string& dorm_number = user_transmitter.return_dorm_number();
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
