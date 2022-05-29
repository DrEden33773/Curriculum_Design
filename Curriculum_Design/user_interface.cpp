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
    goto_necessary_affairs_check(true); // �����������ƽ̨������ǿ�ƽ��дߴ�
}

void user_interface::shell_of_user_interface() const
{
    system("cls");
    cout << endl;
    cout << "��ӭʹ�� [�������һ�廯����ƽ̨ <�û���>] !" << endl;
    cout << endl;
    show_current_user_info();
    Sleep(250);
    cout << "������ʾ <�û��˹��ܲ˵�> ... " << endl;
    while (true) {
        cout << "<�û��˹��ܲ˵�>" << endl;
        cout << "=======================================================" << endl;
        cout << "\t" << "0.���� <��ǰ�û���������> �ۺϹ���ƽ̨" << endl;
        cout << "\t" << "1.���� <������> ƽ̨" << endl;
        cout << "\t" << "2.���� <��������Ϣ����> ƽ̨" << endl;
        cout << "\t" << "3.���� <־Ը�߷���> ƽ̨ (δ����)" << endl;
        cout << "\t" << "4.���� <����������Ϣ����> ƽ̨ (δ����)" << endl;
        cout << "\t" << "5.���� <���԰�> ģ�� (δ����)" << endl;
        cout << "\t" << "6.�ٴ���ʾ <���˺�> ������Ϣ" << endl;
        cout << "\t" << "7.�ٴ���ʾ <�û��˹��ܲ˵�>" << endl;
        cout << "\t" << "8.ֱ���˳�����" << endl;
        cout << "=======================================================" << endl;
        cout << "������ ��Ӧ������ >> ";
        string flag;
        cin >> flag;
        if (flag == "1") {
            goto_daily_check();
        } else if (flag == "2") {
            goto_nat_check();
        } else if (flag == "3") {
            cout << R"(Ŀǰ��δ���� <־Ը�߷���> ƽ̨������������ʾ <�û��˹��ܲ˵�> ... )" << endl;
            Sleep(250);
        } else if (flag == "4") {
            cout << R"(Ŀǰ��δ���� <����������Ϣ����> ƽ̨������������ʾ <�û��˹��ܲ˵�> ... )" << endl;
            Sleep(250);
        } else if (flag == "5") {
            cout << R"(Ŀǰ��δ���� <���԰�> ƽ̨������������ʾ <�û��˹��ܲ˵�> ... )" << endl;
            Sleep(250);
        } else if (flag == "6") {
            cout << "�յ�������������ʾ <��ǰ�˺���Ϣ> ... " << endl;
            Sleep(250);
            show_current_user_info();
        } else if (flag == "7") {
            cout << "�յ�������������ʾ <�û��˹��ܲ˵�> ... " << endl;
            Sleep(250);
        } else if (flag == "0") {
            goto_necessary_affairs_check(false);
        } else if (flag == "8") {
            cout << "�����˳� [�������һ�廯����ƽ̨]����л����ʹ�� (*^��^*) ... " << endl;
            Sleep(500);
            exit(1); // �����˳�
        } else {
            cout << "��Ǹ����δ�����˹��ܣ�����������ʾ <�û��˹��ܲ˵�> ... " << endl;
            Sleep(350);
        }
    }
}

void user_interface::show_current_user_info() const
{
    cout << "��ǰ��¼���û���Ϣ���£�" << endl;
    cout.setf(ios::left);
    cout << "\t" << "�û�����" << c_account;
    cout << "\t" << "��ʵ������" << real_name;
    cout << "\t" << "ѧ�ţ�" << student_number;
    cout.unsetf(ios::left);
    cout << endl;
}

void user_interface::goto_daily_check() const
{
    // �β�˳�� => real_name, c_account, student_number
    daily_health_check_user daily_health_check(this->real_name, this->c_account, this->student_number);
    system("cls");
    // END OF MODULE
}

void user_interface::goto_nat_check() const
{
    // �β�˳�� =>
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

// �ӿں���
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
