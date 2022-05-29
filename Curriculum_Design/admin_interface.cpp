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
    cout << "��ӭʹ�� [�������һ�廯����ƽ̨ <����Ա��>] !" << endl;
    cout << endl;
    Sleep(250);
    show_current_user_info();
    cout << "������ʾ <����Ա�˹��ܲ˵�> ... " << endl;
    Sleep(250);
    while (true) {
        cout << "<����Ա�˹��ܲ˵�>" << endl;
        cout << "=======================================================" << endl;
        cout.setf(ios::right);
        cout << "\t" << "1.���� <������> ����ƽ̨" << endl;
        cout << "\t" << "2.���� <��������Ϣ> ����ƽ̨" << endl;
        cout << "\t" << "3.���� <��ͨ�û���Ϣ> ����ƽ̨" << endl;
        cout << "\t" << "4.���� <־Ը�߷���> ����ƽ̨ (δ����)" << endl;
        cout << "\t" << "5.���� <����������Ϣ> ����ƽ̨ (δ����)" << endl;
        cout << "\t" << "6.���� <���԰�> ģ�� (δ����)" << endl;
        cout << "\t" << "7.���� <ʡ�����������������Ϣ> ģ��" << endl;
        cout << "\t" << "8.�ٴ���ʾ <���˺�> ������Ϣ" << endl;
        cout << "\t" << "9.�ٴ���ʾ <�û��˹��ܲ˵�>" << endl;
        cout << "\t" << "10.ֱ���˳�����" << endl;
        cout << "=======================================================" << endl;
        cout << "������ ��Ӧ������ >> ";
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
            cout << "�յ�������������ʾ <����Ա�˹��ܲ˵�> ... " << endl;
            Sleep(250);
        } else if (flag == "10") {
            // TODO: exit
            cout << "�����˳� [�������һ�廯����ƽ̨]����л����ʹ�� (*^��^*) ... " << endl;
            Sleep(500);
            exit(1); // �����˳�
        } else if (flag == "3") {
            // TODO: go to account_info_manager module
            goto_account_info_manager();
        } else if (flag == "7") {
            // TODO: go to province_info_manager module
            goto_province_info_manager();
        } else {
            cout << "�ǳ���Ǹ����δ������Ӧ���ܣ�����������ʾ <����Ա�˹���˵�> ... " << endl;
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
    cout << "��ǰ��¼���û���Ϣ���£�" << endl;
    cout.setf(ios::left);
    cout << "=======================================================" << endl;
    cout << "\t" << "�û�����" << c_account;
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
