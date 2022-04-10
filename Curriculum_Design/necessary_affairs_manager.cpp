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
        cout << "已完成 健康打卡 和 当日所有核酸检测！没有待办事项！" << endl;
        cout << "您 >>已完成了<< 所有待办事项，按下任意键后，将回到 <用户端功能菜单> ... " << endl;
        _getch();
    } else {
        cout << "待办事项有：" << endl;
        if (!if_finished_daily_check) {
            cout << "\t"
                 << "进行 <每日健康打卡> ！" << endl;
        }
        if (!if_finished_all_nat_check_no_later_than_today) {
            cout << "\t"
                 << "完成 <当日核酸检测> 人工确认 ！" << endl;
        }
    }
}

void necessary_affairs_manager::check_if_finished_daily_check()
{
    // 检查是否完成每日打卡
    // 形参顺序 => real_name, account, student_number, "flag"
    const auto* daily_health_check_checker
        = new daily_health_check_user(real_name, account, student_number, "flag");
    const bool if_unfinished_daily_check = daily_health_check_checker->plug_of_if_should_alert;
    if_finished_daily_check = !if_unfinished_daily_check;
    delete daily_health_check_checker;
}

void necessary_affairs_manager::check_if_finished_all_nat_check()
{
    // 检查是否完成当天的 所有 核酸检测
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
            cout << "按照规则，将会 先指引您完成<每日健康打卡>，在指引您人工确认<当日核酸检测>完成状态 ... " << endl;
            Sleep(250);
            cout << "稍等片刻，接下来将会指引您完成 <每日健康打卡> ... " << endl;
            Sleep(250);
            cout << "按任意键继续 ..." << endl;
            _getch();
            // daily_health_check_
            const auto* daily_health_check_
                = new daily_health_check_user(real_name, account, student_number);
            delete daily_health_check_;
            if_finished_daily_check = true;
            // TODO: nat_check_
            //
            cout << "稍等片刻，接下来将会指引您 人工确认<当日核酸检测>完成状态 ... " << endl;
            cout << "按任意键继续 ..." << endl;
            _getch();
            Sleep(250);
            const auto* nat_user_confirm_
                = new NAT_user(real_name, student_number, dorm_number, false);
            delete nat_user_confirm_;
            if_finished_all_nat_check_no_later_than_today = true;
        } else if (!if_finished_daily_check) {
            cout << "稍等片刻，接下来将会指引您完成 <每日健康打卡> ... " << endl;
            Sleep(250);
            cout << "按任意键继续 ..." << endl;
            _getch();
            // daily_health_check_
            const auto* daily_health_check_
                = new daily_health_check_user(real_name, account, student_number);
            delete daily_health_check_;
            if_finished_daily_check = true;
        } else if (!if_finished_all_nat_check_no_later_than_today) {
            cout << "稍等片刻，接下来将会指引您 人工确认<当日核酸检测>完成状态 ... " << endl;
            cout << "按任意键继续 ..." << endl;
            _getch();
            Sleep(250);
            // TODO: daily_health_check_
            //
            const auto* nat_user_confirm_
                = new NAT_user(real_name, student_number, dorm_number, false);
            delete nat_user_confirm_;
            if_finished_all_nat_check_no_later_than_today = true;
        }
        cout << "您已经 完成了 所有待办事项！" << endl;
    }
    cout << "输入任意非空内容后，回车，即可返回上级菜单 >> " << endl;
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
