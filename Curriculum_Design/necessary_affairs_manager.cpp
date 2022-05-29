#include "necessary_affairs_manager.h"

#include <conio.h>

#include "NAT_user.h"
#include "daily_health_check_user.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void necessary_affairs_manager::show_unfinished_tasks() const
{
    if (if_finished_daily_check && if_finished_all_nat_check_no_later_than_today) {
        cout << "����� ������ �� �������к����⣡û�д������" << endl;
        cout << "�� >>�������<< ���д����������������󣬽��ص� <�û��˹��ܲ˵�> ... " << endl;
        _getch();
    } else {
        cout << "���������У�" << endl;
        if (!if_finished_daily_check) {
            cout << "\t"
                 << "���� <ÿ�ս�����> ��" << endl;
        }
        if (!if_finished_all_nat_check_no_later_than_today) {
            cout << "\t"
                 << "��� <���պ�����> �˹�ȷ�� ��" << endl;
        }
    }
}

void necessary_affairs_manager::check_if_finished_daily_check()
{
    // ����Ƿ����ÿ�մ�
    // �β�˳�� => real_name, account, student_number, "flag"
    const auto* daily_health_check_checker
        = new daily_health_check_user(real_name, account, student_number, "flag");
    const bool if_unfinished_daily_check = daily_health_check_checker->plug_of_if_should_alert;
    if_finished_daily_check = !if_unfinished_daily_check;
    delete daily_health_check_checker;
}

void necessary_affairs_manager::check_if_finished_all_nat_check()
{
    // ����Ƿ���ɵ���� ���� ������
    const auto* nat_health_check_checker
        = new NAT_user(real_name, student_number, dorm_number, true);
    const bool if_unfinished_nat_check = nat_health_check_checker->return_if_have_unfinished_nat_no_later_than_today();
    if_finished_all_nat_check_no_later_than_today = !if_unfinished_nat_check;
    delete nat_health_check_checker;
}

void necessary_affairs_manager::unfinished_tasks_management()
{
    show_unfinished_tasks();
    if (if_finished_daily_check && if_finished_all_nat_check_no_later_than_today) {
        return;
    }
    if (if_push_to_finish) {
        if (!if_finished_daily_check && !if_finished_all_nat_check_no_later_than_today) {
            cout << "���չ��򣬽��� ��ָ�������<ÿ�ս�����>����ָ�����˹�ȷ��<���պ�����>���״̬ ... " << endl;
            Sleep(250);
            cout << "�Ե�Ƭ�̣�����������ָ������� <ÿ�ս�����> ... " << endl;
            Sleep(250);
            cout << "����������� ..." << endl;
            _getch();
            // daily_health_check_
            const auto* daily_health_check_
                = new daily_health_check_user(real_name, account, student_number);
            delete daily_health_check_;
            if_finished_daily_check = true;
            // TODO: nat_check_
            //
            cout << "�Ե�Ƭ�̣�����������ָ���� �˹�ȷ��<���պ�����>���״̬ ... " << endl;
            cout << "����������� ..." << endl;
            _getch();
            Sleep(250);
            const auto* nat_user_confirm_
                = new NAT_user(real_name, student_number, dorm_number, false);
            delete nat_user_confirm_;
            if_finished_all_nat_check_no_later_than_today = true;
        } else if (!if_finished_daily_check) {
            cout << "�Ե�Ƭ�̣�����������ָ������� <ÿ�ս�����> ... " << endl;
            Sleep(250);
            cout << "����������� ..." << endl;
            _getch();
            // daily_health_check_
            const auto* daily_health_check_
                = new daily_health_check_user(real_name, account, student_number);
            delete daily_health_check_;
            if_finished_daily_check = true;
        } else if (!if_finished_all_nat_check_no_later_than_today) {
            cout << "�Ե�Ƭ�̣�����������ָ���� �˹�ȷ��<���պ�����>���״̬ ... " << endl;
            cout << "����������� ..." << endl;
            _getch();
            Sleep(250);
            // TODO: daily_health_check_
            //
            const auto* nat_user_confirm_
                = new NAT_user(real_name, student_number, dorm_number, false);
            delete nat_user_confirm_;
            if_finished_all_nat_check_no_later_than_today = true;
        }
        cout << "���Ѿ� ����� ���д������" << endl;
    }
    cout << "��������ǿ����ݺ󣬻س������ɷ����ϼ��˵� >> " << endl;
    string flag;
    cin >> flag;
    // end
}

necessary_affairs_manager::necessary_affairs_manager(
    const string& account,
    const string& real_name,
    const string& student_number,
    const string& dorm_number,
    const bool& if_push_to_finish)
{
    system("cls");
    this->account = account;
    this->real_name = real_name;
    this->student_number = student_number;
    this->dorm_number = dorm_number;
    this->if_push_to_finish = if_push_to_finish;
    if_finished_daily_check = false;
    if_finished_all_nat_check_no_later_than_today = true;
    check_if_finished_daily_check();
    check_if_finished_all_nat_check();
    unfinished_tasks_management();
}
